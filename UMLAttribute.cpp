/*
  Filename   : UMLAttribute.cpp
  Description: Implementation of an attribute.
*/

//--------------------------------------------------------------------
// System includes
#include "UMLAttribute.hpp"
//--------------------------------------------------------------------

// Constructor for attribute objects
UMLAttribute::UMLAttribute(string newAttribute) 
:attributeName(newAttribute)
{
}

// Grab name of the given attribute
string UMLAttribute::getAttributeName() const
{
	return attributeName;
}

// Change name of the given attribute
void UMLAttribute::changeName(string newAttributeName)
{
	attributeName = newAttributeName;
}