#ifndef __JSONC_JSON_H__
#define __JSONC_JSON_H__

#include <memory>
#include <string>

#include "json_parser.h"
#include "json_minifier.h"
#include "json_value.h"

namespace json {

std::unique_ptr<JsonValue> FromJson(const std::string& json) {
    json::__internal::JsonParser parser;
    return std::unique_ptr<JsonValue>{ parser.parse(json) };
}

std::string ToJson(JsonValue* json) {
    json::JsonMinifier minifier;
    json->accept(&minifier);
    return minifier.minifiedJson();
}

} // namespace json

#endif // __JSONC_JSON_H__
