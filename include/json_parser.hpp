#ifndef JSON_PARSER_IMPL_HPP
#define JSON_PARSER_IMPL_HPP
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>

class JSONValue {
    public: 
        using Object=std::unordered_map<std::string, JSONValue>;
        using Array=std::vector<JSONValue>;
        using ValueType=std::variant<std::nullptr_t, bool, double, std::string, Array, Object>;
    private: 
        ValueType value;

    public:
        JSONValue()                     : value(nullptr){}
        JSONValue(bool b)               : value(b){}
        JSONValue(double d)             : value(d){}
        JSONValue(const std::string& s) : value(s){}
        JSONValue(const char* c)        : value(std::string(c)){}
        JSONValue(const Array& a)       : value(a){}
        JSONValue(const Object& o)      : value(o){}
     
        bool asBool() const {
            return std::get<bool>(value);
        }

        double asNumber() const {
            return std::get<double>(value);
        }

        const std::string& asString() const {
            return std::get<std::string>(value);
        }

        const Array& asArray() const {
            return std::get<Array>(value);
        }

        const Object& asObject() const {
            return std::get<Object>(value);
        }

        JSONValue& operator[](const std::string& key){
            return std::get<Object>(value)[key];
        }

        JSONValue& operator[](size_t index) {
            return std::get<Array>(value)[index];
        }

    };
class JSONParser {
    private:
        std::string json;
        size_t index = 0;
    
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