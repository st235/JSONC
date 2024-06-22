#ifndef __JSONC_JSON_VALUE_H__
#define __JSONC_JSON_VALUE_H__

namespace json {

class JsonValue {
  public:
    virtual bool isNull() const {
        return false;
    }

    virtual bool isArray() const {
        return false;
    }

    virtual bool isBoolean() const {
        return false;
    }

    virtual bool isNumber() const {
        return false;
    }

    virtual bool isObject() const {
        return false;
    }

    virtual bool isString() const {
        return false;
    }

    virtual ~JsonValue() {}
};

} // namespace json

#endif // __JSONC_JSON_VALUE_H__
