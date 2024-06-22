#ifndef __JSONC_JSON_NULL_H__
#define __JSONC_JSON_NULL_H__

#include "json_value.h"

namespace json {

class JsonNull: public JsonValue {
  public:
    static JsonNull* VALUE;

  private:
    explicit JsonNull() {}
    
    // copy constructors
    JsonNull(const JsonNull& that) = delete;
    JsonNull& operator=(const JsonNull& that) = delete;

    // move constructors
    JsonNull(JsonNull&& that) = delete;
    JsonNull& operator=(JsonNull&& that) = delete;

    virtual bool isNull() const override {
        return true;
    }

    virtual ~JsonNull() override = default;
};

} // namespace json

#endif // __JSONC_JSON_NULL_H__
