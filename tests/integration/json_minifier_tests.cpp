#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "json.h"
#include "json_minifier.h"
#include "test_utils.h"

using ::test_utils::TestData;
using ::test_utils::PrepareTestData;
using ::testing::AnyOfArray;

class MinifyJsonTestingFixture: public ::testing::TestWithParam<TestData<std::string>> {
  protected:
    json::JsonMinifier minifier;
};

INSTANTIATE_TEST_SUITE_P(
        MinifyJsonTests,
        MinifyJsonTestingFixture,
        ::testing::Values(
            // Basics.
            PrepareTestData<std::string>("null", { "null" }),
            PrepareTestData<std::string>("true", { "true" }),
            PrepareTestData<std::string>("false", { "false" }),
            PrepareTestData<std::string>("1", { "1" }),
            PrepareTestData<std::string>(R"("Hello World")", { R"("Hello World")" }),

            PrepareTestData<std::string>("{}", { "{}" }),
            PrepareTestData<std::string>("[]", { "[]" }),

            // Basics with extra spaces.
            PrepareTestData<std::string>("    null   ", { "null" }),
            PrepareTestData<std::string>("true \t \t    \n", { "true" }),
            PrepareTestData<std::string>("\r \r \t false", { "false" }),
            PrepareTestData<std::string>("   1     ", { "1" }),
            PrepareTestData<std::string>(R"(     "Hello World" )", { R"("Hello World")" }),

            PrepareTestData<std::string>("\n\t{\t\t\t\t}\n\n\n\n", { "{}" }),
            PrepareTestData<std::string>("\r\t\t\n[\n\n\n\n]\t\t\t\t", { "[]" }),

            // Arrays.
            PrepareTestData<std::string>("[true, 1,     5 \n]", { "[true,1,5]" }),
            PrepareTestData<std::string>("[true,\t -1,\n\t 5, [8, \t false] ]", { "[true,-1,5,[8,false]]" }),
            PrepareTestData<std::string>("[true,\t -1,\n\t 5, [8, null\t, [\n \n \"hello world\", 8.3], true \n] ]", { R"([true,-1,5,[8,null,["hello world",8.3],true]])" }),

            // Objects.
            PrepareTestData<std::string>(R"({   "b":   [ 1, true, null, ["b"   ]] })", { R"({"b":[1,true,null,["b"]]})" }),
            PrepareTestData<std::string>(
                R"({   "b":   [ 1, true, null, ["b"   ]]  , "c": "a" })",
                {
                    R"({"b":[1,true,null,["b"]],"c":"a"})",
                    R"({"c":"a","b":[1,true,null,["b"]]})"
                }
            )
        )
);

TEST_P(MinifyJsonTestingFixture, ValidJsonYieldsBeautifiedString) {
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_jsons = pair.second;

    const auto& json_value = json::Json::fromJson(json);
    const auto& beautified_json = minifier.minify(*json_value);
    EXPECT_THAT(beautified_json, AnyOfArray(expected_jsons));
}
