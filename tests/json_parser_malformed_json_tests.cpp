#include <gtest/gtest.h>

#include <string>
#include <optional>
#include <utility>

#include "json_parser.h"

#include "json.h"

class MalformedJsonTestingFixture: public ::testing::TestWithParam<std::string> {
protected:
    json::__internal::JsonParser parser;
};

INSTANTIATE_TEST_SUITE_P(
        MalformedJsonTests,
        MalformedJsonTestingFixture,
        ::testing::Values(
            // empty strings
            "",
            "\t     \n     ",
            "\r\t\n      \t\t\r\r\n\n",

            // null with typos
            "nulls",

            // booleans with typos
            "truth",
            "falso",

            // numbers with issues:
            // leading zero
            "0111",
            "025.56",
            // fraction with no digits
            "111.",
            "52.",
            // fraction with coma separator
            "5,22",
            "1,07",
            // exponent with no digits
            "1e",
            "-5e",
            "4E+",
            "1.23E",
            "-8.11e-"

            // strings with issues:
            // no brackets
            "hello world",
            // no matching closing bracket
            "\"hello world",
            "hello world\"",
            // disallowed character after control symbol
            "\"hello \\z \"",
            "\" \\a \"",
            // invalid length of hex number
            "\"\\u01A\"",
            "\"\\uF0\"",
            // invalid hex number
            "\"\\uXAF1\"",
            "\"number is \\u1Z11\""

            // arrays with issues:
            // no closing bracket
            "["
            // no value
            "[,]"
            // trailing coma
            "[5,]",
            "[true, {}, ]",

            // objects with issues:
            // no closing bracket
            "{",
            // traling coma
            "{ \"a\" : 5, }",
            "{ \"a\" : 5, \"b\": true, }",

            // complex cases:
            // multiple objects without array brackets
            "5, 2, 1, true",
            "{}, {}",
            // unknown keyword
            "{ \"a\" : hello_world }"
        )
);

TEST_P(MalformedJsonTestingFixture, MalformedJsonYieldsNull) {
    const auto& json = GetParam();
    const auto& value = parser.parse(json);
    EXPECT_EQ(std::nullopt, value);
}

TEST(JsonParser, NullYieldsValidJson) {
    json::__internal::JsonParser parser;
    const auto& opt_value = parser.parse("null");
    EXPECT_TRUE((*opt_value).isNull());
    EXPECT_EQ(json::Json::null(), *opt_value);
}

TEST(JsonParser, NullWithWhitespacesYieldsValidJson) {
    json::__internal::JsonParser parser;
    const auto& opt_value = parser.parse("\t \n    null \r \t \n");
    EXPECT_EQ(json::Json::null(), *opt_value);
}
