#ifndef __JSONC_JSON_DEFINITIONS_H__
#define __JSONC_JSON_DEFINITIONS_H__

#include <string>
#include <vector>
#include <unordered_map>

namespace json {

class Json;

using bool_t = bool;
using number_t = double;
using string_t = std::string;
using array_t = std::vector<Json>;
using object_t = std::unordered_map<std::string, Json>;

} // namespace json

#endif // __JSONC_JSON_DEFINITIONS_H__
