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
