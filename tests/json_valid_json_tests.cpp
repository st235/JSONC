#include <gtest/gtest.h>

#include <string>
#include <memory>
#include <utility>

#include "json.h"

class ValidJsonTestingFixture: public ::testing::TestWithParam<std::pair<std::string, std::string>> {};

INSTANTIATE_TEST_SUITE_P(
        ValidJsonTests,
        ValidJsonTestingFixture,
        ::testing::Values(
            // primitives
            std::make_pair("null", "null"),
            std::make_pair("true", "true"),
            std::make_pair("false", "false"),
            std::make_pair("\"hello world\"", "\"hello world\""),
            std::make_pair("\"special character: \\b \"", "\"special character: \\b \""),
            std::make_pair("\"special character: \\uAF22 \"", "\"special character: \\uAF22 \""),
            std::make_pair("\"special character: \\\\ \"", "\"special character: \\\\ \""),
            std::make_pair("0", "0"),
            std::make_pair("-1", "-1"),
            std::make_pair("122", "122"),
            std::make_pair("15", "15"),
            std::make_pair("0.55", "0.55"),
            std::make_pair("-0.27", "-0.27"),
            std::make_pair("89.11", "89.11"),
            std::make_pair("-2.7e-32", "-2.7e-32"),
            std::make_pair("-5.4e+29", "-5.4e+29"),

            // empty objects
            std::make_pair("{}", "{}"),
            std::make_pair("[]", "[]"),
            std::make_pair("[{},{},{}]", "[{},{},{}]"),

            // complex jsons
            std::make_pair("\n \t    true   \t", "true"),
            std::make_pair("[5, true]", "[5,true]"),
            std::make_pair("{  \"a\":  \"hello world!\"}", "{\"a\":\"hello world!\"}"),
            std::make_pair(
                "[{\"index\":0,\"guid\":\"bb66bf8e-ee5f-433a-9208-00db1ddec8d3\",\"isActive\":true,\"balance\":\"$3,496.62\"},{\"index\":1,\"guid\":\"97e3f427-bc92-4f44-8c42-b8e708530651\",\"isActive\":false,\"balance\":\"$1,540.04\"}]",
                "[{\"index\":0,\"guid\":\"bb66bf8e-ee5f-433a-9208-00db1ddec8d3\",\"isActive\":true,\"balance\":\"$3,496.62\"},{\"index\":1,\"guid\":\"97e3f427-bc92-4f44-8c42-b8e708530651\",\"isActive\":false,\"balance\":\"$1,540.04\"}]"
            ),
            std::make_pair(
                "[{\"a\":{\"a\":false,\"b\":19.3235},\"c\":[19,20]},{\"a\":{\"a\":false,\"b\":19.4282},\"c\":[14,15,17,14]}]",
                "[{\"a\":{\"b\":19.3235,\"a\":false},\"c\":[19,20]},{\"a\":{\"b\":19.4282,\"a\":false},\"c\":[14,15,17,14]}]"
            )
        )
);

TEST_P(ValidJsonTestingFixture, ValidJsonYieldsCorrectMinification) {
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_json = pair.second;

    const auto& opt_json_value = json::Json::fromJson(json);
    std::string minified_json = json::Json::toJson(*opt_json_value);

    EXPECT_EQ(expected_json, minified_json);
}
