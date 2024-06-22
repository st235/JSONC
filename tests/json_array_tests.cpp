#include <gtest/gtest.h>

#include "json_array.h"
#include "json_number.h"

TEST(JsonArray, EmptyArrayHasSizeOfZero) {
    json::JsonArray array;
    EXPECT_EQ(0, array.size());
}

TEST(JsonArray, InitialisingArrayWithElementsYieldsRightSize) {
    json::JsonNumber expected(0.0);
    json::JsonArray array({ new json::JsonNumber(0.0) });

    EXPECT_EQ(1, array.size());
    EXPECT_EQ(expected, *array.get(0));
}
