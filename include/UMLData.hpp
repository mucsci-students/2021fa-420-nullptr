#pragma once
/*
  Filename   : UMLData.hpp
  Description: Stores the relationship and class information, serving as
  the primary model for the UML class diagram.
*/

//--------------------------------------------------------------------
// System includes
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
#include <vector>
#include <iostream>
#include "json/json.hpp"
#include <list>
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
using json = nlohmann::json;
//--------------------------------------------------------------------

class UMLData
{
    private:

        std::list<UMLClass> classes;
        vector<UMLRelationship> relationships;

    public: 
        // Empty constructor
        UMLData();

        // Constructor that takes in vector of classes 
        UMLData(const vector<UMLClass>& vclass);

        // Returns vector of all classes
        std::list<UMLClass> getClasses() const;

        // Return a single class
        UMLClass getClassCopy(std::string name);
   
        // Returns vector of all relationships
        vector<UMLRelationship> getRelationships() const;

        // Takes in class and adds it to vector
        void addClass(const UMLClass& classIn);

        // Takes in string name and creates class and adds to classes vector
        void addClass(string name);

        // Takes in name and vector of attributes and creates class and adds to vector of classes
        void addClass(string name, vector<UMLAttribute> attributes);

        // Takes in src string, dest string, and type int creates relationship and adds to relationships vector
        void addRelationship(string srcName, string destName, int type);
        
        // Takes in className string and returns a vector of all the relationships associated with that class
        vector<UMLRelationship> getRelationshipsByClass(string className);

        // Deletes relationshp based on two strings
        void deleteRelationship(string srcName, string destName);

        // Returns string representation of relationship type
        string getRelationshipType(const string& srcName, const string& destName);

        // Modifies relationship type given a new relationship type 
        void changeRelationshipType(const string& srcName, const string& destName, int newType);

        // Gets relationship reference for the given string class names
        UMLRelationship& getRelationship(string srcName, string destName);

        // Deletes a class by string in the classes vector
        void deleteClass(string name);

        // Changes class name from old name and new name
        void changeClassName(string oldName, string newName);

        // Gets class attributes for a className class and returns them in a vector
        vector<std::shared_ptr<UMLAttribute>> getClassAttributes(string className);

        // Adds class attribute to specified className
        void addClassAttribute(string className, UMLAttribute attribute);

        // Adds class attribute to specified className using a smart pointer
        void addClassAttribute(string className, std::shared_ptr<UMLAttribute> attribute);

        // Removes className class attribute by the name
        void removeClassAttribute(string className, string attributeName);

        // Removes className class attribute by smart pointer
        void removeClassAttribute(string className, std::shared_ptr<UMLAttribute> attr);

        // Changes className class attribute by the new attribute name
        void changeAttributeName(string className, string oldAttributeName, string newAttributeName);

        // Checks if class/attribute name is valid
        bool isValidName(string name);

        // Checks if class exists within classses list (string argument) 
        bool doesClassExist(const string& name);

        // Checks if class exists with classes list (class argument)
        bool doesClassExist(const UMLClass& uclass);

        // Generates json file given a set of data
        json getJson();

    private:
        // Finds class by name and returns iterator within member classes list, returns end() if not found
        std::list<UMLClass>::iterator findClass(string name);
        
        // Alternate find class using a reference to a UMLClass object
        std::list<UMLClass>::iterator findClass(const UMLClass& uclass);

        // Finds attribute by name and returns index within the attribute's vector, returns -1 if not found
        int findAttribute(string name, const vector<std::shared_ptr<UMLAttribute>>&);

        // Finds relationship using two UML classes and returns index within member classes vector
        int findRelationship(const UMLClass& sourceClassIn, const UMLClass& destClassIn);

        // Gets class reference for the given name
        UMLClass& getClass(string name);

        // Takes in relationship object and adds it to relationship vector
        void addRelationship(const UMLRelationship& relationshipIn);
};