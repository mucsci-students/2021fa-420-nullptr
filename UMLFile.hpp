#pragma once
/*
  Filename   : UMLFile.hpp
  Description: Serves as an object for which information about a class
  in the UML diagram is stored in a JSON file. 
*/


//--------------------------------------------------------------------
// System includes
#include <vector>
#include <string>
#include <fstream>
#include "include/json/json.hpp"
#include "UMLClass.hpp"
#include "UMLData.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
using json = nlohmann::json;
//--------------------------------------------------------------------

class UMLFile
{
    private:

        json jsonFile;
        string path;

    public:

        //constructor: takes in the name of the file to save
        UMLFile(const string&);

        //saving file
        void save(const UMLData& data);

        //loads a system file and returns a UML data object
        UMLData load();  

    private:

        //takes in vector of classes and adds a json string to the jsonFile
        void addUMLClassVec(const vector<UMLClass>& umlclasses);

        //takes in vector of relationships and adds them to the jsonFile
        void addUMLRelationshipVec(const vector<UMLRelationship>& relationships);

        //gets the classes from the json file and returns classes vector
        vector<UMLClass> getUMLClassVec();
        
        //takes in UML Data object
        //gets the relationships from the json file and adds them to the UMLData object
        void getUMLRelationshipVec(UMLData& data);
};

UMLFile::UMLFile(const string& newpath)
:path(newpath)
{
}

void UMLFile::save(const UMLData& data)
{
    addUMLClassVec(data.getClasses());
    addUMLRelationshipVec(data.getRelationships());

    std::ofstream file;
    file.open(path);
    file << jsonFile;
    file.close();
}

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

void UMLFile::addUMLRelationshipVec(const vector<UMLRelationship>& relationships)
{
    for (UMLRelationship relationship : relationships)
    {
        jsonFile["Relationship"] += {{"src", relationship.getSource().getName()}, {"dest", relationship.getDestination().getName()}};
    }    
}



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

void UMLFile::getUMLRelationshipVec(UMLData& data)
{
    for (auto rel : jsonFile["Relationship"])
    {
        string dest = rel["dest"];
        string src = rel["src"];

        data.addRelationship(dest, src);

    }
}