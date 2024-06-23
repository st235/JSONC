#include <gtest/gtest.h>

#include <string>
#include <memory>
#include <utility>

#include "json_beautifier.h"

#include "json.h"
#include "json_value.h"

class BeautifyJsonTestingFixture: public ::testing::TestWithParam<std::pair<std::string, std::string>> {};

INSTANTIATE_TEST_SUITE_P(
        BeautifyJsonTests,
        BeautifyJsonTestingFixture,
        ::testing::Values(
            std::make_pair("{}", "{\n}"),
            std::make_pair("[]", "[\n]"),
            std::make_pair("[true, 1, 5]", "[\n\ttrue,\n\t1,\n\t5\n]"),
            std::make_pair("[true, 1, 5, [8, false] ]", "[\n\ttrue,\n\t1,\n\t5,\n\t[\n\t\t8,\n\t\tfalse\n\t]\n]"),
            std::make_pair("[  {\"a\":   { \t\t \"b\"    : 5 } } ]", "[\n\t{\n\t\t\"a\": {\n\t\t\t\"b\": 5\n\t\t}\n\t}\n]"),
            std::make_pair("[  {\"a\":   12}, {\"b\": \"Hello world\"}  ]", "[\n\t{\n\t\t\"a\": 12\n\t},\n\t{\n\t\t\"b\": \"Hello world\"\n\t}\n]")
        )
);

TEST_P(BeautifyJsonTestingFixture, ValidJsonYieldsBeautifiedString) {
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_json = pair.second;

    json::JsonBeautifier beautifier;
    std::unique_ptr<json::JsonValue> json_value = json::FromJson(json);
    std::string beautified_json = beautifier.beautify(json_value.get());

    EXPECT_EQ(expected_json, beautified_json);
}
