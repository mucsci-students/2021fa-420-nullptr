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
using namespace std;
//--------------------------------------------------------------------

class UMLAttribute
{
	private:
		// Name of attribute
		string attributeName;

	public:
		// Params: string newAttribute (name of attribute)
		// Constructor for attribute objects
		UMLAttribute (string newAttribute) {
			attributeName = newAttribute;
		}

		// Grab name of the given attribute
		string getAttributeName ();

		// Change name of the given attribute
		void changeName (string newAttributeName);

};

// Grab name of the given attribute
string UMLAttribute::getAttributeName ()
{
	return attributeName;
}

// Change name of the given attribute
void UMLAttribute::changeName (string newAttributeName)
{
	attributeName = newAttributeName;
}

/************************************************************/
#endif
/************************************************************/