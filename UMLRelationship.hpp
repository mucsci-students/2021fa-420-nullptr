/*
  Filename   : UMLClass.cpp
  Description: Serves as an object for which information about a relationship
  in the UML diagram is stored. To be further expanded with different types
  of relationships.
*/

/************************************************************/
// Macro guard
#ifndef UMLRELATIONSHIP_HPP
#define UMLRELATIONSHIP_HPP
/************************************************************/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "UMLClass.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using namespace std;
//--------------------------------------------------------------------

class UMLRelationship
{
	private:
		// Name of class that owns attribute and name of attribute
		const UMLClass* source = nullptr;
		const UMLClass* destination = nullptr;

	public:
		// Constructor for class objects
		UMLRelationship (const UMLClass& src, const UMLClass& dest)
		{
			source = &src;
			destination = &dest;
		}

		// Grab name of the source class
		const UMLClass& getSource () const
		{
			return *source;
		}

		// Grab name of the destination classs
		const UMLClass& getDestination () const
		{
			return *destination;
		}
};

/************************************************************/
#endif
/************************************************************/