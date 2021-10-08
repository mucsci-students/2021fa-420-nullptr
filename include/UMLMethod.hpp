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
#include "UMLAttribute.hpp"
// --------------------------------------------------------------------

// --------------------------------------------------------------------
//  Using declarations
using std::string;
using std::vector;
// --------------------------------------------------------------------

class UMLMethod : public UMLAttribute
{
	private:

		// List of parameters for the method
		vector<UMLParameter> param;

	public:

		// Creates a UMLMethod object with the constructor's parameters as its fields
		UMLMethod(string newName, string newType, vector<UMLParameter> newParam);

		// Returns a list of all of the method's parameters
		vector<UMLParameter> getParam();

		// Changes the list of the method's parameters to match the parameter
		void setParam(vector<UMLParameter> newParam);

		// Adds a parameter to the list of parameters
		void addParam(UMLParameter newParam);

		// Identifies this attribute as a Method
		string identifier();
};