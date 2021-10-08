/*
  Filename   : CLI.cpp
  Description: Implementation of the command line interface.
*/

/************************************************************/
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
#include "include/CLI.hpp"
//--------------------------------------------------------------------

// Displays CLI using a large loop routine.
void CLI::displayCLI ()
{
    cout << "Welcome to UML++!" << endl << endl;
    // Primary display routine
    while (mainLoop) {
        // Error status reset when main loop begins
        errorStatus = false;
        // Subloop toggled to guarantee entry
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
            // Subloop toggled to break loop unless error occurs
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
                cout << "[3] Change" << endl;
                cout << "[4] Back" << endl;

                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl << endl;

                // Class and attribute name input storage
                string className, attributeName, attributeName2;
                
                // Add attribute
                if (userChoice == "1") {
                    // Display all class names for user clarity
                    displayDiagram(false, false);
                   
                    cout << "Enter the name of the class: ";
                    cin >> className;
                    cout << endl;
                    
                    // Allow user to choose between a Method or a Field
                    bool attributeLoop = true;
                    while (attributeLoop)
                    {
                        cout << "Add Method or Field:" << endl << "[1] Field" << endl << "[2] Method" << endl << endl << "Choice: ";
                        cin >> userChoice;
                        cout << endl;
                        // User chooses to add a field                     
                        if (userChoice == "1")
                        {
                            cout << "Enter the name of the field: ";
                            cin >> attributeName;
                            cout << endl << "Enter type: ";
                            string type;
                            cin >> type;
                            ERR_CATCH(data.addClassAttributeP(className, new UMLField(attributeName, type) ));
                            if (errorStatus == false) cout << endl << "Field " << attributeName << " added to " << className << endl << endl;
                            else errorStatus = false;
                            attributeLoop = false;
                        }

                        //User chooses to add a method
                        else if (userChoice == "2")
                        {
                            cout << "Enter the name of the method: ";
                            cin >> attributeName;
                            cout << endl << "Enter return type: ";
                            string returnType;
                            cin >> returnType;
                            // Promt user to enter as many parameters as they want
                            bool paramLoop = true;
                            vector<UMLParameter> paramList = {};
                            string userChoice2;
                            // First loop to check for correct input
                            while(paramLoop)
                            {
                                cout << endl << "Add parameter? (y/n): ";
                                cin >> userChoice2;
                                // Add the parameters
                                if(userChoice2 == "y" || userChoice2 == "Y")
                                {
                                    string paramName;
                                    string paramType;
                                    // Second loop to allow for unlimited parameters
                                    while(paramLoop)
                                    {
                                        cout << endl << "Enter parameter name: ";
                                        cin >> paramName;
                                        cout << endl << "Enter parameter type: ";
                                        cin >> paramType;
                                        paramList.push_back( UMLParameter(paramName, paramType) );
                                        // Loop to check user input
                                        bool paramLoop2 = true;
                                        while(paramLoop2)
                                        {
                                            cout << endl << "Add more? (y/n): ";
                                            cin >> userChoice2;
                                            // Add parameter again
                                            if(userChoice2 == "y" || userChoice2 == "Y")
                                                paramLoop2 = false;
                                            // Exit add parameter loop
                                            else if(userChoice2 == "n" || userChoice2 == "N")
                                            {
                                                paramLoop = false;
                                                paramLoop2 = false;
                                            }
                                            // Invalid input, enter again
                                            else
                                                cout << endl << "Invalid choice!" << endl;
                                        }
                                    }
                                }
                                // Do not add the parameters
                                else if(userChoice2 == "n" || userChoice2 == "N")
                                    paramLoop = false;
                                // Enter input again
                                else
                                    cout << endl << "Invalid choice!" << endl;
                            }
                            
                            ERR_CATCH(data.addClassAttributeP(className, new UMLMethod(attributeName, returnType, paramList) )); //REMEMBER TO DEALLOCATE
                            if (errorStatus == false) cout << endl << "Method " << attributeName << " added to " << className << endl << endl;
                            else errorStatus = false;
                            attributeLoop = false;
                        }  

                        //Redo loop if invalid option entered
                        else
                        {
                            cout << "Invalid choice!" << endl << endl;
                        }
                    }

                }
                // Remove attribute
                else if (userChoice == "2") {
                    // Display all classes and attributes for user clarity
                    displayDiagram(true, false);
                    
                    cout << "Enter the name of the class: ";
                    cin >> className;
                    cout << "Enter the name of the attribute: ";
                    cin >> attributeName;

                    ERR_CATCH(data.removeClassAttributeP(className, attributeName));
                    if (errorStatus == false) cout << endl << "Attribute " << attributeName << " removed from " << className << endl << endl;
                    else errorStatus = false;
                } 
                // Change attribute type and name or parameter
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
                cout << "[3] Modify Type" << endl;
                cout << "[4] Back" << endl;

                cout << endl << "Choice: ";
                cin >> userChoice;
                cout << endl;

                // String representing source, destination, type
                string source, destination, stringType;
                // Integer representing type 
                int type;
                // Boolean to control type loop
                bool typeLoop = true;

                // Add relationship
                if (userChoice == "1") {
                    // Display all classes for user clarity
                    displayDiagram(false, false);

                    cout << "Enter the name of the source: " << endl;
                    cin >> source;
                    cout << "Enter the name of the destination: " << endl;
                    cin >> destination;

                    // Loop to grab string of type and convert into integer
                    while (typeLoop) {
                        typeLoop = false;
                        cout << "Choose the type of relationship:" << endl;
                        cout << "[1] Aggregation" << endl;
                        cout << "[2] Composition" << endl;
                        cout << "[3] Generalization" << endl;
                        cout << "[4] Realization" << endl;
                        cin >> stringType;
                        if (stringType == "1" || stringType == "2" || stringType == "3" || stringType == "4") {
                            // Type is enum starting from 0, so subtract by 1
                            type = std::stoi(stringType) - 1;
                        }
                        else {
                            cout << "Invalid choice!" << endl << endl;
                            typeLoop = true;
                        }
                    }

                    ERR_CATCH(data.addRelationship(source, destination, type));
                    if (errorStatus == false) cout << endl << "Relationship added between " << source << " and " << destination
                        << " of type " << data.getRelationshipType(source, destination) << endl << endl;
                    else errorStatus = false;
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
                else if (userChoice == "3") {
                    // Display all classes and relationships for user clarity
                    displayDiagram(false, true);

                    cout << "Enter the name of the source: " << endl;
                    cin >> source;
                    cout << "Enter the name of the destination: " << endl;
                    cin >> destination;
                    
                    // Loop to grab string of type and convert into integer
                    while (typeLoop) {
                        typeLoop = false;
                        cout << "Enter the new type of relationship:" << endl;
                        cout << "[1] Aggregation" << endl;
                        cout << "[2] Composition" << endl;
                        cout << "[3] Generalization" << endl;
                        cout << "[4] Realization" << endl;
                        cin >> stringType;
                        if (stringType == "1" || stringType == "2" || stringType == "3" || stringType == "4") {
                            // Type is enum starting from 0, so subtract by 1
                            type = std::stoi(stringType) - 1;
                        }
                        else {
                            cout << "Invalid choice!" << endl << endl;
                            typeLoop = true;
                        }
                    }

                    ERR_CATCH(data.changeRelationshipType(source, destination, type));
                    if (errorStatus == false) cout << endl << "Relationship between " << source << " and " << destination
                        << " changed to type " << data.getRelationshipType(source, destination) << endl << endl;
                    else errorStatus = false;
                }
                // Go back
                else if (userChoice == "4") {
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

                    ERR_CATCH(displayClass(name));
                    if (errorStatus == false) cout << endl << "Class named " << name << " listed" << endl;
                    else errorStatus = false;
                    
                    subLoop = false;
                    cout << endl << "Enter anything to continue..." << endl;
                    cin >> name; // Pause for input
                    cout << endl; 
                }
                // Display all information
                else if (userChoice == "2") {
                    ERR_CATCH(displayDiagram (true, true));
                    if (errorStatus == false) cout << endl << "Diagram displayed" << endl;
                    else errorStatus = false;
                    
                    subLoop = false;
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
                // Requires unique try catch in order to handle file loading error
                try {
                    data = file.load();
                } catch (const std::exception& ex)
                {
                    cout << endl << "Error loading file" << endl << endl;
                    errorStatus = true;
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

// Displays information about classes within the diagram.
// Has conditional booleans to optionally display attributes and relationships.
void CLI::displayDiagram (bool displayAttribute, bool displayRelationship) 
{
    vector<UMLClass> classes = data.getClasses();
    cout << "Classes:" << endl << endl;
    for (UMLClass umlclass : classes) {
        cout << umlclass.getName() << endl;
        if (displayAttribute) {
            listAttributes(umlclass);
        }
        if (displayRelationship) {
            cout << "Relationships:" << endl;
            for (UMLRelationship rel : data.getRelationshipsByClass(umlclass.getName()))
            {
                cout << rel.getSource().getName() << " => " << rel.getDestination().getName() << endl;
                cout << "Type: " << data.getRelationshipType(rel.getSource().getName(), rel.getDestination().getName()) << endl;
            }
        }
        // Don't cause spacing within loop if only showing classes
        if (displayAttribute || displayRelationship) cout << endl;
    }
    // Display single line break if only showing classes. but NOT if classes are empty
    if (!displayAttribute && !displayRelationship && data.getClasses().size() > 0) cout << endl;
}

// Displays information about a single class with the name className.
void CLI::displayClass (string className) 
{
    // Grab copy of class in order to display attributes
    UMLClass c = data.getClassCopy(className);
    
    listAttributes(c);

    // Find relationships based on name of the class
    cout << "Relationships:" << endl;
    vector<UMLRelationship> relationshipList = data.getRelationshipsByClass(className);
    for(UMLRelationship rel : relationshipList)
    {
        cout << rel.getSource().getName() << " => " << rel.getDestination().getName() << endl;
        cout << "Type: " << data.getRelationshipType(rel.getSource().getName(), rel.getDestination().getName()) << endl;
    }
}

// *********PRIVATE METHODS*********
// Private method to display fields and methods to command line
void CLI::listAttributes(UMLClass& c)
{
    vector<UMLAttribute*> attributeList = c.getAttributesP();
    //list Fields first
    cout <<  "Fields:" << endl;
    for(UMLAttribute* attribute : attributeList)
    {
        if(attribute->identifier() == "field")
            cout << attribute->getType() << " " << attribute->getAttributeName() << endl;
    }
    cout << endl;
    
    // List methods
    cout << "Methods:" << endl;
    
    for(UMLAttribute* attribute : attributeList)
    {
        if(attribute->identifier() == "method")
        {
            cout << attribute->getType() << " " << attribute->getAttributeName() << endl;
            cout << "Param: ";
            // Get and print parameters TODO
            /*
            if(UMLMethod* test = dynamic_cast<UMLMethod*>(attribute))
            for(vector<UMLParameter>::iterator i = test->getParam().begin(); i != test->getParam().end(); ++i)
            {
                cout << i->getType() << " " << i->getName();
                if(i++ != test->getParam().end())
                    cout << ", ";
            }*/
            
        }
    }
    cout << endl;
}