#include "json_beautifier.h"

#include "json_array.h"
#include "json_boolean.h"
#include "json_number.h"
#include "json_object.h"
#include "json_string.h"
#include "json_value.h"
#include "json_null.h"

namespace json {

void JsonBeautifier::visitNull(const JsonNull* node) {
    _stream << "null";
}

void JsonBeautifier::visitBoolean(const JsonBoolean* node) {
    if (node->value()) {
        _stream << "true";
    } else {
        _stream << "false";
    }
}

void JsonBeautifier::visitNumber(const JsonNumber* node) {
    _stream << node->value();
}

void JsonBeautifier::visitString(const JsonString* node) {
    _stream << '\"' << node->value() << '\"';
}

void JsonBeautifier::visitObject(const JsonObject* node) {
    const auto& keys = node->keys();
    _stream << '{' << std::endl;

    size_t iter = 0;

    for (const auto& key: keys) {
        _depth += 1;

        writeSpacing();
        _stream << '\"' << key << '\"' << ": ";

        auto* child = node->get(key);
        child->accept(this);

        if (iter < (node->size() - 1)) {
            _stream << ',';
        }
        iter += 1;

        _stream << std::endl;

        _depth -= 1;
    }

    writeSpacing();
    _stream << '}';
}

void JsonBeautifier::visitArray(const JsonArray* node) {
    _stream << '[' << std::endl;

    for (size_t i = 0; i < node->size(); i++) {
        _depth += 1;

        writeSpacing();
        auto* child = node->get(i);
        child->accept(this);

        if (i < (node->size() - 1)) {
            _stream << ',';
        }

        _stream << std::endl;

        _depth -= 1;
    }

    writeSpacing();
    _stream << ']';
}

} // namespace json
