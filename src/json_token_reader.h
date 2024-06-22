#ifndef __JSONC_JSON_TOKEN_READER_H__
#define __JSONC_JSON_TOKEN_READER_H__

#include <cstdint>
#include <string>

namespace json {

namespace __internal {

class JsonTokenReader {
  public:
    static inline constexpr char TOKEN_EOF = 0;

    explicit JsonTokenReader(const std::string& raw_json):
        _index(0),
        _raw_json(raw_json) {
        // Empty on purpose.
    }

    JsonTokenReader(const JsonTokenReader& that) {
        this->_index = that._index;
        this->_raw_json = that._raw_json;
    }

    JsonTokenReader& operator=(const JsonTokenReader& that) {
        if (this != &that) {
            this->_index = that._index;
            this->_raw_json = that._raw_json;
        }

        return *this;
    }

    JsonTokenReader(JsonTokenReader&& that) noexcept {
        this->_index = that._index;
        this->_raw_json = std::move(that._raw_json);
    }

    JsonTokenReader& operator=(JsonTokenReader&& that) noexcept {
        if (this != &that) {
            this->_index = that._index;
            this->_raw_json = std::move(that._raw_json);
        }

        return *this;
    }

    inline bool hasNext() const {
        return _index < _raw_json.length();
    }

    inline bool next() {
        if (!hasNext()) {
            return false;
        }

        _index = _index + 1;
        return true;
    }

    inline char peek() const {
        if (_index == _raw_json.length()) {
            return TOKEN_EOF;
        }

        return _raw_json[_index];
    }

    ~JsonTokenReader() = default;
  private:
    size_t _index;
    std::string _raw_json;
};

} // namespace __internal

} // namespace json

#endif // __JSONC_JSON_TOKEN_READER_H__