#include "json_parser.hpp"
#include <cctype>
#include <stdexcept>

// Constructor
JSONParser::JSONParser(const std::string& jsonString) : json(jsonString), index(0) {}

// Checks if we've reached the end of input
bool JSONParser::isEnd() const {
    return index >= json.length();
}

// Peeks at the current character
char JSONParser::peek() const {
    if (isEnd()) throw std::runtime_error("Unexpected end of input");
    return json[index];
}

// Advances to the next character
char JSONParser::advance() {
    if (isEnd()) throw std::runtime_error("Unexpected end of input");
    return json[index++];
}

// Skips whitespace characters
void JSONParser::skipWhitespace() {
    while (!isEnd() && std::isspace(peek())) advance();
}

// Parses a generic JSON value
JSONValue JSONParser::parseValue() {
    skipWhitespace();
    if (isEnd()) throw std::runtime_error("Unexpected end of input");
    
    char ch = peek();
    if (ch == '{') return parseObject();
    if (ch == '[') return parseArray();
    if (ch == '"') return parseString();
    if (std::isdigit(ch) || ch == '-') return parseNumber();
    if (ch == 't' || ch == 'f' || ch == 'n') return parseBoolOrNull();
    
    throw std::runtime_error("Invalid JSON value");
}

// Parses a JSON object { "key": value }
JSONValue JSONParser::parseObject() {
    JSONValue::Object obj;
    advance(); // Consume '{'
    skipWhitespace();
    
    if (peek() == '}') {
        advance(); // Empty object
        return obj;
    }
    
    while (true) {
        if (peek() != '"') throw std::runtime_error("Expected string key in object");
        
        JSONValue key = parseString();
        skipWhitespace();
        
        if (advance() != ':') throw std::runtime_error("Expected ':' after key");
        skipWhitespace();
        
        obj[key.asString()] = parseValue();
        skipWhitespace();
        
        if (peek() == '}') {
            advance(); // Consume '}'
            break;
        }
        
        if (peek() != ',') throw std::runtime_error("Expected ',' or '}' after value in object");
        advance(); // Consume ','
        skipWhitespace();
    }
    
    return obj;
}

// Parses a JSON array [value1, value2, ...]
JSONValue JSONParser::parseArray() {
    JSONValue::Array arr;
    advance(); // Consume '['
    skipWhitespace();
    
    if (peek() == ']') {
        advance(); // Empty array
        return arr;
    }
    
    while (true) {
        arr.push_back(parseValue());
        skipWhitespace();
        
        if (peek() == ']') {
            advance(); // Consume ']'
            break;
        }
        
        if (peek() != ',') throw std::runtime_error("Expected ',' or ']' after value in array");
        advance(); // Consume ','
        skipWhitespace();
    }
    
    return arr;
}

// Parses a JSON string
JSONValue JSONParser::parseString() {
    advance(); // Consume '"'
    std::string str;
    
    while (!isEnd() && peek() != '"') {
        char ch = advance();
        
        if (ch == '\\') {
            if (isEnd()) throw std::runtime_error("Unterminated escape sequence");
            
            ch = advance();
            switch (ch) {
                case '"': case '\\': case '/':
                    str += ch;
                    break;
                case 'b': str += '\b'; break;
                case 'f': str += '\f'; break;
                case 'n': str += '\n'; break;
                case 'r': str += '\r'; break;
                case 't': str += '\t'; break;
                default:
                    throw std::runtime_error("Invalid escape sequence");
            }
        } else {
            str += ch;
        }
    }
    
    if (isEnd()) throw std::runtime_error("Unterminated string");
    advance(); // Consume closing '"'
    
    return str;
}

// Parses a JSON number
JSONValue JSONParser::parseNumber() {
    std::string numStr;
    
    // Handle negative numbers
    if (peek() == '-') {
        numStr += advance();
    }
    
    // Integer part
    if (!std::isdigit(peek())) throw std::runtime_error("Expected digit");
    while (!isEnd() && std::isdigit(peek())) {
        numStr += advance();
    }
    
    // Fractional part
    if (!isEnd() && peek() == '.') {
        numStr += advance();
        if (!std::isdigit(peek())) throw std::runtime_error("Expected digit after decimal point");
        while (!isEnd() && std::isdigit(peek())) {
            numStr += advance();
        }
    }
    
    // Exponent part
    if (!isEnd() && (peek() == 'e' || peek() == 'E')) {
        numStr += advance();
        if (!isEnd() && (peek() == '+' || peek() == '-')) {
            numStr += advance();
        }
        if (!isEnd() && !std::isdigit(peek())) throw std::runtime_error("Expected digit in exponent");
        while (!isEnd() && std::isdigit(peek())) {
            numStr += advance();
        }
    }
    
    return std::stod(numStr);
}

// Parses true, false, or null
JSONValue JSONParser::parseBoolOrNull() {
    if (json.length() - index >= 4 && json.substr(index, 4) == "true") {
        index += 4;
        return true;
    }
    if (json.length() - index >= 5 && json.substr(index, 5) == "false") {
        index += 5;
        return false;
    }
    if (json.length() - index >= 4 && json.substr(index, 4) == "null") {
        index += 4;
        return nullptr;
    }
    
    throw std::runtime_error("Invalid JSON keyword");
}

// Starts parsing from the beginning
JSONValue JSONParser::parse() {
    index = 0;
    skipWhitespace();
    JSONValue result = parseValue();
    skipWhitespace();
    
    if (!isEnd()) {
        throw std::runtime_error("Unexpected data after JSON value");
    }
    
    return result;
}

// #include "json_parser.hpp"
// #include <cctype>
// #include <stdexcept>

// // Constructor
// JSONParser::JSONParser(const std::string& jsonString) : json(jsonString) {}

// // Peeks at the current character
// char JSONParser::peek() const { return json[index]; }

// // Advances to the next character
// char JSONParser::advance() { return json[index++]; }

// // Skips whitespace characters
// void JSONParser::skipWhitespace() { while (std::isspace(peek())) advance(); }

// // Parses a generic JSON value
// JSONValue JSONParser::parseValue() {
//     skipWhitespace();
//     char ch = peek();

//     if (ch == '{') return parseObject();
//     if (ch == '[') return parseArray();
//     if (ch == '"') return parseString();
//     if (std::isdigit(ch) || ch == '-') return parseNumber();
//     if (std::isalpha(ch)) return parseBoolOrNull();

//     throw std::runtime_error("Invalid JSON value");
// }

// // Parses a JSON object { "key": value }
// JSONValue JSONParser::parseObject() {
//     JSONValue::Object obj;
//     advance(); // Consume '{'
//     skipWhitespace();

//     while (peek() != '}') {
//         JSONValue key = parseString();
//         skipWhitespace();
//         if (advance() != ':') throw std::runtime_error("Expected ':' after key");
//         skipWhitespace();
//         obj[key.asString()] = parseValue();
//         skipWhitespace();
//         if (peek() == ',') advance(); // Consume ',' and continue
//         skipWhitespace();
//     }

//     advance(); // Consume '}'
//     return obj;
// }

// // Parses a JSON array [value1, value2, ...]
// JSONValue JSONParser::parseArray() {
//     JSONValue::Array arr;
//     advance(); // Consume '['
//     skipWhitespace();

//     while (peek() != ']') {
//         arr.push_back(parseValue());
//         skipWhitespace();
//         if (peek() == ',') advance(); // Consume ',' and continue
//         skipWhitespace();
//     }

//     advance(); // Consume ']'
//     return arr;
// }

// // Parses a JSON string
// JSONValue JSONParser::parseString() {
//     advance(); // Consume '"'
//     std::string str;
//     while (peek() != '"') {
//         str += advance();
//     }
//     advance(); // Consume closing '"'
//     return str;
// }

// // Parses a JSON number
// JSONValue JSONParser::parseNumber() {
//     std::string numStr;
//     while (std::isdigit(peek()) || peek() == '.' || peek() == '-') {
//         numStr += advance();
//     }
//     return std::stod(numStr);
// }

// // Parses true, false, or null
// JSONValue JSONParser::parseBoolOrNull() {
//     std::string word;
//     while (std::isalpha(peek())) {
//         word += advance();
//     }

//     if (word == "true") return true;
//     if (word == "false") return false;
//     if (word == "null") return nullptr;

//     throw std::runtime_error("Invalid JSON keyword");
// }

// // Starts parsing from the beginning
// JSONValue JSONParser::parse() {
//     index = 0;
//     skipWhitespace();
//     return parseValue();
// }
