/*
  Filename   : UMLClass.cpp
  Description: Implementation of a class.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLClass.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLField.hpp"
#include "include/UMLMethod.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations 
using std::list;
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

// Adds attribute to attribute vector. ONLY works if raw attribute.
void UMLClass::addAttribute(const UMLAttribute& newAttribute) 
{
	// Workaround solution with errors until better one is found
	if(newAttribute.identifier() == "method") {
		throw std::runtime_error("Cannot directly add method without smart_ptr");
	}
	else if (newAttribute.identifier() == "field") {
		throw std::runtime_error("Cannot directly add field without smart_ptr");
	}
	else {
		addAttribute(std::make_shared<UMLAttribute>(newAttribute));
	}
}

// Adds attribute to attribute vector with a smart pointer
void UMLClass::addAttribute(std::shared_ptr<UMLAttribute> newAttribute) 
{
	for(auto attribute : classAttributes)
	{
		if(attribute->getAttributeName() == newAttribute->getAttributeName())
			throw std::runtime_error("No duplicate attributes");
	}
	classAttributes.push_back(newAttribute); // NEW POINTER VECTOR
}

// Changes name of attribute within class
void UMLClass::changeAttributeName(string oldAttributeName, string newAttributeName)
{
	getAttribute(oldAttributeName)->changeName(newAttributeName);
}

// Changes name of attribute within class using smart ptr 
void UMLClass::changeAttributeName(std::shared_ptr<UMLAttribute> attribute, string newAttributeName) 
{
	attribute->changeName(newAttributeName);
}

// Remove attributes from pointer vector
void UMLClass::deleteAttribute(string attributeName) 
{
	int loc = findAttribute(attributeName);
	if (loc < 0)
	{
		throw std::runtime_error("Attribute not found");
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
	throw std::runtime_error("Attribute not found");
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
// If true, it causes identical attributes. If false, it does not
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
		// Booolean to check status of parameters when checking 2 methods
		// When true, the current observed types of the param signature are identical
		bool equalParameter = false;
		
		for (int i = 0; i < classAttributes.size(); ++i) {
			// If they share the same name but the other one is a field, then the attribute cannot exist
			if (classAttributes[i]->getAttributeName() == attribute->getAttributeName() && classAttributes[i]->identifier() == "field") {
				return true;
			}
			// If they share the same name but they are both methods, check parameters
			else if (classAttributes[i]->getAttributeName() == attribute->getAttributeName() && classAttributes[i]->identifier() == "method"){
				list<UMLParameter> params1 = std::dynamic_pointer_cast<UMLMethod>(classAttributes[i])->getParam();
				list<UMLParameter> params2 = std::dynamic_pointer_cast<UMLMethod>(attribute)->getParam();
				auto param2 = params2.begin();

				if (params1.empty() && params2.empty()) {
					// Cannot overload a method with no parameters with another with no parameters
					return true;
				}

				// Compare parameters in params1 with param2 iterator 
				for (UMLParameter param : params1) {
					if (param2 == params2.end() || param.getType() != param2->getType()) {
						// Param1 has more parameters, or the types are not identical.
						// Therefore, overload rules are being followed.
						equalParameter = false;
						break;
					}
					else {
						// Iterate through param2 if params are equal at this stage
						equalParameter = true;
						param2 = std::next(param2);
					}
				}
				// If true, both methods have identical parameter types. Rules are broken
				if (equalParameter) {
					return true;
				}
				// Otherwise, loop through attributes continues
			}
		}
		// If reached, no attributes share names with this attribute, so no rules are broken
		return false;
	}
	// Attribute shouldn't break rules by default
	return false;
}

// OLD Finds attribute within pointer vector, returns smart pointer
std::shared_ptr<UMLAttribute> UMLClass::getAttribute(string attributeName)
{
	int loc = findAttribute(attributeName);
	if (loc < 0)
	{
		throw std::runtime_error("Attribute not found");
	}
	return classAttributes[loc];
}

// Returns vector pointer of attributes 
vector<std::shared_ptr<UMLAttribute>> UMLClass::getAttributes() const
{
	return classAttributes;
}

//sets the x value
void UMLClass::setX(int val)
{
	x = val;
}

//sets the y value
void UMLClass::setY(int val)
{
	y = val;
}

//gets the x value
int UMLClass::getX()
{
	return x;
}

//gets the y value
int UMLClass::getY()
{
	return y;
}
