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
 using std::list;
 using std::invalid_argument;
//--------------------------------------------------------------------

class CLI
{
    private:
        // displays command line interface
        // prompts user for options
        void displayCLI();


    public:

void CLI::displayCLI()
{
   
    

    // Main prompt user for option.
    cout << "Choose an option:"<< endl;
    cout << "Class [0]: Lists operations for modifying classes." << endl;
    cout << "Attribute [1]: Lists operations for modifying attributes." << endl;
    cout << "Relationship [2]: Lists operations for modifying relationships." << endl;
    cout << "List [3]: Lists operations for viewing information within the diagram. " << endl;
    cout << "Save [4]: Saves your UML diagram to a JSON file in the same directory as the executable." << endl;
    cout << "Load [5]: Prompts for a directory. If the directory exists, a UML diagram 
            made previously by this program will be loaded for modification." << endl;
    cout << "Help [6]: Loads this help file into the console. " << endl;
    cout << "Exit [7]: Exits the program. If the UML class diagram is not saved 
            beforehand, data will be lost." << endl;

    // store user option
    int userChoice;
    cin >> userChoice;
        
        // Lists operations for modifying classes
        if(userChoice == 0 ){

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