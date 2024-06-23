#ifndef __JSONC_JSON_PARSER_H__
#define __JSONC_JSON_PARSER_H__

#include <cstdint>
#include <string>

namespace json {

// Forward declaration of json types.
class JsonValue;

class JsonArray;
class JsonBoolean;
class JsonNumber;
class JsonObject;
class JsonString;
class JsonNull;

namespace __internal {

// Forward declaration of the reader.
class JsonTokenReader;

class JsonParser {
  public:
    JsonValue* parse(const std::string& raw_json);

  private:
    /**
     * Implemented with accordance
     * to https://www.json.org/json-en.html
     **/

    // Base.
    JsonValue* value(JsonTokenReader& reader);
    
    // Objects.
    JsonObject* object(JsonTokenReader& reader);
    JsonArray* array(JsonTokenReader& reader);

    // Primitives.
    JsonNull* null(JsonTokenReader& reader);
    JsonBoolean* boolean(JsonTokenReader& reader);
    JsonNumber* number(JsonTokenReader& reader);
    JsonString* string(JsonTokenReader& reader);

    // Misc.
    std::string* raw_string(JsonTokenReader& reader);
    void whitespace(JsonTokenReader& reader);
};

} // namespace internal

} // namespace json

#endif // __JSONC_JSON_PARSER_H__
