#pragma once
/*
  Filename   : UMLData.hpp
  Description: Stores the relationship and class information, serving as
  the primary model for the UML class diagram.
*/

/**************************************************************/
// System includes
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLMethod.hpp"
#include "UMLRelationship.hpp"
#include <vector>
#include <iostream>
#include "json/json.hpp"
#include <list>


/**************************************************************/
// Using declarations

using std::string;
using std::vector;
using std::list;
using std::shared_ptr;
using json = nlohmann::json;


//--------------------------------------------------------------------
// Memento design pattern
// Holds current state of UMLData 
class UMLDataSnapshot
{
    private:
        friend class UMLData;
        list<UMLClass> classes;
        vector<UMLRelationship> relationships;
    public:
        UMLDataSnapshot(const list<UMLClass>& classesIn, vector<UMLRelationship> relationshipsIn)
        : classes(classesIn), 
        relationships(relationshipsIn) 
        {}
};
//***********************************************************************

class UMLData
{
  private:

    /********************************/
    // Typedefs

    typedef shared_ptr<UMLAttribute> attr_ptr;
    typedef shared_ptr<UMLMethod> method_ptr;
    
    /********************************/
    // Global vars

    list<UMLClass> classes;
    vector<UMLRelationship> relationships;

  public: 

    /********************************/
    // Constructors


    // Empty constructor
    UMLData();

    // Constructor that takes in vector of classes 
    UMLData(const vector<UMLClass>& vclass);


    /********************************/
    //Get Collections


    // Returns vector of all classes
    list<UMLClass> getClasses() const;

    // Returns vector of all relationships
    vector<UMLRelationship> getRelationships() const;
    
    // Takes in className string and returns a vector of all the relationships associated with that class
    vector<UMLRelationship> getRelationshipsByClass(string className);

    // Gets class attributes for a className class and returns them in a vector
    vector<attr_ptr> getClassAttributes(string className);


    /********************************/
    //Get Data


    // Return a single class
    UMLClass getClassCopy(string name);

    // Gets relationship reference for the given string class names
    UMLRelationship& getRelationship(string srcName, string destName);

    // Generates json file given a set of data
    json getJson();

    // Returns string representation of relationship type
    string getRelationshipType(const string& srcName, const string& destName);

    //---------------------------------------------------
    // Memento pattern
    // Returns const snapshot of UMLData object
    const UMLDataSnapshot make_snapshot();

    // Restores UMLData object from a snapshot
    void restore(const UMLDataSnapshot& snapshot);
    //---------------------------------------------------


    /********************************/
    //Adding


    // Takes in class and adds it to vector
    void addClass(const UMLClass& classIn);

    // Takes in string name and creates class and adds to classes vector
    void addClass(string name);

    // Takes in name and vector of attributes and creates class and adds to vector of classes
    void addClass(string name, vector<UMLAttribute> attributes);

    // Takes in src string, dest string, and type int creates relationship and adds to relationships vector
    void addRelationship(string srcName, string destName, int type);

    // Adds class attribute to specified className
    void addClassAttribute(string className, UMLAttribute attribute);

    // Adds class attribute to specified className using a smart pointer
    void addClassAttribute(string className, attr_ptr attribute);

    // Adds parameter to a given method
    void addParameter(method_ptr method, string paramName, string paramType);


    /********************************/
    //Deleting


    // Deletes a class by string in the classes vector
    void deleteClass(string name);

    // Deletes relationshp based on two strings
    void deleteRelationship(string srcName, string destName);

    // Removes className class attribute by the name
    void removeClassAttribute(string className, string attributeName);

    // Removes className class attribute by smart pointer
    void removeClassAttribute(string className, attr_ptr attr);

    // Deletes parameter from given method
    void deleteParameter(method_ptr method, string paramName);


    /********************************/
    //Renaming
    

    // Changes class name from old name to new name
    void changeClassName(string oldName, string newName);

    // Changes className class attribute by the new attribute name
    void changeAttributeName(string className, string oldAttributeName, string newAttributeName);

    // Overload of changeAttributeName to work with a smart pointer
    void changeAttributeName(string className, attr_ptr attribute, string newAttributeName);

    // Takes in a shared method pointer, the name of the old parameter, and the new name, 
    // and renames the parameter accordingly.
    void changeParameterName(method_ptr methodIter, string oldParamName, string newParamName);
    

    /********************************/
    //Type Changing


    // Modifies relationship type given a new relationship type 
    void changeRelationshipType(const string& srcName, const string& destName, int newType);

    // Changes className class attribute's type by the new type name 
    void changeAttributeType(attr_ptr attribute, string newTypeName);

    // Takes in a shared method pointer, the name of the parameter, and the new type, 
    // and changes the parameter's type accordingly.
    void changeParameterType(method_ptr methodIter, string paramName, string newParamType);


    /********************************/
    //Bools


    // Checks if identifier name is valid
    bool isValidName(string name);

    // Checks if class exists within classses list (string argument) 
    bool doesClassExist(const string& name);

    // Checks if class exists with classes list (class argument)
    bool doesClassExist(const UMLClass& uclass);

    // Takes in 2 strings (class name and field name) and 
    // checks if field exists in current class
    bool doesFieldExist(string className, string fieldName);

    // Takes in a shared method pointer and a string, and
    // checks to see if the specified parameter exists in
    // the current class.
    bool doesParameterExist(method_ptr methodIter, string paramName);

  private:
    // Finds class by name and returns iterator within member classes list, returns end() if not found
    std::list<UMLClass>::iterator findClass(string name);
    
    // Alternate find class using a reference to a UMLClass object
    std::list<UMLClass>::iterator findClass(const UMLClass& uclass);

    // Finds attribute by name and returns index within the attribute's vector, returns -1 if not found
    int findAttribute(string name, const vector<attr_ptr>&);

    // Finds relationship using two UML classes and returns index within member classes vector
    int findRelationship(const UMLClass& sourceClassIn, const UMLClass& destClassIn);

    // Gets class reference for the given name
    UMLClass& getClass(string name);

    // Takes in relationship object and adds it to relationship vector
    void addRelationship(const UMLRelationship& relationshipIn);
};
