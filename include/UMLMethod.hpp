#pragma once
/*
  Filename   : UMLMethod.hpp
  Description: Serves as an object for which information about a method 
	is stored.
*/

// --------------------------------------------------------------------
//  System includes
#include <string>
#include <vector>
#include "UMLParameter.hpp"
// --------------------------------------------------------------------

// --------------------------------------------------------------------
//  Using declarations
using std::string;
using std::vector;
// --------------------------------------------------------------------

class UMLMethod
{
	private:

		// Name of method
		string name;

		// Type of the returned value
		string returnType;

		// List of parameters for the method
		vector<UMLParameter> param;

	public:

		// Creates a UMLMethod object with the constructor's parameters as its fields
		UMLMethod(string newName, string newReturnType, vector<UMLParameter> newParam);

		// Returns the method's name
		string 
		getName();

		// Returns the method's return type
		string
		getReturnType();

		// Returns a list of all of the method's parameters
		vector<UMLParameter>
		getParam();

		// Changes the method's name to match the parameter
		void
		setName(string newName);

		// Changes the method's return type to match the parameter
		void
		setReturnType(string newReturnType);

		// Changes the list of the method's parameters to match the parameter
		void
		setParam(vector<UMLParameter> newParam);
};