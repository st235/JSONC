#include <gtest/gtest.h>

#include <memory>
#include <unordered_set>

#include "json_object.h"
#include "json_boolean.h"

namespace {

template <typename T>
bool IsEqualSets(const std::unordered_set<T>& one, const std::unordered_set<T>& another) {
  if (one.size() != another.size()) {
    return false;
  }

  for (const auto& item: one) {
    if (another.find(item) == another.end()) {
      return false;
    }
  }

  return true;
}

} // namespace

TEST(JsonObject, EmptyJsonObjectHasSizeZero) {
    json::JsonObject json_object;
  
    EXPECT_EQ(0, json_object.size());
}

TEST(JsonObject, JsonObjectWithElementsReturnsNonZeroSize) {
    json::JsonObject json_object;

    json_object["a"] = new json::JsonBoolean(true);
    json_object["b"] = new json::JsonBoolean(false);
    json_object["c"] = new json::JsonBoolean(false);
  
    EXPECT_EQ(3, json_object.size());
}

TEST(JsonObject, AddingKeyAddsItToJsonObject) {
    json::JsonObject json_object;

    json_object["a"] = new json::JsonBoolean(true);
    json_object["b"] = new json::JsonBoolean(false);

    EXPECT_EQ(json::JsonBoolean(true), *(json_object["a"]));
    EXPECT_EQ(json::JsonBoolean(false), *(json_object["b"]));
}
