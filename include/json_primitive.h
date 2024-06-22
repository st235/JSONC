#ifndef __JSONC_JSON_PRIMITIVE_H__
#define __JSONC_JSON_PRIMITIVE_H__

#include "json_value.h"

namespace json {

template<typename T>
class JsonPrimitive: public JsonValue {
  public:
    explicit JsonPrimitive(T primitive):
        _primitive(primitive) {
        // Empty on purpose.
    }

    JsonPrimitive(const JsonPrimitive<T>& that) {
        this->_primitive = that._primitive;
    }

    JsonPrimitive<T>& operator=(const JsonPrimitive<T>& that) {
        if (this != &that) {
            this->_primitive = that._primitive;
        }

        return *this;
    }

    JsonPrimitive(JsonPrimitive<T>&& that) {
        this->_primitive = std::move(that._primitive);
    }

    JsonPrimitive<T>& operator=(const JsonPrimitive<T>&& that) {
        if (this != &that) {
            this->_primitive = std::move(that._primitive);
        }

        return *this;
    }

    inline const T& value() const {
        return _primitive;
    }

    virtual ~JsonPrimitive() {}

  protected:
    T _primitive;
};

} // namespace json

#endif // __JSONC_JSON_PRIMITIVE_H__
