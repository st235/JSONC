#ifndef __JSONC_JSON_VISITOR_H__
#define __JSONC_JSON_VISITOR_H__

namespace json {

class JsonArray;
class JsonBoolean;
class JsonNumber;
class JsonObject;
class JsonString;
class JsonNull;

class JsonVisitor {
  public:
    virtual void visitNull(const JsonNull* node) = 0;
    virtual void visitBoolean(const JsonBoolean* node) = 0;
    virtual void visitNumber(const JsonNumber* node) = 0;
    virtual void visitString(const JsonString* node) = 0;
    virtual void visitObject(const JsonObject* node) = 0;
    virtual void visitArray(const JsonArray* node) = 0;
    virtual ~JsonVisitor() = default;
};

} // namespace json

#endif // __JSONC_JSON_VISITOR_H__
