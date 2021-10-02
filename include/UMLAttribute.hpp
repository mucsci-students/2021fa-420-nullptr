#pragma once
/*
  Filename   : UMLAttribute.hpp
  Description: Serves as an object for which information about an attribute
  in the UML diagram is stored. Stored as object for the sake of further
  implementation in later iterations.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
//--------------------------------------------------------------------

class UMLAttribute
{
	private:
		// Name of attribute
		string attributeName;

	public:
		// Constructor for attribute objects
		UMLAttribute(string newAttribute);

		// Grab name of the given attribute
		string getAttributeName() const;

		// Change name of the given attribute
		void changeName(string newAttributeName);

};