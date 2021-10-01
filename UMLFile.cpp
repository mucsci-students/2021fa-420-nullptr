/*
  Filename   : UMLFile.cpp
  Description: Implementation of a file.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLFile.hpp"
//--------------------------------------------------------------------

// constructor: takes in the name of the file to save
UMLFile::UMLFile(const string& newpath)
:path(newpath)
{
}

// saving file
void UMLFile::save(const UMLData& data)
{
    addUMLClassVec(data.getClasses());
    addUMLRelationshipVec(data.getRelationships());

    std::ofstream file;
    file.open(path);
    file << jsonFile;
    file.close();
}

// loads a system file and returns a UML data object
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

// takes in vector of classes and adds a json string to the jsonFile
void UMLFile::addUMLClassVec(const vector<UMLClass>& classes)
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

// takes in vector of relationships and adds them to the jsonFile
void UMLFile::addUMLRelationshipVec(const vector<UMLRelationship>& relationships)
{
    for (UMLRelationship relationship : relationships)
    {
        jsonFile["Relationship"] += {{"src", relationship.getSource().getName()}, {"dest", relationship.getDestination().getName()}};
    }    
}

// gets the classes from the json file and returns classes vector
vector<UMLClass> UMLFile::getUMLClassVec()
{
    vector<UMLClass> classVec;
    for (auto member : jsonFile["Class"])
    {
        string name = member["name"];
        vector<UMLAttribute> attrVec;
        for (auto attributes : member["Attributes"])
        {
            attrVec.push_back({attributes["name"]});
        }
        classVec.push_back({name, attrVec});
    }
    return classVec;
}

// gets the relationships from the json file and adds them to the UMLData object
void UMLFile::getUMLRelationshipVec(UMLData& data)
{
    for (auto rel : jsonFile["Relationship"])
    {
        string dest = rel["dest"];
        string src = rel["src"];

        data.addRelationship(dest, src);

    }
}