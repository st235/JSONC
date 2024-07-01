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

TEST(JsonObject, IsObjectReturnsTrueWhenInitilizedThroughFactoryMethod) {
    json::Json json = json::Json::object();
    EXPECT_TRUE(json.isObject());
}

TEST(JsonObject, IsObjectReturnsTrueIfInitializedFromInitializerList) {
    json::Json json({ std::make_pair("Hello world", json::Json(true)) });
    EXPECT_TRUE(json.isObject());
}

TEST(JsonObject, EmptyJsonObjectHasSizeZero) {
    json::Json json = json::Json::object();
    EXPECT_EQ(0, json.size());
}

TEST(JsonObject, InitialisingObjectWithElementsYieldsRightSize) {
    json::Json json{ 
      std::make_pair("Hello world", json::Json(true)),
      std::make_pair("A", json::Json(5.0))
     };

    EXPECT_TRUE(json.isObject());
    EXPECT_EQ(2, json.size());
}

TEST(JsonObject, UnaryOperatorReturnsFalseIfObjectIsEmpty) {
    json::Json json = json::Json::object();
    EXPECT_FALSE(json);
}

TEST(JsonObject, UnaryOperatorReturnsTrueIfObjectIsNotEmpty) {
    EXPECT_TRUE(json::Json({ std::make_pair("A", json::Json(5.0)) }));
    EXPECT_TRUE(json::Json({ std::make_pair("B", json::Json(true)), std::make_pair("A", json::Json("Hello")) }));
}

TEST(JsonObject, ObjectsWithDifferentValuesYeildFalseWhenCompared) {
    json::Json json_a{ std::make_pair("Hello world", json::Json(true)) };
    json::Json json_b{ std::make_pair("Hello world", json::Json(false)) };
    EXPECT_NE(json_a, json_b);
}

TEST(JsonObject, ObjectsWithDifferentKeysYeildFalseWhenCompared) {
    json::Json json_a{ std::make_pair("A", json::Json(true)) };
    json::Json json_b{ std::make_pair("B", json::Json(true)) };
    EXPECT_NE(json_a, json_b);
}

TEST(JsonObject, SameObjectsYieldTrueWhenCompared) {
    json::Json json_a{ std::make_pair("A", json::Json(12.1)) };
    json::Json json_b{ std::make_pair("A", json::Json(12.1)) };
    EXPECT_EQ(json_a, json_b);
}

TEST(JsonObject, Adding3ElementsYieldsSize3) {
    json::Json json_object = json::Json::object();

    json_object["a"] = json::Json(true);
    json_object["b"] = json::Json(false);
    json_object["c"] = json::Json("Hello world");
  
    EXPECT_EQ(3, json_object.size());
}

TEST(JsonObject, AddingKeyModifiesTheObject) {
    json::Json json_object = json::Json::object();

    json_object["a"] = json::Json(true);
    json_object["b"] = json::Json(-1.1);
    json_object["c"] = json::Json("Hello world");

    EXPECT_EQ(json::Json(true), json_object["a"]);
    EXPECT_EQ(json::Json(-1.1), json_object["b"]);
    EXPECT_EQ(json::Json("Hello world"), json_object["c"]);
}
