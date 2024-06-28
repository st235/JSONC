#ifndef __JSONC_JSON_PARSER_H__
#define __JSONC_JSON_PARSER_H__

#include <cstdint>
#include <optional>
#include <string>

namespace json {

class Json;

namespace __internal {

// Forward declaration of the reader.
class JsonTokenReader;

class JsonParser {
  public:
    std::optional<Json> parse(const std::string& raw_json);

  private:
    /**
     * Implemented with accordance
     * to https://www.json.org/json-en.html
     **/

    // Base.
    std::optional<Json> value(JsonTokenReader& reader);
    
    // Objects.
    std::optional<Json> object(JsonTokenReader& reader);
    std::optional<Json> array(JsonTokenReader& reader);

    // Primitives.
    std::optional<Json> null(JsonTokenReader& reader);
    std::optional<Json> boolean(JsonTokenReader& reader);
    std::optional<Json> number(JsonTokenReader& reader);
    std::optional<Json> string(JsonTokenReader& reader);

    // Misc.
    std::optional<std::string> raw_string(JsonTokenReader& reader);
    void whitespace(JsonTokenReader& reader);
};

} // namespace internal

} // namespace json

#endif // __JSONC_JSON_PARSER_H__
