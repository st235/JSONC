#include <gtest/gtest.h>

#include "json.h"

TEST(JsonBoolean, IsBoolReturnsTrue) {
    json::Json json_boolean = false;
    EXPECT_TRUE(json_boolean.isBool());
}

TEST(JsonBoolean, IfInitialisedWithTrueReturnsTrue) {
    json::Json json_boolean = true;
    EXPECT_TRUE(json_boolean.asBool());
}

TEST(JsonBoolean, IfInitialisedWithFalseReturnsFalse) {
    json::Json json_boolean = false;
    EXPECT_FALSE(json_boolean.asBool());
}

TEST(JsonBoolean, CopyModifiesNewObject) {
    json::Json initial_boolean = false;

    json::Json new_boolean = initial_boolean;
    new_boolean = true;

    EXPECT_FALSE(initial_boolean.asBool());
    EXPECT_TRUE(new_boolean.asBool());
}

TEST(JsonBoolean, UnaryOperatorReturnsTrueIfTheValueIsTrue) {
    json::Json json_boolean = true;
    EXPECT_TRUE(json_boolean);
}

TEST(JsonBoolean, UnaryOperatorReturnsFalseIfTheValueIsFalse) {
    json::Json json_boolean = false;
    EXPECT_FALSE(json_boolean);
}

TEST(JsonBoolean, DifferentBooleanValuesReturnFalseWhenCompared) {
    json::Json json_a = true;
    json::Json json_b = false;
    EXPECT_NE(json_a, json_b);
}

TEST(JsonBoolean, SameBooleanValuesReturnTrueWhenCompared) {
    json::Json json_a = true;
    json::Json json_b = true;
    EXPECT_EQ(json_a, json_b);
}
