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
#include <memory>
#include <list>
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
                    // Prompt user for class
                    ERR_CATCH(name = orderClasses(false, false));
                    // User choose a class to remove
                    if(errorStatus == false) 
                    {
                        data.deleteClass(name);
                        cout << endl << "Class named " << name << " removed" << endl << endl;
                    }
                    // User either cancelled or there were no classes
                    else errorStatus = false;
                } 
                // Rename class
                else if (userChoice == "3") {
                    // Prompt user for class
                    ERR_CATCH(name = orderClasses(false, false));
                    // User either cancelled or there were no classes
                    if (errorStatus)
                        errorStatus = false;
                    else
                    {
                        cout << "Enter new name of class: ";
                        cin >> name2;

                        // Catch for duplicate/invalid name
                        ERR_CATCH(data.changeClassName(name, name2));
                        // Prevent success message if error was caught
                        if(errorStatus == false) 
                            cout << endl << "Class named " << name << " renamed to " << name2 << endl << endl;
                        else 
                            errorStatus = false;
                    }
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

                // Class, attribute name, type input storage
                string className, attributeName, attributeName2, type;
                
                // Add attribute
                if (userChoice == "1") {
                    // Prompt user for class
                    ERR_CATCH(className = orderClasses(false, false));
                    // User either cancelled or there were no classes
                    if (errorStatus)
                        errorStatus = false;
                    else
                    {
                        // Allow user to choose between a method or a field
                        bool attributeLoop = true;
                        // Loop for correct user input
                        while (attributeLoop)
                        {
                            cout << endl << "Add method or field:" << endl << "[1] Field" << endl << "[2] Method" << endl << endl << "Choice: ";
                            cin >> userChoice;
                            cout << endl;
                            // User chooses to add a field                     
                            if (userChoice == "1")
                            {
                                cout << "Enter the name of the field: ";
                                cin >> attributeName;
                                cout << endl << "Enter type: ";
                                cin >> type;
                                ERR_CATCH(data.addClassAttribute(className, std::make_shared<UMLField>(attributeName, type)));
                                if (errorStatus == false) cout << endl << "Field " << attributeName << " added to " << className << endl << endl;
                                else errorStatus = false;
                                attributeLoop = false;
                            }
                            // User chooses to add a method
                            else if (userChoice == "2")
                            {
                                cout << "Enter the name of the method: ";
                                cin >> attributeName;
                                cout << endl << "Enter type: ";
                                cin >> type;
                                // Construct new method with an empty list, save method for ease of modification
                                auto newMethod = std::make_shared<UMLMethod>(attributeName, type, std::list<UMLParameter>());
                                ERR_CATCH(data.addClassAttribute(className, newMethod));
                                if (errorStatus == false) {
                                    cout << endl << "Method " << attributeName << " added to " << className << endl << endl;
                                    // para
                                    bool paramLoop, paramLoop2 = true;
                                    string userChoice2;
                                    // First loop to check for correct input
                                    while(paramLoop) {
                                        cout << endl << "Add parameter? (y/n): ";
                                        cin >> userChoice2;
                                        // User chooses to add the parameters
                                        if(userChoice2 == "y" || userChoice2 == "Y") {
                                            string paramName;
                                            string paramType;
                                            // Loop to allow for unlimited parameters
                                            while(paramLoop2) {
                                                cout << endl << "Enter parameter name: ";
                                                cin >> paramName;
                                                cout << endl << "Enter parameter type: ";
                                                cin >> paramType;
                                                ERR_CATCH(data.addParameter(newMethod, paramName, paramType));
                                                // Loop to check user input
                                                bool paramLoop2 = true;
                                                while(paramLoop2) {
                                                    cout << endl << "Add more? (y/n): ";
                                                    cin >> userChoice2;
                                                    // Prompt to add parameter again
                                                    if(userChoice2 == "y" || userChoice2 == "Y")
                                                        paramLoop2 = false;
                                                    // Exit add parameter loop
                                                    else if(userChoice2 == "n" || userChoice2 == "N") {
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
                                }
                                else {
                                    errorStatus = false;
                                    attributeLoop = false;
                                }
                            }  
                            //Redo loop if invalid option entered
                            else
                                cout << "Invalid choice!" << endl << endl;
                        }
                    }
                }
                // Remove attribute
                else if (userChoice == "2") {
                    // Prompt user for class
                    ERR_CATCH(className = orderClasses(true, false));
                    // User either cancelled or there were no classes
                    if (errorStatus)
                        errorStatus = false;
                    else
                    {
                        // Prompts user for attribute from the class they chose
                        std::shared_ptr<UMLAttribute> attribute;
                        ERR_CATCH(attribute = orderAttributes(data.getClassCopy(className)));
                        // User either cancelled or the class had no attributes
                        if (errorStatus)
                            errorStatus = false;
                        else
                        {
                            data.removeClassAttribute(className, attribute);
                            cout << endl << "Attribute " << attribute->getAttributeName() << " removed from " << className << endl << endl;
                        }
                    }
                } 
                // Change attribute name, type, or parameter
                else if (userChoice == "3") {
                    // Prompt user for class
                    ERR_CATCH(className = orderClasses(true, false));
                    // User either cancelled or there were no classes
                    if (errorStatus)
                        errorStatus = false;
                    else
                    {
                        string change;
                        bool changed = false;
                        // Prompts user for attribute from the class they chose
                        std::shared_ptr<UMLAttribute> attribute;
                        ERR_CATCH(attribute = orderAttributes(data.getClassCopy(className)));
                        // User either cancelled or the class had no attributes
                        if (errorStatus)
                            errorStatus = false;
                        else
                        {
                            string identity = attribute->identifier(); // For printing correct attribute type to console
                            // Primary loop to maintain the structure of modifying an attribute
                            bool changeLoop = true;
                            // First changeLoop for changing name
                            while (changeLoop)
                            {
                                cout << "Change name? (y/n): ";
                                string option;
                                cin >> option;
                                // Check user input
                                if(option == "y" || option == "Y")
                                {
                                    cout << "Enter new name of " << identity << ": ";
                                    cin >> change;
                                    // Change attribute name within model
                                    ERR_CATCH(data.changeAttributeName(className, attribute, change));
                                    // Only break out of loop if there wasn't an error
                                    if (!errorStatus) {
                                        changeLoop = false;
                                        changed = true;
                                    }
                                    else errorStatus = false;
                                }
                                else if(option == "n" || option == "N")
                                    changeLoop = false;
                                else
                                    cout << "Invalid input!" << endl << endl;
                            }
                            // Reset changeLoop to go into next loop
                            changeLoop = true;
                            // Second changeLoop for changing type
                            while (changeLoop)
                            {
                                cout << "Change type? (y/n): ";
                                string option;
                                cin >> option;
                                // Check user input
                                if(option == "y" || option == "Y")
                                {
                                    cout << "Enter new type of " << identity << ": ";
                                    cin >> change;
                                    // Directly change attribute type (may change to fit future design patterns)
                                    // attribute->changeType(change);
                                    ERR_CATCH(data.changeAttributeType(attribute, change));
                                    if (!errorStatus) {
                                        changeLoop = false;
                                        changed = true;
                                    }
                                    else errorStatus = false;
                                }
                                else if(option == "n" || option == "N")
                                    changeLoop = false;
                                else
                                    cout << "Invalid input!" << endl << endl;
                            }
                            // Only change parameters if the attribute is a method
                            if(identity == "method")
                            {
                                // Third changeLoop for changing parameters
                                changeLoop = true;
                                while (changeLoop)
                                {
                                    cout << "Add, delete, or change parameter? (y/n): ";
                                    string option;
                                    cin >> option;
                                    // Check user input
                                    if(option == "y" || option == "Y")
                                    {
                                        bool paramLoop, paramLoop2, paramLoop3 = true;
                                        ERR_CATCH(listParameters(std::dynamic_pointer_cast<UMLMethod>(attribute)));
                                        // Only enter loop if there was no issue in listing parameters
                                        if (errorStatus)
                                            errorStatus = false;
                                        else
                                        {
                                            
                                            std::shared_ptr<UMLMethod> method = std::dynamic_pointer_cast<UMLMethod>(attribute);
                                            string userChoice2;
                                            // Reset paramLoop
                                            bool paramLoop = true;
                                            // Add parameters loop
                                            while(paramLoop) {
                                                cout << endl << "Add? (y/n): ";
                                                cin >> userChoice2;
                                                // User chooses to add the parameters
                                                if(userChoice2 == "y" || userChoice2 == "Y") {
                                                    string paramName;
                                                    string paramType;
                                                    // Reset paramLoop2
                                                    bool paramLoop2 = true;
                                                    // Loop to allow for unlimited parameters
                                                    while(paramLoop2) {
                                                        cout << endl << "Enter parameter name: ";
                                                        cin >> paramName;
                                                        cout << endl << "Enter parameter type: ";
                                                        cin >> paramType;
                                                        // Cast attribute to parameter, add parameter
                                                        ERR_CATCH(data.addParameter(method, paramName, paramType));
                                                        if(errorStatus)
                                                            errorStatus = false;
                                                        else
                                                            changed = true;
                                                       
                                                        bool paramLoop3 = true;
                                                        // Final loop to check if more should be added, otherwise break paramLoops
                                                        while(paramLoop3) {
                                                            cout << endl << "Add more? (y/n): ";
                                                            cin >> userChoice2;
                                                            // Add parameter again
                                                            if(userChoice2 == "y" || userChoice2 == "Y")
                                                                paramLoop3 = false;
                                                            // Exit add parameter loop
                                                            else if(userChoice2 == "n" || userChoice2 == "N") {
                                                                paramLoop = false;
                                                                paramLoop2 = false;
                                                                paramLoop3 = false;
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
                                            
                                            // Reset paramLoop
                                            paramLoop = true;
                                            // Delete parameters loop
                                            while(paramLoop) 
                                            {
                                                cout << endl << "Delete? (y/n): ";
                                                cin >> userChoice2;
                                                // User chooses to delete parameters
                                                if(userChoice2 == "y" || userChoice2 == "Y") {
                                                    // Loop to allow for unlimited deletion
                                                    while(method->getParam().size() > 0 && paramLoop) {
                                                        ERR_CATCH(data.deleteParameter(method, orderParameters(method).getName()));
                                                        // Error or user selected go back
                                                        if(errorStatus)
                                                        {
                                                            errorStatus = false;
                                                        }
                                                        else
                                                        {
                                                            // Successfully deleted
                                                            changed = true;
                                                            // Reset paramLoop2
                                                            paramLoop2 = true;
                                                            // Final loop to check if more should be added, otherwise break paramLoops
                                                            while(paramLoop2) {
                                                                cout << endl << "Delete more? (y/n): ";
                                                                cin >> userChoice2;
                                                                // Delete parameter again
                                                                if(userChoice2 == "y" || userChoice2 == "Y")
                                                                    paramLoop2 = false;
                                                                // Exit delete parameter loop
                                                                else if(userChoice2 == "n" || userChoice2 == "N") {
                                                                    paramLoop = false;
                                                                    paramLoop2 = false;
                                                                }
                                                                // Invalid input, enter again
                                                                else
                                                                    cout << endl << "Invalid choice!" << endl;
                                                            }
                                                        }
                                                    }
                                                    if(method->getParam().size() == 0)
                                                    {
                                                        paramLoop = false;
                                                        cout << endl << "No parameters to delete." << endl;
                                                    }
                                                }
                                                // Do not delete the parameters
                                                else if(userChoice2 == "n" || userChoice2 == "N")
                                                    paramLoop = false;
                                                // Enter input again
                                                else
                                                    cout << endl << "Invalid choice!" << endl;
                                            }
                                            // Reset paramLoop
                                            paramLoop = true;
                                            // Change parameters loop
                                            while(paramLoop) 
                                            {  
                                                cout << endl << "Change? (y/n): ";
                                                cin >> userChoice2;
                                                // User chooses to change parameters
                                                if(userChoice2 == "y" || userChoice2 == "Y") {
                                                    // Loop to allow for unlimited changing
                                                    while(method->getParam().size() > 0 && paramLoop) {
                                                        // User selected method for changed first gets deleted
                                                        ERR_CATCH(data.deleteParameter(method, orderParameters(method).getName()));
                                                        if(errorStatus)
                                                        {
                                                            errorStatus = false;
                                                        }
                                                        else
                                                        {
                                                            changed = true;
                                                            // Create new parameter to replace old parameter
                                                            cout << endl << "Enter new name: ";
                                                            string paramName, paramType;
                                                            cin >> paramName;
                                                            cout << endl << "Enter new type: ";
                                                            cin >> paramType;
                                                            ERR_CATCH(data.addParameter(method, paramName, paramType));
                                                            // If fails, just set to false and move to "change more"
                                                            if(errorStatus)
                                                                errorStatus = false;
                                                            // Reset paramLoop2
                                                            paramLoop2 = true;
                                                            // Final loop to check if more should be changed, otherwise break paramLoops
                                                            while(paramLoop2) {
                                                                cout << endl << "Change more? (y/n): ";
                                                                cin >> userChoice2;
                                                                // Add parameter again
                                                                if(userChoice2 == "y" || userChoice2 == "Y")
                                                                    paramLoop2 = false;
                                                                // Exit add parameter changeLoop
                                                                else if(userChoice2 == "n" || userChoice2 == "N") {
                                                                    paramLoop2 = false;
                                                                    paramLoop2 = false;
                                                                }
                                                                // Invalid input, enter again
                                                                else
                                                                    cout << endl << "Invalid choice!" << endl;
                                                            }
                                                        }
                                                    }
                                                    if(method->getParam().size() == 0)
                                                    {
                                                        paramLoop2 = false;
                                                        cout << endl << "No parameters to change." << endl;
                                                    }
                                                }
                                                // Do not change the parameters
                                                else if(userChoice2 == "n" || userChoice2 == "N")
                                                    paramLoop2 = false;
                                                // Enter input again
                                                else
                                                    cout << endl << "Invalid choice!" << endl;
                                            }
                                            // Loop is over, break changeLoop
                                            changeLoop = false;
                                        }
                                    }
                                    // Don't change anything within the parameters
                                    else if(option == "n" || option == "N")
                                        changeLoop = false;
                                    // Enter input again
                                    else
                                        cout << "Invalid input!" << endl << endl;
                                }
                            }
                            // In case the user decides not to do anything
                            if(!changed)
                            {
                                identity[0] = toupper(identity[0]);
                                cout << endl << identity << " unchanged." << endl;
                            }
                            else
                            {
                                identity[0] = toupper(identity[0]);
                                cout << endl << identity << " changed." << endl;
                            }
                        }
                        cout << endl;
                    }
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
                    cout << "Source: " << endl;
                    // Prompt user for source class
                    ERR_CATCH(source = orderClasses(false, false));
                    // There were no classes or user chose to go back
                    if(errorStatus)
                        errorStatus = false;
                    else 
                    {
                        cout << endl << "Destination: " << endl;
                        // Prompt user for destination class
                        ERR_CATCH(destination = orderClasses(false, false));
                        // There were no classes or user chose to go back
                        if(errorStatus)
                            errorStatus = false;
                        else 
                        {
                            // Loop to grab string of type and convert into integer
                            while (typeLoop) 
                            {
                                typeLoop = false;
                                cout << endl << "Choose the type of relationship:" << endl;
                                cout << "[1] Aggregation" << endl;
                                cout << "[2] Composition" << endl;
                                cout << "[3] Generalization" << endl;
                                cout << "[4] Realization" << endl;
                                cout << endl << "Choice: ";
                                cin >> stringType;
                                if (stringType == "1" || stringType == "2" || stringType == "3" || stringType == "4") {
                                    // Type is enum starting from 0, so subtract by 1
                                    type = std::stoi(stringType) - 1;
                                }
                                else {
                                    cout << endl << "Invalid choice!" << endl << endl;
                                    typeLoop = true;
                                }
                            }
                            ERR_CATCH(data.addRelationship(source, destination, type));
                            if (errorStatus == false) cout << endl << "Relationship added between " << source << " and " << destination
                                << " of type " << data.getRelationshipType(source, destination) << endl << endl;
                            else 
                                errorStatus = false;
                        }
                    }
                }
                // Remove relationship
                else if (userChoice == "2") 
                {
                    cout << "Source: " << endl;
                    // Prompt user for source class
                    ERR_CATCH(source = orderClasses(false, true));
                    // There were no classes or user chose to go back
                    if(errorStatus)
                        errorStatus = false;
                    else 
                    {
                        // Prompt user to choose relationship from the chosen class
                        ERR_CATCH(destination = orderRelationships(data.getClassCopy(source)));              
                        // There were no classes or user chose to go back
                        if(errorStatus)
                            errorStatus = false;
                        else
                        {
                            ERR_CATCH(data.deleteRelationship(source, destination));
                            if (errorStatus == false) 
                                cout << endl << "Relationship deleted between " << source << " and " << destination << endl << endl;
                            else 
                                errorStatus = false;
                        }
                    }
                } 
                // Change relationship
                else if (userChoice == "3") {
                    cout << "Source: " << endl;
                    // Prompt user for source class
                    ERR_CATCH(source = orderClasses(false, true));
                    // There were no classes or user chose to go back
                    if(errorStatus)
                        errorStatus = false;
                    else 
                    {
                        // Prompt user to choose relationship from the chosen class
                        ERR_CATCH(destination = orderRelationships(data.getClassCopy(source)));              
                        // There were no classes or user chose to go back
                        if(errorStatus)
                            errorStatus = false;
                        else
                        {
                            // Loop to grab string of type and convert into integer
                            while (typeLoop) {
                                typeLoop = false;
                                cout << endl;
                                cout << "Enter the new type of relationship:" << endl;
                                cout << "[1] Aggregation" << endl;
                                cout << "[2] Composition" << endl;
                                cout << "[3] Generalization" << endl;
                                cout << "[4] Realization" << endl;
                                cout << endl << "Choice: ";
                                cin >> stringType;
                                if (stringType == "1" || stringType == "2" || stringType == "3" || stringType == "4") {
                                    // Type is enum starting from 0, so subtract by 1
                                    type = std::stoi(stringType) - 1;
                                }
                                else {
                                    cout << endl << "Invalid choice!" << endl << endl;
                                    typeLoop = true;
                                }
                            }
                            ERR_CATCH(data.changeRelationshipType(source, destination, type));
                            if (errorStatus == false) cout << endl << "Relationship between " << source << " and " << destination
                                << " changed to type " << data.getRelationshipType(source, destination) << endl << endl;
                            else errorStatus = false;
                        }
                    }
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
                    // Prompt user for class to display
                    name = orderClasses(false, false); 

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
    std::list<UMLClass> classes = data.getClasses();
    cout << "Classes:" << endl << endl;
    for (UMLClass umlclass : classes) {
        cout << umlclass.getName() << endl;
        if (displayAttribute) {
            listAttributes(umlclass);
        }
        if (displayRelationship) {
            listRelationships(umlclass);
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
void CLI::listAttributes(UMLClass& umlclass)
{
    //list Fields first
    cout << "    Fields:" << endl;
    for(auto attribute : umlclass.getAttributes())
    {
        if(attribute->identifier() == "field")
            cout << "     " << attribute->getType() << " " << attribute->getAttributeName() << endl;
    }
    cout << endl;
    
    // List methods
    cout << "    Methods:" << endl;

    bool isMethod = false;
    for(auto attribute : umlclass.getAttributes())
    {
        if(attribute->identifier() == "method")
        {
            cout << "     " << attribute->getType() << " " << attribute->getAttributeName() << endl;
            cout << "      Parameters: " << endl;
            for (auto param : (std::dynamic_pointer_cast<UMLMethod>(attribute))->getParam())
                cout << "       " << param.getType() << " " << param.getName() << endl;
            isMethod = true;
        }
    }
    // If there's no methods add white space for better appearance
    if(!isMethod)
        cout << endl;
    cout << endl;
}

// Display relationships of a class to command line
void CLI::listRelationships(UMLClass& umlclass)
{
    cout << "     Relationships:" << endl;
            for (UMLRelationship rel : data.getRelationshipsByClass(umlclass.getName()))
            {
                cout << "     " << rel.getSource().getName() << " => " << rel.getDestination().getName() << endl;
                cout << "     Type: " << data.getRelationshipType(rel.getSource().getName(), rel.getDestination().getName()) << endl;
            }
}

// List classes numerically so user can choose easier and throws error if there are no classes or user decides to cancel the operation
string CLI::orderClasses(bool displayAttribute, bool displayRelationship)
{
    std::list<UMLClass> classes = data.getClasses();
    //If there are no classes throw an error
    if(classes.size() == 0)
        throw "There are no classes.";
    int num;        //converted user input to int
    int option;     //option displayed to command line
    string input;   //user input
    // Loop for user input
    while(true)
    {
        cout << "Choose a class:" << endl << endl;
        option = 0;
        // Loop to display classes to CLI
        for (UMLClass umlclass : classes) 
        {
            option++;
            cout << "[" << option << "] " << umlclass.getName() << endl;
            // display attributes if option is chosen
            if(displayAttribute)
                listAttributes(umlclass);
            if(displayRelationship)
                listRelationships(umlclass);    
        }
        cout << "[0] Go back" << endl;

        cout << endl << "Choice: ";

        // Check input string if its valid, i.e. a single number between 0 and the number of classes
        cin >> input;
        // String must contain a digit, otherwise it will represent -1 (invalid input).
        if (std::all_of(input.begin(), input.end(), ::isdigit))
        {
            num = std::stoi(input);
        }
        else
        {
            num = -1;
        }
        
        // Check user input
        // Run loop again if user enters incorrect input
        if (num < 0 || num > option)
            cout << endl << "Invalid input!" << endl << endl;
        // Not an actual error, just exits the add Class option
        else if (num == 0)
            throw "Going back...";
        // Return name of chosen class
        else
        {
            auto temp = classes.begin();
            advance(temp, num - 1);
            return temp->getName();
        }
    }
    return "something bad's happened"; // Should never return this
}

// Lists attributes of a class with numbers for selection, returns a smart pointer of the chosen attribute
std::shared_ptr<UMLAttribute> CLI::orderAttributes(UMLClass c)
{
    // If there are no attributes throw an error
    if(c.getAttributes().size() == 0)
        throw "There are no attributes.";

    int num;        //converted user input to int
    int option; //option displayed to command line
    string input;   //user input
    int methodindex;

    // Loop for user input
    while(true)
    {
        cout << endl;
        cout << "Choose an attribute:" << endl << endl;
        int option = 0;
        //list Fields first
        cout << "Fields:" << endl;
        for(auto attribute : c.getAttributes())
        {
            if(attribute->identifier() == "field")
            {
                option++;
                cout << "[" << option << "] " << attribute->getType() << " " << attribute->getAttributeName() << endl;
            }
        }
        cout << endl;
        // Save method index for later separation of fields and methods
        methodindex = option;
    
        // List methods
        cout << "Methods:" << endl;
        for(auto attribute : c.getAttributes())
        {
            bool method = false;
            if(attribute->identifier() == "method")
            {
                option++;
                cout << "[" << option << "] " << attribute->getType() << " " << attribute->getAttributeName() << endl;
                cout << "     Parameters: " << endl;
                for (auto param : (std::dynamic_pointer_cast<UMLMethod>(attribute))->getParam())
                    cout << "      " << param.getType() << " " << param.getName() << endl;
                method = true;
            }
            if (!method)
                cout << endl;
        }
        cout << "[0] Go back" << endl;
        cout << endl << "Choice: ";

        // Check input string if its valid, i.e. a single number between 0 and the number of classes
        // and convert string input to int num
        cin >> input;
        if (std::all_of(input.begin(), input.end(), ::isdigit))
        {
            num = std::stoi(input);
        }
        else
        {
            num = -1;
        }

        // Check user input
        // Run loop again if user enters incorrect input
        if (num < 0 || num > option)
            cout << endl << "Invalid input!" << endl;
        // Not an actual error, just exits the add Class option
        else if (num == 0)
            throw "Going back...";
        // Return pointer of chosen attribute
        else
        {
            // Check if input is for method or field
            // num refers to a field so find the field
            if(num <= methodindex)
            {
                int option = 0;
                for(auto attribute : c.getAttributes())
                {
                    if(attribute->identifier() == "field")
                    {
                        option++;
                        if(option == num)
                            return attribute;
                    }
                }
            }
            // num refers to method so find the method
            else
            {
                int option = methodindex;
                for(auto attribute : c.getAttributes())
                {
                    if(attribute->identifier() == "method")
                    {
                        option++;
                        if(option == num)
                            return attribute;
                    }
                }
            }
        }
    }
}

// Display relationships of a class to command line and allows selection, returning the destination string
string CLI::orderRelationships(UMLClass umlclass)
{
    std::vector<UMLRelationship> relationships = data.getRelationshipsByClass(umlclass.getName());

    // Check if there are any relationships
    if(relationships.size() == 0)
        throw "There are no relationships.";
    int num;        //converted user input to int
    int option = 0; //option displayed to command line
    string input;   //user input

    // Loop for user input
    while(true)
    {
        cout << endl << "Choose a relationship:" << endl;

        for (UMLRelationship rel : relationships)
        {
            option++;
            cout << "[" << option << "] " << rel.getSource().getName() << " => " << rel.getDestination().getName() << endl;
            cout << "     Type: " << data.getRelationshipType(rel.getSource().getName(), rel.getDestination().getName()) << endl;
        }
        cout << "[0] Go back" << endl;
        cout << endl << "Choice: ";

        // Check input string if its valid, i.e. a single number between 0 and the number of classes
        cin >> input;
        if (std::all_of(input.begin(), input.end(), ::isdigit))
        {
            num = std::stoi(input);
        }
        else
        {
            num = -1;
        }

        // Check user input
        // Run loop again if user enters incorrect input
        if (num < 0 || num > option)
            cout << endl << "Invalid input!" << endl;
        // Not an actual error, just exits the add Class option
        else if (num == 0)
            throw "Going back...";
        // Return pointer of chosen attribute
        else
            return relationships[num-1].getDestination().getName();
    }
}

// Lists parameters for a given method
void CLI::listParameters(std::shared_ptr<UMLMethod> method)
{
    std::list<UMLParameter> paramList = method->getParam();
    //If there are no parameters throw an error
    if(paramList.size() == 0)
        return;

    cout << endl << "Parameters:" << endl;
    for(UMLParameter param : paramList)
        cout << param.getType() << " " << param.getName() << endl;
    
}

// Lists parameters with numbers and returns a reference to the chosen one
UMLParameter CLI::orderParameters(std::shared_ptr<UMLMethod> method)
{
    std::list<UMLParameter> paramList = method->getParam();
    //If there are no parameters throw an error
    if(paramList.size() == 0)
        throw "There are no parameters.";

    // Loop for user input
    int num;        //converted user input to int
    int option = 0; //option displayed to command line
    string input;   //user input
    while(true)
    {
        cout << endl << "Choose a parameter:" << endl;

        for (UMLParameter param : paramList)
        {
            option++;
            cout << "[" << option << "] " << param.getType() << " " << param.getName() << endl;
        }
        cout << "[0] Go back" << endl;
        cout << endl << "Choice: ";

        // Check input string if its valid, i.e. a single number between 0 and the number of classes
        cin >> input;
        if (std::all_of(input.begin(), input.end(), ::isdigit))
        {
            num = std::stoi(input);
        }
        else
        {
            num = -1;
        }

        // Check user input
        // Run loop again if user enters incorrect input
        if (num < 0 || num > option)
            cout << endl << "Invalid input!" << endl;
        // Not an actual error, just exits the add Class option
        else if (num == 0)
            throw "Going back...";
        // Return pointer of chosen attribute
        else
        {
            int i = 0;
            for(UMLParameter param : method->getParam())
            {
                if(i == num - 1)
                    return param;
                i++;
            }
        }
    }
}