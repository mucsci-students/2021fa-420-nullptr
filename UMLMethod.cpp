/*
  Filename   : UMLMethod.cpp
  Description: Implementation of a method.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include <vector>
#include "include/UMLMethod.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
//--------------------------------------------------------------------

UMLMethod::UMLMethod(string newName, string newReturnType, vector<string> newParam)
:name(newName)
,returnType(newReturnType)
,param(newParam)
{
}

string UMLMethod::getName()
{
	return name;
}

string UMLMethod::getReturnType()
{
	return returnType;
}

vector<string> UMLMethod::getParam()
{
	return param;
}

void UMLMethod::setName(string newName)
{
	name = newName;
}

void UMLMethod::setReturnType(string newReturnType)
{
	returnType = newReturnType;
}

void UMLMethod::setParam(vector<string> newParam)
{
	param = newParam;
}
