#pragma once
/*
  Filename   : UMLClass.cpp
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
using namespace std;
//--------------------------------------------------------------------

class UMLClass
{
	private:
		// Name of class and a vector of all of its attributes as objects
		string className;
		vector<UMLAttribute> classAttributes;

	public:
		// Constructor for class objects

		UMLClass() {}

		UMLClass (string newClass) : 
			className (newClass)
		{
		}

		UMLClass(string newClass, const std::vector<UMLAttribute>& attributes)
		{
			className = newClass;
			classAttributes = attributes;
		}

		// Grab name from given class object
		string getName () const
		{
			return className;
		}

		// Change name of given class object
		void changeName (string newClassName)
		{
			className = newClassName;
		}

		// Adds attribute to attribute vector
		void addAttribute (UMLAttribute newAttribute) {
			classAttributes.push_back(newAttribute);
		}

		// Removes attribute from attribute vector
		vector<UMLAttribute>::iterator deleteAttribute (string attributeName) {
			auto attribute = findAttribute(attributeName);
			// attribute not found 
			if (attribute == classAttributes.end()) {
				// 
				return classAttributes.end();
			}
			classAttributes.erase(attribute);
			return attribute;
		}

		// Finds attribute within attribute vector
		vector<UMLAttribute>::iterator findAttribute (string attributeName) {
			for (vector<UMLAttribute>::iterator ptr = classAttributes.begin(); ptr != classAttributes.end(); ++ptr){
				if (ptr->getAttributeName() == attributeName){
					return ptr;
				}
			}
			// return empty if attribute not found
			return classAttributes.end();
		}

		// Returns vector of attributes 
		vector<UMLAttribute> getAttributes () {
			return classAttributes;
		}
};