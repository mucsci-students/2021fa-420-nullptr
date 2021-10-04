#pragma once
/*
  Filename   : UMLParameter.hpp
  Description: Serves as an object for which information about a parameter
  for methods are stored.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
//--------------------------------------------------------------------

class UMLParameter
{
	private:
		// Name of parameter
		string name;
		// Type of parameter
		string type;

	public:
		// Params: string newParameter (name of parameter)
		// Constructor for parameter objects
		UMLParameter(string name, string type);

		// Grab name of the given parameter
		string getName() const;

		// Change name of the given parameter
		void changeName(string newName);

		// Grab type of the given parameter
		string getType() const;

		// Change type of the given parameter
		void changeType(string newType);

};
