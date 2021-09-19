#pragma once
/*
  Filename   : UMLData.hpp
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

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
//--------------------------------------------------------------------

class UMLData
{
    
    private:

        vector<UMLClass> classes;
        vector<UMLRelationship> relationships;

    public: 
        
        //Empty constructor
        UMLData();

        //Constructor that takes in vector of classes 
        UMLData(const vector<UMLClass>& vclass);

        //returns vector of all classes
        vector<UMLClass> getClasses() const;

        //return a single class
        UMLClass getClassCopy(std::string name);
   
        //returns vector of all relationships
        vector<UMLRelationship> getRelationships() const;

        //takes in class and adds it to vector
        void addClass(const UMLClass& classIn);

        //takes in string name and creates class and adds to classes vector
        void addClass(string name);

        //takes in name and vector of attributes and creates class and adds to vector of classes
        void addClass(string name, vector<UMLAttribute> attributes);

        //takes in src string and dest string, creates relationship and adds to relationships vector
        void addRelationship(string srcName, string destName);
        
        //takes in className string and returns a vector of all the relationshps associated with that class
        vector<UMLRelationship> getRelationshipsByClass(string className);

        //deletes relationshp based on two strings
        void deleteRelationship(string srcName, string destName);

        //deletes a class by string in the classes vector
        void deleteClass(string name);

        //changes class name from old name and new name
        void changeClassName(string oldName, string newName);

        //gets class attributes for a className class and returns them in a vector
        vector<UMLAttribute> getClassAttributes(string className);

        //adds class attribute to specified className
        void addClassAttribute(string className, UMLAttribute attribute);

        //removes className class attribute by the name
        void removeClassAttribute(string className, string attributeName);

        //removes className class attribute by the name
        void changeAttributeName(string className, string oldAttributeName, string newAttributeName);

        //checks if class/attribute name is valid
        bool isValidName(string name);

    private:

        //params: string name
        //finds class by name and returns index within member classes vector, returns -1 if not found
        int findClass(string name);

        //params: string name, vector<UMLAttribute> attributes
        //finds attribute by name and returns index within the attribute's vector, returns -1 if not found
        int findAttribute(string name, vector<UMLAttribute> attributes);

        //params: UMLClass sourceClassIn, UMLClass destClassIn
        //finds relationship using two UML classes and returns index within member classes vector
        int findRelationship(const UMLClass& sourceClassIn, const UMLClass& destClassIn);

        //params: string name
        //gets class reference for the given name
        UMLClass& getClass(string name);

        //params: string name
        //gets relationship reference for the given string class names
        UMLRelationship& getRelationship(string srcName, string destName);

        //params: UMLRelationship relationshipIn
        //takes in relationship object and adds it to relationship vector
        void addRelationship(const UMLRelationship& relationshipIn);

        //params: UMLClass source, UMLClass destClass
        //creates relationship from two classes and adds to relationshp vector
        void addRelationship(const UMLClass& sourceClass, const UMLClass& destClass);
};

UMLData::UMLData()
{
}

UMLData::UMLData(const vector<UMLClass>& vclass)
{
    for (UMLClass uclass : vclass )
    {
        addClass(uclass);
    }
}

vector<UMLClass> UMLData::getClasses() const
{
    return classes;
}

UMLClass UMLData::getClassCopy(std::string name)
{
    return getClass(name);
}

vector<UMLRelationship> UMLData::getRelationships() const
{
    return relationships;
}

void UMLData::addClass(const UMLClass& classIn)
{
    //check if already exists
    int loc = findClass(classIn.getName());
    if (loc >= 0)
        throw "Class name already exists";
    if (!isValidName(classIn.getName()))
        throw "Class name not valid";
    classes.push_back(classIn);
}

void UMLData::addClass(string name)
{
    addClass(UMLClass(name));
}

void UMLData::addClass(string name, vector<UMLAttribute> attributes)
{
    addClass(UMLClass(name, attributes));
}

void UMLData::addRelationship(string srcName, string destName)
{
    addRelationship(getClass(srcName), getClass(destName));
}

vector<UMLRelationship> UMLData::getRelationshipsByClass(string classNameIn)
{
    vector<UMLRelationship> relationshipsContainingClass;

    string className = getClass(classNameIn).getName();

    for (int i = 0; i < relationships.size(); ++i)
    {
        //pull src and destination classes from vector location
        string src = relationships[i].getSource().getName();
        string dest = relationships[i].getDestination().getName();
        //compare
        if ((src == className) or (dest == className))
        {
            relationshipsContainingClass.push_back(relationships[i]);
        }
    }
    return relationshipsContainingClass;

}

void UMLData::deleteRelationship(string srcName, string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "Relationship not found";
    relationships.erase(relationships.begin() + loc);
}

void UMLData::deleteClass(string name)
{
    int loc = findClass(name);
    if (loc < 0)
        throw "Class not found";
    
    //delete relationships associated with class
    vector<UMLRelationship> relationshipsFromClass = getRelationshipsByClass(name);

    for (UMLRelationship rel : relationshipsFromClass)
    {
        deleteRelationship(rel.getSource().getName(), rel.getDestination().getName());
    }

    //remove class
    classes.erase(classes.begin() + loc);
}

void UMLData::changeClassName(string oldName, string newName)
{
    if (findClass(newName) >= 0)
        throw "Class name already exists";
    if (!isValidName(newName))
        throw "New class name is not valid";
    getClass(oldName).changeName(newName);
}

vector<UMLAttribute> UMLData::getClassAttributes(string className)
{
    return getClass(className).getAttributes();
}

void UMLData::addClassAttribute(string className, UMLAttribute attribute)
{
    if (!isValidName(attribute.getAttributeName()))
        throw "Attribute name is not valid";
    getClass(className).addAttribute(attribute);
}

void UMLData::removeClassAttribute(string className, string attributeName)
{
    getClass(className).deleteAttribute(attributeName);
}

void UMLData::changeAttributeName(string className, string oldAttributeName, string newAttributeName)
{
    if (findAttribute(newAttributeName, getClassAttributes(className)) >= 0)
        throw "Attribute name already exists";
    if (!isValidName(newAttributeName))
        throw "New attribute name is not valid";
    getClass(className).changeAttributeName(oldAttributeName, newAttributeName);
}

int UMLData::findClass(string name)
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

int UMLData::findAttribute(string name, vector<UMLAttribute> attributes)
{
    for (int i = 0; i < attributes.size(); ++i)
    {
        if (attributes[i].getAttributeName() == name)
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
        string src = relationships[i].getSource().getName();
        string dest = relationships[i].getDestination().getName();
        //compare
        if ((src == sourceClassIn.getName()) and (dest == destClassIn.getName()))
        {
            return i;
        }
    }
    return -1;
}

UMLClass& UMLData::getClass(string name)
{
    int loc = findClass(name);
    if (loc < 0)
        throw "Class not found";
    return classes[loc];
}

UMLRelationship& UMLData::getRelationship(string srcName, string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "Relationship not found";
    return relationships[loc];
}

void UMLData::addRelationship(const UMLRelationship& relIn)
{
    int loc = findRelationship(relIn.getSource(), relIn.getDestination());
    if (loc >= 0)
        throw "New relationship already exists";

    relationships.push_back(relIn); 
}

void UMLData::addRelationship(const UMLClass& sourceClass, const UMLClass& destClass)
{
    addRelationship(UMLRelationship(sourceClass, destClass));
}

bool UMLData::isValidName(string name)
{
    //checking first character
    if (name.size() < 1)
    {
        return false;
    } else 
    {
        //check first character
        if (!((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z'))) return false;
        //check the rest of the chracters 
        for (int i = 1; i < name.length(); i++) 
        {
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9') || name[i] == '_')) return false;
        }
    }
    return true;
}