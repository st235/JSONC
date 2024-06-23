#ifndef __JSONC_JSON_STRING_H__
#define __JSONC_JSON_STRING_H__

#include <string>

#include "json_primitive.h"

namespace json {

class JsonString final: public JsonPrimitive<std::string> {
  public:
    explicit JsonString(const std::string& value) noexcept: JsonPrimitive(value) {}
    
    // copy constructors
    JsonString(const JsonString& that) noexcept: JsonPrimitive(that) {}
    JsonString& operator=(const JsonString& that) noexcept {
        JsonPrimitive::operator=(that);
        return *this;
    }

    // move constructors
    JsonString(JsonString&& that) noexcept: JsonPrimitive(std::move(that)) {}
    JsonString& operator=(JsonString&& that) noexcept {
        JsonPrimitive::operator=(std::move(that));
        return *this;
    }

    virtual bool isString() const override {
        return true;
    }

    virtual JsonValue* clone() const override {
      return new JsonString(*this);
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitString(this);
    }

    virtual ~JsonString() override = default;
};

} // namespace json

#endif // __JSONC_JSON_STRING_H__
