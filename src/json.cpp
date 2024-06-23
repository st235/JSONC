#include "json.h"

#include "json_parser.h"
#include "json_minifier.h"

namespace json {

std::unique_ptr<JsonValue> FromJson(const std::string& json) {
    __internal::JsonParser parser;
    return std::unique_ptr<JsonValue>{ parser.parse(json) };
}

std::string ToJson(JsonValue* json) {
    JsonMinifier minifier;
    return minifier.minify(json);
}

} // namespace json
