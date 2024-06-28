#include "json.h"

#include "json_parser.h"
#include "json_minifier.h"

namespace json {

const Json Json::VALUE_NULL = Json();

const Json& Json::null() {
    return VALUE_NULL;
}

Json Json::array() {
    return std::move(Json(array_t()));
}

Json Json::object() {
    return std::move(Json(object_t()));
}

std::optional<Json> Json::fromJson(const std::string& json) {
    __internal::JsonParser parser;
    return std::move(parser.parse(json));
}

std::string Json::toJson(const Json& json) {
    JsonMinifier minifier;
    return std::move(minifier.minify(json));
}

} // namespace json
