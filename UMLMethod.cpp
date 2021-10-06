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

UMLMethod::UMLMethod(string newName, string newType, vector<UMLParameter> newParam)
:UMLAttribute(newName, newType)
,param(newParam)
{
}

vector<UMLParameter> UMLMethod::getParam()
{
	return param;
}

void UMLMethod::setParam(vector<UMLParameter> newParam)
{
	param = newParam;
}

void UMLMethod::addParam(UMLParameter newParam)
{
	param.push_back(newParam);
}

string UMLAttribute::identifier()
{
	return "method";
}