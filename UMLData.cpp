/*
  Filename   : UMLData.cpp
  Author(s)  : Matt Giacoponello, Others(Not sure which group members wrote this)
  Description: Implementation of the data storage model.
*/


/**************************************************************/
//SYSTEM INCLUDES

#include "include/UMLAttribute.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLData.hpp"
#include "include/UMLField.hpp"
#include "include/UMLFile.hpp"
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "include/UMLRelationship.hpp"
#include <algorithm>
#include <list>
#include <memory>




/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                            PUBLIC                            |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

/**************************************************************/
//CONSTRUCTORS


// Empty constructor
UMLData::UMLData()
{
}


// Constructor that takes in vector of classes 
UMLData::UMLData(const vector<UMLClass>& vclass)
{
  for (UMLClass uclass : vclass)
  {
    addClassObject(uclass);
  }
}


/**************************************************************/
//GET COLLECTIONS


/**
 * @brief Returns vector of all classes.
 * 
 * @return list<UMLClass> 
 */
list<UMLClass> UMLData::getClasses() const
{
  return classes;
}


/************************************/


/**
 * @brief Returns vector of all relationships.
 * 
 * @return vector<UMLRelationship> 
 */
vector<UMLRelationship> UMLData::getRelationships() const
{
  return relationships;
}


/************************************/


/**
 * @brief Takes in className string and returns a vector of all the 
 * relationships associated with that class.
 * 
 * @param classNameIn 
 * @return vector<UMLRelationship> 
 */
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
    if ((src == className) || (dest == className))
    {
      relationshipsContainingClass.push_back(relationships[i]);
    }
  }
  return relationshipsContainingClass;
}


/************************************/


/**
 * @brief Gets class attributes for a className class and returns them
 * in a vector.
 * 
 * @param className 
 * @return vector<attr_ptr> 
 */
vector<attr_ptr> UMLData::getClassAttributes(string className)
{
  return getClass(className).getAttributes();
}


/**************************************************************/
//GET DATA


/**
 * @brief Return a single class.
 * 
 * @param name 
 * @return UMLClass 
 */
UMLClass UMLData::getClassCopy(string name)
{
  return getClass(name);
}


/************************************/


/**
 * @brief Returns string representation of relationship type.
 * 
 * @param srcName 
 * @param destName 
 * @return string 
 */
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


/************************************/


/**
 * @brief Gets relationship reference for the given string class names.
 * 
 * @param srcName 
 * @param destName 
 * @return UMLRelationship& 
 */
UMLRelationship& UMLData::getRelationship(string srcName, string destName)
{
  int location = findRelationship(getClass(srcName), getClass(destName));
  if (location < 0)
    throw std::runtime_error("Relationship not found");
  return relationships[location];
}


/************************************/


/**
 * @brief Generates json file given a set of data.
 * 
 * @return json 
 */
json UMLData::getJson()
{
  json jsonObj;
  jsonObj["classes"] = json::array();

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
    jsonObj["classes"] += { {"name", uclass.getName()}, {"position_x", uclass.getX()}, {"position_y", uclass.getY()}, {"fields", jsonattr["fields"]}, {"methods", jsonattr["methods"]} };
  }

  jsonObj["relationships"] = json::array();
  for (UMLRelationship urelationship : relationships)
  {
    jsonObj["relationships"] += { 
      {"source", urelationship.getSource().getName()}, 
      {"destination", urelationship.getDestination().getName()},
      {"type", getRelationshipType(urelationship.getSource().getName(), urelationship.getDestination().getName())}
    };
  }

  return jsonObj;
}


/************************************/


//-----------------------------------------------------------------------
// Memento pattern - creates snapshots that are able to be restored

/**
 * @brief Returns a snapshot of the model in its current state.
 * 
 * @return const UMLDataSnapshot 
 */
// const UMLDataSnapshot UMLData::make_snapshot()
// {
//   return UMLDataSnapshot(classes, relationships);
// }



/************************************/


/**
 * @brief Overwrites current model with a snapshot.
 * 
 * @param snapshot 
 */
// void UMLData::restore(const UMLDataSnapshot& snapshot)
// {
//   classes = snapshot.classes;
//   relationships = snapshot.relationships;
// }
//-----------------------------------------------------------------------


/**************************************************************/
//ADDING


/**
 * @brief Takes in class and adds it to vector.
 * 
 * @param classIn 
 */
void UMLData::addClassObject(const UMLClass& classIn)
{
  //check if already exists
  if (doesClassExist(classIn.getName()))
    throw std::runtime_error("Class name already exists");
  if (!isValidName(classIn.getName()))
    throw std::runtime_error("Class name not valid");
  classes.push_back(classIn);
}


/************************************/


/**
 * @brief Takes in string name and creates class and adds to classes
 * vector.
 * 
 * @param name 
 */
void UMLData::addClass(string name)
{
  addClassObject(UMLClass(name));
}


/************************************/


/**
 * @brief Takes in src string, dest string, and type int creates
 * relationship and adds to relationships vector.
 * 
 * @param srcName 
 * @param destName 
 * @param type 
 */
void UMLData::addRelationship(string srcName, string destName, int type)
{
  // Type must be in bounds
  if (type < 0 || type > 3) 
    throw std::runtime_error("Invalid type");
  addRelationship(UMLRelationship(getClass(srcName), getClass(destName), type));
}


/************************************/


/**
 * @brief Adds class attribute to specified className using a smart pointer.
 * 
 * @param className 
 * @param attribute 
 */
void UMLData::addClassAttribute(string className, attr_ptr attribute)
{
  if (!isValidName(attribute->getAttributeName()))
    throw std::runtime_error("Attribute name is not valid");
  else if (!isValidName(attribute->getType()))
    throw std::runtime_error("Attribute type is not valid");
  else if (getClass(className).checkAttribute(attribute)) {
    if (attribute->identifier() == "field") {
      throw std::runtime_error("Field cannot be added, conflicts with other attributes");
    }
    else if (attribute->identifier() == "method") {
      throw std::runtime_error("Method cannot be added, conflicts with other attributes");
    }
  }
  getClass(className).addAttribute(attribute);
}


/************************************/


/**
 * @brief Adds parameter to a given method.
 * 
 * @param method 
 * @param paramName 
 * @param paramType 
 */
void UMLData::addParameter(string className, method_ptr method, string paramName, string paramType)
{
  if (!isValidName(paramName))
    throw std::runtime_error("Parameter name is not valid");

  else if (!isValidName(paramType))
    throw std::runtime_error("Parameter type is not valid");
  
  else 
  {
    for (UMLParameter param : method->getParam()) { 
      if (param.getName() == paramName) 
        throw std::runtime_error("Parameter already exists");
    }
  }
 
  method_ptr testAttribute = std::make_shared<UMLMethod>(method->getAttributeName(), method->getType(), 
    std::dynamic_pointer_cast<UMLMethod>(method)->getParam());

  testAttribute->addParam(UMLParameter(paramName, paramType));
  

  ///////////////////////////////////////////////////////////////////////////////////////////////
  // cout << "\nAdd parameter test:\n";
  // cout << testAttribute->getAttributeName();
  // auto testParamList = testAttribute->getParam() << ": ";

  // for (auto iter : testParamList)
  // {
  //   cout << *iter << ",";
  // }
  ///////////////////////////////////////////////////////////////////////////////////////////////
  if (getClass(className).checkAttribute(testAttribute)) {
    throw std::runtime_error("This parameter cannot be created, as this would create duplicate methods.");
  }
 
  method->addParam(UMLParameter(paramName, paramType));
}


/**************************************************************/
//DELETING


/**
 * @brief Deletes a class by string in the classes vector.
 * 
 * @param name 
 */
void UMLData::deleteClass(string name)
{
  if (!doesClassExist(name))
    throw std::runtime_error("Class not found");
  
  //delete relationships associated with class
  vector<UMLRelationship> relationshipsFromClass = getRelationshipsByClass(name);

  for (UMLRelationship rel : relationshipsFromClass)
  {
    deleteRelationship(rel.getSource().getName(), rel.getDestination().getName());
  }

  //remove class
  classes.erase(findClass(name));
}


/************************************/


/**
 * @brief Deletes relationshp based on two strings.
 * 
 * @param srcName 
 * @param destName 
 */
void UMLData::deleteRelationship(string srcName, string destName)
{
  int location = findRelationship(getClass(srcName), getClass(destName));
  if (location < 0)
    throw std::runtime_error("Relationship not found");
  relationships.erase(relationships.begin() + location);
}



/************************************/


/**
 * @brief Removes className class attribute by smart pointer.
 * 
 * @param className 
 * @param attr 
 */
void UMLData::removeClassAttribute(string className, attr_ptr attr)
{
  getClass(className).deleteAttribute(attr); // Error handing in UMLClass
}


/************************************/


/**
 * @brief Deletes parameter from given method
 * 
 * @param method 
 * @param paramName 
 */
void UMLData::deleteParameter(string className, method_ptr method, string paramName) 
{
  method_ptr testAttribute = std::make_shared<UMLMethod>(method->getAttributeName(), method->getType(), 
    std::dynamic_pointer_cast<UMLMethod>(method)->getParam());

  testAttribute->deleteParameter(paramName);

  if (getClass(className).checkAttribute(testAttribute)) {
    throw std::runtime_error("This parameter cannot be deleted now, as it would cause duplicate methods to exist.");
  }

  method->deleteParameter(paramName);
}


/**************************************************************/
//RENAMING


/**
 * @brief Changes class name from old name and new name.
 * 
 * @param oldName 
 * @param newName 
 */
void UMLData::changeClassName(string oldName, string newName)
{
  //change class name
  if (doesClassExist(newName))
    throw std::runtime_error("Class name already exists");
  if (!isValidName(newName))
    throw std::runtime_error("New class name is not valid");
  getClass(oldName).changeName(newName);
  //change name in relationship
}


/************************************/


/**
 * @brief Overload of changeAttributeName to work with a smart pointer.
 * 
 * @param className 
 * @param attribute 
 * @param newAttributeName 
 */
void UMLData::changeAttributeName(string className, attr_ptr attribute, string newAttributeName)
{
  // Make attribute that has the same type but a different name
  attr_ptr newAttribute;
  
  if (attribute->identifier() == "method")
    newAttribute = std::make_shared<UMLMethod>(newAttributeName, attribute->getType(), std::dynamic_pointer_cast<UMLMethod>(attribute)->getParam());
  else if (attribute->identifier() == "field")
    newAttribute = std::make_shared<UMLField>(newAttributeName, attribute->getType());

  if (getClass(className).checkAttribute(newAttribute)) {
    if (attribute->identifier() == "field") {
      throw std::runtime_error("Field name cannot be changed due to conflicts with other attributes");
    }
    else if (attribute->identifier() == "method") {
      throw std::runtime_error("Method name cannot be changed due to conflicts with other attributes");
    }
  }
  else if (!isValidName(newAttributeName))
    throw std::runtime_error("New attribute name is not valid");
  getClass(className).changeAttributeName(attribute, newAttributeName);
}


/************************************/


/**
 * @brief Takes in a shared method pointer, the name of the old parameter, 
 * and the new name, and renames the parameter accordingly.
 * 
 * @param methodIter 
 * @param oldParamName 
 * @param newParamName 
 */
void UMLData::changeParameterName(method_ptr methodIter, string oldParamName, string newParamName)
{
  if(doesParameterExist(methodIter, newParamName))
    throw std::runtime_error("That name is already taken.");
  methodIter->changeParameterName(oldParamName, newParamName);
}


/**************************************************************/
//TYPE CHANGING


/**
 * @brief Modifies relationship type given a new relationship type.
 * 
 * @param srcName 
 * @param destName 
 * @param newType 
 */
void UMLData::changeRelationshipType(const string& srcName, const string& destName, int newType) 
{
  // Also throws exception if nonexistent relationship.
  int oldType = getRelationship(srcName, destName).getType();

  if (!doesRelationshipExist(srcName, destName))
    throw std::runtime_error("Relationship does not exist.");

  // Type must be in bounds
  if (newType < 0 || newType > 3) {
    throw std::runtime_error("Invalid type");
  }
  // Generalization/realization check for self relationships
  else if (newType == 2 || newType == 3) {
    if (srcName == destName) {
      throw std::runtime_error("Cannot have self-relationship of generalizations or realizations");
    }
  }
  // Composition check for duplicate destinations
  else if (newType == 1) {
    for(UMLRelationship relationship : getRelationships()) {
      // Need to check for identical destination name and type without counting itself
      if (relationship.getDestination().getName() == destName 
      && relationship.getSource().getName() != srcName
      && relationship.getType() == composition) {
        throw std::runtime_error("Class can not be the destination for more than one composition");
      }
    }
  }
  getRelationship(srcName, destName).setType(newType);
}


/************************************/


/**
 * @brief Changes attribute's type by the new type name.
 * 
 * @param attribute 
 * @param newTypeName 
 */
void UMLData::changeAttributeType(attr_ptr attribute, string newTypeName)
{
  if (!isValidName(newTypeName))
    throw std::runtime_error("New type name is not valid");
  else {
    attribute->changeType(newTypeName);
  }
}


/************************************/


/**
 * @brief Takes in the class name (string), a shared method pointer, the name of the parameter, 
 * and the new type, and changes the parameter's type accordingly.
 * 
 * @param className
 * @param methodIter 
 * @param oldParamType 
 * @param newParamType 
 */
void UMLData::changeParameterType(string className, method_ptr methodIter, string paramName, string newParamType)
{
  method_ptr testAttribute = std::make_shared<UMLMethod>(methodIter->getAttributeName(), methodIter->getType(), 
    std::dynamic_pointer_cast<UMLMethod>(methodIter)->getParam());

  testAttribute->changeParameterType(paramName, newParamType);

  if (getClass(className).checkAttribute(testAttribute)) {
    throw std::runtime_error("Parameter type cannot be changed due to conflicts with other overloads");
  }

  else if (!isValidName(newParamType))
    throw std::runtime_error("New attribute name is not valid");

  methodIter->changeParameterType(paramName, newParamType); 
}


/**************************************************************/
//BOOLS


/**
 * @brief Checks if class exists within classses list (string argument).
 * 
 * @param name 
 * @return true 
 * @return false 
 */
bool UMLData::doesClassExist(const string& name)
{
  list<UMLClass>::iterator findIter = findClass(name);
  if (findIter == classes.end())
    return false;
  return true;
}


/************************************/


/**
 * @brief Checks to see if relationship exists.
 * 
 * @param source 
 * @param destination 
 * @return true 
 * @return false 
 */
bool UMLData::doesRelationshipExist(string source, string destination)
{
  int location = findRelationship(getClass(source), getClass(destination));
  if (location < 0)
    return false;
  
  return true;
}


/************************************/


/**
 * @brief Takes in 2 strings (class name and field name) and 
 * checks if field exists in current class.
 * 
 * @param className 
 * @param fieldName 
 * @return true 
 * @return false 
 */
bool UMLData::doesFieldExist(string className, string fieldName)
{
  UMLClass currentClass = getClassCopy(className);
  
  for(auto iter : currentClass.getAttributes())
  {
    if(iter->identifier() == "field" && iter->getAttributeName() == fieldName)
      return true;
  }
  return false;
}


/************************************/


/**
 * @brief Takes in a shared method pointer and a string, and
 * checks to see if the specified parameter exists in the 
 * current class.
 * 
 * @param methodIter 
 * @param paramName 
 * @return true 
 * @return false 
 */
bool UMLData::doesParameterExist(method_ptr methodIter, string paramName)
{
  std::list<UMLParameter> parameters = methodIter->getParam();
  
  for (UMLParameter element : parameters)
  {
    if(paramName == element.getName())
      return true;
  }
  return false;
}


/************************************/


/**
 * @brief Checks if identiifier name is valid.
 * 
 * @param name 
 * @return true 
 * @return false 
 */
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


/**************************************************************/
//TO BE DELETED

/**
 * @brief Adds parameter to a given method.
 * 
 * @param method 
 * @param paramName 
 * @param paramType 
 */
void UMLData::addParameter(method_ptr method, string paramName, string paramType)
{
  if (!isValidName(paramName))
    throw std::runtime_error("Parameter name is not valid");
  else if (!isValidName(paramType))
    throw std::runtime_error("Parameter type is not valid");
  else 
  {
    for (UMLParameter param : method->getParam()) { 
      if (param.getName() == paramName) {
        throw std::runtime_error("Parameter already exists");
      }
    }
  }
  method->addParam(UMLParameter(paramName, paramType));
}

/************************************/

/**
 * @brief Deletes parameter from given method
 * 
 * @param method 
 * @param paramName 
 */
void UMLData::deleteParameter(method_ptr method, string paramName) 
{
  method->deleteParameter(paramName);
}


/************************************/


/**
 * @brief THIS WILL BE DELETED!!!!!!!!!!!!!!
 * 
 * @param className 
 * @param attributeName 
 */
void UMLData::removeClassAttribute(string className, string attributeName)
{
  for (attr_ptr attr : getClass(className).getAttributes()) {
    if (attr->getAttributeName() == attributeName) {
      getClass(className).deleteAttribute(attributeName);
      return;
    }
  }
  throw std::runtime_error("Attribute does not exist");
}



/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                           PRIVATE                            |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/


/**
 * @brief Finds class in classes list returns first matching iterator or 
 * returns end() if no matches.
 * 
 * @param name 
 * @return list<UMLClass>::iterator 
 */
list<UMLClass>::iterator UMLData::findClass(string name)
{
  list<UMLClass>::iterator findIter = std::find(classes.begin(), classes.end(), UMLClass(name));
  return findIter;
}

/************************************/

/**
 * @brief Alternate find class using a reference to a UMLClass object.
 * 
 * @param uclass 
 * @return list<UMLClass>::iterator 
 */
list<UMLClass>::iterator UMLData::findClass(const UMLClass& uclass)
{
  list<UMLClass>::iterator findIter = std::find(classes.begin(), classes.end(), uclass);
  return findIter;
}

/************************************/

/**
 * @brief Finds attribute by name and returns index within the attribute's
 * vector, returns -1 if not found.
 * 
 * @param name 
 * @param attributes 
 * @return int 
 */
int UMLData::findAttribute(string name, const vector<attr_ptr>& attributes)
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

/************************************/

/**
 * @brief Finds relationship using two UML classes and returns index within
 * member classes vector.
 * 
 * @param sourceClassIn 
 * @param destClassIn 
 * @return int 
 */
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

/************************************/

/**
 * @brief Gets class reference for the given name.
 * 
 * @param name 
 * @return UMLClass& 
 */
UMLClass& UMLData::getClass(string name)
{
  list<UMLClass>::iterator findIter = findClass(name);
  if (findIter == classes.end())
    throw std::runtime_error("Class not found");
  return *findIter;
}

/************************************/

/**
 * @brief Takes in relationship object and adds it to relationship vector.
 * 
 * @param relIn 
 */
void UMLData::addRelationship(const UMLRelationship& relIn)
{
  // Check to see if relationship already exists
  int loc = findRelationship(relIn.getSource(), relIn.getDestination());
  if (loc >= 0)
    throw std::runtime_error("New relationship already exists");
  // Generalization/realization check for self relationships
  else if (relIn.getType() == generalization || relIn.getType() == realization) {
    if (relIn.getSource().getName() == relIn.getDestination().getName()) {
      throw std::runtime_error("Cannot have self-relationship of generalizations or realizations");
    }
  }
  // Composition check for duplicate destinations
  else if (relIn.getType() == composition) {
    for(UMLRelationship relationship : getRelationships()) {
      // Need to check for identical destination name and type
      if (relationship.getDestination().getName() == relIn.getDestination().getName()
        && relationship.getType() == composition) {
        throw std::runtime_error("Class can not be the destination for more than one composition");
      }
    }
  }
  relationships.push_back(relIn); 
}