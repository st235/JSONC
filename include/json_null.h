#ifndef __JSONC_JSON_NULL_H__
#define __JSONC_JSON_NULL_H__

#include "json_value.h"

namespace json {

class JsonNull final: public JsonValue {
  public:
    explicit JsonNull() noexcept {}
    
    // Copy constructors.
    JsonNull(const JsonNull& that) = default;
    JsonNull& operator=(const JsonNull& that) = default;

    // Move constructors.
    JsonNull(JsonNull&& that) = default;
    JsonNull& operator=(JsonNull&& that) = default;

    virtual bool isNull() const override {
        return true;
    }

    virtual JsonValue* clone() const override {
      return new JsonNull(*this);
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitNull(this);
    }

    virtual ~JsonNull() override = default;

  protected:
    virtual bool isEqual(const JsonValue& that) const override {
      // All nulls are equal to each other.
      return that.isNull();
    }
};

} // namespace json

#endif // __JSONC_JSON_NULL_H__
