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
        // stores choice input by user
        string userChoice;
        // loop boolean that maintains CLI routine
        bool mainLoop;
        // loop boolean that maintains CLI subrountines
        bool subLoop;
        // main UML data object storing UML stuff
        UMLData data;
    public:
        // displays command line interface
        void displayCLI();
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
        cout << "[0] Class" << endl;
        cout << "[1] Attribute" << endl;
        cout << "[2] Relationship" << endl;
        cout << "[3] List" << endl;
        cout << "[4] Save" << endl;
        cout << "[5] Load" << endl;
        cout << "[6] Help" << endl;
        cout << "[7] Exit" << endl;

        // store user option
        cout << endl << "Choice: ";
        cin >> userChoice;
        cout << endl;

        // start subloop
        subLoop = true;

        while (subLoop) { 
            // Class
            if(userChoice == "0") {
                // Lists operations for modifying classes
                cout << "Choose an option:"<< endl;
                cout << "[0] Add" << endl;
                cout << "[1] Remove" << endl;
                cout << "[2] Rename" << endl;
                cout << "[3] Back" << endl;

                // store user option
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;
                
                // class names
                string name;
                string name2;

                // Add class
                if (userChoice == "0") {
                    // prompt name of class then add class
                    cout << "Enter name of class:" << endl;
                    cin >> name;
                    data.addClass(name);
                    cout << endl << "Class named " << name << " added" << endl << endl;
                    subLoop = false;
                }
                // Remove class
                else if (userChoice == "1") {
                    // prompt name of class then remove class
                    cout << "Enter name of class:" << endl;
                    cin >> name;
                    data.deleteClass(name);
                    cout << endl << "Class named " << name << " removed" << endl << endl;
                    subLoop = false;
                } 
                // Rename class
                else if (userChoice == "2") {
                    // prompt name of class then rename class
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
                    // exits loop, goes back
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // show error, reset user choice
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "0";
                }
            }

            // Attribute
            else if(userChoice == "1") {
                // Lists operations for modifying attributes
                cout << "Choose an option:"<< endl;
                cout << "[0] Add" << endl;
                cout << "[1] Remove" << endl;
                cout << "[2] Rename" << endl;
                cout << "[3] Back" << endl;

                // store user option
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                string className, attributeName;
                // Add attribute
                if (userChoice == "0") {
                    // prompt name of class and attribute then add attribute
                    cout << "Enter the name of the class: "<< endl;
                    cin >> className;
                    cout << "Enter the name of the attribute: "<< endl;
                    cin >> attributeName;
                    data.addClassAttribute(className, attributeName);
                    cout << "Attribute " << attributeName << " added to " << className << endl;
                    subLoop = false;

                }
                // Remove class
                else if (userChoice == "1") {
                    // prompt name of class and attribute then remove attribute
                    cout << "Enter the name of the class: "<< endl;
                    cin >> className;
                    cout << "Enter the name of the attribute: "<< endl;
                    cin >> attributeName;
                    data.removeClassAttribute(className, attributeName);
                    cout << "Attribute " << attributeName << " removed from " << className << endl;
                    subLoop = false;
                } 
                // Rename class
                else if (userChoice == "2") {
                    // prompt name of class, old attribute name, and new attribute name. 
                    // replace attribute with one of new name.
                    cout << "Enter the name of the class: "<< endl;
                    cin >> className;
                    cout << "Enter the name of the attribute: "<< endl;
                    cin >> attributeName;
                    cout << "Enter new name of attribute:" << endl;
                    string attributeName2;
                    cin >> attributeName2;
                    data.removeClassAttribute(className, attributeName);
                    data.addClassAttribute(className, attributeName2);
                    subLoop = false;
                }
                // Go back
                else if (userChoice == "3") {
                    // exits loop, goes back
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // show error, reset user choice
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "1";
                }
            }

            // Relationship
            else if(userChoice == "2") {
                // Lists operations for modifying relationships
                cout << "Choose an option:"<< endl;
                cout << "[0] Add" << endl;
                cout << "[1] Remove" << endl;
                cout << "[2] Back" << endl;

                // store user option
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // class name representing source and destination
                string source, destination;

                // Add relationship
                if (userChoice == "0") {
                    cout << "Enter the name of the source: "<< endl;
                    cin >> source;
                    cout << "Enter the name of the destination: "<< endl;
                    cin >> destination;
                    data.addRelationship(source, destination);
                    cout << "Relationship added between " << source << " and " << destination << endl;
                    subLoop = false;
                }
                // Remove relationship
                else if (userChoice == "1") {
                    // prompt name of source and destination and removes relationship
                    cout << "Enter the name of the source: "<< endl;
                    cin >> source;
                    cout << "Enter the name of the destination: "<< endl;
                    cin >> destination;
                    data.deleteRelationship(source, destination);
                    cout << "Relationship deleted between " << source << " and " << destination << endl;
                    subLoop = false;
                } 
                // Go back
                else if (userChoice == "2") {
                    // exits loop, goes back
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // show error, reset user choice
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "2";
                }
            }

            // Diagram
            else if(userChoice == "3") {
                // Lists operations for viewing information within the diagram
                cout << "Choose an option:"<< endl;
                cout << "[0] Class" << endl;
                cout << "[1] Diagram" << endl;
                cout << "[2] Back" << endl;

                // store user option
                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // Display single class
                if (userChoice == "0") {
                    // prompt class name, shows information about class
                    cout << "Enter name of class:" << endl;
                    string name;
                    cin >> name;
                    cout << "Attributes:" << endl;
                    UMLClass c = data.getClassCopy(name);
                    vector<UMLAttribute> attributeList = c.getAttributes();
                    for(UMLAttribute attribute : attributeList)
                    {
                        cout << attribute.getAttributeName() << endl;
                    }
                    cout << "Relationships:" << endl;
                    vector<UMLRelationship> relationshipList = data.getRelationshipsByClass(name);
                    for(UMLRelationship relationship : relationshipList)
                    {
                        cout << relationship.getSource().getName() << " <=> " << relationship.getDestination().getName() << endl;
                    }
                    cout << endl << "Enter anything to continue..." << endl;
                    cin >> name; //just to have a pause so user can have time to view attributes and relationships
                    subLoop = false;
                }
                // Display all information
                else if (userChoice == "1") {
                    std::vector<UMLClass> classes = data.getClasses();
                    for (UMLClass umlclass : classes)
                    {
                        std::cout << "Name: " << umlclass.getName() << std::endl;
                        std::cout << "Attributes:" << std::endl;
                        for (UMLAttribute attr : data.getClassAttributes(umlclass.getName()))
                        {
                            std::cout << attr.getAttributeName() << std::endl;
                        }
                        std::cout << "Relationships:" << std::endl;
                        for (UMLRelationship rel : data.getRelationshipsByClass(umlclass.getName()))
                        {
                            std::cout << rel.getSource().getName() << " <=> " << rel.getDestination().getName() << std::endl;
                        }
                    }  
                    cout << endl << "Enter anything to continue..." << endl;
                    std::string name;
                    cin >> name; //just to have a pause so user can have time to view attributes and relationships                 
                    subLoop = false;
                } 
                // Go back
                else if (userChoice == "2") {
                    // exits loop, goes back
                    subLoop = false;
                }
                // Invalid choice
                else {
                    // show error, reset user choice
                    cout << "Invalid choice!" << endl << endl;
                    userChoice = "3";
                }
            }

            // Save UML
            else if (userChoice == "4") {
                // Saves UML diagram to a JSON file in the same directory as the executable
                std::cout << "Name of file: ";
                std::string fileName;
                std::cin >> fileName;
                UMLFile file(fileName + ".json");
                file.save(data);
                std::cout << "Your file has been saved!" << std::endl;
                subLoop = false;
            }

            // Load UML
            else if (userChoice == "5") {
                std::cout << "Name of file (<name>.json): ";
                std::string fileName;
                std::cin >> fileName;
                UMLFile file(fileName);
                data = file.load();
                std::cout << "Your file has been loaded!" << std::endl;
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
                // show error, reset user choice and break loop
                cout << "Invalid choice!" << endl << endl;
                userChoice = "";
                subLoop = false;
            }
        }  
    } 
}

/************************************************************/
#endif
/************************************************************/