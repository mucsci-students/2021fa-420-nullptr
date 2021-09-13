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
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using namespace std;
//--------------------------------------------------------------------

class UMLRelationship
{
	private:
		// Name of class that owns attribute and name of attribute
		string source;
		string destination;

	public:
		// Constructor for class objects
		UMLRelationship (string newSource, string newDestination) : 
			source (newSource),
			destination (newDestination)
		{
		}

		// Grab name of the source class
		string getSource ()
		{
			return source;
		}

		// Grab name of the destination class
		string getDestination ()
		{
			return destination;
		}
};

/************************************************************/
#endif
/************************************************************/