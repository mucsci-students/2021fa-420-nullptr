/*
  Filename   : UMLClass.cpp
  Description: Implementation of a class.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLClass.hpp"
#include "include/UMLAttribute.hpp"
//--------------------------------------------------------------------

// Constructor for class object without attributes
UMLClass::UMLClass(string newClass) 
:className(newClass)
{
}

// Constructor for class object with attributes
UMLClass::UMLClass(string newClass, const std::vector<UMLAttribute>& attributes) 
:className(newClass)
{
	for (UMLAttribute attr : attributes)
	{
		addAttribute(attr);
	}
}

// Grab name from given class object
string UMLClass::getName() const
{
	return className;
}

// Change name of given class object
void UMLClass::changeName(string newClassName)
{
	className = newClassName;
}

// Adds attribute to attribute vector
void UMLClass::addAttribute(const UMLAttribute& newAttribute) 
{
	addAttribute(std::make_shared<UMLAttribute>(newAttribute));
}
// TEMP
void UMLClass::addAttribute(std::shared_ptr<UMLAttribute> newAttribute) 
{
	for(auto attribute : classAttributes)
	{
		if(attribute->getAttributeName() == newAttribute->getAttributeName())
			throw "No duplicate attributes";
	}
	classAttributes.push_back(newAttribute); //NEW POINTER VECTOR
}

// Changes name of attribute within class
void UMLClass::changeAttributeName(string oldAttributeName, string newAttributeName)
{
	getAttribute(oldAttributeName)->changeName(newAttributeName);
}
// TEMP remove attribute from pointer vector
void UMLClass::deleteAttribute(string attributeName) 
{
	int loc = findAttribute(attributeName);
	if (loc < 0)
	{
		throw "attriubte not found";
	}

	classAttributes.erase(classAttributes.begin() + loc);

}

// TEMP finds attribute within pointer vector
int UMLClass::findAttribute(string attributeName) 
{
	for (int i = 0; i < classAttributes.size(); ++i) {
		if (classAttributes[i]->getAttributeName() == attributeName){
			return i;
		}
	}
	// return -1 if attribute not found
	return -1;
}

std::shared_ptr<UMLAttribute> UMLClass::getAttribute(string attributeName)
{
	int loc = findAttribute(attributeName);
	if (loc < 0)
	{
		throw "attribute not found";
	}

	return classAttributes[loc];
	
}

// Returns vector pointer of attributes 
vector<std::shared_ptr<UMLAttribute>> UMLClass::getAttributes() const
{
	return classAttributes;
}