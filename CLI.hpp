/*
  Filename   : CLI.hpp
  Description: File which generates the command line interface
  for the user to create UML diagrams
*/

/************************************************************/
// Macro guard
#ifndef CLI_HPP
#define CLI_HPP
// Catch for functions to protect from invalid inputs
#define ERR_CATCH(fun)                           \
    try {                                        \
        fun;                                     \
    }                                            \
    catch (const char* error) {                  \
        cout << endl << error << endl << endl;   \
        errorStatus = true;                      \
    }
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
        // Loop boolean that maintains CLI subrountines
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


// Displays CLI using a large loop routine.
void CLI::displayCLI ()
{

    cout << "Welcome to UML++!" << endl << endl;
    // Primary display routine
    while (mainLoop) {
        subLoop = true;
        // Main prompt: prompts user for options.
        cout << "Choose an option:" << endl;
        cout << "[1] Class" << endl;
        cout << "[2] Attribute" << endl;
        cout << "[3] Relationship" << endl;
        cout << "[4] List" << endl;
        cout << "[5] Save" << endl;
        cout << "[6] Load" << endl;
        cout << "[7] Help" << endl;
        cout << "[8] Exit" << endl;

        cout << endl << "Choice: ";
        cin >> userChoice;
        cout << endl;
        // Start subloop
        while (subLoop) {
            subLoop = false;
            // Class subroutine
            if(userChoice == "1") {
                // Lists operations for modifying classes
                cout << "Choose an option:" << endl;
                cout << "[1] Add" << endl;
                cout << "[2] Remove" << endl;
                cout << "[3] Rename" << endl;
                cout << "[4] Back" << endl;
                
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;
                
                // Class name input storage
                string name, name2;

                // Add class
                if (userChoice == "1") {
                    cout << "Enter name of class: ";
                    cin >> name;
                    
                    // Catch for duplicate/invalid name
                    ERR_CATCH(data.addClass(name));
                    // Prevent success message if error was caught
                    if(errorStatus == false) cout << endl << "Class named " << name << " added" << endl << endl;
                    else errorStatus = false;
                }
                // Remove class
                else if (userChoice == "2") {
                    // Display all class names for user clarity
                    displayDiagram(false, false);

                    cout << "Enter name of class: ";
                    cin >> name;

                    // Catch to see if name exists
                    ERR_CATCH(data.deleteClass(name));
                    // Prevent success message if error was caught
                    if(errorStatus == false) cout << endl << "Class named " << name << " removed" << endl << endl;
                    else errorStatus = false;
                } 
                // Rename class
                else if (userChoice == "3") {
                    // Display all class names for user clarity
                    displayDiagram(false, false);

                    cout << "Enter old name of class: ";
                    string name;
                    cin >> name;
                    cout << "Enter new name of class: ";
                    cin >> name2;

                    // Catch for duplicate/invalid name
                    ERR_CATCH(data.changeClassName(name, name2));
                    // Prevent success message if error was caught
                    if(errorStatus == false) cout << endl << "Class named " << name << " renamed to " << name2 << endl << endl;
                    else errorStatus = false;
                }
                // Go back
                else if (userChoice == "4") {
                    // Exits subroutine to go back to main routine
                }
                // Invalid choice
                else {
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "1";
                    subLoop = true;
                }
            }

            // Attribute subroutine
            else if(userChoice == "2") {
                // Lists operations for modifying attributes
                cout << "Choose an option:" << endl;
                cout << "[1] Add" << endl;
                cout << "[2] Remove" << endl;
                cout << "[3] Rename" << endl;
                cout << "[4] Back" << endl;

                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // Class and attribute name input storage
                string className, attributeName, attributeName2;
                
                // Add attribute
                if (userChoice == "1") {
                    // Display all class names for user clarity
                    displayDiagram(false, false);
                   
                    cout << "Enter the name of the class: ";
                    cin >> className;
                    cout << "Enter the name of the attribute: ";
                    cin >> attributeName;

                    ERR_CATCH(data.addClassAttribute(className, attributeName));
                    if (errorStatus == false) cout << endl << "Attribute " << attributeName << " added to " << className << endl << endl;
                    else errorStatus = false;

                }
                // Remove attribute
                else if (userChoice == "2") {
                    // Display all classes and attributes for user clarity
                    displayDiagram(true, false);
                    
                    cout << "Enter the name of the class: ";
                    cin >> className;
                    cout << "Enter the name of the attribute: ";
                    cin >> attributeName;

                    ERR_CATCH(data.removeClassAttribute(className, attributeName));
                    if (errorStatus == false) cout << endl << "Attribute " << attributeName << " removed from " << className << endl << endl;
                    else errorStatus = false;
                } 
                // Rename attribute
                else if (userChoice == "3") {
                    // Display all classes and attributes for user clarity
                    displayDiagram(true, false);

                    cout << "Enter the name of the class: ";
                    cin >> className;
                    cout << "Enter the name of the attribute: ";
                    cin >> attributeName;
                    cout << "Enter new name of attribute: ";
                    cin >> attributeName2;

                    ERR_CATCH(data.changeAttributeName(className, attributeName, attributeName2));
                    if (errorStatus == false) cout << endl << "Attribute " << attributeName << " renamed to " << attributeName2 << endl << endl;
                    else errorStatus = false;
                }
                // Go back
                else if (userChoice == "4") {
                    // Exits subroutine to go back to main routine
                }
                // Invalid choice
                else {
                    cout << "Invalid choice" << endl << endl;
                    userChoice = "2";
                    subLoop = true;
                }
            }

            // Relationship subroutine
            else if(userChoice == "3") {
                // Lists operations for modifying relationships
                cout << "Choose an option:" << endl;
                cout << "[1] Add" << endl;
                cout << "[2] Remove" << endl;
                cout << "[3] Back" << endl;

                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // Class name representing source and destination
                string source, destination;

                // Add relationship
                if (userChoice == "1") {
                    // Display all classes for user clarity
                    displayDiagram(false, false);

                    cout << "Enter the name of the source: " << endl;
                    cin >> source;
                    cout << "Enter the name of the destination: " << endl;
                    cin >> destination;

                    ERR_CATCH(data.addRelationship(source, destination));
                    if (errorStatus == false) cout << endl <<"Relationship added between " << source << " and " << destination << endl << endl;
                }
                // Remove relationship
                else if (userChoice == "2") {
                    // Display all classes and relationships for user clarity
                    displayDiagram(false, true);

                    cout << "Enter the name of the source: " << endl;
                    cin >> source;
                    cout << "Enter the name of the destination: " << endl;
                    cin >> destination;

                    ERR_CATCH(data.deleteRelationship(source, destination));
                    if (errorStatus == false) cout << endl << "Relationship deleted between " << source << " and " << destination << endl << endl;
                    else errorStatus = false;
                } 
                // Go back
                else if (userChoice == "3") {
                    // Exits subroutine to go back to main routine
                }
                // Invalid choice
                else {
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "3";
                    subLoop = true;
                }
            }

            // List subroutine
            else if(userChoice == "4") {
                // Lists operations for viewing information within the diagram
                cout << "Choose an option:" << endl;
                cout << "[1] Class" << endl;
                cout << "[2] Diagram" << endl;
                cout << "[3] Back" << endl;

                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // Class name input storage
                string name;

                // Display single class
                if (userChoice == "1") {
                    // Display class names for user clarity
                    displayDiagram (false, false); 

                    cout << "Enter name of class:" << endl;
                    cin >> name;

                    displayClass(name);
                    cout << endl << "Enter anything to continue..." << endl;
                    cin >> name; // Pause for input
                    cout << endl; 
                }
                // Display all information
                else if (userChoice == "2") {
                    displayDiagram (true, true); 
                    
                    cout << "Enter anything to continue..." << endl;
                    cin >> name; // Pause for input
                    cout << endl;                  
                } 
                // Go back
                else if (userChoice == "3") {
                    // Exits subroutine to go back to main routine
                }
                // Invalid choice
                else {
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "4";
                    subLoop = true;
                }
            }

            // Save UML subroutine
            else if (userChoice == "5") {
                // Saves UML diagram to a JSON file in the same directory as the executable
                cout << "Name of file: ";
                string fileName;
                cin >> fileName;

                UMLFile file(fileName + ".json");
                file.save(data);
                cout << "Your file has been saved" << endl;
            }

            // Load UML subroutine
            else if (userChoice == "6") {
                // Ask for name of file, and then load UML data given the proper format
                cout << "Name of file: ";
                string fileName;
                cin >> fileName;

                UMLFile file(fileName + ".json");
                try {
                    data = file.load();
                } catch (const std::exception& ex)
                {
                    cout << endl << "Error loading file" << endl << endl;
                    bool errorStatus = true;
                }
                if (errorStatus == false) cout << "Your file has been loaded" << endl;
                else errorStatus = false;
            }

            // Help subroutine
            else if (userChoice == "7") {
                // Displays help if help file exists, otherwise display error
                string line;
                std::ifstream myfile ("../help.txt");
                if (myfile.is_open()) {
                    while (getline (myfile,line) ) {
                        cout << line << '\n';
                    }
                    myfile.close();
                }
                else cout << "Unable to open file";

                cout << endl << "Enter anything to continue..." << endl;
                cin >> line; // Pause for input
                cout << endl; 
            }

            // Exits the program
            else if (userChoice == "8") {
                cout << "Exiting program..." << endl << endl;
                mainLoop = false;
            }

            // Invalid choice
            else {
                cout << "Invalid choice!" << endl << endl;
                userChoice = "";
            }
        }  
    } 
}

void CLI::displayDiagram (bool displayAttribute, bool displayRelationship) 
{
    vector<UMLClass> classes = data.getClasses();
    cout << "Classes:" << endl << endl;
    for (UMLClass umlclass : classes) {
        cout << umlclass.getName() << endl;
        if (displayAttribute) {
            cout << "Attributes:" << endl;
            for (UMLAttribute attr : data.getClassAttributes(umlclass.getName()))
            {
                cout << attr.getAttributeName() << endl;
            }
        }
        if (displayRelationship) {
            cout << "Relationships:" << endl;
            for (UMLRelationship rel : data.getRelationshipsByClass(umlclass.getName()))
            {
                cout << rel.getSource().getName() << " => " << rel.getDestination().getName() << endl;
            }
        }
        // Don't cause spacing within loop if only showing classes
        if (displayAttribute || displayRelationship) cout << endl;
    }
    // Display single line break if only showing classes. but NOT if classes are empty
    if (!displayAttribute && !displayRelationship && data.getClasses().size() > 0) cout << endl;
}

void CLI::displayClass (string className) 
{
    // Grab copy of class in order to display attributes
    cout << "Attributes:" << endl;
    UMLClass c = data.getClassCopy(className);
    vector<UMLAttribute> attributeList = c.getAttributes();
    for(UMLAttribute attribute : attributeList)
    {
        cout << attribute.getAttributeName() << endl;
    }

    // Find relationships based on name of the class
    cout << "Relationships:" << endl;
    vector<UMLRelationship> relationshipList = data.getRelationshipsByClass(className);
    for(UMLRelationship relationship : relationshipList)
    {
        cout << relationship.getSource().getName() << " => " << relationship.getDestination().getName() << endl;
    }
}

/************************************************************/
#endif
/************************************************************/