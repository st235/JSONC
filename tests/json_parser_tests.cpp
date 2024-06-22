#include <gtest/gtest.h>

#include "json_parser.h"
#include "json_value.h"
#include "json_null.h"

TEST(JsonParser, EmptyStringYieldsInvalidJson) {
    json::__internal::JsonParser parser;
    json::JsonValue* value = parser.parse("");

    EXPECT_EQ(nullptr, value);
}

TEST(JsonParser, WhitespacesYieldsInvalidJson) {
    json::__internal::JsonParser parser;
    json::JsonValue* value = parser.parse("   \t    \n     ");

    EXPECT_EQ(nullptr, value);
}

TEST(JsonParser, NullShouldYieldJsonNull) {
    json::__internal::JsonParser parser;
    json::JsonValue* value = parser.parse("null");

    EXPECT_EQ(json::JsonNull::VALUE, value);

    delete value;
}

TEST(JsonParser, NullWithWhitespacesShouldYieldJsonNull) {
    json::__internal::JsonParser parser;
    json::JsonValue* value = parser.parse("  \t\n\n  null      \n\n");

    EXPECT_EQ(json::JsonNull::VALUE, value);

    delete value;
}
