#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "json_parser.h"
#include "json_minifier.h"

#include "json_array.h"
#include "json_boolean.h"
#include "json_number.h"
#include "json_object.h"
#include "json_string.h"
#include "json_value.h"
#include "json_null.h"

class ValidJsonTestingFixture: public ::testing::TestWithParam<std::pair<std::string, std::string>> {
protected:
    json::__internal::JsonParser parser;
};

INSTANTIATE_TEST_SUITE_P(
        ValidJsonTests,
        ValidJsonTestingFixture,
        ::testing::Values(
            std::make_pair("\n \t    true   \t", "true"),
            std::make_pair("[5, true]", "[5,true]"),
            std::make_pair("{  \"a\":  \"hello world!\"}", "{\"a\":\"hello world!\"}")
        )
);

TEST_P(ValidJsonTestingFixture, ValidJsonYieldsCorrectMinification) {
    json::JsonMinifier minifier;
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_json = pair.second;

    json::JsonValue* value = parser.parse(json);
    value->accept(&minifier);
    delete value;

    EXPECT_EQ(expected_json, minifier.minifiedJson());
}
