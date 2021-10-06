/*
  Filename   : UMLClass.cpp
  Description: Implementation of a class.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLClass.hpp"
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
void UMLClass::addAttribute(UMLAttribute newAttribute) 
{
	//should be check for dup
	for(UMLAttribute attribute : classAttributes)
	{
		if(attribute.getAttributeName() == newAttribute.getAttributeName())
			throw "No duplicate attributes";
	}
	classAttributes.push_back(newAttribute); //OLD
}
// TEMP
void UMLClass::addAttributeP(UMLAttribute* newAttribute) 
{
	//
	classAttributesP.push_back(newAttribute); //NEW POINTER VECTOR
}

// Changes name of attribute within class
void UMLClass::changeAttributeName(string oldAttributeName, string newAttributeName)
{
	(*findAttribute(oldAttributeName)).changeName(newAttributeName);
}

// Removes attribute from attribute vector
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

// TEMP remove attribute from pointer vector
vector<UMLAttribute*>::iterator UMLClass::deleteAttributeP(string attributeName) 
{
	auto attribute = findAttributeP(attributeName);
	// attribute not found 
	if (attribute == classAttributesP.end()) {
		// return empty if attribute not found
		return classAttributesP.end();
	}
	classAttributesP.erase(attribute);
	return attribute;
}

// Finds attribute within attribute vector
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

// TEMP finds attribute within pointer vector
vector<UMLAttribute*>::iterator UMLClass::findAttributeP(string attributeName) 
{
	for (vector<UMLAttribute*>::iterator ptr = classAttributesP.begin(); ptr != classAttributesP.end(); ++ptr) {
		if ((*ptr)->getAttributeName() == attributeName){
			return ptr;
		}
	}
	// return empty if attribute not found
	return classAttributesP.end();
}

// OLD Returns vector of attributes 
vector<UMLAttribute> UMLClass::getAttributes() const
{
	return classAttributes;
}

// Returns vector pointer of attributes 
vector<UMLAttribute*> UMLClass::getAttributesP() const
{
	return classAttributesP;
}