#ifndef __JSONC_JSON_NUMBER_H__
#define __JSONC_JSON_NUMBER_H__

#include "json_primitive.h"

namespace json {

class JsonNumber: public JsonPrimitive<double> {
  public:
    explicit JsonNumber(double value): JsonPrimitive(value) {}
    
    // copy constructors
    JsonNumber(const JsonNumber& that): JsonPrimitive(that) {}
    JsonNumber& operator=(const JsonNumber& that) {
        JsonPrimitive<double>::operator=(that);
        return *this;
    }

    // move constructors
    JsonNumber(JsonNumber&& that): JsonPrimitive(std::move(that)) {}
    JsonNumber& operator=(JsonNumber&& that) {
        JsonPrimitive<double>::operator=(std::move(that));
        return *this;
    }

    bool operator==(const JsonValue& that) const {
        if (!that.isNumber()) {
            return false;
        }

        return _primitive == static_cast<const JsonNumber*>(&that)->_primitive;
    }

    bool operator!=(const JsonValue& that) const {
        return !operator==(that);
    }

    virtual bool isNumber() const override {
        return true;
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitNumber(this);
    }

    virtual ~JsonNumber() override = default;
};

} // namespace json

#endif // __JSONC_JSON_NUMBER_H__
