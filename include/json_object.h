#ifndef __JSONC_JSON_OBJECT_H__
#define __JSONC_JSON_OBJECT_H__

#include <string>
#include <unordered_map>

#include "json_value.h"

namespace json {

class JsonObject: public JsonValue {
  public:
    JsonObject():
        _values() {
        // Empty on purpose.
    }

    void put(const std::string& key,
             JsonValue* value) {
        _values[key] = value;
    }

    JsonValue* get(const std::string& key) {
        return _values[key];
    }

    virtual ~JsonObject() override {
        for (const auto& pair: _values) {
            JsonValue* value = pair.second;
            delete value;
        }
    }

  private:
    std::unordered_map<std::string, JsonValue*> _values;
};

} // namespace json

#endif // __JSONC_JSON_OBJECT_H__
