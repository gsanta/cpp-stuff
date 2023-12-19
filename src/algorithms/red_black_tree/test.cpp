#include "red_black_tree.h"

#include <catch2/catch_test_macros.hpp>

SCENARIO("Red black tree")
{
  GIVEN("an empty tree")
  {
    RedBlackTree<int> tree;

    WHEN("insering elements into the tree")
    {

      tree.insert(1);
      tree.insert(5);
      tree.insert(7);

      THEN("it returns true when querying inserted elements")
      {
        REQUIRE(tree.search(1) == true);
        REQUIRE(tree.search(5) == true);
        REQUIRE(tree.search(7) == true);
      }

      THEN("it returns false when querying not inserted elements")
      {
        REQUIRE(tree.search(2) != true);
        REQUIRE(tree.search(4) != true);
        REQUIRE(tree.search(6) != true);
      }
    }

    WHEN("the tree becomes unbalanced")
    {

      THEN("it balances the tree")
      {
        tree.insert(11);
        tree.insert(2);
        tree.insert(14);
        tree.insert(1);
        tree.insert(7);
        tree.insert(15);
        tree.insert(5);
        tree.insert(8);

        // balancing needed at this point
        tree.insert(4);

        REQUIRE(tree.height() == 3);
      }
    }
  }
}
