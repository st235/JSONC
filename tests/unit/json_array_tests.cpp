#include <gtest/gtest.h>

#include "json.h"

TEST(JsonArray, IsArrayReturnsTrueIfInitializedAsArray) {
    json::Json array = json::Json::array();
    EXPECT_TRUE(array.isArray());
}

TEST(JsonArray, IsArrayReturnsTrueIfInitializedFromInitializerList) {
    json::Json array({ json::Json(true) });
    EXPECT_TRUE(array.isArray());
}

TEST(JsonArray, EmptyArrayReturnsSize0) {
    json::Json array = json::Json::array();

    EXPECT_TRUE(array.isArray());
    EXPECT_EQ(0, array.size());
}

TEST(JsonArray, InitialisingArrayWithElementsYieldsRightSize) {
    json::Json array{ json::Json(0.0), json::Json(1.0), json::Json(2.0) };

    EXPECT_TRUE(array.isArray());
    EXPECT_EQ(3, array.size());
}

TEST(JsonArray, UnaryOperatorReturnsFalseIfArrayIsEmpty) {
    json::Json json = json::Json::array();
    EXPECT_FALSE(json);
}

TEST(JsonArray, UnaryOperatorReturnsTrueIfArrayIsNotEmpty) {
    EXPECT_TRUE(json::Json({ json::Json(true) }));
    EXPECT_TRUE(json::Json({ json::Json(25.0) }));
    EXPECT_TRUE(json::Json({ json::Json("String"), json::Json(false) }));
}

TEST(JsonArray, DifferentArraysYeildFalseWhenCompared) {
    json::Json json_a{ json::Json(true), json::Json(5.7) };
    json::Json json_b{ json::Json(false), json::Json(12.0) };
    EXPECT_NE(json_a, json_b);
}

TEST(JsonArray, SameArraysYieldTrueWhenCompared) {
    json::Json json_a{ json::Json(5.0), json::Json("a") };
    json::Json json_b{ json::Json(5.0), json::Json("a") };
    EXPECT_EQ(json_a, json_b);
}

TEST(JsonArray, ArraysWithDifferentOrdersOfElementsAreNotEqual) {
    json::Json json_a{ json::Json(5.0), json::Json("a") };
    json::Json json_b{ json::Json("a"), json::Json(5.0) };
    EXPECT_NE(json_a, json_b);
}

TEST(JsonArray, AccessOperatorReturnsRightJson) {
    json::Json array{ json::Json(0.0), json::Json("Hello world"), json::Json(true) };

    EXPECT_EQ(json::Json(0.0), array[0]);
    EXPECT_EQ(json::Json("Hello world"), array[1]);
    EXPECT_EQ(json::Json(true), array[2]);
}

TEST(JsonArray, AddActuallyAddsElementToArray) {
    json::Json array = json::Json::array();

    EXPECT_TRUE(array.isArray());
    EXPECT_EQ(0, array.size());

    array.add(json::Json(5.0));

    EXPECT_EQ(1, array.size());
    EXPECT_EQ(json::Json(5.0), array[0]);

    array.add(json::Json(true));

    EXPECT_EQ(2, array.size());
    EXPECT_EQ(json::Json(true), array[1]);
}
