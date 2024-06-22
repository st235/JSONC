#ifndef __JSONC_JSON_STRING_H__
#define __JSONC_JSON_STRING_H__

#include <string>

#include "json_primitive.h"

namespace json {

class JsonString: public JsonPrimitive<std::string> {
  public:
    explicit JsonString(const std::string& value): JsonPrimitive(value) {}
    
    // copy constructors
    JsonString(const JsonString& that): JsonPrimitive(that) {}
    JsonString& operator=(const JsonString& that) {
        JsonPrimitive::operator=(that);
        return *this;
    }

    // move constructors
    JsonString(JsonString&& that): JsonPrimitive(std::move(that)) {}
    JsonString& operator=(JsonString&& that) {
        JsonPrimitive::operator=(std::move(that));
        return *this;
    }

    virtual bool isString() const override {
        return true;
    }

    virtual ~JsonString() override = default;
};

} // namespace json

#endif // __JSONC_JSON_STRING_H__
