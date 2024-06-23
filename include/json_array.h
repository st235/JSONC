#ifndef __JSONC_JSON_ARRAY_H__
#define __JSONC_JSON_ARRAY_H__

#include <vector>

#include "json_value.h"

namespace json {

class JsonArray final: public JsonValue {
  public:
    JsonArray() noexcept: _items() {
        // Empty on purpose.
    }

    explicit JsonArray(const std::vector<JsonValue*> values) noexcept:
        _items(values) {
        // Empty on purpose.
    }

    // Copy constructors.
    JsonArray(const JsonArray& that) noexcept: _items() {
        for (const auto* item: that._items) {
            this->_items.push_back(item->clone());
        }
    }

    JsonArray& operator=(const JsonArray& that) noexcept {
        if (this != &that) {
            this->_items.clear();
            for (const auto* item: that._items) {
                this->_items.push_back(item->clone());
            }
        }

        return *this;
    }

    // Move constructors.
    JsonArray(JsonArray&& that) noexcept: _items(std::move(that._items)) {
    }

    JsonArray& operator=(JsonArray&& that) noexcept {
        if (this != &that) {
            this->_items = std::move(that._items);
        }

        return *this;
    }

    virtual bool isArray() const override {
        return true;
    }

    void add(JsonValue* value) {
        _items.push_back(value);
    }

    JsonValue* get(size_t index) const {
        return _items[index];
    }

    inline size_t size() const {
        return _items.size();
    }

    virtual JsonValue* clone() const override {
      return new JsonArray(*this);
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitArray(this);
    }

    virtual ~JsonArray() override {
        for (const auto* value: _items) {
            delete value;
        }
    }

  protected:
    virtual bool isEqual(const JsonValue& that) const override {
      const auto& that_array = static_cast<const JsonArray&>(that);

      if (this->size() != that_array.size()) {
        return false;
      }

      for (size_t i = 0; i < this->size(); i++) {
        if (*(this->get(i)) != *(that_array.get(i))) {
            return false;
        }
      }

      return true;
    }

  private:
    std::vector<JsonValue*> _items;
};

} // namespace json

#endif // __JSONC_JSON_ARRAY_H__
