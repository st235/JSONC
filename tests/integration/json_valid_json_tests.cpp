#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#include "json.h"
#include "test_utils.h"

using ::test_utils::TestData;
using ::test_utils::PrepareTestData;
using ::testing::AnyOfArray;

class ValidJsonTestingFixture: public ::testing::TestWithParam<TestData<std::string>> {};

INSTANTIATE_TEST_SUITE_P(
        ValidJsonTests,
        ValidJsonTestingFixture,
        ::testing::Values(
            // Primitives.
            PrepareTestData<std::string>("null", { "null" }),
            PrepareTestData<std::string>("true", { "true" }),
            PrepareTestData<std::string>("false", { "false" }),
            PrepareTestData<std::string>(R"("hello world")", { R"("hello world")" }),
            PrepareTestData<std::string>(R"("special character: \b ")", { R"("special character: \b ")" }),
            PrepareTestData<std::string>(R"("special character: \uAF22 ")", { R"("special character: \uAF22 ")" }),
            PrepareTestData<std::string>(R"("special character: \\ ")", { R"("special character: \\ ")" }),
            PrepareTestData<std::string>("0", { "0" }),
            PrepareTestData<std::string>("-1", { "-1" }),
            PrepareTestData<std::string>("122", { "122" }),
            PrepareTestData<std::string>("15", { "15" }),
            PrepareTestData<std::string>("0.55", { "0.55" }),
            PrepareTestData<std::string>("-0.27", { "-0.27" }),
            PrepareTestData<std::string>("89.11", { "89.11" }),
            PrepareTestData<std::string>("-2.7e-32", { "-2.7e-32" }),
            PrepareTestData<std::string>("-5.4e+29", { "-5.4e+29" }),

            // Whitespaces.
            PrepareTestData<std::string>("\t \t    \n \n    null \t \t \n\n\n\n", { "null" }),
            PrepareTestData<std::string>("\n \t \t \n    false     ", { "false" }),

            // Empty objects.
            PrepareTestData<std::string>("{}", { "{}" }),
            PrepareTestData<std::string>("[]", { "[]" }),
            PrepareTestData<std::string>("[{},{},{}]", { "[{},{},{}]" }),
            PrepareTestData<std::string>("[\n\n\t\t\n         \n ]", { "[]" }),
            PrepareTestData<std::string>("{\n    \t\t\r\n         \n }", { "{}" }),

            // Arrays.
            // Keys separated with whitespaces are fine.
            PrepareTestData<std::string>("[1, null \t ,   \t \n \"a\", true   \t, \"c\" \n\n\n \t]", { "[1,null,\"a\",true,\"c\"]" }),

            // Check that ordering is preserved.
            PrepareTestData<std::string>("[1, 3, 6, true]", { "[1,3,6,true]" }),
            PrepareTestData<std::string>(R"(["a",  false, 5.6, "b"])", { R"(["a",false,5.6,"b"])" }),

            // Compound arrays.
            PrepareTestData<std::string>(R"(["a", [1, 2, 7, 9],"c", "hello"])", { R"(["a",[1,2,7,9],"c","hello"])" }),
            PrepareTestData<std::string>(R"([[true, true, false], [1, 2, 3], "c", ["a", "b", "c"]])", { R"([[true,true,false],[1,2,3],"c",["a","b","c"]])" }),

            // Objects.
            // Whitespaces between keys and values are fine.
            PrepareTestData<std::string>("{\"a\"    :    \t\n 5   \n}", { "{\"a\":5}" }),
            // Keys separated with whitespaces are fine.
            PrepareTestData<std::string>("{\"a\":5, \t\n    \"b\": true}", { "{\"a\":5,\"b\":true}", "{\"b\":true,\"a\":5}" }),

            // Compound objects.
            PrepareTestData<std::string>("\n \t    true   \t", { "true" }),
            PrepareTestData<std::string>("[5, true]", { "[5,true]" }),
            PrepareTestData<std::string>(R"({  "a":  "hello world!"})", { R"({"a":"hello world!"})" }),
            PrepareTestData<std::string>(
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
            PrepareTestData<std::string>(
                R"([ { "a": { "a": ["hello" , 5, true], "c": ["a"] }, "c": [19, 20] }, { "b": null } ])",
                {
                    R"([{"a":{"a":["hello",5,true],"c":["a"]},"c":[19,20]},{"b":null}])",
                    R"([{"a":{"c":["a"],"a":["hello",5,true]},"c":[19,20]},{"b":null}])",
                    R"([{"c":[19,20],"a":{"a":["hello",5,true],"c":["a"]}},{"b":null}])",
                    R"([{"c":[19,20],"a":{"c":["a"],"a":["hello",5,true]}},{"b":null}])"
                }
            ),
            PrepareTestData<std::string>(
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
            PrepareTestData<std::string>(
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
