#pragma once
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
#include <vector>
#include <iostream>

class UMLData
{
    public: 
        
        UMLData() {};

        std::vector<UMLClass> getClasses() { return classes; }
        std::vector<UMLRelationship> getRelationships() { return relationships; }

        UMLClass getClass(std::string name);
        UMLRelationship getRelationship(std::string srcName, std::string destName);

        void addClass(const UMLClass& classIn);
        void addClass(std::string name);
        void addClass(std::string name, std::vector<UMLAttribute> attributes);

     
        void addRelationship(std::string srcName, std::string destName);

        void deleteRelationship(std::string srcName, std::string destName);
        void deleteClass(std::string name);

    private:

        int findClass(std::string name);
        int findRelationship(const UMLClass& sourceClassIn, const UMLClass& destClassIn);

        void addRelationship(const UMLRelationship& relationshipIn);
        void addRelationship(const UMLClass& sourceClass, const UMLClass& destClass);

        std::vector<UMLClass> classes;
        std::vector<UMLRelationship> relationships;
};

int UMLData::findClass(std::string name)
{
    for (int i = 0; i < classes.size(); ++i)
    {
        if (classes[i].getName() == name)
        {
            return i;
        }
    }
    return -1;
}
int UMLData::findRelationship(const UMLClass& sourceClassIn, const UMLClass& destClassIn)
{
    for (int i = 0; i < relationships.size(); ++i)
    {
        //pull src and destination classes from vector location
        std::string src = relationships[i].getSource().getName();
        std::string dest = relationships[i].getDestination().getName();
        //compare
        if ((src == sourceClassIn.getName()) and (dest == destClassIn.getName()))
        {
            return i;
        }
    }
    return -1;
}

UMLClass UMLData::getClass(std::string name)
{
    int loc = findClass(name);
    if (loc < 0)
        throw "name not found";
    return classes[loc];
}

UMLRelationship UMLData::getRelationship(std::string srcName, std::string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "relationship not found";
    return relationships[loc];
}


void UMLData::addClass(const UMLClass& classIn)
{
    //check if already exists
    int loc = findClass(classIn.getName());
    if (loc > 0)
        throw "class name already exists";

    classes.push_back(classIn);
}

void UMLData::addClass(std::string name)
{
    addClass(UMLClass(name));
}

void UMLData::addClass(std::string name, std::vector<UMLAttribute> attributes)
{
    addClass(UMLClass(name, attributes));
}

void UMLData::addRelationship(const UMLRelationship& relIn)
{
    int loc = findRelationship(relIn.getSource(), relIn.getDestination());
    if (loc > 0)
        throw "relationship already exists";
    
    relationships.push_back(relIn); 
}

void UMLData::addRelationship(const UMLClass& sourceClass, const UMLClass& destClass)
{
    addRelationship(UMLRelationship(sourceClass, destClass));
}

void UMLData::addRelationship(std::string srcName, std::string destName)
{
    addRelationship(getClass(srcName), getClass(destName));
}

void UMLData::deleteClass(std::string name)
{
    int loc = findClass(name);
    if (loc < 0)
        throw "class not found";
    classes.erase(classes.begin() + loc);
}

void UMLData::deleteRelationship(std::string srcName, std::string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "relationship not found";
    relationships.erase(relationships.begin() + loc);
}
