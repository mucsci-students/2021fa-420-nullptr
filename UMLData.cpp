/*
  Filename   : UMLData.cpp
  Description: Implementation of the data storage model.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLFile.hpp"
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "include/UMLRelationship.hpp"
#include <algorithm>
#include <list>
//--------------------------------------------------------------------

// Empty constructor
UMLData::UMLData()
{
}

// Constructor that takes in vector of classes 
UMLData::UMLData(const vector<UMLClass>& vclass)
{
    for (UMLClass uclass : vclass)
    {
        addClass(uclass);
    }
}

// Returns vector of all classes
std::list<UMLClass> UMLData::getClasses() const
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
    if (doesClassExist(classIn))
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
    // Only change type if the type is actually different
    else if (newType != oldType) {
        getRelationship(srcName, destName).setType(newType);
    }
    // Don't change if relationship is already the same
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
    if (!doesClassExist(name))
        throw "Class not found";
    
    //delete relationships associated with class
    vector<UMLRelationship> relationshipsFromClass = getRelationshipsByClass(name);

    for (UMLRelationship rel : relationshipsFromClass)
    {
        deleteRelationship(rel.getSource().getName(), rel.getDestination().getName());
    }

    //remove class
    classes.erase(findClass(name));
}

// Changes class name from old name and new name
void UMLData::changeClassName(string oldName, string newName)
{
    //change class name
    if (doesClassExist(newName))
        throw "Class name already exists";
    if (!isValidName(newName))
        throw "New class name is not valid";
    getClass(oldName).changeName(newName);
    //change name in relationship
}

// Gets class attributes for a className class and returns them in a vector
vector<std::shared_ptr<UMLAttribute>> UMLData::getClassAttributes(string className)
{
    return getClass(className).getAttributes();
}

// Adds class attribute to specified className
void UMLData::addClassAttribute(string className, UMLAttribute attribute)
{
    if (!isValidName(attribute.getAttributeName()))
        throw "Attribute name is not valid";
    else if (!isValidName(attribute.getType()))
        throw "Attribute type is not valid";
    getClass(className).addAttribute(attribute);
}

// Adds class attribute to specified className using a smart pointer
void UMLData::addClassAttribute(string className, std::shared_ptr<UMLAttribute> attribute)
{
    if (!isValidName(attribute->getAttributeName()))
        throw "Attribute name is not valid";
    else if (!isValidName(attribute->getType()))
        throw "Attribute type is not valid";
    else if (getClass(className).checkAttribute(attribute)) {
        if (attribute->identifier() == "field") {
            throw "Field cannot be added, conflicts with other attributes";
        }
        else if (attribute->identifier() == "method") {
            throw "Method cannot be added, conflicts with other attributes";
        }
    }
    getClass(className).addAttribute(attribute);
}

// Removes className class attribute by the name
void UMLData::removeClassAttribute(string className, string attributeName)
{
    for (std::shared_ptr<UMLAttribute> attr : getClass(className).getAttributes()) {
        if (attr->getAttributeName() == attributeName) {
            getClass(className).deleteAttribute(attributeName);
            return;
        }
    }
    throw "Attribute does not exist";
}

// Removes className class attribute by smart pointer
void UMLData::removeClassAttribute(string className, std::shared_ptr<UMLAttribute> attr)
{
    getClass(className).deleteAttribute(attr); // Error handing in UMLClass
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

// Overload of changeAttributeName to work with a smart pointer
void UMLData::changeAttributeName(string className, std::shared_ptr<UMLAttribute> attribute, string newAttributeName)
{
    // Make attribute that has the same type but a different name
    std::shared_ptr<UMLAttribute> newAttribute;
    newAttribute->changeName(newAttributeName);
    newAttribute->changeType(attribute->getType());

    if (getClass(className).checkAttribute(newAttribute)) {
        if (attribute->identifier() == "field") {
            throw "Field name cannot be changed to " + newAttributeName + ", conflicts with other attributes";
        }
        else if (attribute->identifier() == "method") {
            throw "Method name cannot be changed to " + newAttributeName + ", conflicts with other attributes";
        }
    }
    else if (!isValidName(newAttributeName))
        throw "New attribute name is not valid";
    getClass(className).changeAttributeName(attribute, newAttributeName);
}

// Changes className class attribute's type by the new type name 
void UMLData::changeAttributeType(std::shared_ptr<UMLAttribute> attribute, string newTypeName)
{
    if (!isValidName(newTypeName))
        throw "New type name is not valid";
    else {
        attribute->changeType(newTypeName);
    }
}

// Adds parameter to a given method
void UMLData::addParameter(std::shared_ptr<UMLMethod> method, string paramName, string paramType)
{
    if (!isValidName(paramName))
        throw "Parameter name is not valid";
    else if (!isValidName(paramType))
        throw "Parameter type is not valid";
    else {
        for (UMLParameter param : method->getParam()) {
            if (param.getName() == paramName && param.getType() == paramType) {
                throw "Parameter already exists";
            }
        }
    }
    method->addParam(UMLParameter(paramName, paramType));
}

// Deletes parameter from given method
void UMLData::deleteParameter(std::shared_ptr<UMLMethod> method, string paramName) 
{
    method->deleteParameter(paramName);
}

// Checks if identiifier name is valid
bool UMLData::isValidName(string name)
{
    // Cannot have empty type
    if (name.size() < 1) 
    {
        return false;
    } 
    else 
    {
        // Check first character, detect if it is a letter
        if (isalpha(name[0]) == 0) return false;
        // Check the rest of the characters 
        for (int i = 1; i < name.length(); ++i) 
        {
            // Anything afterwards can be a letter, digit, or underscore. If not, return false
            if (isalpha(name[i]) == 0 && isdigit(name[i]) == 0 && name[i] != '_') return false;
        }
    }
    return true;
}

// Finds class in classes list returns first matching iterator or returns end() if no matches
std::list<UMLClass>::iterator UMLData::findClass(string name)
{
    std::list<UMLClass>::iterator findIter = std::find(classes.begin(), classes.end(), UMLClass(name));
    return findIter;
}

// Alternate find class using a reference to a UMLClass object
std::list<UMLClass>::iterator UMLData::findClass(const UMLClass& uclass)
{
    std::list<UMLClass>::iterator findIter = std::find(classes.begin(), classes.end(), uclass);
    return findIter;
}

// Finds attribute by name and returns index within the attribute's vector, returns -1 if not found
int UMLData::findAttribute(string name, const vector<std::shared_ptr<UMLAttribute>>& attributes)
{
    for (int i = 0; i < attributes.size(); ++i)
    {
        if (attributes[i]->getAttributeName() == name)
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
    std::list<UMLClass>::iterator findIter = findClass(name);
    if (findIter == classes.end())
        throw "Class not found";
    return *findIter;
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

// Generates json file given a set of data
json UMLData::getJson()
{
    json j;
    j["classes"] = json::array();

    for (UMLClass uclass : classes)
    {
        json jsonattr;
        jsonattr["fields"] = json::array();
        jsonattr["methods"] = json::array();

        for (auto uattr : uclass.getAttributes())
        {
            if (uattr->identifier() == "field")
                jsonattr["fields"] += { {"name", uattr->getAttributeName()}, {"type", uattr->getType()} };

            else
            {
                json jsonparams = json::array();
                for (auto param : (std::static_pointer_cast<UMLMethod>(uattr))->getParam())
                {
                   jsonparams += {{"name", param.getName()}, {"type", param.getType()}};
                } 

                jsonattr["methods"] += {{"name", uattr->getAttributeName()}, {"return_type", uattr->getType()}, {"params", jsonparams}};
            }
        } 
          j["classes"] += { {"name", uclass.getName()}, {"fields", jsonattr["fields"]}, {"methods", jsonattr["methods"]} };
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

// Checks if class exists within classses list (string argument) 
bool UMLData::doesClassExist(const string& name)
{
    std::list<UMLClass>::iterator findIter = findClass(name);
    if (findIter == classes.end())
        return false;
    return true;
}

// Checks if class exists with classes list (class argument)
bool UMLData::doesClassExist(const UMLClass& uclass)
{
    std::list<UMLClass>::iterator findIter = findClass(uclass);
    if (findIter == classes.end())
        return false;
    return true;
}