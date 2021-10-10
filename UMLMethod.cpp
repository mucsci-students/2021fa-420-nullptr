/*
  Filename   : UMLMethod.cpp
  Description: Implementation of a method.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include <vector>
#include <list>
#include "include/UMLMethod.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
//--------------------------------------------------------------------

// Creates a UMLMethod object with the constructor's parameters as its fields
UMLMethod::UMLMethod(string newName, string newType, std::list<UMLParameter> newParam)
:UMLAttribute(newName, newType)
,parameterList(newParam)
{
}

// Returns a list of all of the method's parameters
std::list<UMLParameter> UMLMethod::getParam()
{
	return parameterList;
}

// Changes the list of the method's parameters to match the parameter
void UMLMethod::setParam(std::list<UMLParameter> newParam)
{
	parameterList = newParam;
}

// Adds a parameter to the list of parameters
void UMLMethod::addParam(UMLParameter newParam)
{
	parameterList.push_back(newParam);
}

// Identifies this attribute as a method
string UMLMethod::identifier()
{
	return "method";
}

// Delete parameter from parameter vector
void UMLMethod::deleteParameter(string name)
{
	auto paramIndex = parameterList.begin();
	for(auto paramIndex = parameterList.begin(); paramIndex != parameterList.end(); ++paramIndex)
	{
		if (paramIndex->getName() == name)
		{
			parameterList.erase(paramIndex);
			return;
		}
	}
	throw
		"Parameter not found.";
}