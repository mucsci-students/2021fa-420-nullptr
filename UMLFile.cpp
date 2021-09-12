#include "UMLFile.hpp"
#include <iostream>
#include <fstream>

UMLFile::UMLFile(const std::string& path) 
{
    this->path = path;
}

void UMLFile::addUMLClassVec(const std::vector<UMLClass>& umlclasses)
{
    for (UMLClass umlclass : umlclasses)
    {
        json jsonattr;
        for (UMLAttribute attribute : umlclass.attributes)
        {
            jsonattr += {{"name", attribute.name}};
        }

        data["Class"] += {{"name", umlclass.name}, {"Attributes", jsonattr}};
    }    
}

void UMLFile::save()
{
    std::ofstream file;
    file.open(path);
    file << data;
    file.close();
}

void UMLFile::load() 
{
    std::ifstream file; 
    file.open(path);
    file >> data;
    file.close(); 
}

std::vector<UMLClass> UMLFile::getUMLClassVec()
{
    std::vector<UMLClass> classVec;
    for (auto member : data["Class"])
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