#include "animal_transport.h"

unsigned int maxAggregate(unsigned int leftVal, unsigned int rightVal) {
    return leftVal > rightVal ? leftVal : rightVal;
}

AnimalTransport::AnimalTransport(int zooNum, int animalsToTransport, std::vector<char> animal, std::vector<int> source, std::vector<int> dest): m_ZooCount(zooNum), m_AnimalsToTransport(animalsToTransport) {
    std::vector<std::vector<int>> catSourceByDest(zooNum + 1);
    std::vector<std::vector<int>> dogSourceByDest(zooNum + 1);

    for (int i = 0; i < animal.size(); i++) {
        if (source[i] < dest[i]) {
            if (animal[i] == 'c' || animal[i] == 'C' || animal[i] == 'e' || animal[i] == 'E') {
                catSourceByDest[dest[i]].push_back(source[i]);
            } else {
                dogSourceByDest[dest[i]].push_back(source[i]);
            }
        }
    }

    m_CatSourceByDest = catSourceByDest;
    m_DogSourceByDest = dogSourceByDest;

    m_DogMaxCount = SegmentationTree<unsigned int>(std::vector(zooNum + 1, 0), maxAggregate);
    m_CatMaxCount = SegmentationTree<unsigned int>(std::vector(zooNum + 1, 0), maxAggregate);
}

std::vector<int> AnimalTransport::transport() {
    int currentMax = 0;

    std::vector<int> result(m_AnimalsToTransport, -1);

    for (int i = 1; i < m_ZooCount + 1; i++) {
        update(m_CatSourceByDest, m_CatMaxCount, m_DogMaxCount, i);
        update(m_DogSourceByDest, m_DogMaxCount, m_CatMaxCount, i);

        int dogMax = m_DogMaxCount.query(1, i);

        for (int j = currentMax + 1; j <= dogMax; j++) {
            result[j - 1] = i;
        }

        currentMax = dogMax;

        if (currentMax >= m_AnimalsToTransport) {
            break;
        }
    }

    return result;
}

void
AnimalTransport::update(const SourceByDest &sourceByDest, SegmentationTree<unsigned int> &current, SegmentationTree<unsigned int> &other, int currentZoo) {
    for (int source : sourceByDest[currentZoo]) {
        for (int j = 1; j <= source; j++) {
            int curr = current.query(j, j);
            current.update(j, curr + 1);
        }
    }

    int currentMax = current.query(1, currentZoo);
    int otherMax = other.query(1, currentZoo);
    other.update(currentZoo, currentMax > otherMax ? currentMax : otherMax);
}
