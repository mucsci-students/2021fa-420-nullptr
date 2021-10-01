#pragma once
/*
  Filename   : UMLParameter.cpp
  Description: Implementation of a parameter.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "include/UMLParameter.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
//--------------------------------------------------------------------

UMLParameter::UMLParameter(string name, string type) 
{
	UMLParameter::name = name;
	UMLParameter::type = type;
}

string UMLParameter::getName() const
{
	return name;
}

void UMLParameter::changeName(string newName)
{
	name = newName;
}

string UMLParameter::getType() const
{
	return type;
}

void UMLParameter::changeType(string newType)
{
	type = newType;
}
