#include "quick_sort.h"

#include <catch2/catch_test_macros.hpp>


SCENARIO("Quick sort")
{
  GIVEN("an unordered array")
  {
    int arr[] = {
        2, 8, 7, 1, 3, 5, 6, 4
    };

    WHEN("calling quick sort on the array")
    {
        THEN("the array will be sorted") {

            quick_sort(arr, 0, 7);

            REQUIRE(arr[0] == 1);
            REQUIRE(arr[1] == 2);
            REQUIRE(arr[2] == 3);
            REQUIRE(arr[3] == 4);
            REQUIRE(arr[4] == 5);
            REQUIRE(arr[5] == 6);
            REQUIRE(arr[6] == 7);
            REQUIRE(arr[7] == 8);
        }
    }
  }
}