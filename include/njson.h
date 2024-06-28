#ifndef __JSONC_JSON_H__
#define __JSONC_JSON_H__

#include <string>
#include <vector>
#include <unordered_map>

namespace json {

class Json {
  private:
    using bool_t = bool;
    using number_t = double;
    using string_t = std::string;
    using array_t = std::vector<Json>;
    using object_t = std::unordered_map<std::string, Json>;

    struct ValueContainer {
      public:
        enum {
          kTypeBool,
          kTypeNumber,
          kTypeString,
          kTypeArray,
          kTypeObject,
          kTypeNull,
        } type;

        union {
          bool_t _bool;
          number_t _number;
          string_t* _string;
          array_t* _array;
          object_t* _object;
        } value;

        ValueContainer() noexcept:
          type(kTypeNumber) {
            value._object = nullptr;
        }

        explicit ValueContainer(bool_t raw_value) noexcept:
          type(kTypeBool) {
            value._bool = raw_value;
        }

        explicit ValueContainer(number_t raw_value) noexcept:
          type(kTypeNumber) {
            value._number = raw_value;
        }

        ValueContainer(const string_t& raw_value) noexcept:
          type(kTypeString) {
            value._string = new string_t(raw_value);
        }

        ValueContainer(string_t&& raw_value) noexcept:
          type(kTypeString) {
            value._string = new string_t(std::move(raw_value));
        }

        ValueContainer(const array_t& raw_value) noexcept:
          type(kTypeArray) {
            value._array = new array_t(raw_value);
        }

        ValueContainer(array_t&& raw_value) noexcept:
          type(kTypeArray) {
            value._array = new array_t(std::move(raw_value));
        }

        ValueContainer(const object_t& raw_value) noexcept:
          type(kTypeObject) {
            value._object = new object_t(raw_value);
        }

        ValueContainer(object_t&& raw_value) noexcept:
          type(kTypeObject) {
            value._object = new object_t(std::move(raw_value));
        }

        ValueContainer(const ValueContainer& that) noexcept:
          type(that.type) {
            copyContainerValue(that);
        }

        ValueContainer& operator=(const ValueContainer& that) noexcept {
          if (this != &that) {
            type = that.type;
            copyContainerValue(that);
          }

          return *this;
        }

        ValueContainer(ValueContainer&& that) noexcept:
          type(that.type) {
            swapContainerValue(std::move(that));
        }

        ValueContainer& operator=(ValueContainer&& that) noexcept {
          if (this != &that) {
            type = that.type;
            swapContainerValue(std::move(that));
          }

          return *this;
        }

        ~ValueContainer() {
          switch (type) {
            case kTypeNull:
            case kTypeBool:
            case kTypeNumber:
              break;
            case kTypeString:
              delete value._string;
              break;
            case kTypeArray:
              delete value._array;
              break;
            case kTypeObject:
              delete value._object;
              break;
          }
        }

      private:
        void copyContainerValue(const ValueContainer& that) {
          switch (that.type) {
            case kTypeNull:
              value._object = nullptr;
              break;
            case kTypeBool:
              value._bool = that.value._bool;
              break;
            case kTypeNumber:
              value._number = that.value._number;
              break;
            case kTypeString:
              value._string = new string_t(*that.value._string);
              break;
            case kTypeArray:
              value._array = new array_t(*that.value._array);
              break;
            case kTypeObject:
              value._object = new object_t(*that.value._object);
              break;
          }
        }

        void swapContainerValue(ValueContainer&& that) {
          switch (that.type) {
            case kTypeNull:
              value._object = nullptr;
              break;
            case kTypeBool:
              value._bool = that.value._bool;
              break;
            case kTypeNumber:
              value._number = that.value._number;
              break;
            case kTypeString:
              value._string = new string_t(std::move(*that.value._string));
              break;
            case kTypeArray:
              value._array = new array_t(std::move(*that.value._array));
              break;
            case kTypeObject:
              value._object = new object_t(std::move(*that.value._object));
              break;
          }
        }
    };

  ValueContainer _container;

  public:
    Json() noexcept: _container() {}
    Json(bool_t value) noexcept: _container(value) {}
    Json(number_t value) noexcept: _container(value) {}
    Json(const string_t& value) noexcept: _container(value) {}
    Json(string_t&& value) noexcept: _container(std::move(value)) {}
    Json(const array_t& value) noexcept: _container(value) {}
    Json(array_t&& value) noexcept: _container(std::move(value)) {}
    Json(const object_t& value) noexcept: _container(value) {}
    Json(object_t&& value) noexcept: _container(std::move(value)) {}

    Json(const Json& that) noexcept:
      _container(that._container) {
    }

    Json& operator=(const Json& that) noexcept {
      if (this != &that) {
        _container = that._container;
      }
      return *this;
    }

    Json(Json&& that) noexcept:
      _container(std::move(that._container)) {
    }

    Json& operator=(Json&& that) noexcept {
      if (this != &that) {
        _container = std::move(that._container);
      }
      return *this;
    }

    bool operator==(const Json& that) const {
      if (_container.type != that._container.type) {
        return false;
      }

      switch (_container.type) {
        case ValueContainer::kTypeNull:
          return _container.value._object == that._container.value._object;
        case ValueContainer::kTypeBool:
          return _container.value._bool == that._container.value._bool;
        case ValueContainer::kTypeNumber:
          return _container.value._number == that._container.value._number;
        case ValueContainer::kTypeString:
          return *_container.value._string == *that._container.value._string;
        case ValueContainer::kTypeArray:
          return *_container.value._array == *that._container.value._array;
        case ValueContainer::kTypeObject:
          return *_container.value._object == *that._container.value._object;
      }
    }

    bool operator!=(const Json& that) const {
      return !operator==(that);
    }

    explicit operator bool() const {
      switch (_container.type) {
        case ValueContainer::kTypeBool:
          return _container.value._bool != false;
        case ValueContainer::kTypeNumber:
          return _container.value._number != 0.0;
        case ValueContainer::kTypeString:
          return _container.value._string->length() > 0;
        case ValueContainer::kTypeArray:
          return _container.value._array->size() > 0;
        case ValueContainer::kTypeNull:
        case ValueContainer::kTypeObject:
          return _container.value._object != nullptr;
      }
    }

    inline bool isNull() const {
      return _container.type == ValueContainer::kTypeNull;
    }

    inline bool isBool() const {
      return _container.type == ValueContainer::kTypeBool;
    }

    inline bool isNumber() const {
      return _container.type == ValueContainer::kTypeNumber;
    }

    inline bool isString() const {
      return _container.type == ValueContainer::kTypeString;
    }

    inline bool isArray() const {
      return _container.type == ValueContainer::kTypeArray;
    }

    inline bool isObject() const {
      return _container.type == ValueContainer::kTypeObject;
    }

    inline bool_t asBool() const {
      return _container.value._bool;
    }

    inline number_t asNumber() const {
      return _container.value._number;
    }

    inline const string_t& asString() const {
      return *_container.value._string;
    }

    inline const array_t& asArray() const {
      return *_container.value._array;
    }

    inline const object_t& asObject() const {
      return *_container.value._object;
    }

    void add(const Json& that) {
      _container.value._array->push_back(that);
    }

    void add(Json&& that) {
      _container.value._array->emplace_back(std::move(that));
    }

    void put(const std::string& key, const Json& json) {
      (*_container.value._object)[key] = json;
    }

    void put(const std::string& key, Json&& json) {
      (*_container.value._object)[key] = std::move(json);
    }

    ~Json() = default;
};

} // namespace json

#endif // __JSONC_JSON_H__