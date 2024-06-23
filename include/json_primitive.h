#ifndef __JSONC_JSON_PRIMITIVE_H__
#define __JSONC_JSON_PRIMITIVE_H__

#include "json_value.h"

namespace json {

template<typename T>
class JsonPrimitive: public JsonValue {
  public:
    explicit JsonPrimitive(T primitive) noexcept:
        _primitive(primitive) {
        // Empty on purpose.
    }

    JsonPrimitive(const JsonPrimitive<T>& that) noexcept {
        this->_primitive = that._primitive;
    }

    JsonPrimitive<T>& operator=(const JsonPrimitive<T>& that) noexcept {
        if (this != &that) {
            this->_primitive = that._primitive;
        }

        return *this;
    }

    JsonPrimitive(JsonPrimitive<T>&& that) noexcept {
        this->_primitive = std::move(that._primitive);
    }

    JsonPrimitive<T>& operator=(const JsonPrimitive<T>&& that) noexcept {
        if (this != &that) {
            this->_primitive = std::move(that._primitive);
        }

        return *this;
    }

    inline const T& value() const {
        return _primitive;
    }

    virtual bool isEqual(const JsonValue& that) const override {
      return _primitive == static_cast<const JsonPrimitive<T>&>(that)._primitive;
    }

    virtual ~JsonPrimitive() {}

  protected:
    T _primitive;
};

} // namespace json

#endif // __JSONC_JSON_PRIMITIVE_H__
