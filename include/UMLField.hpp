#pragma once
/*
  Filename   : UMLField.hpp
  Description: Serves as an object for which information about a field 
	for methods are stored.
*/

// --------------------------------------------------------------------
//  System includes
#include <string>
#include "UMLAttribute.hpp"
// --------------------------------------------------------------------

// --------------------------------------------------------------------
//  Using declarations
using std::string;
// --------------------------------------------------------------------

class UMLField : public UMLAttribute
{
	private:
		
		// No private methods

	public:

		// Creates a UMLField object with the constructor's parameters as its fields
		UMLField(string newName, string newType);

		// Identifies this attribute as a field
		string identifier();
};
