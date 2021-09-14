/*
  Filename   : UMLAttribute.hpp
  Description: Serves as an object for which information about an attribute
  in the UML diagram is stored. Stored as object for the sake of further
  implementation in later iterations.
*/

/************************************************************/
// Macro guard
#ifndef UMLATTRIBUTE_HPP
#define UMLATTRIBUTE_HPP
/************************************************************/

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
		// Params: string newAttribute (name of attribute)
		// Constructor for attribute objects
		UMLAttribute(string newAttribute);

		// Grab name of the given attribute
		string getAttributeName();

		// Change name of the given attribute
		void changeName(string newAttributeName);

};

UMLAttribute::UMLAttribute(string newAttribute) 
:attributeName(newAttribute)
{
}

string UMLAttribute::getAttributeName()
{
	return attributeName;
}

void UMLAttribute::changeName(string newAttributeName)
{
	attributeName = newAttributeName;
}

/************************************************************/
#endif
/************************************************************/