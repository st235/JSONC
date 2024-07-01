#include <gtest/gtest.h>

#include "json.h"

TEST(JsonNumber, IsNumberReturnsTrue) {
    json::Json json_number = 0.0;
    EXPECT_TRUE(json_number.isNumber());
}

TEST(JsonNumber, UnaryOperatorReturnsFalseIfTheValueIs0) {
    json::Json json_number = 0.0;
    EXPECT_FALSE(json_number);
}

TEST(JsonNumber, UnaryOperatorReturnsTrueIfTheValueIsNot0) {
    EXPECT_TRUE(json::Json(0.1));
    EXPECT_TRUE(json::Json(10.5));
    EXPECT_TRUE(json::Json(-0.1));
    EXPECT_TRUE(json::Json(5.0));
}

TEST(JsonNumber, DifferentNumberValuesReturnFalseWhenCompared) {
    json::Json json_a = 1.0;
    json::Json json_b = 1.1;
    EXPECT_NE(json_a, json_b);
}

TEST(JsonNumber, SameNumberValuesReturnTrueWhenCompared) {
    json::Json json_a = 17.1;
    json::Json json_b = 17.1;
    EXPECT_EQ(json_a, json_b);
}