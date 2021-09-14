/*
  Filename   : CLI.hpp
  Description: File which generates the command line interface
  for the user to create UML diagrams
  Author: Tyler York
  Date: 9/14/2021
*/

/************************************************************/
// Macro guard
#ifndef CLI_HPP
#define CLI_HPP
/************************************************************/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
#include "UMLData.hpp"
#include "UMLFile.hpp"
#include <vector>
#include <iostream>
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
        // displays command line interface
        void displayCLI();

    public:
        // stores choice input by user
        int userChoice;
        // loop boolean that maintains CLI routine
        bool mainLoop;
        // loop boolean that maintains CLI subrountines
        bool subLoop;
};

void CLI::displayCLI ()
{
    // loop boolean that maintains CLI routine
    mainLoop = true;
    // loop boolean that maintains CLI subrountines
    subLoop = false;

    while (mainLoop) {
        // Main prompt: prompts user for options.
        cout << "Choose an option:"<< endl;
        cout << "Class [0]" << endl;
        cout << "Attribute [1]" << endl;
        cout << "Relationship [2]" << endl;
        cout << "List [3]" << endl;
        cout << "Save [4]" << endl;
        cout << "Load [5]" << endl;
        cout << "Help [6]" << endl;
        cout << "Exit [7]" << endl;

        // store user option
        cin >> userChoice;

        subLoop = true;
        while (subLoop) { 
            // Class
            if(userChoice == 0) {
                // Lists operations for modifying classes
                cout << "Choose an option:"<< endl;
                cout << "Add [0]" << endl;
                cout << "Remove [1]" << endl;
                cout << "Rename [2]" << endl;
                cout << "Back [3]" << endl;

                // store user option
                cin >> userChoice;
                
                // Add class
                if (userChoice == 0) {
                    // prompt name of class then add class
                    subLoop = false;
                }
                // Remove class
                else if (userChoice == 1) {
                    // prompt name of class then remove class
                    subLoop = false;
                } 
                // Rename class
                else if (userChoice == 2) {
                    // prompt name of class then rename class
                    subLoop = false;
                }
                // Go back
                else if (userChoice == 3) {
                    // exits loop, goes back
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // show error
                }
            }

            // Attribute
            if(userChoice == 1) {
                // Lists operations for modifying attributes
                cout << "Choose an option:"<< endl;
                cout << "Add [0]" << endl;
                cout << "Remove [1]" << endl;
                cout << "Rename [2]" << endl;
                cout << "Back [3]" << endl;

                // store user option
                cin >> userChoice;

                // Add attribute
                if (userChoice == 0) {
                    // prompt name of class and attribute then add attribute
                    subLoop = false;
                }
                // Remove class
                else if (userChoice == 1) {
                    // prompt name of class and attribute then remove attribute
                    subLoop = false;
                } 
                // Rename class
                else if (userChoice == 2) {
                    // prompt name of class and attribute then rename attribute
                    subLoop = false;
                }
                // Go back
                else if (userChoice == 3) {
                    // exits loop, goes back
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // show error
                }
            }

            // Relationship
            if(userChoice == 2) {
                // Lists operations for modifying relationships
                cout << "Choose an option:"<< endl;
                cout << "Add [0]" << endl;
                cout << "Remove [1]" << endl;
                cout << "Back [2]" << endl;

                // store user option
                cin >> userChoice;

                // Add relationship
                if (userChoice == 0) {
                    // prompt name of source and destination and adds relationship
                    subLoop = false;
                }
                // Remove relationship
                else if (userChoice == 1) {
                    // prompt name of source and destination and removes relationship
                    subLoop = false;
                } 
                // Go back
                else if (userChoice == 2) {
                    // exits loop, goes back
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // show error
                }
            }

            // Diagram
            if(userChoice == 3) {
                // Lists operations for viewing information within the diagram
                cout << "Choose an option:"<< endl;
                cout << "Class [0]" << endl;
                cout << "Diagram [1]" << endl;
                cout << "Back [2]" << endl;

                // store user option
                cin >> userChoice;

                // Display single class
                if (userChoice == 0) {
                    // prompt class name, shows information about class
                    subLoop = false;
                }
                // Display all information
                else if (userChoice == 1) {
                    // show all information and return back to base loop
                    subLoop = false;
                } 
                // Go back
                else if (userChoice == 2) {
                    // exits loop, goes back
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // show error
                }
            }

            // Save UML
            if(userChoice == 4) {
                // Saves UML diagram to a JSON file in the same directory as the executable
            }

            // Load UML
            if(userChoice == 5) {
                // Prompts for a directory. If the directory exists, UML diagram info is displayed
            }

            // Help
            if(userChoice == 6) {
                // Loads this help file into the console
            }

            // Exits the program
            if(userChoice == 7) {
                mainLoop = false;
            }
            
            // Throw error, userChoice is not an option
            else {
                // throw error
            }
        }  
    } 
}

/************************************************************/
#endif
/************************************************************/