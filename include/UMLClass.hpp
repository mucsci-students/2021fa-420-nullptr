#pragma once
/*
  Filename   : UMLClass.hpp
  Description: Serves as an object for which information about a class
  in the UML diagram is stored. 
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "UMLAttribute.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
//--------------------------------------------------------------------

class UMLClass
{
	private:
		// Name of class and a vector of all of its attributes as objects
		string className;
		vector<UMLAttribute> classAttributes; //OLD
		vector<std::shared_ptr<UMLAttribute>> classAttributesP;

	public:
		// Constructor for class object without attributes
		UMLClass(string newClass);

		// Constructor for class object with attributes
		UMLClass(string newClass, const std::vector<UMLAttribute>& attributes);

		// Grab name from given class object
		string getName() const;

		// Change name of given class object
		void changeName(string newClassName);

		// Adds attribute to attribute vector
		void addAttribute(UMLAttribute newAttribute);

		// temp
        void addAttributeP(std::shared_ptr<UMLAttribute> newAttribute);

		// Changes name of attribute within class
		void changeAttributeName(string oldAttributeName, string newAttributeName);

		// Removes attribute from attribute vector
		vector<UMLAttribute>::iterator deleteAttribute(string attributeName);

		// TEMP remove from pointer vector
		void deleteAttributeP(string attributeName);

		// Finds attribute within attribute vector
		vector<UMLAttribute>::iterator findAttribute(string attributeName);

		// TEMP find attribute within pointer vector
		int findAttributeP(string attributeName);

		std::shared_ptr<UMLAttribute> getAttribute(string attributeName); 

		// OLD Returns vector of attributes 
		vector<UMLAttribute> getAttributes() const;

		// Returns vector pointer of attributes 
		vector<std::shared_ptr<UMLAttribute>> getAttributesP() const;

		bool operator==(const UMLClass& other) {return (this->getName() == other.getName());}
};