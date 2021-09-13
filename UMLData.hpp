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
    private:
        //params: std::string name
        //finds class by name and returns index within member classes vector
        int findClass(std::string name);

        //params: UMLClass sourceClassIn, UMLClass destClassIn
        //finds relationship using two UML classes and returns index within member classes vector
        int findRelationship(const UMLClass& sourceClassIn, const UMLClass& destClassIn);

        //params: std::string name
        //gets class reference for the given name
        UMLClass& getClass(std::string name);

        //params: std::string name
        //gets relationship reference for the given string class names
        UMLRelationship& getRelationship(std::string srcName, std::string destName);

        //params: UMLRelationship relationshipIn
        //takes in relationship object and adds it to relationship vector
        void addRelationship(const UMLRelationship& relationshipIn);

        //params: UMLClass source, UMLClass destClass
        //creates relationship from two classes and adds to relationshp vector
        void addRelationship(const UMLClass& sourceClass, const UMLClass& destClass);

        std::vector<UMLClass> classes;
        std::vector<UMLRelationship> relationships;

    public: 
        
        //Empty constructor
        UMLData() {};

        //Constructor that takes in vector of classes 
        UMLData(const std::vector<UMLClass>& vclass)
        {
            classes = vclass;
        }

        //returns vector of all classes
        std::vector<UMLClass> getClasses() const { return classes; }
   
        //returns vector of all relationships
        std::vector<UMLRelationship> getRelationships() const { return relationships; }

        //params: classIn
        //takes in class and adds it to vector
        void addClass(const UMLClass& classIn);

        //params: std::string name
        //takes in string name and creates class and adds to classes vector
        void addClass(std::string name);

        //params: std::string name, vector<UMLAttributes> attributes
        //takes in name and vector of attributes and creates class and adds to vector of classes
        void addClass(std::string name, std::vector<UMLAttribute> attributes);

        //params: std::string srcName, destName
        //takes in src string and dest string, creates relationship and adds to relationships vector
        void addRelationship(std::string srcName, std::string destName);
        
        //params: std:string className
        //takes in className string and returns a vector of all the relationshps associated with that class
        std::vector<UMLRelationship> getRelationshipsByClass(std::string className);

        //params: std::string srcName, std::string destName
        //deletes relationshp based on two strings
        void deleteRelationship(std::string srcName, std::string destName);

        //params: std::string name
        //deletes a class by string in the classes vector
        void deleteClass(std::string name);

        //params: std::string oldName, std::string newName
        //changes class name from old name and new name
        void changeClassName(std::string oldName, std::string newName);

        //params std::string className
        //gets class attributes for a className class and returns them in a vector
        std::vector<UMLAttribute> getClassAttributes(std::string className);

        //params std::string className, UMLAttribute attribute
        //adds class attribute to specified className
        void addClassAttribute(std::string className, UMLAttribute attribute);

        //params: std::string className, std::string attribute name
        //removes className class attribute by the name
        void removeClassAttriubte(std::string className, std::string attributeName);
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

UMLClass& UMLData::getClass(std::string name)
{
    int loc = findClass(name);
    if (loc < 0)
        throw "name not found";
    return classes[loc];
}

UMLRelationship& UMLData::getRelationship(std::string srcName, std::string destName)
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
    
    //delete relationships associated with class
    std::vector<UMLRelationship> relationshipsFromClass = getRelationshipsByClass(name);

    for (UMLRelationship rel : relationshipsFromClass)
    {
        deleteRelationship(rel.getSource().getName(), rel.getDestination().getName());
    }

    //remove class
    classes.erase(classes.begin() + loc);
}

void UMLData::deleteRelationship(std::string srcName, std::string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "relationship not found";
    relationships.erase(relationships.begin() + loc);
}

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
    if (findClass(newName) >= 0)
        throw "new name already exists";
    getClass(oldName).changeName(newName);
}

void UMLData::addClassAttribute(std::string className, UMLAttribute attribute)
{
    getClass(className).addAttribute(attribute);
}

void UMLData::removeClassAttriubte(std::string className, std::string attributeName)
{
    getClass(className).deleteAttribute(attributeName);
}

std::vector<UMLAttribute> UMLData::getClassAttributes(std::string className)
{
    return getClass(className).getAttributes();
}