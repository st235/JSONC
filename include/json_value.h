#ifndef __JSONC_JSON_VALUE_H__
#define __JSONC_JSON_VALUE_H__

#include "json_visitor.h"

namespace json {

class JsonValue {
  public:
    bool operator==(const JsonValue& that) const {
      return typeid(*this) == typeid(that) && isEqual(that);
    }

    bool operator!=(const JsonValue& that) const {
      return !operator==(that);
    }

    virtual bool isNull() const {
        return false;
    }

    virtual bool isBoolean() const {
        return false;
    }

    virtual bool isNumber() const {
        return false;
    }

    virtual bool isString() const {
        return false;
    }

    virtual bool isArray() const {
        return false;
    }

    virtual bool isObject() const {
        return false;
    }

    virtual JsonValue* clone() const = 0;

    virtual void accept(JsonVisitor* visitor) = 0;

    virtual ~JsonValue() {}

  protected:
    virtual bool isEqual(const JsonValue& that) const = 0;
};

} // namespace json

#endif // __JSONC_JSON_VALUE_H__
