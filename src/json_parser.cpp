#include "json_parser.hpp"
#include <cctype>
#include <stdexcept>

// Constructor
JSONParser::JSONParser(const std::string& jsonString) : json(jsonString) {}

// Peeks at the current character
char JSONParser::peek() const { return json[index]; }

// Advances to the next character
char JSONParser::advance() { return json[index++]; }

// Skips whitespace characters
void JSONParser::skipWhitespace() { while (std::isspace(peek())) advance(); }

// Parses a generic JSON value
JSONValue JSONParser::parseValue() {
    skipWhitespace();
    char ch = peek();

    if (ch == '{') return parseObject();
    if (ch == '[') return parseArray();
    if (ch == '"') return parseString();
    if (std::isdigit(ch) || ch == '-') return parseNumber();
    if (std::isalpha(ch)) return parseBoolOrNull();

    throw std::runtime_error("Invalid JSON value");
}

// Parses a JSON object { "key": value }
JSONValue JSONParser::parseObject() {
    JSONValue::Object obj;
    advance(); // Consume '{'
    skipWhitespace();

    while (peek() != '}') {
        JSONValue key = parseString();
        skipWhitespace();
        if (advance() != ':') throw std::runtime_error("Expected ':' after key");
        skipWhitespace();
        obj[key.asString()] = parseValue();
        skipWhitespace();
        if (peek() == ',') advance(); // Consume ',' and continue
        skipWhitespace();
    }

    advance(); // Consume '}'
    return obj;
}

// Parses a JSON array [value1, value2, ...]
JSONValue JSONParser::parseArray() {
    JSONValue::Array arr;
    advance(); // Consume '['
    skipWhitespace();

    while (peek() != ']') {
        arr.push_back(parseValue());
        skipWhitespace();
        if (peek() == ',') advance(); // Consume ',' and continue
        skipWhitespace();
    }

    advance(); // Consume ']'
    return arr;
}

// Parses a JSON string
JSONValue JSONParser::parseString() {
    advance(); // Consume '"'
    std::string str;
    while (peek() != '"') {
        str += advance();
    }
    advance(); // Consume closing '"'
    return str;
}

// Parses a JSON number
JSONValue JSONParser::parseNumber() {
    std::string numStr;
    while (std::isdigit(peek()) || peek() == '.' || peek() == '-') {
        numStr += advance();
    }
    return std::stod(numStr);
}

// Parses true, false, or null
JSONValue JSONParser::parseBoolOrNull() {
    std::string word;
    while (std::isalpha(peek())) {
        word += advance();
    }

    if (word == "true") return true;
    if (word == "false") return false;
    if (word == "null") return nullptr;

    throw std::runtime_error("Invalid JSON keyword");
}

// Starts parsing from the beginning
JSONValue JSONParser::parse() {
    index = 0;
    skipWhitespace();
    return parseValue();
}
