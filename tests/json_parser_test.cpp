#include "json_parser.hpp"
#include <cassert>
#include <iostream>

int main() {
    try {
        std::cout << "Creating parser..." << std::endl;
        // Test JSON input with multiple data types
        JSONParser parser(R"({
            "name": "Alice",
            "age": 25,
            "is_student": false,
            "grade": null,
            "scores": [95, 88, 76],
            "address": { "city": "New York", "zip": 10001 }
        })");
        
        std::cout << "Parsing..." << std::endl;
        JSONValue json = parser.parse();
        
        std::cout << "Checking if JSON is an object..." << std::endl;
        assert(json.isObject());
        
        std::cout << "Checking if object has 'name'..." << std::endl;
        assert(json.asObject().count("name") > 0);
        
        std::cout << "Checking name value..." << std::endl;
        assert(json["name"].isString());
        assert(json["name"].asString() == "Alice");
        
        std::cout << "Checking age value..." << std::endl;
        assert(json["age"].isNumber());
        assert(json["age"].asNumber() == 25);
        
        std::cout << "Checking is_student value..." << std::endl;
        assert(json["is_student"].isBool());
        assert(json["is_student"].asBool() == false);
        
        std::cout << "Checking grade value..." << std::endl;
        assert(json["grade"].isNull());
        
        // Check array values
        std::cout << "Checking scores array..." << std::endl;
        assert(json["scores"].isArray());
        const auto& scores = json["scores"].asArray();
        assert(!scores.empty());
        assert(scores.size() == 3);
        assert(scores[0].isNumber());
        assert(scores[0].asNumber() == 95);
        assert(scores[1].asNumber() == 88);
        assert(scores[2].asNumber() == 76);
        
        // Check object values
        std::cout << "Checking address object..." << std::endl;
        assert(json["address"].isObject());
        const auto& address = json["address"].asObject();
        assert(address.find("city") != address.end());
        assert(address.at("city").isString());
        assert(address.at("city").asString() == "New York");
        assert(address.at("zip").isNumber());
        assert(address.at("zip").asNumber() == 10001);
        
        // Test for an invalid JSON string
        std::cout << "Testing invalid JSON..." << std::endl;
        JSONParser invalidParser(R"({ "name": "Alice", "age": 25, })");
        try {
            JSONValue invalidJson = invalidParser.parse();
            assert(false);  // If we reach here, the parser didn't throw an error
        } catch (const std::runtime_error& e) {
            std::cout << "Caught expected error: " << e.what() << std::endl;
        }
        
        // Test missing key in object
        std::cout << "Testing missing key..." << std::endl;
        const auto& missingKey = json["non_existent_key"];
        assert(missingKey.isNull());
        
        // Test parsing an empty object
        std::cout << "Testing empty object..." << std::endl;
        JSONParser emptyObjParser("{}");
        JSONValue emptyObj = emptyObjParser.parse();
        assert(emptyObj.isObject());
        assert(emptyObj.asObject().empty());
        
        // Test parsing an empty array
        std::cout << "Testing empty array..." << std::endl;
        JSONParser emptyArrParser("[]");
        JSONValue emptyArr = emptyArrParser.parse();
        assert(emptyArr.isArray());
        assert(emptyArr.asArray().empty());
        
        // Test parsing a more complex nested structure
        std::cout << "Testing nested structure..." << std::endl;
        JSONParser nestedParser(R"({
            "data": {
                "people": [
                    {
                        "name": "Bob",
                        "hobbies": ["fishing", "hiking"]
                    },
                    {
                        "name": "Carol",
                        "hobbies": ["painting", "dancing", "singing"]
                    }
                ]
            }
        })");
        JSONValue nested = nestedParser.parse();
        assert(nested["data"]["people"][0]["name"].asString() == "Bob");
        assert(nested["data"]["people"][1]["hobbies"][2].asString() == "singing");
        
        std::cout << "✅ All tests passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cout << "❌ Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}


