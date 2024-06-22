#include <gtest/gtest.h>

#include "json_boolean.h"

TEST(JsonBoolean, IsBooleanReturnsTrue) {
    json::JsonBoolean jsonBoolean(false);
    EXPECT_TRUE(jsonBoolean.isBoolean());
}

TEST(JsonBoolean, IfInitialisedWithTrueReturnsTrue) {
    json::JsonBoolean jsonBoolean(true);
    EXPECT_TRUE(jsonBoolean.value());
}

TEST(JsonBoolean, IfInitialisedWithFalseReturnsFalse) {
    json::JsonBoolean jsonBoolean(false);
    EXPECT_FALSE(jsonBoolean.value());
}
