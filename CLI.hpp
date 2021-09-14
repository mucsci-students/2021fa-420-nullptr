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
        // prompts user for options
        void displayCLI();


    public:
};

void CLI::displayCLI ()
{
    int userChoice;
    bool loopCondition = true;
    bool classLoop = false;
    bool attributeLoop = false;
    bool relationshipLoop = false;

    while(loopCondition){
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

        // Lists operations for modifying classes
        if(userChoice == 0) {
            classLoop = true;
            while(classLoop) {
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
                    classLoop = false;
                }
                // Remove class
                else if (userChoice == 1) {
                    // prompt name of class then remove class
                    classLoop = false;
                } 
                // Rename class
                else if (userChoice == 2) {
                    // prompt name of class then rename class
                    classLoop = false;
                }
                // Go Back
                else if (userChoice == 3) {
                    // exits loop, goes back
                    classLoop = false;
                }
                // Invalid choice
                else {
                    // show error
                }
            }
        }
        // Lists operations for modifying attributes
        if(userChoice == 1){

        }
        //  Lists operations for modifying relationships
        if(userChoice == 2){

        }
        //  Lists operations for viewing information within the diagram
        if(userChoice == 3){

        }
        // Saves UML diagram to a JSON file in the same directory as the executable
        if(userChoice == 4){

        }
        // Prompts for a directory. If the directory exists, a UML diagram
        if(userChoice == 5){

        }
        // Loads this help file into the console
        if(userChoice == 6){

        }
        // Exits the program
        if(userChoice == 7){

        }
        // Throw error, userChoice is not an option
        else{

        }
    } 
}

/************************************************************/
#endif
/************************************************************/