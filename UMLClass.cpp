/*
  Filename   : UMLClass.cpp
  Description: Implementation of a class.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLClass.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLMethod.hpp"
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

// Adds attribute to attribute vector with a smart pointer
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

// Changes name of attribute within class using smart ptr 
void changeAttributeName(std::shared_ptr<UMLAttribute> attribute, string newAttributeName) 
{
	attribute->changeName(newAttributeName);
}

// Remove attributes from pointer vector
void UMLClass::deleteAttribute(string attributeName) 
{
	int loc = findAttribute(attributeName);
	if (loc < 0)
	{
		throw "Attribute not found";
	}

	classAttributes.erase(classAttributes.begin() + loc);

}

// Remove attribute from pointer vector by pointer
void UMLClass::deleteAttribute(std::shared_ptr<UMLAttribute> attributePtr)
{
	for(int i = 0; i < classAttributes.size(); i++)
	{
		if(attributePtr == classAttributes[i])
		{
			classAttributes.erase(classAttributes.begin() + i);
			return;
		}
	}
	throw "Attribute not found";
}

// OLD Finds attribute within pointer vector
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

// Checks attribute within pointer vector to see if it causes identical attributes to exist
bool UMLClass::checkAttribute(std::shared_ptr<UMLAttribute> attribute)
{
	if(attribute->identifier() == "field") {
		for (int i = 0; i < classAttributes.size(); ++i) {
			// Check if the name is the same--doesn't matter if it's a field or method
			if (classAttributes[i]->getAttributeName() == attribute->getAttributeName()) {
				return true;
			}
		}
		// Attribute does not break identitical attribute rules
		return false;
	}
	else if (attribute->identifier() == "method") {
		for (int i = 0; i < classAttributes.size(); ++i) {
			// If they share the same name but the other one is a field, then the attribute cannot exist
			if (classAttributes[i]->getAttributeName() == attribute->getAttributeName() && classAttributes[i]->identifier() == "field") {
				return true;
			}
			else if (classAttributes[i]->getAttributeName() == attribute->getAttributeName() && classAttributes[i]->identifier() == "method"){
				if(std::dynamic_pointer_cast<UMLMethod>(classAttributes[i])->getParam() == std::dynamic_pointer_cast<UMLMethod>(attribute)->getParam()) {
					return true;
				}
			}
		}
		// Attribute does not break identitical attribute rules
		return false;
	}
	// Attribute does not break identitical attribute rules
	return false;
}

// OLD Finds attribute within pointer vector, returns smart pointer
std::shared_ptr<UMLAttribute> UMLClass::getAttribute(string attributeName)
{
	int loc = findAttribute(attributeName);
	if (loc < 0)
	{
		throw "Attribute not found";
	}
	return classAttributes[loc];
}

// Returns vector pointer of attributes 
vector<std::shared_ptr<UMLAttribute>> UMLClass::getAttributes() const
{
	return classAttributes;
}