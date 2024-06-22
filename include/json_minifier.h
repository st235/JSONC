#ifndef __JSONC_JSON_MINIFIER_H__
#define __JSONC_JSON_MINIFIER_H__

#include <sstream>

#include "json_visitor.h"

namespace json {

class JsonMinifier: public JsonVisitor {
  public:
    JsonMinifier():
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
        _stream.str(std::string());
        _stream.clear();
    }

    inline std::string minifiedJson() const {
        return _stream.str();
    }

    virtual ~JsonMinifier() = default;
  private:
    std::stringstream _stream;
};

} // namespace json

#endif // __JSONC_JSON_MINIFIER_H__
