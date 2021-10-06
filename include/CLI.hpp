#pragma once
/*
  Filename   : CLI.hpp
  Description: File which generates the command line interface
  for the user to create UML diagrams
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
#include "UMLData.hpp"
#include "UMLFile.hpp"
#include "UMLMethod.hpp"
#include <vector>
#include <iostream>
#include <fstream>
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
 using std::cin;
 using std::cout;
 using std::endl;
 using std::string;
 using std::vector;
 using std::invalid_argument;
//--------------------------------------------------------------------

class CLI
{
    private:
        // Stores choice input by user, representing position within diagram
        // When an invalid input is set, reverts to its previous position
        string userChoice;
        // Loop boolean that maintains CLI routine
        bool mainLoop;
        // Loop boolean that maintains CLI subroutines
        bool subLoop;
        // Error check to prevent 'success' print 
        bool errorStatus;
        // Main UML data object storing UML stuff
        UMLData data;
    public:
        // Displays command line interface
        void displayCLI();
        // Displays information about classes within the diagram.
        // Has conditional booleans to optionally display attributes and relationships.
        void displayDiagram (bool displayAttribute, bool displayRelationship);
        // Displays information about a single class with the name className.
        void displayClass (string className);
};