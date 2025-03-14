#ifndef JSON_PARSER_IMPL_HPP
#define JSON_PARSER_IMPL_HPP
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>
 
class JSONValue {
    public:
        using Object = std::unordered_map<std::string, JSONValue>;
        using Array = std::vector<JSONValue>;
        using ValueType = std::variant<std::nullptr_t, bool, double, std::string, Array, Object>;
    
    private:
        ValueType value;
    
    public:
        JSONValue() : value(nullptr) {}
        JSONValue(std::nullptr_t) : value(nullptr) {}
        JSONValue(bool b) : value(b) {}
        JSONValue(double d) : value(d) {}
        JSONValue(int i) : value(double(i)) {}
        JSONValue(const std::string& s) : value(s) {}
        JSONValue(const char* c) : value(std::string(c)) {}
        JSONValue(const Array& a) : value(a) {}
        JSONValue(const Object& o) : value(o) {}
    
        bool isNull() const { return std::holds_alternative<std::nullptr_t>(value); }
        bool isBool() const { return std::holds_alternative<bool>(value); }
        bool isNumber() const { return std::holds_alternative<double>(value); }
        bool isString() const { return std::holds_alternative<std::string>(value); }
        bool isArray() const { return std::holds_alternative<Array>(value); }
        bool isObject() const { return std::holds_alternative<Object>(value); }
    
        bool asBool() const {
            if (!isBool()) throw std::runtime_error("JSONValue is not a boolean");
            return std::get<bool>(value);
        }
    
        double asNumber() const {
            if (!isNumber()) throw std::runtime_error("JSONValue is not a number");
            return std::get<double>(value);
        }
    
        const std::string& asString() const {
            if (!isString()) throw std::runtime_error("JSONValue is not a string");
            return std::get<std::string>(value);
        }
    
        const Array& asArray() const {
            if (!isArray()) throw std::runtime_error("JSONValue is not an array");
            return std::get<Array>(value);
        }
    
        Array& asArray() {
            if (!isArray()) throw std::runtime_error("JSONValue is not an array");
            return std::get<Array>(value);
        }
    
        const Object& asObject() const {
            if (!isObject()) throw std::runtime_error("JSONValue is not an object");
            return std::get<Object>(value);
        }
    
        Object& asObject() {
            if (!isObject()) throw std::runtime_error("JSONValue is not an object");
            return std::get<Object>(value);
        }
    
        const JSONValue& operator[](const std::string& key) const {
            if (!isObject()) throw std::runtime_error("JSONValue is not an object");
            const auto& obj = std::get<Object>(value);
            auto it = obj.find(key);
            static const JSONValue nullValue;
            return (it != obj.end()) ? it->second : nullValue;
        }
    
        JSONValue& operator[](const std::string& key) {
            if (!isObject()) {
                value = Object();
            }
            return std::get<Object>(value)[key];
        }
    
        const JSONValue& operator[](size_t index) const {
            if (!isArray()) throw std::runtime_error("JSONValue is not an array");
            const auto& arr = std::get<Array>(value);
            if (index >= arr.size()) throw std::runtime_error("Array index out of bounds");
            return arr[index];
        }
    
        JSONValue& operator[](size_t index) {
            if (!isArray()) {
                value = Array();
            }
            auto& arr = std::get<Array>(value);
            if (index >= arr.size()) {
                arr.resize(index + 1);
            }
            return arr[index];
        }
    };
    class JSONParser {
        private:
            std::string json;
            size_t index = 0;
           
            bool isEnd() const;  // Add this new method
            char peek() const;
            char advance();
            void skipWhitespace();
            JSONValue parseValue();
            JSONValue parseObject();
            JSONValue parseArray();
            JSONValue parseString();
            JSONValue parseNumber();
            JSONValue parseBoolOrNull();
           
        public:
            JSONParser(const std::string& jsonString);
            JSONValue parse();
        };
        #endif 