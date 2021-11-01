/*
  Filename   : UMLFile.cpp
  Description: Implementation of a file.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLFile.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "include/UMLRelationship.hpp"
#include "include/UMLField.hpp"

#include <memory>
#include <filesystem>
//--------------------------------------------------------------------

// Constructor: takes in the name of the file to save
UMLFile::UMLFile(const string& newpath)
:path(newpath)
{
}

// Saves information from UML diagram to JSON
void UMLFile::save(UMLData& data)
{
    json j = data.getJson();

    std::ofstream file;
    file.open(path);
    file << j.dump(2);
    file.close();
}

// Loads a system file and returns a UML data object
UMLData UMLFile::load() 
{
    std::ifstream file; 
    file.open(path);
    json j;
    file >> j;
    file.close(); 

    UMLData data;
    addClasses(data, j);
    addRelationships(data, j);

    return data;
}

// Gets the relationships from the json file and adds them to the UMLData object
void UMLFile::addClasses(UMLData& data, const json& j)
{
    for (auto umlclass : j["classes"])
    {
        std::string className = umlclass["name"];
        data.addClass(className);

        //set x and y for gui
        data.getClass(className).setX(umlclass["position_x"]);
        data.getClass(className).setY(umlclass["position_y"]);

        for (auto field : umlclass["fields"])
        {
            data.addClassAttribute(className, std::make_shared<UMLField>(field["name"], field["type"]));
        }
        for (auto method : umlclass["methods"])
        {
            std::list<UMLParameter> params;
            for (auto param : method["params"])
                params.push_back(UMLParameter(param["name"], param["type"]));

            data.addClassAttribute(className, std::make_shared<UMLMethod>(method["name"], method["return_type"], params));
        }
    }
}

// Gets the relationships from the json file and adds them to the UMLData object
void UMLFile::addRelationships(UMLData& data, const json& j)
{
    for (auto relationship : j["relationships"])
    {
        data.addRelationship(relationship["source"], 
        relationship["destination"], 
        UMLRelationship::string_to_type(relationship["type"]));
    }
}

// Makes a list of all JSON files in the build directory that can be used for loading.
json UMLFile::listSaves()
{
    json files = json::array();
    for (const auto & entry : std::filesystem::directory_iterator("."))
    {
        if (entry.path().string().find("json") != std::string::npos && entry.path().string().find("compile_commands") == std::string::npos)
        {
            std::string path = entry.path().string();
            path = path.substr(2, std::string::npos);
            path = path.substr(0, path.find(".json"));
            files += path;
        }
            
    }
    return files;
}

