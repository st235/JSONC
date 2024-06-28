#include <gtest/gtest.h>

#include "json.h"

TEST(JsonArray, EmptyArrayHasSizeOfZero) {
    json::Json array = json::Json::array();

    EXPECT_TRUE(array.isArray());
    EXPECT_EQ(0, array.size());
}

TEST(JsonArray, InitialisingArrayWithElementsYieldsRightSize) {
    json::Json array({ json::Json(0.0), json::Json(1.0), json::Json(2.0) });

    EXPECT_TRUE(array.isArray());
    EXPECT_EQ(3, array.size());

    EXPECT_EQ(json::Json(0.0), array[(size_t)0]);
    EXPECT_EQ(json::Json(1.0), array[(size_t)1]);
    EXPECT_EQ(json::Json(2.0), array[(size_t)2]);
}
