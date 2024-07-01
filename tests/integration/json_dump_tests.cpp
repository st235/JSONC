#include <gtest/gtest.h>

#include <string>
#include <memory>
#include <utility>

#include "json.h"

class JsonDumpsTestingFixture: public ::testing::TestWithParam<std::pair<json::Json, std::string>> {};

INSTANTIATE_TEST_SUITE_P(
        JsonDumpTests,
        JsonDumpsTestingFixture,
        ::testing::Values(
            std::make_pair(json::Json::null(), "null"),
            std::make_pair(json::Json(2.0), "2"),
            std::make_pair(json::Json({ json::Json(true), json::Json(5.0), json::Json(static_cast<std::string>("Hello")) }), R"([true,5,"Hello"])")
        )
);

TEST_P(JsonDumpsTestingFixture, JsonYieldsValidDump) {
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_json = pair.second;

    const auto& opt_dumped_json = json::Json::toJson(json);

    EXPECT_EQ(expected_json, opt_dumped_json);
}
