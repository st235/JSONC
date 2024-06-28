#include <gtest/gtest.h>

#include "json.h"

TEST(JsonNull, JsonNullFactoryReturnsNull) {
    const auto& json_null = json::Json::null();
    EXPECT_TRUE(json_null.isNull());
}

TEST(JsonNull, JsonNullReturnsIsNull) {
    json::Json json_null;
    EXPECT_TRUE(json_null.isNull());
}

