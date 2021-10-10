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
//--------------------------------------------------------------------

// constructor: takes in the name of the file to save
UMLFile::UMLFile(const string& newpath)
:path(newpath)
{
}

// saving file
void UMLFile::save(UMLData& data)
{
    json j = data.getJson();

    std::ofstream file;
    file.open(path);
    file << j.dump(2);
    file.close();
}

// loads a system file and returns a UML data object
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

// gets the relationships from the json file and adds them to the UMLData object
void UMLFile::addClasses(UMLData& data, const json& j)
{
    for (auto umlclass : j["classes"])
    {
        std::string className = umlclass["name"];
        data.addClass(className);

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

// gets the relationships from the json file and adds them to the UMLData object
void UMLFile::addRelationships(UMLData& data, const json& j)
{
    for (auto relationship : j["relationships"])
    {
        data.addRelationship(relationship["source"], 
        relationship["destination"], 
        UMLRelationship::string_to_type(relationship["type"]));
    }
}

