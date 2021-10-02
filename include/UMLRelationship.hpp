#pragma once
/*
  Filename   : UMLRelationship.hpp
  Description: Serves as an object for which information about a relationship
  in the UML diagram is stored, alongside its relationship type.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "UMLClass.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
/* Types of relationships 
Aggregation: shared, ownerless collection 
Composition: unshared, 'has-a' relationship collection
Generalization: inheritance relationship
Realization: interface implementation relationship */
//--------------------------------------------------------------------
enum Type {aggregation, composition, generalization, realization};

class UMLRelationship
{
	private:
		// Name of class that owns attribute and name of attribute
		const UMLClass* source;
		const UMLClass* destination;
		// Type of relationship
		Type relationshipType;

	public:
		// Constructor for class objects
		UMLRelationship(const UMLClass& src, const UMLClass& dest, Type type);

		// Grab name of the source class
		const UMLClass& getSource() const;

		// Grab name of the destination class
		const UMLClass& getDestination() const;

		// Grab type of relationship
		Type getType() const;

		// Set type of relationship
		void setType(Type newType);
};