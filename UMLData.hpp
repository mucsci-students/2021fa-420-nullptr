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

        //params: classIn
        //takes in class and adds it to vector
        void addClass(const UMLClass& classIn);

        //params: string name
        //takes in string name and creates class and adds to classes vector
        void addClass(string name);

        //params: string name, vector<UMLAttributes> attributes
        //takes in name and vector of attributes and creates class and adds to vector of classes
        void addClass(string name, vector<UMLAttribute> attributes);

        //params: string srcName, destName
        //takes in src string and dest string, creates relationship and adds to relationships vector
        void addRelationship(string srcName, string destName);
        
        //params: std:string className
        //takes in className string and returns a vector of all the relationshps associated with that class
        vector<UMLRelationship> getRelationshipsByClass(string className);

        //params: string srcName, string destName
        //deletes relationshp based on two strings
        void deleteRelationship(string srcName, string destName);

        //params: string name
        //deletes a class by string in the classes vector
        void deleteClass(string name);

        //params: string oldName, string newName
        //changes class name from old name and new name
        void changeClassName(string oldName, string newName);

        //params string className
        //gets class attributes for a className class and returns them in a vector
        vector<UMLAttribute> getClassAttributes(string className);

        //params string className, UMLAttribute attribute
        //adds class attribute to specified className
        void addClassAttribute(string className, UMLAttribute attribute);

        //params: string className, string attribute name
        //removes className class attribute by the name
        void removeClassAttribute(string className, string attributeName);

    private:

        //params: string name
        //finds class by name and returns index within member classes vector, returns -1 if not found
        int findClass(string name);

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
:classes(vclass)
{
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
        throw "New name already exists";
    getClass(oldName).changeName(newName);
}

vector<UMLAttribute> UMLData::getClassAttributes(string className)
{
    return getClass(className).getAttributes();
}

void UMLData::addClassAttribute(string className, UMLAttribute attribute)
{
    getClass(className).addAttribute(attribute);
}

void UMLData::removeClassAttribute(string className, string attributeName)
{
    getClass(className).deleteAttribute(attributeName);
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
        throw "Name not found";
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
        throw "Relationship already exists";

    relationships.push_back(relIn); 
}

void UMLData::addRelationship(const UMLClass& sourceClass, const UMLClass& destClass)
{
    addRelationship(UMLRelationship(sourceClass, destClass));
}