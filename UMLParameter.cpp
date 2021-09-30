#pragma once
/*
  Filename   : UMLParameter.cpp
  Description: Serves as an object for which information about a parameter
  for methods and fields is stored.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "UMLParameter.hpp"
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
