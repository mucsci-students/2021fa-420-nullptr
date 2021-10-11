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

// Constructor for parameter objects
UMLParameter::UMLParameter(string name, string type) 
:name(name)
,type(type)
{	
}

// Grab name of the given parameter
string UMLParameter::getName() const
{
	return name;
}

// Change name of the given parameter
void UMLParameter::changeName(string newName)
{
	name = newName;
}

// Grab type of the given parameter
string UMLParameter::getType() const
{
	return type;
}

// Change type of the given parameter
void UMLParameter::changeType(string newType)
{
	type = newType;
}
