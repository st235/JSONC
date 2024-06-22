#ifndef __JSONC_JSON_ARRAY_H__
#define __JSONC_JSON_ARRAY_H__

#include <vector>

#include "json_value.h"

namespace json {

class JsonArray: public JsonValue {
  public:
    JsonArray():
        _vector() {
        // Empty on purpose.
    }

    explicit JsonArray(const std::vector<JsonValue*> values):
        _vector(values) {
        // Empty on purpose.
    }

    JsonArray(JsonArray&& that):
        _vector(std::move(that._vector)) {
    }

    JsonArray& operator=(JsonArray&& that) {
        if (this != &that) {
            this->_vector = std::move(that._vector);
        }

        return *this;
    }

    virtual bool isArray() const override {
        return true;
    }

    void add(JsonValue* value) {
        _vector.push_back(value);
    }

    JsonValue* get(size_t index) const {
        return _vector[index];
    }

    inline size_t size() const {
        return _vector.size();
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitArray(this);
    }

    virtual ~JsonArray() override {
        for (auto* value: _vector) {
            delete value;
        }
    }

  private:
    JsonArray(const JsonArray& that) = delete;
    JsonArray& operator=(const JsonArray& that) = delete;

    std::vector<JsonValue*> _vector;
};

} // namespace json

#endif // __JSONC_JSON_ARRAY_H__
