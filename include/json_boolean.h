#ifndef __JSONC_JSON_BOOLEAN_H__
#define __JSONC_JSON_BOOLEAN_H__

#include "json_primitive.h"

namespace json {

class JsonBoolean: public JsonPrimitive<bool> {
  public:
    explicit JsonBoolean(bool value): JsonPrimitive(value) {}
    
    // copy constructors
    JsonBoolean(const JsonBoolean& that): JsonPrimitive(that) {}
    JsonBoolean& operator=(const JsonBoolean& that) {
        JsonPrimitive::operator=(that);
        return *this;
    }

    // move constructors
    JsonBoolean(JsonBoolean&& that): JsonPrimitive(std::move(that)) {}
    JsonBoolean& operator=(JsonBoolean&& that) {
        JsonPrimitive::operator=(std::move(that));
        return *this;
    }

    bool operator==(const JsonValue& that) const {
        if (!that.isBoolean()) {
            return false;
        }

        return _primitive == static_cast<const JsonBoolean*>(&that)->_primitive;
    }

    bool operator!=(const JsonValue& that) const {
        return !operator==(that);
    }

    virtual bool isBoolean() const override {
        return true;
    }

    virtual ~JsonBoolean() override = default;
};

} // namespace json

#endif // __JSONC_JSON_BOOLEAN_H__
