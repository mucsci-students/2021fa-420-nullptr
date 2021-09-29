/*
  Filename   : UMLRelationship.cpp
  Description: Implementation of an relationship.
*/

//--------------------------------------------------------------------
// System includes
#include <UMLRelationship.hpp>
//--------------------------------------------------------------------

// Constructor for class objects
UMLRelationship::UMLRelationship(const UMLClass& src, const UMLClass& dest)
:source(&src)
,destination(&dest)
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
