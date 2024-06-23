#ifndef __JSONC_JSON_BOOLEAN_H__
#define __JSONC_JSON_BOOLEAN_H__

#include "json_primitive.h"

namespace json {

class JsonBoolean final: public JsonPrimitive<bool> {
  public:
    explicit JsonBoolean(bool value) noexcept: JsonPrimitive(value) {}
    
    // copy constructors
    JsonBoolean(const JsonBoolean& that) noexcept: JsonPrimitive(that) {}
    JsonBoolean& operator=(const JsonBoolean& that) noexcept {
        JsonPrimitive::operator=(that);
        return *this;
    }

    // move constructors
    JsonBoolean(JsonBoolean&& that) noexcept: JsonPrimitive(std::move(that)) {}
    JsonBoolean& operator=(JsonBoolean&& that) noexcept {
        JsonPrimitive::operator=(std::move(that));
        return *this;
    }

    virtual bool isBoolean() const override {
        return true;
    }

    virtual JsonValue* clone() const override {
      return new JsonBoolean(*this);
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitBoolean(this);
    }

    virtual ~JsonBoolean() override = default;
};

} // namespace json

#endif // __JSONC_JSON_BOOLEAN_H__
