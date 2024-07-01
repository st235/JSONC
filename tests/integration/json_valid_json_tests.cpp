#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <memory>
#include <utility>
#include <vector>

#include "json.h"

using ::testing::AnyOfArray;

namespace {

// Expected value is a vector of strings as JSON specification
// does not provide any gurantees on how keys are ordered within a
// JSON Object, therefore we provide all permutations of keys and
// expect that one of them matches.
using TestsData = std::pair<std::string, std::vector<std::string>>;

TestsData PrepareTestsData(const std::string& actual,
                           const std::vector<std::string>& expected) {
    return std::make_pair(actual, expected);
}

} // namespace

class ValidJsonTestingFixture: public ::testing::TestWithParam<TestsData> {};

INSTANTIATE_TEST_SUITE_P(
        ValidJsonTests,
        ValidJsonTestingFixture,
        ::testing::Values(
            // Primitives.
            PrepareTestsData("null", { "null" }),
            PrepareTestsData("true", { "true" }),
            PrepareTestsData("false", { "false" }),
            PrepareTestsData(R"("hello world")", { R"("hello world")" }),
            PrepareTestsData(R"("special character: \b ")", { R"("special character: \b ")" }),
            PrepareTestsData(R"("special character: \uAF22 ")", { R"("special character: \uAF22 ")" }),
            PrepareTestsData(R"("special character: \\ ")", { R"("special character: \\ ")" }),
            PrepareTestsData("0", { "0" }),
            PrepareTestsData("-1", { "-1" }),
            PrepareTestsData("122", { "122" }),
            PrepareTestsData("15", { "15" }),
            PrepareTestsData("0.55", { "0.55" }),
            PrepareTestsData("-0.27", { "-0.27" }),
            PrepareTestsData("89.11", { "89.11" }),
            PrepareTestsData("-2.7e-32", { "-2.7e-32" }),
            PrepareTestsData("-5.4e+29", { "-5.4e+29" }),

            // Whitespaces.
            PrepareTestsData("\t \t    \n \n    null \t \t \n\n\n\n", { "null" }),
            PrepareTestsData("\n \t \t \n    false     ", { "false" }),

            // Empty objects.
            PrepareTestsData("{}", { "{}" }),
            PrepareTestsData("[]", { "[]" }),
            PrepareTestsData("[{},{},{}]", { "[{},{},{}]" }),
            PrepareTestsData("[\n\n\t\t\n         \n ]", { "[]" }),
            PrepareTestsData("{\n    \t\t\r\n         \n }", { "{}" }),

            // Arrays.
            // Keys separated with whitespaces are fine.
            PrepareTestsData("[1, null \t ,   \t \n \"a\", true   \t, \"c\" \n\n\n \t]", { "[1,null,\"a\",true,\"c\"]" }),

            // Check that ordering is preserved.
            PrepareTestsData("[1, 3, 6, true]", { "[1,3,6,true]" }),
            PrepareTestsData(R"(["a",  false, 5.6, "b"])", { R"(["a",false,5.6,"b"])" }),

            // Compound arrays.
            PrepareTestsData(R"(["a", [1, 2, 7, 9],"c", "hello"])", { R"(["a",[1,2,7,9],"c","hello"])" }),
            PrepareTestsData(R"([[true, true, false], [1, 2, 3], "c", ["a", "b", "c"]])", { R"([[true,true,false],[1,2,3],"c",["a","b","c"]])" }),

            // Objects.
            // Whitespaces between keys and values are fine.
            PrepareTestsData("{\"a\"    :    \t\n 5   \n}", { "{\"a\":5}" }),
            // Keys separated with whitespaces are fine.
            PrepareTestsData("{\"a\":5, \t\n    \"b\": true}", { "{\"a\":5,\"b\":true}", "{\"b\":true,\"a\":5}" }),

            // Compound objects.
            PrepareTestsData("\n \t    true   \t", { "true" }),
            PrepareTestsData("[5, true]", { "[5,true]" }),
            PrepareTestsData(R"({  "a":  "hello world!"})", { R"({"a":"hello world!"})" }),
            PrepareTestsData(
                R"([{"a":{"a":false,"b":19.3235},"c":[19,20]},{"c":[14,15,17,14]}])",
                {
                    R"([{"a":{"a":false,"b":19.3235},"c":[19,20]},{"c":[14,15,17,14]}])",
                    R"([{"a":{"b":19.3235,"a":false},"c":[19,20]},{"c":[14,15,17,14]}])",
                    R"([{"a":{"a":false,"b":19.3235},"c":[19,20]},{"c":[14,15,17,14]}])",
                    R"([{"a":{"b":19.3235,"a":false},"c":[19,20]},{"c":[14,15,17,14]}])",
                    R"([{"c":[19,20],"a":{"a":false,"b":19.3235}},{"c":[14,15,17,14]}])",
                    R"([{"c":[19,20],"a":{"b":19.3235,"a":false}},{"c":[14,15,17,14]}])",
                    R"([{"c":[19,20],"a":{"a":false,"b":19.3235}},{"c":[14,15,17,14]}])",
                    R"([{"c":[19,20],"a":{"b":19.3235,"a":false}},{"c":[14,15,17,14]}])"
                }
            ),
            PrepareTestsData(
                R"([ { "a": { "a": ["hello" , 5, true], "c": ["a"] }, "c": [19, 20] }, { "b": null } ])",
                {
                    R"([{"a":{"a":["hello",5,true],"c":["a"]},"c":[19,20]},{"b":null}])",
                    R"([{"a":{"c":["a"],"a":["hello",5,true]},"c":[19,20]},{"b":null}])",
                    R"([{"c":[19,20],"a":{"a":["hello",5,true],"c":["a"]}},{"b":null}])",
                    R"([{"c":[19,20],"a":{"c":["a"],"a":["hello",5,true]}},{"b":null}])"
                }
            ),
            PrepareTestsData(
                R"([{"index":0,"isActive":true,"balance":"$3,496.62"}])",
                {
                    R"([{"index":0,"isActive":true,"balance":"$3,496.62"}])",
                    R"([{"index":0,"balance":"$3,496.62","isActive":true}])",
                    R"([{"isActive":true,"index":0,"balance":"$3,496.62"}])",
                    R"([{"isActive":true,"balance":"$3,496.62","index":0}])",
                    R"([{"balance":"$3,496.62","index":0,"isActive":true}])",
                    R"([{"balance":"$3,496.62","isActive":true,"index":0}])"
                }
            ),
            PrepareTestsData(
                R"([{"a":0},{"a":1,"b":true},{"a":2,"b":"hello world","c":[1,2,3]}])",
                {
                    R"([{"a":0},{"a":1,"b":true},{"a":2,"b":"hello world","c":[1,2,3]}])",
                    R"([{"a":0},{"a":1,"b":true},{"a":2,"c":[1,2,3],"b":"hello world"}])",
                    R"([{"a":0},{"a":1,"b":true},{"b":"hello world","a":2,"c":[1,2,3]}])",
                    R"([{"a":0},{"a":1,"b":true},{"b":"hello world","c":[1,2,3],"a":2}])",
                    R"([{"a":0},{"a":1,"b":true},{"c":[1,2,3],"a":2,"b":"hello world"}])",
                    R"([{"a":0},{"a":1,"b":true},{"c":[1,2,3],"b":"hello world","a":2}])",
                    R"([{"a":0},{"b":true,"a":1},{"a":2,"b":"hello world","c":[1,2,3]}])",
                    R"([{"a":0},{"b":true,"a":1},{"a":2,"c":[1,2,3],"b":"hello world"}])",
                    R"([{"a":0},{"b":true,"a":1},{"b":"hello world","a":2,"c":[1,2,3]}])",
                    R"([{"a":0},{"b":true,"a":1},{"b":"hello world","c":[1,2,3],"a":2}])",
                    R"([{"a":0},{"b":true,"a":1},{"c":[1,2,3],"a":2,"b":"hello world"}])",
                    R"([{"a":0},{"b":true,"a":1},{"c":[1,2,3],"b":"hello world","a":2}])",
                }
            )
        )
);

TEST_P(ValidJsonTestingFixture, ValidJsonYieldsCorrectMinification) {
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_jsons = pair.second;

    const auto& opt_json_value = json::Json::fromJson(json);
    EXPECT_TRUE(opt_json_value);

    std::string minified_json = json::Json::toJson(*opt_json_value);
    EXPECT_THAT(minified_json, AnyOfArray(expected_jsons));
}
