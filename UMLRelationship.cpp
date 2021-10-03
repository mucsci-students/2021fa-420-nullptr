/*
  Filename   : UMLRelationship.cpp
  Description: Implementation of an relationship.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLRelationship.hpp"
//--------------------------------------------------------------------

// Constructor for class objects
UMLRelationship::UMLRelationship(const UMLClass& src, const UMLClass& dest, int type)
:source(&src)
,destination(&dest)
,relationshipType((Type) type)
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
void UMLRelationship::setType(int newType) {
  if (newType == 0) {
    relationshipType = aggregation;
  }
  else if (newType == 1) {
    relationshipType = composition;
  }
  else if (newType == 2) {
    relationshipType = generalization;
  }
  else if (newType == 3) {
    relationshipType = realization;
  }
  else {
    throw "Invalid type";
  }
}