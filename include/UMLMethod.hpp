#pragma once
/*
  Filename   : UMLMethod.hpp
  Description: Serves as an object for which information about a method 
	is stored.
*/

// --------------------------------------------------------------------
// System includes
#include <string>
#include <vector>
#include <list>
#include "UMLParameter.hpp"
#include "UMLAttribute.hpp"
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
// --------------------------------------------------------------------

class UMLMethod : public UMLAttribute
{
	private:

		// List of parameters for the method
		std::list<UMLParameter> parameterList;

	public:

		// Creates a UMLMethod object with the constructor's parameters as its fields
		UMLMethod(string newName, string newType, std::list<UMLParameter> newParam);

		// Returns a list of all of the method's parameters
		std::list<UMLParameter> getParam();

		// Changes the list of the method's parameters to match the parameter
		void setParam(std::list<UMLParameter> newParam);

		// Adds a parameter to the list of parameters
		void addParam(UMLParameter newParam);

		// Identifies this attribute as a method
		string identifier() const;

		// Deletes a parameter from the given name
		void deleteParameter(string name);

		// Changes parameter name
		void changeParameterName(string oldParamName, string newParamName);

		// Changes parameter's type
		void changeParameterType(string paramName, string newParamType);
};