#include "json_parser.h"

#include <sstream>

#include "json_token_reader.h"

#include "json_array.h"
#include "json_boolean.h"
#include "json_number.h"
#include "json_object.h"
#include "json_string.h"
#include "json_value.h"
#include "json_null.h"

namespace {

bool IsEscapeCharacter(char c) {
    return (c == '\"') || (c == '\\') || (c == '/') ||
        (c == 'b') || (c == 'f') || (c == 'n') ||
        (c == 'r') || (c == 't');
}

bool IsDecimal(char c) {
    return c >= '0' && c <= '9';
}

bool IsHexaDecimal(char c) {
    return (c == 'A') || (c == 'a') ||
        (c == 'B') || (c == 'b') ||
        (c == 'C') || (c == 'c') ||
        (c == 'D') || (c == 'd') ||
        (c == 'E') || (c == 'e') ||
        (c == 'F') || (c == 'f') ||
        IsDecimal(c);
}

} // namespace

namespace json {

namespace __internal {

JsonValue* JsonParser::parse(const std::string& raw_json) {
    JsonTokenReader reader(raw_json);
    JsonValue* value = this->value(reader);

    if (reader.hasNext()) {
        if (value) {
            delete value;
        }

        return nullptr;
    }

    return value;
}

// objects
JsonObject* JsonParser::object(JsonTokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('{')) {
        reader.restore(token);
        return nullptr;
    }

    JsonObject* object = new JsonObject();

    whitespace(reader);

    JsonString* key = string(reader);
    if (key) {
        std::string raw_key(key->value());
        delete key;

        whitespace(reader);

        if (!reader.consume(':')) {
            delete object;
            reader.restore(token);
            return nullptr;
        }

        JsonValue* value = this->value(reader);
        if (!value) {
            delete object;
            reader.restore(token);
            return nullptr;
        }

        object->put(raw_key, value);

        while (reader.consume(',')) {
            JsonString* key = string(reader);
            if (!key) {
                delete object;
                reader.restore(token);
                return nullptr;
            }

            std::string raw_key(key->value());
            delete key;

            whitespace(reader);

            if (!reader.consume(':')) {
                delete object;
                reader.restore(token);
                return nullptr;
            }

            JsonValue* value = this->value(reader);
            if (!value) {
                delete object;
                reader.restore(token);
                return nullptr;
            }

            object->put(raw_key, value);
        }
    }

    if (!reader.consume('}')) {
        delete object;
        reader.restore(token);
        return nullptr;
    }

    return object;
}

JsonArray* JsonParser::array(JsonTokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('[')) {
        reader.restore(token);
        return nullptr;
    }

    JsonArray* array = new JsonArray();

    JsonValue* value = this->value(reader);
    if (value) {
        array->add(value);

        while (reader.consume(',')) {
            value = this->value(reader);

            if (!value) {
                // No value after coma.
                delete array;
                reader.restore(token);
                return nullptr;
            }

            array->add(value);
        }
    }

    whitespace(reader);

    if (!reader.consume(']')) {
        delete array;
        reader.restore(token);
        return nullptr;
    }

    return array;
}

// base
JsonValue* JsonParser::value(JsonTokenReader& reader) {
    auto token = reader.save();

    JsonValue* value = nullptr;
    whitespace(reader);

    value = string(reader);

    if (!value) {
        value = number(reader);
    }

    if (!value) {
        value = object(reader);
    }

    if (!value) {
        value = array(reader);
    }

    if (!value) {
        value = boolean(reader);
    }

    if (!value) {
        value = null(reader);
    }

    whitespace(reader);

    if (!value) {
        reader.restore(token);
        return nullptr;
    }

    return value;
}

// primitives
JsonString* JsonParser::string(JsonTokenReader& reader) {
    auto token = reader.save();

    if (!reader.consume('\"')) {
        return nullptr;
    }

    std::stringstream sstream;

    while (reader.hasNext() && reader.peek() != '\"') {
        char c = reader.next();
        sstream << c;

        if (c == '\\') {
            // Control character flow.

            if (!reader.hasNext()) {
                reader.restore(token);
                return nullptr;
            }

            char control_character = reader.next();
            sstream << control_character;

            if (control_character == 'u') {
                // 4 hex digits should follow

                for (size_t i = 0; i < 4; i++) {
                    if (!reader.hasNext() || !IsHexaDecimal(reader.peek())) {
                        reader.restore(token);
                        return nullptr;
                    }

                    sstream << reader.next();
                }
            } else if (!IsEscapeCharacter(control_character)) {
                // Neither a control character nor hexadecimal number.
                reader.restore(token);
                return nullptr;
            }
        }
    }

    if (reader.consume('\"')) {
        return new JsonString(sstream.str());
    }

    reader.restore(token);
    return nullptr;
}

JsonNumber* JsonParser::number(JsonTokenReader& reader) {
    auto token = reader.save();

    std::stringstream sstream;

    if (reader.peek() == '-') {
        sstream << reader.next();
    }

    if (IsDecimal(reader.peek())) {
        bool isZero = (reader.peek() == '0');
        sstream << reader.next();

        if (!isZero) {
            // Digit 1-9 (as number should not have leading zeros)
            while (IsDecimal(reader.peek())) {
                sstream << reader.next();
            }
        }
    } else {
        // Not a decimal.
        reader.restore(token);
        return nullptr;
    }

    if (reader.peek() == '.') {
        // Fraction part.
        sstream << reader.next();

        if (!IsDecimal(reader.peek())) {
            // Not a decimal after fraction.
            reader.restore(token);
            return nullptr;
        }

        while (IsDecimal(reader.peek())) {
            sstream << reader.next();
        }
    }

    if (reader.peek() == 'e' || reader.peek() == 'E') {
        // Exponent part.
        sstream << reader.next();

        if (reader.peek() == '-' || reader.peek() == '+') {
            sstream << reader.next();
        }

        if (!IsDecimal(reader.peek())) {
            // Not a decimal after exponent.
            reader.restore(token);
            return nullptr;
        }

        while (IsDecimal(reader.peek())) {
            sstream << reader.next();
        }
    }

    return new JsonNumber(std::stod(sstream.str()));
}

JsonBoolean* JsonParser::boolean(JsonTokenReader& reader) {
    auto token = reader.save();

    if (reader.consume('t') && reader.consume('r') && reader.consume('u') && reader.consume('e')) {
        return new JsonBoolean(true);
    } else {
        reader.restore(token);
    }

    if (reader.consume('f') && reader.consume('a') && reader.consume('l') && reader.consume('s') && reader.consume('e')) {
        return new JsonBoolean(false);
    } else {
        reader.restore(token);
    }

    return nullptr;
}

JsonNull* JsonParser::null(JsonTokenReader& reader) {
    auto token = reader.save();

    if (reader.consume('n') && reader.consume('u') && reader.consume('l') && reader.consume('l')) {
        return JsonNull::VALUE;
    } else {
        reader.restore(token);
    }
}

// misc
void JsonParser::whitespace(JsonTokenReader& reader) {
    // In terms of JSON specification
    // spaces are: space, linefeed (aka new line),
    // carriage return, and horizontal tab.
    while (reader.consume(' ') || reader.consume('\n') || reader.consume('\t') || reader.consume('\r')) {
    }
}

} // namespace internal

} // namespace json
