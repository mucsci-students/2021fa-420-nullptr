#pragma once
/*
  Filename   : UMLFile.cpp
  Description: Serves as an object for which information about a class
  in the UML diagram is stored in a JSON file. 
*/


//--------------------------------------------------------------------
// System includes
#include <vector>
#include <string>
#include <json.hpp>
#include <fstream>
#include "UMLClass.hpp"
#include "UMLData.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using json = nlohmann::json;
//--------------------------------------------------------------------


class UMLFile
{
    public:
        UMLFile(const std::string&);

        //saving file
        void save(const UMLData& data);

        //loading file
        UMLData load();

    private:
        void addUMLClassVec(const std::vector<UMLClass>& umlclasses);
        void addUMLRelationshipVec(const std::vector<UMLRelationship>& relationships);
        std::vector<UMLClass> getUMLClassVec();
        void getUMLRelationshipVec(UMLData& data);

        json jsonFile;
        std::string path;
};

//constructor: takes in the name of the file to save
UMLFile::UMLFile(const std::string& path) 
{
    this->path = path;
}

//takes in vector of classes and adds a json string to the jsonFile
void UMLFile::addUMLClassVec(const std::vector<UMLClass>& classes)
{
    for (UMLClass umlclass : classes)
    {
        json jsonattr;
        for (UMLAttribute attribute : umlclass.getAttributes())
        {
            jsonattr += {{"name", attribute.getAttributeName()}};
        }

        jsonFile["Class"] += {{"name", umlclass.getName()}, {"Attributes", jsonattr}};
    }    
}

//takes in vector of relationships and adds them to the jsonFile
void UMLFile::addUMLRelationshipVec(const std::vector<UMLRelationship>& relationships)
{
    for (UMLRelationship relationship : relationships)
    {
        jsonFile["Relationship"] += {{"src", relationship.getSource().getName()}, {"dest", relationship.getDestination().getName()}};
    }    
}

//saves the jsonFile to an actual system file
void UMLFile::save(const UMLData& data)
{
    addUMLClassVec(data.getClasses());
    addUMLRelationshipVec(data.getRelationships());

    std::ofstream file;
    file.open(path);
    file << jsonFile;
    file.close();
}

//loads a system file and returns a UML data object
UMLData UMLFile::load() 
{
    std::ifstream file; 
    file.open(path);
    file >> jsonFile;
    file.close(); 

    UMLData data(getUMLClassVec());
    getUMLRelationshipVec(data);

    return data;
}

//gets the classes from the json file and returns their vector
std::vector<UMLClass> UMLFile::getUMLClassVec()
{
    std::vector<UMLClass> classVec;
    for (auto member : jsonFile["Class"])
    {
        std::string name = member["name"];
        std::vector<UMLAttribute> attrVec;
        for (auto attributes : member["Attributes"])
        {
            attrVec.push_back({attributes["name"]});
        }
        classVec.push_back({name, attrVec});
    }
    return classVec;
}

//takes in UML Data object
//gets the relationships from the json file and adds them to the UMLData object
void UMLFile::getUMLRelationshipVec(UMLData& data)
{
    for (auto rel : jsonFile["Relationship"])
    {
        std::string dest = rel["dest"];
        std::string src = rel["src"];

        data.addRelationship(dest, src);

    }
}