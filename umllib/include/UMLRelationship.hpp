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
[0] Aggregation: shared, ownerless collection 
[1] Composition: unshared, 'has-a' relationship collection
[2] Generalization: inheritance relationship
[3] Realization: interface implementation relationship */
//--------------------------------------------------------------------
enum Type {aggregation, composition, generalization, realization, none};

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
		UMLRelationship(const UMLClass& src, const UMLClass& dest, int type);

		// Grab name of the source class
		const UMLClass& getSource() const;

		// Grab name of the destination class
		const UMLClass& getDestination() const;

		// Grab type of relationship
		Type getType() const;

		// Converts inserted string to proper type enum
		static Type string_to_type(const std::string&);

		// Set type of relationship
		void setType(int newType);

		// Equals operator
		bool operator==(const UMLRelationship& other) const {
			return (this->getSource().getName() == other.getSource().getName() 
			&& this->getDestination().getName() == other.getDestination().getName()
			&& this->getType() == other.getType());}
};