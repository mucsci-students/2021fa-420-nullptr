/*
  Filename   : UMLField.cpp
  Description: Implementation of a field.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "include/UMLField.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
//--------------------------------------------------------------------

// Creates a UMLField object with the constructor's parameters as its fields
UMLField::UMLField(string newName, string newType)
:UMLAttribute(newName, newType)
{
}

// Identifies this attribute as a field
string UMLField::identifier()
{
	return "field";
}