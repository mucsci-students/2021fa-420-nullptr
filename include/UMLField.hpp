#pragma once
/*
  Filename   : UMLField.hpp
  Description: Serves as an object for which information about a field 
	for methods are stored.
*/

// --------------------------------------------------------------------
//  System includes
#include <string>
// --------------------------------------------------------------------

// --------------------------------------------------------------------
//  Using declarations
using std::string;
// --------------------------------------------------------------------

class UMLField
{
  private:
    
		// Name of field
		string name;

		// Scope of field
		string scope;

		// Type of field
		string type;
		  
	public:

		// Creates a UMLField object with the constructor's parameters as its fields
	  UMLField(string newName, string newScope, string newType);

		// Returns the field's name
		string 
		getName();

		// Returns the field's scope
		string 
		getScope();

		// Returns the field's type
		string 
		getType();

		// Changes the field's name to match the parameter
		void 
		setName(string newName);

		// Changes the field's scope to match the parameter
		void 
		setScope(string newScope);

		// Changes the field's type to match the parameter
		void 
		setType(string newType);
};