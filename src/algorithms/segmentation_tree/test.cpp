#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "segmentation_tree.h"

unsigned int aggregate(unsigned int leftVal, unsigned int rightVal)
{
    return leftVal + rightVal;
}

TEST_CASE("SegmentationTree", "[segmentation-tree]")
{

    SECTION("can aggregate a range test 1")
    {

        std::vector<int> elements = {3, 4, 10, 2, 7};

        SegmentationTree<unsigned int> seg(elements, [](unsigned int leftVal, unsigned int rightVal)
                                           { return leftVal + rightVal; });
        REQUIRE(seg.query(0, 4) == 26);
        REQUIRE(seg.query(0, 2) == 17);
        REQUIRE(seg.query(3, 4) == 9);
    }

    SECTION("can update a node")
    {
        std::vector<int> elements = {3, 4, 10, 2, 7};

        SegmentationTree seg(elements, aggregate);
        seg.update(1, 2);
        REQUIRE(seg.query(0, 2) == 15);
    }
}
