#ifndef __JSONC_JSON_OBJECT_H__
#define __JSONC_JSON_OBJECT_H__

#include <string>
#include <unordered_map>
#include <unordered_set>

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

    JsonValue* get(const std::string& key) const {
        return _values.at(key);
    }

    std::unordered_set<std::string> keys() const {
        std::unordered_set<std::string> keys;

        for (const auto& pair: _values) {
            keys.insert(pair.first);
        }

        return keys;
    }

    inline size_t size() const {
        return _values.size();
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitObject(this);
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
