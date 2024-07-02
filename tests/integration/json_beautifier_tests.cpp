#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "json.h"
#include "json_beautifier.h"
#include "test_utils.h"

using ::test_utils::TestData;
using ::test_utils::PrepareTestData;
using ::testing::AnyOfArray;

class BeautifyJsonTestingFixture: public ::testing::TestWithParam<TestData<std::string>> {
  protected:
    json::JsonBeautifier beautifier;
};

INSTANTIATE_TEST_SUITE_P(
        BeautifyJsonTests,
        BeautifyJsonTestingFixture,
        ::testing::Values(
            // Basics.
            PrepareTestData<std::string>("null", { "null" }),
            PrepareTestData<std::string>("true", { "true" }),
            PrepareTestData<std::string>("false", { "false" }),
            PrepareTestData<std::string>("1", { "1" }),
            PrepareTestData<std::string>(R"("Hello World")", { R"("Hello World")" }),

            PrepareTestData<std::string>("{}", { "{\n}" }),
            PrepareTestData<std::string>("[]", { "[\n]" }),

            // Compound objects.
            PrepareTestData<std::string>("[true, 1, 5]", { "[\n\ttrue,\n\t1,\n\t5\n]" }),
            PrepareTestData<std::string>("[true, 1, 5, [8, false] ]", { "[\n\ttrue,\n\t1,\n\t5,\n\t[\n\t\t8,\n\t\tfalse\n\t]\n]" }),
            PrepareTestData<std::string>("[  {\"a\":   { \t\t \"b\"    : 5 } } ]", { "[\n\t{\n\t\t\"a\": {\n\t\t\t\"b\": 5\n\t\t}\n\t}\n]" }),
            PrepareTestData<std::string>("[  {\"a\":   12}, {\"b\": \"Hello world\"}  ]", { "[\n\t{\n\t\t\"a\": 12\n\t},\n\t{\n\t\t\"b\": \"Hello world\"\n\t}\n]" }),
            PrepareTestData<std::string>(R"({ "a": ["hello"], "b": true })", {
                "{\n\t\"a\": [\n\t\t\"hello\"\n\t],\n\t\"b\": true\n}",
                "{\n\t\"b\": true,\n\t\"a\": [\n\t\t\"hello\"\n\t]\n}"
            })
        )
);

TEST_P(BeautifyJsonTestingFixture, ValidJsonYieldsBeautifiedString) {
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_jsons = pair.second;

    const auto& json_value = json::Json::fromJson(json);
    const auto& beautified_json = beautifier.beautify(*json_value);
    EXPECT_THAT(beautified_json, AnyOfArray(expected_jsons));
}
