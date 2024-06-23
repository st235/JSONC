#ifndef __JSONC_JSON_BEAUTIFIER_H__
#define __JSONC_JSON_BEAUTIFIER_H__

#include <cstdint>
#include <sstream>

#include "json_visitor.h"

namespace json {

class JsonBeautifier: public JsonVisitor {
  public:
    JsonBeautifier(uint8_t spacing = 1,
                   char _space_symbol = '\t'):
        _depth(0),
        _spacing(spacing),
        _space_symbol(_space_symbol),
        _stream() {
        // Empty on purpose.
    }

    virtual void visitNull(const JsonNull* node) override;
    virtual void visitBoolean(const JsonBoolean* node) override;
    virtual void visitNumber(const JsonNumber* node) override;
    virtual void visitString(const JsonString* node) override;
    virtual void visitObject(const JsonObject* node) override;
    virtual void visitArray(const JsonArray* node) override;

    void reset() {
        _depth = 0;
        _stream.str(std::string());
        _stream.clear();
    }

    inline std::string beautifiedJson() const {
        return _stream.str();
    }

    virtual ~JsonBeautifier() = default;
  private:
    void writeSpacing() {
        for (uint16_t i = 0; i < _depth * _spacing; i++) {
            _stream << _space_symbol;
        }
    }

    uint16_t _depth;
    uint8_t _spacing;
    char _space_symbol;
    std::stringstream _stream;
};

} // namespace json

#endif // __JSONC_JSON_BEAUTIFIER_H__
