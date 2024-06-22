#include <gtest/gtest.h>

#include "json_object.h"

TEST(JsonObject, BasicAssertions) {
  EXPECT_EQ(5, json::JsonObject::get());
}