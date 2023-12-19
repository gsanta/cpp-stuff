//
// Created by Gergely Sánta on 2023. 05. 06..
//

#ifndef ALGORITHMS_ANIMAL_TRANSPORT_H
#define ALGORITHMS_ANIMAL_TRANSPORT_H

#include <vector>
#include "../algorithms/segmentation_tree/segmentation_tree.h"

class AnimalTransport
{
public:
    AnimalTransport(std::vector<std::vector<int>> catSourceByDest, std::vector<std::vector<int>> dogSourceByDest);
    AnimalTransport(int, int, std::vector<char>, std::vector<int>, std::vector<int>);

    std::vector<int> transport();

private:
    using SourceByDest = std::vector<std::vector<int>>;
    void update(const SourceByDest &sourceByDest, SegmentationTree<unsigned int> &current, SegmentationTree<unsigned int> &other, int currentZoo);

private:
    SourceByDest m_DogSourceByDest;
    SourceByDest m_CatSourceByDest;
    SegmentationTree<unsigned int> m_DogMaxCount;
    SegmentationTree<unsigned int> m_CatMaxCount;
    int m_ZooCount;
    int m_AnimalsToTransport;
};

#endif // ALGORITHMS_ANIMAL_TRANSPORT_H
