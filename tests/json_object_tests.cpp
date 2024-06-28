#include <gtest/gtest.h>

#include <memory>
#include <unordered_set>

#include "json.h"

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
    json::Json json_object = json::Json::object();
  
    EXPECT_EQ(0, json_object.size());
}

TEST(JsonObject, JsonObjectWithElementsReturnsNonZeroSize) {
    json::Json json_object = json::Json::object();

    json_object["a"] = json::Json(true);
    json_object["b"] = json::Json(false);
    json_object["c"] = json::Json(false);
  
    EXPECT_EQ(3, json_object.size());
}

TEST(JsonObject, AddingKeyAddsItToJsonObject) {
    json::Json json_object = json::Json::object();

    json_object["a"] = json::Json(true);
    json_object["b"] = json::Json(false);

    EXPECT_EQ(json::Json(true), json_object["a"]);
    EXPECT_EQ(json::Json(false), json_object["b"]);
}
