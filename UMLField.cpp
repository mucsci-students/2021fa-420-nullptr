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

UMLField::UMLField(string newName, string newType)
:UMLAttribute(newName, newType)
{
}

string UMLField::identifier()
{
	return "field";
}