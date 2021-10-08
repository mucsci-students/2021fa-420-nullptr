/*
  Filename   : UMLData.cpp
  Description: Implementation of the data storage model.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLFile.hpp"
#include "include/UMLRelationship.hpp"
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

// Takes in src string, dest string, and type int creates relationship and adds to relationships vector
void UMLData::addRelationship(string srcName, string destName, int type)
{
    // Type must be in bounds
    if (type < 0 || type > 3) 
        throw "Invalid type";
    addRelationship(UMLRelationship(getClass(srcName), getClass(destName), type));
}

// Takes in className string and returns a vector of all the relationships associated with that class
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

// Returns string representation of relationship type
string UMLData::getRelationshipType(const string& srcName, const string& destName)
{
    Type type = getRelationship(srcName, destName).getType();
    switch (type) {
        case aggregation :
            return "aggregation";
        case composition :
            return "composition";
        case generalization :
            return "generalization";
        case realization :
            return "realization";
        default :
            return "none";
    }
    return "none";
}

// Modifies relationship type given a new relationship type 
void UMLData::changeRelationshipType(const string& srcName, const string& destName, int newType) 
{
    int oldType = getRelationship(srcName, destName).getType();
    // Type must be in bounds
    if (newType < 0 || newType > 3) {
        throw "Invalid type";
    }
    // Type must not be the same as the previous type
    else if (newType == oldType) {
        throw "Type is already set as " + getRelationshipType(srcName, destName);
    }
    // Generalization/realization check for self relationships
    else if (newType == 2 || newType == 3) {
        if (srcName == destName) {
            throw "Cannot have self-relationship of generalizations or realizations";
        }
    }
    // Composition check for duplicate destinations
    else if (newType == 1) {
        for(UMLRelationship relationship : getRelationships()) {
            // Need to check for identical destination name and type without counting itself
            if (relationship.getDestination().getName() == destName 
            && relationship.getSource().getName() != srcName
            && relationship.getType() == composition) {
                throw "Class can not be the destination for more than one composition";
            }
        }
    }
    getRelationship(srcName, destName).setType(newType);
}

// Gets relationship reference for the given string class names
UMLRelationship& UMLData::getRelationship(string srcName, string destName)
{
    int loc = findRelationship(getClass(srcName), getClass(destName));
    if (loc < 0)
        throw "Relationship not found";
    return relationships[loc];
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

// X_X
void UMLData::addClassAttributeP(string className, UMLAttribute* attribute)
{
  //  if (!isValidName(attribute.getAttributeName()))
   //     throw "Attribute name is not valid";
    getClass(className).addAttributeP(attribute);
}

// Removes className class attribute by the name
void UMLData::removeClassAttribute(string className, string attributeName)
{
      for (UMLAttribute attr : getClass(className).getAttributes()) {
           if (attr.getAttributeName() == attributeName){
                getClass(className).deleteAttribute(attributeName);
                return;
           }
       }
        throw "Attribute does not exist";
}

// TEMP remove from pointer
void UMLData::removeClassAttributeP(string className, string attributeName)
{
      for (UMLAttribute* attr : getClass(className).getAttributesP()) {
           if (attr->getAttributeName() == attributeName){
                getClass(className).deleteAttributeP(attributeName);
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
        if ((src == sourceClassIn.getName()) && (dest == destClassIn.getName()))
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

// Takes in relationship object and adds it to relationship vector
void UMLData::addRelationship(const UMLRelationship& relIn)
{
    // Check to see if relationship already exists
    int loc = findRelationship(relIn.getSource(), relIn.getDestination());
    if (loc >= 0)
        throw "New relationship already exists";
    // Generalization/realization check for self relationships
    else if (relIn.getType() == generalization || relIn.getType() == realization) {
        if (relIn.getSource().getName() == relIn.getDestination().getName()) {
            throw "Cannot have self-relationship of generalizations or realizations";
        }
    }
    // Composition check for duplicate destinations
    else if (relIn.getType() == composition) {
        for(UMLRelationship relationship : getRelationships()) {
            // Need to check for identical destination name and type
            if (relationship.getDestination().getName() == relIn.getDestination().getName()
                && relationship.getType() == composition) {
                throw "Class can not be the destination for more than one composition";
            }
        }
    }
    relationships.push_back(relIn); 
}

json UMLData::getJson()
{
    json j;
    j["classes"] = json::array();
    for (UMLClass uclass : classes)
    {
        json jsonattr;
        jsonattr = json::array();
        //add methods and fields here
        for (UMLAttribute uattr : uclass.getAttributes())
        {
            jsonattr += { {"name", uattr.getAttributeName()} };
        } 
          j["classes"] += { {"name", uclass.getName()}, {"attributes", jsonattr} };
    }

    j["relationships"] = json::array();
    for (UMLRelationship urelationship : relationships)
    {
        j["relationships"] += { 
            {"source", urelationship.getSource().getName()}, 
            {"destination", urelationship.getDestination().getName()},
            {"type", getRelationshipType(urelationship.getSource().getName(), urelationship.getDestination().getName())}
            };
    }
    
    return j;
}