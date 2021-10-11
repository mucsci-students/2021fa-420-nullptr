/*
  Filename   : UMLAttribute.cpp
  Description: Implementation of an attribute.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLAttribute.hpp"
//--------------------------------------------------------------------

// OLD Constructor for attribute objects without a type
UMLAttribute::UMLAttribute(string newName) 
:name(newName)
{
}

// Constructor for attribute objects with a type
UMLAttribute::UMLAttribute(string newName, string newType) 
:name(newName)
,type(newType)
{
}

// Grab name of the given attribute
string UMLAttribute::getAttributeName() const
{
	return name;
}

// Change name of the given attribute
void UMLAttribute::changeName(string newName)
{
	name = newName;
}

// Grab type of the given attribute
string UMLAttribute::getType() const
{
	return type;
}

// Change type of the given attribute
void UMLAttribute::changeType(string newType)
{
	type = newType;
}

// Placeholder to identifiy what type an attribute is
string UMLAttribute::identifier()
{
	return "attribute";
}