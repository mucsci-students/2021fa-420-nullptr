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

UMLField::UMLField(string newName, string newScope, string newType)
:name(newName)
,scope(newScope)
,type(newType)
{
}

string UMLField::getName()
{
	return name;
}

string UMLField::getScope()
{
	return scope;
}

string UMLField::getType()
{
	return type;
}

void UMLField::setName(string newName)
{
	name = newName;
}

void UMLField::setScope(string newScope)
{
	scope = newScope;
}

void UMLField::setType(string newType)
{
	type = newType;
}
