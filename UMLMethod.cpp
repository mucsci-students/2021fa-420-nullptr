/*
  Filename   : UMLMethod.cpp
  Description: Implementation of a method.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include <vector>
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
//--------------------------------------------------------------------

// Creates a UMLMethod object with the constructor's parameters as its fields
UMLMethod::UMLMethod(string newName, string newType, vector<UMLParameter> newParam)
:UMLAttribute(newName, newType)
,param(newParam)
{
}

// Returns a list of all of the method's parameters
vector<UMLParameter> UMLMethod::getParam()
{
	return param;
}

// Changes the list of the method's parameters to match the parameter
void UMLMethod::setParam(vector<UMLParameter> newParam)
{
	param = newParam;
}

// Adds a parameter to the list of parameters
void UMLMethod::addParam(UMLParameter newParam)
{
	param.push_back(newParam);
}

// Identifies this attribute as a method
string UMLMethod::identifier()
{
	return "method";
}