#pragma once

#include <vector>
#include <cmath>

template<typename T>
class SegmentationTree {

public:
    using aggregation = T (*)(T left, T right);

    explicit SegmentationTree(std::vector<int> elements, aggregation);
    explicit SegmentationTree();

    int query(T left, T right);

    void update(T index, int newValue);

private:
    void initTree();

    void propagate(T left, T right, T index);

    int queryRecurse(T queryLeft, T queryRight, T rangeLeft, T rangeRight, T nodeIndex);

private:
    std::vector<int> m_Elements;

    std::vector<int> m_SegTree;

    aggregation m_Aggregation;

    T m_Height;

    T m_Size;

    T m_Nodes;
};

template<typename T>
SegmentationTree<T>::SegmentationTree(std::vector<int> elements, aggregation aggregate) : m_Elements(elements),
                                                                                       m_Aggregation(aggregate) {
    initTree();
}

template<typename T>
SegmentationTree<T>::SegmentationTree() {}

template<typename T>
void SegmentationTree<T>::initTree() {
    m_Size = m_Elements.size();

    m_Height = std::ceil(std::log2(m_Size)) + 1;

    m_Nodes = std::pow(2, m_Height) - 1;

    m_SegTree.resize(m_Nodes);

    propagate(0, m_Size - 1, 0);
}

template<typename T>
void SegmentationTree<T>::propagate(T left, T right, T index) {
    if (right < left) {
        return;
    }

    if (left == right) {
        m_SegTree[index] = m_Elements[left];
        return;
    }

    T midPoint = (left + right) / 2;

    T leftSegNodeIndex = index * 2 + 1;
    T leftSegNodeLeft = left;
    T leftSegNodeRight = midPoint;
    propagate(leftSegNodeLeft, leftSegNodeRight, leftSegNodeIndex);

    T rightSegNodeIndex = index * 2 + 2;
    T rightSegNodeLeft = midPoint + 1;
    T rightSegNodeRight = right;
    propagate(rightSegNodeLeft, rightSegNodeRight, rightSegNodeIndex);

    T leftMax = m_SegTree[leftSegNodeIndex];
    T rightMax = m_SegTree[rightSegNodeIndex];
    m_SegTree[index] = m_Aggregation(leftMax, rightMax);
}

template<typename T>
int SegmentationTree<T>::query(T left, T right) {
    return queryRecurse(left, right, 0, m_Size - 1, 0);
}

template<typename T>
int SegmentationTree<T>::queryRecurse(T queryLeft, T queryRight,
                                   T rangeLeft, T rangeRight,
                                   T nodeIndex) {
    if (rangeLeft > rangeRight) {
        return 0;
    }

    if (queryRight < rangeLeft || queryLeft > rangeRight) {
        return 0;
    }

    if (queryLeft <= rangeLeft && queryRight >= rangeRight) {
        return m_SegTree[nodeIndex];
    }

    T midPoint = (rangeLeft + rangeRight) / 2;

    T leftSegNodeIndex = nodeIndex * 2 + 1;
    T leftSegNodeLeft = rangeLeft;
    T leftSegNodeRight = midPoint;
    int leftResult = queryRecurse(queryLeft, queryRight, leftSegNodeLeft, leftSegNodeRight, leftSegNodeIndex);

    T rightSegNodeIndex = nodeIndex * 2 + 2;
    T rightSegNodeLeft = midPoint + 1;
    T rightSegNodeRight = rangeRight;
    int rightResult = queryRecurse(queryLeft, queryRight, rightSegNodeLeft, rightSegNodeRight, rightSegNodeIndex);

    return m_Aggregation(leftResult, rightResult);
}

template<typename T>
void SegmentationTree<T>::update(T index, int newValue) {
    m_Elements[index] = newValue;
    propagate(0, m_Size - 1, 0);
}
