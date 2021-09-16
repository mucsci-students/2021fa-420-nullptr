/*
  Filename   : CLI.hpp
  Description: File which generates the command line interface
  for the user to create UML diagrams
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
        // Stores choice input by user
        string userChoice;
        // Loop boolean that maintains CLI routine
        bool mainLoop;
        // Loop boolean that maintains CLI subrountines
        bool subLoop;
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
    // Start default state of loops
    mainLoop = true;
    subLoop = false;

    // Primary display routine
    while (mainLoop) {
        // Main prompt: prompts user for options.
        cout << "Choose an option:" << endl;
        cout << "[0] Class" << endl;
        cout << "[1] Attribute" << endl;
        cout << "[2] Relationship" << endl;
        cout << "[3] List" << endl;
        cout << "[4] Save" << endl;
        cout << "[5] Load" << endl;
        cout << "[6] Help" << endl;
        cout << "[7] Exit" << endl;

        // Store user option
        cout << endl << "Choice: ";
        cin >> userChoice;
        cout << endl;

        // Start subloop
        subLoop = true;

        while (subLoop) { 
            // Class subroutine
            if(userChoice == "0") {
                // Lists operations for modifying classes
                cout << "Choose an option:" << endl;
                cout << "[0] Add" << endl;
                cout << "[1] Remove" << endl;
                cout << "[2] Rename" << endl;
                cout << "[3] Back" << endl;

                // Store user option
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;
                
                // Class name input storage
                string name, name2;

                // Add class
                if (userChoice == "0") {
                    // Prompt name of class then add class
                    cout << "Enter name of class:" << endl;
                    cin >> name;
                    data.addClass(name);
                    cout << endl << "Class named " << name << " added" << endl << endl;
                    subLoop = false;
                }
                // Remove class
                else if (userChoice == "1") {
                    // Display all classes
                    displayDiagram(false, false);
                    // Prompt name of class then remove class
                    cout << "Enter name of class:" << endl;
                    cin >> name;
                    data.deleteClass(name);
                    cout << endl << "Class named " << name << " removed" << endl << endl;
                    subLoop = false;
                } 
                // Rename class
                else if (userChoice == "2") {
                    // Display all classes
                    displayDiagram(false, false);
                    // Prompt name of class then rename class
                    cout << "Enter old name of class:" << endl;
                    string name;
                    cin >> name;
                    cout << "Enter new name of class:" << endl;
                    cin >> name2;
                    data.changeClassName(name, name2);
                    cout << endl << "Class named " << name << " renamed to " << name2 << endl << endl;
                    subLoop = false;
                }
                // Go back
                else if (userChoice == "3") {
                    // Exits subroutine, goes back to main routine
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // Show error, reset user choice
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "0";
                }
            }

            // Attribute subroutine
            else if(userChoice == "1") {
                // Lists operations for modifying attributes
                cout << "Choose an option:" << endl;
                cout << "[0] Add" << endl;
                cout << "[1] Remove" << endl;
                cout << "[2] Rename" << endl;
                cout << "[3] Back" << endl;

                // Store user option
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // Class and attribute name input storage
                string className, attributeName;
                
                // Add attribute
                if (userChoice == "0") {
                    // Display all classes
                    displayDiagram(false, false);
                    // Prompt name of class and attribute then add attribute
                    cout << "Enter the name of the class: "<< endl;
                    cin >> className;
                    cout << "Enter the name of the attribute: "<< endl;
                    cin >> attributeName;
                    data.addClassAttribute(className, attributeName);
                    cout << endl << "Attribute " << attributeName << " added to " << className << endl << endl;
                    subLoop = false;

                }
                // Remove attribute
                else if (userChoice == "1") {
                    // Display all classes and attributes
                    displayDiagram(true, false);
                    // Prompt name of class and attribute then remove attribute
                    cout << "Enter the name of the class: "<< endl;
                    cin >> className;
                    cout << "Enter the name of the attribute: "<< endl;
                    cin >> attributeName;
                    data.removeClassAttribute(className, attributeName);
                    cout << endl << "Attribute " << attributeName << " removed from " << className << endl << endl;
                    subLoop = false;
                } 
                // Rename attribute
                else if (userChoice == "2") {
                    // Display all classes and attributes
                    displayDiagram(true, false);
                    // Prompt name of class, old attribute name, and new attribute name. 
                    // Replace attribute with one of new name.
                    cout << "Enter the name of the class: " << endl;
                    cin >> className;
                    cout << "Enter the name of the attribute: " << endl;
                    cin >> attributeName;
                    cout << "Enter new name of attribute:" << endl;
                    string attributeName2;
                    cin >> attributeName2;
                    data.removeClassAttribute(className, attributeName);
                    data.addClassAttribute(className, attributeName2);
                    cout << endl << "Attribute " << attributeName << " renamed to " << attributeName2 << endl << endl;
                    subLoop = false;
                }
                // Go back
                else if (userChoice == "3") {
                    // Exits subroutine, goes back to main routine
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // Show error, reset user choice
                    cout << "Invalid choice" << endl << endl;
                    userChoice = "1";
                }
            }

            // Relationship
            else if(userChoice == "2") {
                // Lists operations for modifying relationships
                cout << "Choose an option:" << endl;
                cout << "[0] Add" << endl;
                cout << "[1] Remove" << endl;
                cout << "[2] Back" << endl;

                // Store user option
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // Class name representing source and destination
                string source, destination;

                // Add relationship
                if (userChoice == "0") {
                    // Display all classes
                    displayDiagram(false, false);
                    // Prompt name of source and destination and removes relationship
                    cout << "Enter the name of the source: " << endl;
                    cin >> source;
                    cout << "Enter the name of the destination: " << endl;
                    cin >> destination;
                    data.addRelationship(source, destination);
                    cout << endl <<"Relationship added between " << source << " and " << destination << endl << endl;
                    subLoop = false;
                }
                // Remove relationship
                else if (userChoice == "1") {
                    // Display all classes and relationships
                    displayDiagram(false, true);
                    // Prompt name of source and destination and removes relationship
                    cout << "Enter the name of the source: " << endl;
                    cin >> source;
                    cout << "Enter the name of the destination: " << endl;
                    cin >> destination;
                    data.deleteRelationship(source, destination);
                    cout << endl << "Relationship deleted between " << source << " and " << destination << endl << endl;
                    subLoop = false;
                } 
                // Go back
                else if (userChoice == "2") {
                    // Exits subroutine, goes back to main routine
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // Show error, reset user choice
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "2";
                }
            }

            // Diagram
            else if(userChoice == "3") {
                // Lists operations for viewing information within the diagram
                cout << "Choose an option:" << endl;
                cout << "[0] Class" << endl;
                cout << "[1] Diagram" << endl;
                cout << "[2] Back" << endl;

                // Store user option
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // Class name input storage
                string name;

                // Display single class
                if (userChoice == "0") {
                    // Prompt class name
                    cout << "Enter name of class:" << endl;
                    cin >> name;
                    displayClass(name);
                    cout << endl << "Enter anything to continue..." << endl;
                    cin >> name; // Pause for input
                    cout << endl; 
                    subLoop = false;
                }
                // Display all information
                else if (userChoice == "1") {
                    displayDiagram (true, true); 
                    cout << endl << "Enter anything to continue..." << endl;
                    cin >> name; // Pause for input
                    cout << endl;                  
                    subLoop = false;
                } 
                // Go back
                else if (userChoice == "2") {
                    // Exits subroutine, goes back to main routine
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // Show error, reset user choice
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "3";
                }
            }

            // Save UML
            else if (userChoice == "4") {
                // Saves UML diagram to a JSON file in the same directory as the executable
                cout << "Name of file: ";
                std::string fileName;
                std::cin >> fileName;
                UMLFile file(fileName + ".json");
                file.save(data);
                cout << "Your file has been saved" << endl;
                subLoop = false;
            }

            // Load UML routine
            else if (userChoice == "5") {
                // Ask for name of file, and then load UML data given the proper format
                cout << "Name of file: ";
                std::string fileName;
                std::cin >> fileName;
                UMLFile file(fileName + ".json");
                data = file.load();
                cout << "Your file has been loaded" << endl;
                subLoop = false;
            }

            // Help
            else if (userChoice == "6") {
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
                subLoop = false;
            }

            // Exits the program
            else if (userChoice == "7") {
                subLoop = false;
                mainLoop = false;
            }

            // Invalid choice
            else {
                // Show error, reset user choice and break loop
                cout << "Invalid choice!" << endl << endl;
                userChoice = "";
                subLoop = false;
            }
        }  
    } 
}

void CLI::displayDiagram (bool displayAttribute, bool displayRelationship) 
{
    vector<UMLClass> classes = data.getClasses();
    cout << "Classes:" << endl << endl;
    for (UMLClass umlclass : classes)
    {
        cout << umlclass.getName() << std::endl;
        if (displayAttribute) {
            cout << "Attributes:" << std::endl;
            for (UMLAttribute attr : data.getClassAttributes(umlclass.getName()))
            {
                cout << attr.getAttributeName() << std::endl;
            }
        }
        if (displayRelationship) {
            cout << "Relationships:" << std::endl;
            for (UMLRelationship rel : data.getRelationshipsByClass(umlclass.getName()))
            {
                cout << rel.getSource().getName() << " => " << rel.getDestination().getName() << std::endl;
            }
        }
        // Don't cause spacing within loop if only showing classes
        if (displayAttribute || displayRelationship) cout << endl;
    }
    // Display single line break if only showing classes
    if (!displayAttribute && !displayRelationship) cout << endl;
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
    cout << endl;
}

/************************************************************/
#endif
/************************************************************/