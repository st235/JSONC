#ifndef __JSONC_JSON_OBJECT_H__
#define __JSONC_JSON_OBJECT_H__

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "json_value.h"

namespace json {

class JsonObject final: public JsonValue {
  public:
    JsonObject() noexcept: _items() {
        // Empty on purpose.
    }

    // Copy constructors.
    JsonObject(const JsonObject& that) noexcept: _items() {
        for (const auto& pair: that._items) {
            _items[pair.first] = pair.second->clone();
        }
    }

    JsonObject& operator=(const JsonObject& that) noexcept {
        if (this != &that) {
            this->_items.clear();
            for (const auto& pair: that._items) {
                _items[pair.first] = pair.second->clone();
            }
        }

        return *this;
    }

    // Move constructors.
    JsonObject(JsonObject&& that) noexcept: _items(std::move(that._items)) {
    }

    JsonObject& operator=(JsonObject&& that) noexcept {
        if (this != &that) {
            this->_items = std::move(that._items);
        }

        return *this;
    }

    void put(const std::string& key,
             JsonValue* value) {
        _items[key] = value;
    }

    bool containsKey(const std::string& key) const {
        return _items.find(key) != _items.end();
    }

    JsonValue* get(const std::string& key) const {
        return _items.at(key);
    }

    std::unordered_set<std::string> keys() const {
        std::unordered_set<std::string> keys;

        for (const auto& pair: _items) {
            keys.insert(pair.first);
        }

        return keys;
    }

    inline size_t size() const {
        return _items.size();
    }

    virtual JsonValue* clone() const override {
      return new JsonObject(*this);
    }

    virtual void accept(JsonVisitor* visitor) override {
        visitor->visitObject(this);
    }

    virtual ~JsonObject() override {
        for (const auto& pair: _items) {
            const auto* value = pair.second;
            delete value;
        }
    }

  protected:
    virtual bool isEqual(const JsonValue& that) const override {
      const auto& that_object = static_cast<const JsonObject&>(that);

      if (this->size() != that_object.size()) {
        return false;
      }

      const auto& keys = this->keys();

      for (const auto& key: keys) {
        if (!that_object.containsKey(key)) {
            return false;
        }

        if (*(this->get(key)) != *(that_object.get(key))) {
            return false;
        }
      }

      return true;
    }

  private:
    std::unordered_map<std::string, JsonValue*> _items;
};

} // namespace json

#endif // __JSONC_JSON_OBJECT_H__
