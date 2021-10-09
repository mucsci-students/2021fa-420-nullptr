/*
  Filename   : UMLFile.cpp
  Description: Implementation of a file.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLFile.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLRelationship.hpp"
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

void UMLFile::addClasses(UMLData& data, const json& j)
{
    for (auto umlclass : j["classes"])
    {
        std::string className = umlclass["name"];
        data.addClass(className);
        //change for fields and methods
        for (auto attribute : umlclass["attributes"])
        {
            UMLAttribute attr(attribute["name"]);
            data.addClassAttribute(className, attr);
        }
    }
}

void UMLFile::addRelationships(UMLData& data, const json& j)
{
    for (auto relationship : j["relationships"])
    {
        data.addRelationship(relationship["source"], 
        relationship["destination"], 
        UMLRelationship::string_to_type(relationship["type"]));
    }
}