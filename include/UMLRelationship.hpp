#pragma once
/*
  Filename   : UMLRelationship.hpp
  Description: Serves as an object for which information about a relationship
  in the UML diagram is stored. To be further expanded with different types
  of relationships.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "UMLClass.hpp"
//--------------------------------------------------------------------

class UMLRelationship
{
	private:
		// Name of class that owns attribute and name of attribute
		const UMLClass* source;
		const UMLClass* destination;

	public:
		// Constructor for class objects
		UMLRelationship(const UMLClass& src, const UMLClass& dest);

		// Grab name of the source class
		const UMLClass& getSource() const;

		// Grab name of the destination classs
		const UMLClass& getDestination() const;
};