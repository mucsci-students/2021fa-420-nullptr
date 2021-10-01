/*
  Filename   : UMLFile.cpp
  Description: Implementation of a file.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLFile.hpp"
//--------------------------------------------------------------------

// Empty constructor
UMLData::UMLData()
{
}

// Constructor that takes in vector of classes 
UMLData::UMLData(const vector<UMLClass>& vclass)
{
    for (UMLClass uclass : vclass )
    {
        addClass(uclass);
    }
}

// Returns vector of all classes
vector<UMLClass> UMLData::getClasses() const
{
    return classes;
}

// Return a single class
UMLClass UMLData::getClassCopy(std::string name)
{
    return getClass(name);
}

// Returns vector of all relationships
vector<UMLRelationship> UMLData::getRelationships() const
{
    return relationships;
}

// Takes in class and adds it to vector
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

// Takes in string name and creates class and adds to classes vector
void UMLData::addClass(string name)
{
    addClass(UMLClass(name));
}

// Takes in name and vector of attributes and creates class and adds to vector of classes
void UMLData::addClass(string name, vector<UMLAttribute> attributes)
{
    addClass(UMLClass(name, attributes));
}

// Takes in src string and dest string, creates relationship and adds to relationships vector
void UMLData::addRelationship(string srcName, string destName)
{
    addRelationship(getClass(srcName), getClass(destName));
}

// Takes in className string and returns a vector of all the relationshps associated with that class
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

// Deletes relationshp based on two strings
void UMLData::deleteRelationship(string srcName, string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "Relationship not found";
    relationships.erase(relationships.begin() + loc);
}

// Deletes a class by string in the classes vector
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

// Changes class name from old name and new name
void UMLData::changeClassName(string oldName, string newName)
{
    if (findClass(newName) >= 0)
        throw "Class name already exists";
    if (!isValidName(newName))
        throw "New class name is not valid";
    getClass(oldName).changeName(newName);
}

// Gets class attributes for a className class and returns them in a vector
vector<UMLAttribute> UMLData::getClassAttributes(string className)
{
    return getClass(className).getAttributes();
}

// Adds class attribute to specified className
void UMLData::addClassAttribute(string className, UMLAttribute attribute)
{
    if (!isValidName(attribute.getAttributeName()))
        throw "Attribute name is not valid";
    getClass(className).addAttribute(attribute);
}

// Removes className class attribute by the name
void UMLData::removeClassAttribute(string className, string attributeName)
{
      for (UMLAttribute attr : getClass(className).getAttributes()) {
           if(attr.getAttributeName() == attributeName){
                getClass(className).deleteAttribute(attributeName);
                return;
           }
       }
        throw "Attribute does not exist";
}

// Changes className class attribute by the new attribute name
void UMLData::changeAttributeName(string className, string oldAttributeName, string newAttributeName)
{
    if (findAttribute(newAttributeName, getClassAttributes(className)) >= 0)
        throw "Attribute name already exists";
    if (!isValidName(newAttributeName))
        throw "New attribute name is not valid";
    getClass(className).changeAttributeName(oldAttributeName, newAttributeName);
}

// Checks if class/attribute name is valid
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

// Finds class by name and returns index within member classes vector, returns -1 if not found
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

// Finds attribute by name and returns index within the attribute's vector, returns -1 if not found
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

// Finds relationship using two UML classes and returns index within member classes vector
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

// Gets class reference for the given name
UMLClass& UMLData::getClass(string name)
{
    int loc = findClass(name);
    if (loc < 0)
        throw "Class not found";
    return classes[loc];
}

// Gets relationship reference for the given string class names
UMLRelationship& UMLData::getRelationship(string srcName, string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "Relationship not found";
    return relationships[loc];
}

// Takes in relationship object and adds it to relationship vector
void UMLData::addRelationship(const UMLRelationship& relIn)
{
    int loc = findRelationship(relIn.getSource(), relIn.getDestination());
    if (loc >= 0)
        throw "New relationship already exists";

    relationships.push_back(relIn); 
}

// Creates relationship from two classes and adds to relationshp vector
void UMLData::addRelationship(const UMLClass& sourceClass, const UMLClass& destClass)
{
    addRelationship(UMLRelationship(sourceClass, destClass));
}