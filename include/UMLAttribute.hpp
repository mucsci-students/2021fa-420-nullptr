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
		string name;

		// Type of attribute
		string type;

	public:
		// OLD Constructor for attribute objects without a type
		UMLAttribute(string newName);

		// Constructor for attribute objects with a type
		UMLAttribute(string newName, string newType);

		// Grab name of the given attribute
		string getAttributeName() const;

		// Change name of the given attribute
		void changeName(string newName);

		// Grab type of the given attribute
		string getType() const;

		// Change type of the given attribute
		void changeType(string newType);
        
		// Placeholder to identifiy what type an attribute is
		virtual string identifier();
};