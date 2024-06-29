#include <gtest/gtest.h>

#include "json.h"

TEST(JsonString, IsStringReturnsTrueWhenInitialiedWithString) {
    json::Json json = "Hello world";
    EXPECT_TRUE(json.isString());
}

TEST(JsonString, UnaryOperatorReturnsFalseIfTheStringIsEmpty) {
    json::Json json = "";
    EXPECT_FALSE(json);
}

TEST(JsonString, UnaryOperatorReturnsTrueIfStringIsNotEmpty) {
    EXPECT_TRUE(json::Json("a"));
    EXPECT_TRUE(json::Json("hello world"));
    EXPECT_TRUE(json::Json("\\"));
    EXPECT_TRUE(json::Json("some random value"));
}

TEST(JsonString, DifferentStringValuesReturnFalseWhenCompared) {
    json::Json json_a = "hello world 1";
    json::Json json_b = "hello world 2";
    EXPECT_NE(json_a, json_b);
}

TEST(JsonString, SameStringValuesReturnTrueWhenCompared) {
    json::Json json_a = "hello world 7";
    json::Json json_b = "hello world 7";
    EXPECT_EQ(json_a, json_b);
}
