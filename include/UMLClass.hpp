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
		vector<std::shared_ptr<UMLAttribute>> classAttributes;

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
		void addAttribute(const UMLAttribute& newAttribute);

		// temp
        void addAttribute(std::shared_ptr<UMLAttribute> newAttribute);

		// Changes name of attribute within class
		void changeAttributeName(string oldAttributeName, string newAttributeName);

		// TEMP remove from pointer vector
		void deleteAttribute(string attributeName);

		// TEMP find attribute within pointer vector
		int findAttribute(string attributeName);

		std::shared_ptr<UMLAttribute> getAttribute(string attributeName); 

		// Returns vector pointer of attributes 
		vector<std::shared_ptr<UMLAttribute>> getAttributes() const;

		bool operator==(const UMLClass& other) {return (this->getName() == other.getName());}
};