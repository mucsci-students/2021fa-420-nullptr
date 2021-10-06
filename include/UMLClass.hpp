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
		vector<UMLAttribute*> classAttributesP;

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
        void addAttributeP(UMLAttribute* newAttribute);

		// Changes name of attribute within class
		void changeAttributeName(string oldAttributeName, string newAttributeName);

		// Removes attribute from attribute vector
		vector<UMLAttribute>::iterator deleteAttribute(string attributeName);

		// Finds attribute within attribute vector
		vector<UMLAttribute>::iterator findAttribute(string attributeName);

		// OLD Returns vector of attributes 
		vector<UMLAttribute> getAttributes() const;

		// Returns vector pointer of attributes 
		vector<UMLAttribute*> getAttributesP() const;
};