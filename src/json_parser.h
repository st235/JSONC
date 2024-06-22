#ifndef __JSONC_JSON_PARSER_H__
#define __JSONC_JSON_PARSER_H__

namespace json {

class JsonObject;

namespace __internal {

class JsonParser {
  public:
    JsonObject parse();

  private:
    /**
     * Implemented with accordance
     * to https://www.json.org/json-en.html
     **/
    void value();
    void object();
    void array();
    void string();
    void number();
    void whitespace();
};

}

} // namespace json

#endif // __JSONC_JSON_PARSER_H__
