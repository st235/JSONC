#ifndef __JSONC_JSON_H__
#define __JSONC_JSON_H__

#include <memory>
#include <string>

#include "json_value.h"

namespace json {

std::unique_ptr<JsonValue> FromJson(const std::string& json);

std::string ToJson(JsonValue* json);

} // namespace json

#endif // __JSONC_JSON_H__
