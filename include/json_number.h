#ifndef __JSONC_JSON_NUMBER_H__
#define __JSONC_JSON_NUMBER_H__

#include "json_primitive.h"

namespace json {

class JsonNumber final: public JsonPrimitive<double> {
  public:
    explicit JsonNumber(double value) noexcept: JsonPrimitive(value) {}
    
    // copy constructors
    JsonNumber(const JsonNumber& that) noexcept: JsonPrimitive(that) {}
    JsonNumber& operator=(const JsonNumber& that) {
        JsonPrimitive<double>::operator=(that);
        return *this;
    }

    // move constructors
    JsonNumber(JsonNumber&& that) noexcept: JsonPrimitive(std::move(that)) {}
    JsonNumber& operator=(JsonNumber&& that) noexcept {
        JsonPrimitive<double>::operator=(std::move(that));
        return *this;
    }

    virtual bool isNumber() const override {
        return true;
    }

    virtual JsonValue* clone() const override {
      return new JsonNumber(*this);
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitNumber(this);
    }

    virtual ~JsonNumber() override = default;
};

} // namespace json

#endif // __JSONC_JSON_NUMBER_H__
