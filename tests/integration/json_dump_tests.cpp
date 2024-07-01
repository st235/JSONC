#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "json.h"
#include "test_utils.h"

using ::test_utils::TestData;
using ::test_utils::PrepareTestData;
using ::testing::AnyOfArray;

class JsonDumpsTestingFixture: public ::testing::TestWithParam<TestData<json::Json>> {};

INSTANTIATE_TEST_SUITE_P(
        JsonDumpTests,
        JsonDumpsTestingFixture,
        ::testing::Values(
            // Primitives.
            PrepareTestData<json::Json>(json::Json::null(), { "null" }),
            PrepareTestData<json::Json>(json::Json(2.0), { "2" }),
            PrepareTestData<json::Json>(json::Json(-1.5), { "-1.5" }),
            PrepareTestData<json::Json>(json::Json(true), { "true" }),
            PrepareTestData<json::Json>(json::Json(false), { "false" }),
            PrepareTestData<json::Json>(json::Json("Hello world"), { R"("Hello world")" }),
            PrepareTestData<json::Json>(json::Json::array(), { "[]" }),
            PrepareTestData<json::Json>(json::Json::object(), { "{}" }),

            // Arrays.
            PrepareTestData<json::Json>(json::Json({ json::Json(true), json::Json(5.0), json::Json(static_cast<std::string>("Hello")) }), { R"([true,5,"Hello"])" }),

            // Objects.
            PrepareTestData<json::Json>(json::Json({ 
                std::make_pair("a", json::Json(true)),
                std::make_pair("b", json::Json({ json::Json(0.0), json::Json::null() })),
             }), { 
                R"({"a":true,"b":[0,null]})",
                R"({"b":[0,null],"a":true})"
              })
        )
);

TEST_P(JsonDumpsTestingFixture, JsonYieldsValidDump) {
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_jsons = pair.second;

    const auto& opt_dumped_json = json::Json::toJson(json);
    EXPECT_THAT(opt_dumped_json, AnyOfArray(expected_jsons));
}
