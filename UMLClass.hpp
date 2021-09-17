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
		vector<UMLAttribute> classAttributes;

	public:
		// Params: newClass (name of class)
		// Constructor for class object without attributes
		UMLClass(string newClass);

		// Params: newClass (name of class), attributes (vector of attributes)
		// Constructor for class object with attributes
		UMLClass(string newClass, const std::vector<UMLAttribute>& attributes);

		// Grab name from given class object
		string getName() const;

		// Params: string newClassName (name of class to be changed)
		// Change name of given class object
		void changeName(string newClassName);

		// Params: UMLAttribute newAttribute (attribute object to be added)
		// Adds attribute to attribute vector
		void addAttribute(UMLAttribute newAttribute);

		// Params: string attributeName (name of attribute to be deleted)
		// Removes attribute from attribute vector
		vector<UMLAttribute>::iterator deleteAttribute(string attributeName);

		// Params: string attributeName (name of attribute to be found) 
		// Finds attribute within attribute vector
		vector<UMLAttribute>::iterator findAttribute(string attributeName);

		// Returns vector of attributes 
		vector<UMLAttribute> getAttributes();
};

UMLClass::UMLClass(string newClass) 
:className(newClass)
{
}

UMLClass::UMLClass(string newClass, const std::vector<UMLAttribute>& attributes) 
:className(newClass)
,classAttributes(attributes)
{
}

string UMLClass::getName() const
{
	return className;
}

void UMLClass::changeName(string newClassName)
{
	className = newClassName;
}

void UMLClass::addAttribute(UMLAttribute newAttribute) 
{
	//should be check for dup
	for(UMLAttribute attribute : classAttributes)
	{
		if(attribute.getAttributeName() == newAttribute.getAttributeName())
			throw "No duplicate attributes";
	}
	classAttributes.push_back(newAttribute);
}

vector<UMLAttribute>::iterator UMLClass::deleteAttribute(string attributeName) 
{
	auto attribute = findAttribute(attributeName);
	// attribute not found 
	if (attribute == classAttributes.end()) {
		// return empty if attribute not found
		return classAttributes.end();
	}
	classAttributes.erase(attribute);
	return attribute;
}

vector<UMLAttribute>::iterator UMLClass::findAttribute(string attributeName) 
{
	for (vector<UMLAttribute>::iterator ptr = classAttributes.begin(); ptr != classAttributes.end(); ++ptr) {
		if (ptr->getAttributeName() == attributeName){
			return ptr;
		}
	}
	// return empty if attribute not found
	return classAttributes.end();
}

vector<UMLAttribute> UMLClass::getAttributes() 
{
	return classAttributes;
}