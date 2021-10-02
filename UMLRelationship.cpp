/*
  Filename   : UMLRelationship.cpp
  Description: Implementation of an relationship.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLRelationship.hpp"
//--------------------------------------------------------------------

// Constructor for class objects
UMLRelationship::UMLRelationship(const UMLClass& src, const UMLClass& dest, Type type)
:source(&src)
,destination(&dest)
,relationshipType(type)
{
}

// Grab name of the source class
const UMLClass& UMLRelationship::getSource() const
{
	return *source;
}

// Grab name of the destination classs
const UMLClass& UMLRelationship::getDestination() const
{
	return *destination;
}

// Grab type of relationship
Type UMLRelationship::getType() const
{
  return relationshipType;
}

// Set type of relationship
void UMLRelationship::setType(Type newType) {
  relationshipType = newType;
}