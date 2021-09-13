#pragma once
/*
  Filename   : UMLData.cpp
  Description: Stores the Relationship and Class information of the current state 
*/
//--------------------------------------------------------------------
// System includes
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
#include <vector>
#include <iostream>
//--------------------------------------------------------------------


class UMLData
{
    public: 
        
        UMLData() {};

        //constructor takes in vector of classes
        UMLData(const std::vector<UMLClass>& vclass)
        {
            classes = vclass;
        }

        std::vector<UMLClass> getClasses() const { return classes; }
        std::vector<UMLRelationship> getRelationships() const { return relationships; }

        void addClass(const UMLClass& classIn);
        void addClass(std::string name);
        void addClass(std::string name, std::vector<UMLAttribute> attributes);

     
        void addRelationship(std::string srcName, std::string destName);

        std::vector<UMLRelationship> getRelationshipsByClass(std::string className);

        void deleteRelationship(std::string srcName, std::string destName);
        void deleteClass(std::string name);

        void changeClassName(std::string oldName, std::string newName);
        void addClassAttribute(std::string className, UMLAttribute attribute);
        void removeClassAttriubte(std::string className, std::string attributeName);

        

    private:

        int findClass(std::string name);
        int findRelationship(const UMLClass& sourceClassIn, const UMLClass& destClassIn);

        UMLClass& getClass(std::string name);
        UMLRelationship& getRelationship(std::string srcName, std::string destName);

        void addRelationship(const UMLRelationship& relationshipIn);
        void addRelationship(const UMLClass& sourceClass, const UMLClass& destClass);

        std::vector<UMLClass> classes;
        std::vector<UMLRelationship> relationships;
};

//takes in a class name and then returns the index within classes vector
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
//takes in source and dest class and returns index within relationship vector
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
//takes in name string and returns class object
UMLClass& UMLData::getClass(std::string name)
{
    int loc = findClass(name);
    if (loc < 0)
        throw "name not found";
    return classes[loc];
}
//takes in src string and dest string and returns relationship object
UMLRelationship& UMLData::getRelationship(std::string srcName, std::string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "relationship not found";
    return relationships[loc];
}

//takes in class and adds it to classes vector
void UMLData::addClass(const UMLClass& classIn)
{
    //check if already exists
    int loc = findClass(classIn.getName());
    if (loc > 0)
        throw "class name already exists";

    classes.push_back(classIn);
}

//takes in string name and creates class and adds to classes vector
void UMLData::addClass(std::string name)
{
    addClass(UMLClass(name));
}

//takes in string name and vector attributes creates umlclass and adds to vector
void UMLData::addClass(std::string name, std::vector<UMLAttribute> attributes)
{
    addClass(UMLClass(name, attributes));
}

//adds relationship to relationships vector
void UMLData::addRelationship(const UMLRelationship& relIn)
{
    int loc = findRelationship(relIn.getSource(), relIn.getDestination());
    if (loc > 0)
        throw "relationship already exists";
    
    relationships.push_back(relIn); 
}
//creates relationship from two classes and adds to relationshp vector
void UMLData::addRelationship(const UMLClass& sourceClass, const UMLClass& destClass)
{
    addRelationship(UMLRelationship(sourceClass, destClass));
}
//adds relationshp to vector via strings
void UMLData::addRelationship(std::string srcName, std::string destName)
{
    addRelationship(getClass(srcName), getClass(destName));
}
//deletes class by name
void UMLData::deleteClass(std::string name)
{
    int loc = findClass(name);
    if (loc < 0)
        throw "class not found";
    
    //delete relationships associated with class
    std::vector<UMLRelationship> relationshipsFromClass = getRelationshipsByClass(name);

    for (UMLRelationship rel : relationshipsFromClass)
    {
        deleteRelationship(rel.getSource().getName(), rel.getDestination().getName());
    }

    //remove class
    classes.erase(classes.begin() + loc);
}
//deletes class by relationship
void UMLData::deleteRelationship(std::string srcName, std::string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "relationship not found";
    relationships.erase(relationships.begin() + loc);
}

//takes in a class name and finds all relationshps associated with that class
std::vector<UMLRelationship> UMLData::getRelationshipsByClass(std::string classNameIn)
{
    std::vector<UMLRelationship> relationshipsContainingClass;

    std::string className = getClass(classNameIn).getName();

    for (int i = 0; i < relationships.size(); ++i)
    {
        //pull src and destination classes from vector location
        std::string src = relationships[i].getSource().getName();
        std::string dest = relationships[i].getDestination().getName();
        //compare
        if ((src == className) or (dest == className))
        {
            relationshipsContainingClass.push_back(relationships[i]);
        }
    }
    return relationshipsContainingClass;

}
void UMLData::changeClassName(std::string oldName, std::string newName)
{
    getClass(oldName).changeName(newName);
}
