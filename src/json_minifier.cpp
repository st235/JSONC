#include "json_minifier.h"

#include "json_array.h"
#include "json_boolean.h"
#include "json_number.h"
#include "json_object.h"
#include "json_string.h"
#include "json_value.h"
#include "json_null.h"

namespace json {

void JsonMinifier::visitNull(const JsonNull* node) {
    _stream << "null";
}

void JsonMinifier::visitBoolean(const JsonBoolean* node) {
    if (node->value()) {
        _stream << "true";
    } else {
        _stream << "false";
    }
}

void JsonMinifier::visitNumber(const JsonNumber* node) {
    _stream << node->value();
}

void JsonMinifier::visitString(const JsonString* node) {
    _stream << node->value();
}

void JsonMinifier::visitObject(const JsonObject* node) {
    const auto& keys = node->keys();
    _stream << '{';

    size_t iter = 0;

    for (const auto& key: keys) {
        if (iter > 0) {
            _stream << ',';
        }

        _stream << '\"' << key << '\"' << ':';

        auto* child = node->get(key);
        child->accept(this);

        iter += 1;
    }

    _stream << '}';
}

void JsonMinifier::visitArray(const JsonArray* node) {
    _stream << '[';

    for (size_t i = 0; i < node->size(); i++) {
        if (i > 0) {
            _stream << ',';
        }

        auto* child = node->get(i);
        child->accept(this);
    }

    _stream << ']';
}

} // namespace json
