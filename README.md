# JSONParser

A simple and efficient C++ JSON parser that supports parsing JSON strings, numbers, booleans, null values, arrays, and objects. This project demonstrates how to build a JSON parser and is an excellent way to learn about handling JSON data in C++.

## Features

Parse strings, numbers, booleans, null values, arrays, and objects.
Supports nested objects and arrays.
Provides an easy-to-use API for accessing parsed JSON values.

## Table of Contents

TODO:ADD LINKS to doc here
Features
Getting Started
Prerequisites
Building
Running Tests
Usage
Contributing
License

### Getting Started

These instructions will guide you through setting up and running the JSON parser project on your local machine.
Prerequisites

Make sure you have the following installed:

    CMake (version 3.10 or higher)
    A C++17 compatible compiler (e.g., GCC, Clang, MSVC)

### Building

Clone this repository:

TODO:MAKE A REPO Change this

```
bash
git clone https://github.com/joelcrouch/JSONParser.git
cd JSONParser
```

Create a build directory and run cmake to generate Makefiles:

    bash
    mkdir build
    cd build
    cmake ..

Build the project:

    bash
    make

### Running Tests

After building the project, you can run the unit tests to check if everything is working correctly.

```
bash

./json_parser_tests

```

with output: ✅ All tests passed!

## Usage

Here’s how to use the JSONParser class to parse a JSON string:

### Example: Parsing JSON

```
c++
#include "json_parser.hpp"
#include <iostream>

int main() {
    JSONParser parser(R"({ "name": "Alice", "age": 25 })");
    JSONValue json = parser.parse();

    std::cout << "Name: " << json["name"].asString() << std::endl;
    std::cout << "Age: " << json["age"].asNumber() << std::endl;

    return 0;
}


```

### Example: Handling Arrays and Objects

```
cpp
#include "json_parser.hpp"
#include <iostream>

int main() {
    JSONParser parser(R"({
        "scores": [95, 88, 76],
        "address": { "city": "New York", "zip": 10001 }
    })");
    JSONValue json = parser.parse();

    // Accessing array elements
    const auto& scores = json["scores"].asArray();
    std::cout << "First score: " << scores[0].asNumber() << std::endl;

    // Accessing object values
    const auto& address = json["address"].asObject();
    std::cout << "City: " << address.at("city").asString() << std::endl;

    return 0;
}

```

### Example #3:
ToDO Maybe:  Modify CMakeLists.txt to install library:
```
# Add to  original CMakeLists.txt
install(TARGETS json_parser DESTINATION lib)
install(FILES json_parser.hpp DESTINATION include)

```
Rebuild and install using the '.sh' or '.ps1' files, bash or powershell.
In teh project add '#include <json_parser.hpp>'
and 
g++ =std=c++17 main.pp -ljson_parser -o my_program



#include "json_parser.hpp"
#include <iostream>
#include <fstream>

int main() {
    // Read JSON from a file
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    
    std::string jsonContent((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
    file.close();
    
    try {
        // Parse the JSON
        JSONParser parser(jsonContent);
        JSONValue config = parser.parse();
        
        // Use the parsed configuration
        std::string serverAddress = config["server"]["address"].asString();
        int port = static_cast<int>(config["server"]["port"].asNumber());
        
        // Access an array
        const auto& allowedUsers = config["allowedUsers"].asArray();
        for (const auto& user : allowedUsers) {
            std::cout << "User: " << user.asString() << std::endl;
        }
        
        // Create or modify JSON data
        JSONValue response;
        response["status"] = "success";
        response["timestamp"] = 1647267892;
        
        // You could add array manipulation
        JSONValue::Array dataPoints;
        for (int i = 0; i < 5; i++) {
            JSONValue point;
            point["x"] = i;
            point["y"] = i * i;
            dataPoints.push_back(point);
        }
        response["data"] = dataPoints;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

TODO:  JSON serialization: json object to string

## Contributing

## License
