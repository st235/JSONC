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
            // primitives
            std::make_pair(json::Json::null(), "null")
        )
);

TEST_P(JsonDumpsTestingFixture, JsonYieldsValidDump) {
    const auto& pair = GetParam();

    const auto& json = pair.first;
    const auto& expected_json = pair.second;

    const auto& opt_dumped_json = json::Json::toJson(json);

    EXPECT_EQ(expected_json, opt_dumped_json);
}
