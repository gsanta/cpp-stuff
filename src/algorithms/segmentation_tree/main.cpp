#include "segmentation_tree.h"
#include <vector>
#include <iostream>

int main()
{

  std::cout << "ALGORITHM: Segmentation tree: " << std::endl;
  std::cout << "-------------------------------" << std::endl;

  std::vector<int> elements = {3, 4, 10, 2, 7};

  SegmentationTree<unsigned int> seg(elements, [](unsigned int leftVal, unsigned int rightVal)
                                     { return leftVal + rightVal; });

  seg.query(0, 4);
}
