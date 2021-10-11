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
#include "UMLParameter.hpp"
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

		// Adds attribute to attribute vector with a smart pointer
        void addAttribute(std::shared_ptr<UMLAttribute> newAttribute);

		// Changes name of attribute within class
		void changeAttributeName(string oldAttributeName, string newAttributeName);

		// Changes name of attribute within class using smart ptr 
		void changeAttributeName(std::shared_ptr<UMLAttribute> attribute, string newAttributeName);

		// Remove attributes from pointer vector
		void deleteAttribute(string attributeName);

		// Remove attribute from pointer vector by pointer
		void deleteAttribute(std::shared_ptr<UMLAttribute> attributePrt);

		// Finds attribute within pointer vector
		int findAttribute(string attributeName);

		// Checks attribute within pointer vector to see if it causes identical attributes to exist
		// If true, it causes identical attributes. If false, it does not
		bool checkAttribute(std::shared_ptr<UMLAttribute> attribute);

		// OLD Finds attribute within pointer vector, returns smart pointer
		std::shared_ptr<UMLAttribute> getAttribute(string attributeName);

		// Returns vector pointer of attributes 
		vector<std::shared_ptr<UMLAttribute>> getAttributes() const;

		bool operator==(const UMLClass& other) {return (this->getName() == other.getName());}
};