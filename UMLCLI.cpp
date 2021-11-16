/*
  Filename   : CLI.cpp
  Description: Implementation of the command line interface.
*/

/************************************************************/
// Catch for functions to protect from invalid inputs
#define ERR_CATCH(fun)                                  \
    try {                                               \
        fun;                                            \
        History.save(Model);                            \
    }                                                   \
    catch (const std::runtime_error& error) {           \
        cout << endl << error.what() << endl << endl;   \
        ErrorStatus = true;                             \
    }
/************************************************************/

//--------------------------------------------------------------------
// System includes
#include <cli/cli.h>
#include <cli/loopscheduler.h>
#include <cli/clilocalsession.h>
#include <vector>
#include <algorithm>
#include "include/UMLCLI.hpp"
//--------------------------------------------------------------------
// Using declarations
using namespace cli;
using namespace std;
//--------------------------------------------------------------------
// strcasecmp Windows support
#if defined(_WIN64)
    #define strcasecmp _stricmp
#endif
//--------------------------------------------------------------------

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                        PUBLIC FUNCTIONS                      |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

/**
 * @brief Takes in user input and calls different functions based on
 * what command the user types.
 * 
 */
void UMLCLI::cli_menu()
{
  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                           MAIN MENU                          |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Setup CLI's initial root menu
  auto rootMenu = make_unique<Menu>("uml", "Main menu for basic UML functions.");

  // Load 
  rootMenu -> Insert(
    "load", {"file_name"},
    [&](std::ostream& out, string fileName)
    {
      load_uml(fileName);
    },
    "Enter the name of a json file (no file extension) within your build directory as an argument to override the current UML diagram with a new model.");

  // Save
  rootMenu -> Insert(
    "save", {"file_name"},
    [&](std::ostream& out, string fileName)
    {
      save_uml(fileName);
    },
    "Enter the name of your UML diagram (no file extension) as an argument to save a json representation of it within your build directory.");

  // Turn On Color
  rootMenu -> Insert(
      "color",
      [](std::ostream& out){ out << "Colors ON\n"; SetColor(); },
      "Enable colors in the CLI.");

  // Turn Off Color
  rootMenu -> Insert(
      "nocolor",
      [](std::ostream& out){ out << "Colors OFF\n"; SetNoColor(); },
      "Disable colors in the CLI.");

  // Undo
  rootMenu -> Insert(
    "undo",
    [&](std::ostream& out){ clear_selected_method(); undo(); },
    "Undo the most recent thing you\'ve done. WARNING: Also clears your selected method.");

  // Redo 
  rootMenu -> Insert(
    "redo",
    [&](std::ostream& out){ clear_selected_method(); redo(); },
    "Redo your most recently undone action. WARNING: Also clears your selected method.");


  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                           CLASS MENU                         |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Create submenu for class operations
  auto classMenu = make_unique<Menu>("class", "Menu for operations on classes.");

  // List Classes
  classMenu -> Insert(
    "list",
    [&](std::ostream& out){ list_classes(); },
    "Lists all classes the user has created, as well as their attributes.");
  
  // Add Class
  classMenu -> Insert(
    "add", {"class_name"},
    [&](std::ostream& out, string className)
    {
      create_class(className);
    },
    "Create a class with the name of the given argument.");
  
  // Delete Class
  classMenu -> Insert(
    "delete", {"class_name"},
    [&](std::ostream& out, string className)
    {
      delete_class(className);
    },
    "Delete a class with the name of the given argument.");
  
  // Rename Class
  classMenu -> Insert(
    "rename_class", {"old_class_name", "new_class_name"},
    [&](std::ostream& out, string oldClassName, string newClassName)
    {
      rename_class(oldClassName, newClassName);
    },
    "Renames class of old_class_name to new_class_name.");
  
  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                      RELATIONSHIP MENU                       |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Create submenu for class operations
  auto relationshipMenu = make_unique<Menu>("relationships", "Menu for operations on relationships.");

  // List Relationships
  relationshipMenu -> Insert(
    "list",
    [&](std::ostream& out){ list_relationships(); },
    "Lists all relationships created by the user. (e.g. [source -> destination])");
  
  // Add Relationship
  relationshipMenu -> Insert(
    "add", {"source", "destination", "relship_type"},
    [&](std::ostream& out, string source, string destination, string relshipType)
    {
      create_relationship(source, destination, relshipType);
    },
    "Creates a relationship using a source class, destination class, and relationship type (options: aggregation, composition, generalization, realization).");
  
  // Delete Relationship
  relationshipMenu -> Insert(
    "delete", {"source", "destination"},
    [&](std::ostream& out, string source, string destination)
    {
      delete_relationship(source, destination);
    },
    "Deletes a relationship between a given source class and destination class.");
  
  // Change Relationship
  relationshipMenu -> Insert(
    "change", {"source", "destination", "relship_type"},
    [&](std::ostream& out, string source, string destination, string relshipType)
    {
      change_relationship(source, destination, relshipType);
    },
    "Changes a relationship given a source class and destination class to a new relationship type (options: aggregation, composition, generalization, realization).");


  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                          FIELD MENU                          |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Create submenu for editing fields
  auto fieldMenu = make_unique<Menu>("field", "Menu for operations on class fields.");

  // View Class
  fieldMenu -> Insert(
    "view", {"class_name"},
    [&](std::ostream& out, string className)
    {
      if (Model.doesClassExist(className)) {
        UMLClass currentClass = Model.getClassCopy(className);
        display_class(currentClass);
      }
      else{
        out << "Class does not exist. Cannot view class.\n";
      };
    },
    "View a given class with its fields and methods.");
  
  // Add Field
  fieldMenu -> Insert(
    "add", {"class_name", "field_type", "field_name"},
    [&](std::ostream& out, string className, string fieldType, string fieldName)
    {
      if (Model.doesClassExist(className)) {
        add_field(className, fieldName, fieldType);
      }
      else{
        out << "Class does not exist. Cannot add field.\n";
      };
    },
    "Add a new field.");
  
  // Delete Field
  fieldMenu -> Insert(
    "delete", {"class_name", "field_name"},
    [&](std::ostream& out, string className, string fieldName)
    {
      if (Model.doesClassExist(className)) {
        delete_field(className, fieldName);
      }
      else{
        out << "Class does not exist. Cannot delete field.\n";
      };
    },
    "Deletes an existing field.");
  
  // Rename Field
  fieldMenu -> Insert(
    "rename", {"class_name", "field_name", "new_field_name"},
    [&](std::ostream& out, string className, string fieldName, string newFieldName)
    {
      if (Model.doesClassExist(className)) {
        rename_field(className, fieldName, newFieldName);
      }
      else{
        out << "Class does not exist. Cannot rename field.\n";
      };
    },
    "Renames an existing field.");
  
  // Change Field
  fieldMenu -> Insert(
    "change", {"class_name", "field_name", "new_field_type"},
    [&](std::ostream& out, string className, string fieldName, string newFieldType)
    {
      if (Model.doesClassExist(className)) {
        change_field(className, fieldName, newFieldType);
      }
      else{
        out << "Class does not exist. Cannot change field type.\n";
      };
    },
    "Changes the type of an existing field.");
    
  // Undo
  fieldMenu -> Insert(
    "undo",
    [&](std::ostream& out){ clear_selected_method(); undo(); },
    "Undo the most recent thing you\'ve done. WARNING: Also clears your selected method.");

  // Redo 
  fieldMenu -> Insert(
    "redo",
    [&](std::ostream& out){ clear_selected_method(); redo(); },
    "Redo your most recently undone action. WARNING: Also clears your selected method.");

  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                         METHOD MENU                          |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Create submenu for editing methods
  auto methodMenu = make_unique<Menu>("method", "Menu for operations on class methods.");

   // Select Method
  methodMenu -> Insert(
    "select", {"class_name", "method_name", "method_number"},
    [&](std::ostream& out, string className, string methodName, int methodNumber)
    {
      if (Model.doesClassExist(className)) {
        // Check to see if method we're attempting to select exists
        method_ptr methodIter;
        ERR_CATCH(methodIter = select_overload(className, methodName, methodNumber));
        if (!ErrorStatus) { 
          out << "Method " << methodName << " selected.\n";
          cout << "Overview:\n";
          display_method(className, methodIter);
          store_selected_method(className, methodIter);
        }
        else {
          out << "Cannot select method.\n";
          out << "Make sure you are selecting the correct method number.\n";
          out << "This number be found by viewing the class and observing the final number placed next to a method.\n";
        }
      }
      else{
        out << "Class does not exist. Cannot select method.\n";
      };
    },
    "Select a method for use in other operations.");

  // View Selected Method
  methodMenu -> Insert(
    "view_select", {},
    [&](std::ostream& out)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot view selected method..\n";
      }
      else {
        out << "CLASS: " << MethodClassName << "\n";
        display_method(MethodClassName, SelectedMethod);
      };
    },
    "View the currently selected method.");

  // View Class
  methodMenu -> Insert(
    "view_class", {"class_name"},
    [&](std::ostream& out, string className)
    {
      if (Model.doesClassExist(className)) {
        UMLClass currentClass = Model.getClassCopy(className);
        display_class(currentClass);
      }
      else{
        out << "Class does not exist. Cannot view class.\n";
      };
    },
    "View a given class with its fields and methods.");
  
  // Add Method
  methodMenu -> Insert(
    "add", {"class_name", "method_type", "method_name"},
    [&](std::ostream& out, string className, string methodType, string methodName)
    {
      if (Model.doesClassExist(className)) {
        add_method(className, methodName, methodType);
      }
      else{
        out << "Class does not exist. Cannot add method.\n";
      };
    },
    "Add a new method.");
  
  // Delete Method
  methodMenu -> Insert(
    "delete", {},
    [&](std::ostream& out)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot delete method.\n";
      }
      else {
        delete_method();
        // Clear global variables, as method no longer exists
        clear_selected_method();
      };
    },
    "Deletes the method selected by select_method.");
  
  // Rename Method
  methodMenu -> Insert(
    "rename", {"new_method_name"},
    [&](std::ostream& out, string newMethodName)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot rename method.\n";
      }
      else {
        rename_method(newMethodName);
      }
      },
    "Renames the method selected by select_method to new_method_name.");
  
  // Change Method
  methodMenu -> Insert(
    "change", {"new_method_type"},
    [&](std::ostream& out, string newMethodType)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot change method type.\n";
      }
      else {
        change_method(newMethodType);
      }
    },
    "Changes the type of the method selected by select_method to new_method_type.");
    
  // Undo
  methodMenu -> Insert(
    "undo",
    [&](std::ostream& out){ clear_selected_method(); undo(); },
    "Undo the most recent thing you\'ve done. WARNING: Also clears your selected method.");

  // Redo 
  methodMenu -> Insert(
    "redo",
    [&](std::ostream& out){ clear_selected_method(); redo(); },
    "Redo your most recently undone action. WARNING: Also clears your selected method.");

  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                        PAREMETER MENU                        |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Create sub-submenu for editing parameters
  auto parameterMenu = make_unique<Menu>("parameter", "Menu for operations on method parameters.");

  // Select Method
  parameterMenu -> Insert(
    "select", {"class_name", "method_name", "method_number"},
    [&](std::ostream& out, string className, string methodName, int methodNumber)
    {
      if (Model.doesClassExist(className)) {
        // Check to see if method we're attempting to select exists
        method_ptr methodIter;
        ERR_CATCH(methodIter = select_overload(className, methodName, methodNumber));
        if (!ErrorStatus) { 
          out << "Method " << methodName << " selected.\n";
          cout << "Overview:\n";
          display_method(className, methodIter);
          store_selected_method(className, methodIter);
        }
        else {
          out << "Cannot select method.\n";
          out << "Make sure you are selecting the correct method number.\n";
          out << "This number be found by viewing the class and observing the final number placed next to a method.\n";
        }
      }
      else{
        out << "Class does not exist. Cannot select method.\n";
      };
    },
    "Select a method for use in other operations.");
  
  // View Selected Method
  parameterMenu -> Insert(
    "view_select", {},
    [&](std::ostream& out)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot view selected method..\n";
      }
      else {
        out << "CLASS: " << MethodClassName << "\n";
        display_method(MethodClassName, SelectedMethod);
      };
    },
    "View the currently selected method.");

  // View Class
  parameterMenu -> Insert(
    "view_class", {"class_name"},
    [&](std::ostream& out, string className)
    {
      if (Model.doesClassExist(className)) {
        UMLClass currentClass = Model.getClassCopy(className);
        display_class(currentClass);
      }
      else{
        out << "Class does not exist. Cannot view class.\n";
      };
    },
    "View a given class with its fields and methods.");

  // View Method
  parameterMenu -> Insert(
    "view_method", {"class_name", "method_name", "method_number"},
    [&](std::ostream& out, string className, string methodName, int methodNumber)
    {
      // Only perform method find if class was found
      if (Model.doesClassExist(className)) {
        // Check if method exists and store into pointer.
        method_ptr methodIter;
        ERR_CATCH(methodIter = select_overload(className, methodName, methodNumber));
        // Only perform action if method was found
        if(!ErrorStatus) {
          display_method(className, methodIter);
        }
        else {
          out << "Method does not exist. Cannot view method.\n";
          ErrorStatus = false;
        }
      }
      else{
        out << "Class does not exist. Cannot view methods.\n";
      };
    },
    "View a given method with its parameters.");
  
  // Add Parameter
  parameterMenu -> Insert(
    "add", {"param_type", "param_name"},
    [&](std::ostream& out, string paramType, string paramName)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot add parameter.\n";
      }
      else {
        add_parameter(paramName, paramType);
      }
    },
    "Add a new parameter to a method. Requires a selected method.");

  // Delete Parameter
  parameterMenu -> Insert(
    "delete", {"param_name"},
    [&](std::ostream& out, string paramName)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot delete parameter.\n";
      }
      else {
        delete_parameter(paramName);
      }
    },
    "Delete an existing parameter of a method. Requires a selected method.");
  
  // Delete Parameter
  parameterMenu -> Insert(
    "rename", {"param_name_old", "param_name_new"},
    [&](std::ostream& out, string paramNameOld, string paramNameNew)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot rename parameter.\n";
      }
      else {
        rename_parameter(paramNameOld, paramNameNew);
      }
    },
    "Delete an existing parameter of a method. Requires a selected method.");
  
  // Change Parameter
  parameterMenu -> Insert(
    "change", {"param_name", "new_param_type"},
    [&](std::ostream& out, string paramName, string newParamType)
    {
      if (!MethodSelected) {
        out << "No method selected. Cannot change parameter type.\n";
      }
      else {
        change_parameter(paramName, newParamType);
      }
    },
    "Changes an existing parameter's type within a method. Requires a selected method.");
  
  // Undo
  parameterMenu -> Insert(
    "undo",
    [&](std::ostream& out){ clear_selected_method(); undo(); },
    "Undo the most recent thing you\'ve done. WARNING: Also clears your selected method.");

  // Redo 
  parameterMenu -> Insert(
    "redo",
    [&](std::ostream& out){ clear_selected_method(); redo(); },
    "Redo your most recently undone action. WARNING: Also clears your selected method.");
  
  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                        INITIALIZATION                        |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Initialize global variables
  ErrorStatus = false;
  clear_selected_method();

  // Initialize menus in order of submenuing.
  
  methodMenu -> Insert(std::move(parameterMenu));
  rootMenu -> Insert(std::move(classMenu));
  rootMenu -> Insert(std::move(relationshipMenu));
  rootMenu -> Insert(std::move(fieldMenu));
  rootMenu -> Insert(std::move(methodMenu));

  // Initialize CLI that starts at root menu.
  Cli cli(std::move(rootMenu));

  // Initialize and run the local CLI session.
  // Until the exit action is called, the scheduler operates on a loop.
  LoopScheduler scheduler;
  CliLocalTerminalSession localSession(cli, scheduler, std::cout, 200);
  localSession.ExitAction(
    [&scheduler](auto& out)
    {
      out << "Exiting CLI...\n"; // Session exit action
      scheduler.Stop();
    }
  );
  scheduler.Run();
}

/************************************/

/**
 * @brief Lists all classes the user has created.
 * 
 */
void UMLCLI::list_classes()
{
  list<UMLClass> classList = Model.getClasses();

  //if no classes, error message.
  if (classList.size() == 0)
  {
    cout << "You have no classes.\n";
    return;
  }
  
  for(auto currentClass : classList)   
    display_class(currentClass);
  
}

/************************************/

/**
 * @brief Lists all relationships the user has created.
 * 
 */
void UMLCLI::list_relationships()
{
  std::vector <UMLRelationship> allRelationships = Model.getRelationships();
  if (allRelationships.size() == 0)
  {
    cout << "You have no relationships.\n";
    return;
  }

  for(auto iter = allRelationships.begin(); iter != allRelationships.end(); iter++)
  {
    UMLRelationship currentRel = *iter;
    string source = currentRel.getSource().getName();
    string destination = currentRel.getDestination().getName();
    
    
    string rType = Model.getRelationshipType(source, destination);

    display_relationship(source, destination, rType);
  }
}

/************************************/

/**
 * @brief User creates and names a class and may give it any number
 * of attributes.
 * 
 */
void UMLCLI::create_class(string className)
{
  if(Model.doesClassExist(className))
  {
    cout << "That class name already exists. Aborting.\n";
    return;
  }

  ERR_CATCH(Model.addClass(className));
  if(ErrorStatus)
  {
    cout << "Failed to add class.\n";
    ErrorStatus = false;
    return;
  }

  cout << "Successfully added new class \"" << className << "\".\n";

  UMLClass newClass = Model.getClassCopy(className);

  cout << "Overview:\n";
  display_class(newClass);
}

/************************************/

/**
 * @brief Creates a new relationship between classes.
 * 
 */
void UMLCLI::create_relationship(string source, string destination, string relshipType)
{
  int typeIndex = -1;
  
  // Check to see if source exists
  if(!Model.doesClassExist(source)) {
    cout << "The class \"" << source << "\" does not exist.\n";
    return;
  }
  // Check to see if destination exists
  else if(!Model.doesClassExist(destination)) {
    cout << "The class \"" << destination << "\" does not exist.\n";
    return;
  }
  // Check to see if relationship already exists
  else if(Model.doesRelationshipExist(source, destination)) {
    cout << "A relationship already exists between " << source << " and " << destination << ". Aborting.\n";
    return;
  }

  // Check to see if valid type was input
  else if(!strcasecmp(relshipType.c_str(), "A") || !strcasecmp(relshipType.c_str(), "Aggregation")) {
    typeIndex = 0;
  }
  else if(!strcasecmp(relshipType.c_str(), "C") || !strcasecmp(relshipType.c_str(), "Composition")) {
    typeIndex = 1;
  }
  else if(!strcasecmp(relshipType.c_str(), "G") || !strcasecmp(relshipType.c_str(), "Generalization")) {
    typeIndex = 2;
  }
  else if(!strcasecmp(relshipType.c_str(), "R") || !strcasecmp(relshipType.c_str(), "Realization")) {
    typeIndex = 3;
  }
  else {
    cout << "Invalid type!\n";
    return;
  }

  ERR_CATCH(Model.addRelationship(source, destination, typeIndex));
  if(ErrorStatus)
  {
    cout << "Error! Could not add new relationship.\n";
    ErrorStatus = false;
    return;
  }

  cout << "Relationship added between " << source << " and " << destination
  << " of type " << Model.getRelationshipType(source, destination) << "\n";
  
}

/************************************/

/**
 * @brief User will be prompted to type in the class name,
 * and if it exists, it will be deleted.
 * 
 */
void UMLCLI::delete_class(string className)
{
  ERR_CATCH(Model.deleteClass(className));
  if (ErrorStatus)
  {
    cout << "Could not find class name \"" << className << "\". Aborting.\n";
    ErrorStatus = false;
    return;
  }
  cout << className << " was successfully removed.\n";
}

/************************************/

/**
 * @brief User will be prompted to type in the source and destination,
 * and if the relationship exists, it will be deleted.
 * 
 */
void UMLCLI::delete_relationship(string source, string destination)
{
  ERR_CATCH(Model.deleteRelationship(source, destination));

  if(ErrorStatus)
  {
    cout << "Relationship was not found. Aborting.\n";
    ErrorStatus = false;
    return;
  }
  
  cout << "Relationship was successfully deleted.\n";
}

/************************************/

/**
 * @brief User types in the current class name, and then the name
 * they'd like to change it to. Then it gets renamed.
 * 
 */
void UMLCLI::rename_class(string oldClassName, string newClassName)
{
  if (!Model.doesClassExist(oldClassName))
  {
    cout << "Error! The class you typed does not exist.\n";
    return;
  }
  ERR_CATCH(Model.changeClassName(oldClassName, newClassName));
  if(ErrorStatus)
  {
    cout << "Name modification failed. Make sure the name you typed is a valid class\n"
    << "name, and isn\'t the same name as another class.\n"
    << "Aborting...\n";
    ErrorStatus = false;
    return;
  }
  cout << "The class \"" << oldClassName << "\" has been renamed to \"" << newClassName << "\".\n";
}

/************************************/

/**
 * @brief User will be prompted to type in the source, destination,
 * and NEW type. Then the relationship type will be changed.
 * 
 */
void UMLCLI::change_relationship(string source, string destination, string relshipType)
{
  int typeIndex = -1;
  
  // Check to see if source exists
  if(!Model.doesClassExist(source)) {
    cout << "The class \"" << source << "\" does not exist.\n";
    return;
  }
  // Check to see if destination exists
  else if(!Model.doesClassExist(destination)) {
    cout << "The class \"" << destination << "\" does not exist.\n";
    return;
  }
  // Check to see if relationship already exists
  else if(Model.doesRelationshipExist(source, destination)) {
    cout << "A relationship already exists between " << source << " and " << destination << ". Aborting.\n";
    return;
  }

  // Check to see if valid type was input
  else if(!strcasecmp(relshipType.c_str(), "A") || !strcasecmp(relshipType.c_str(), "Aggregation")) {
    typeIndex = 0;
  }
  else if(!strcasecmp(relshipType.c_str(), "C") || !strcasecmp(relshipType.c_str(), "Composition")) {
    typeIndex = 1;
  }
  else if(!strcasecmp(relshipType.c_str(), "G") || !strcasecmp(relshipType.c_str(), "Generalization")) {
    typeIndex = 2;
  }
  else if(!strcasecmp(relshipType.c_str(), "R") || !strcasecmp(relshipType.c_str(), "Realization")) {
    typeIndex = 3;
  }
  else {
    cout << "Invalid type!\n";
    return;
  }

  ERR_CATCH(Model.changeRelationshipType(source, destination, typeIndex));
  if(ErrorStatus)
  {
    cout << "Could not change relationship type.\n";
    ErrorStatus = false;
    return;
  }

  cout << "The relationship\'s type was changed successfully!\n";
}

/************************************/

/**
 * @brief Saves the user's progress into a json file.
 * 
 */
void UMLCLI::save_uml(string fileName)
{
  UMLFile file(fileName + ".json");
  file.save(Model);
  cout << "Your file has been saved\n";
}

/************************************/

/**
 * @brief Loads a json save file, overwriting the current session.
 * 
 */
void UMLCLI::load_uml(string fileName)
{
  UMLFile file(fileName + ".json");
  // Requires unique try catch in order to handle file loading error
  try {
    Model = file.load();
  } catch (const std::exception& ex)
  {
    cout << "\nError loading file\n\n";
    ErrorStatus = true;
  }
  if (!ErrorStatus) 
    cout << "Your file has been loaded\n";
  else 
    ErrorStatus = false;
}

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                       PRIVATE FUNCTIONS                      |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

/**************************************************************/
//ADDING

/**
 * @brief User types in the name and type, and the field
 * is created.
 * 
 * @param className 
 */
bool UMLCLI::add_field(string className, string fieldName, string fieldType)
{
  ERR_CATCH(Model.addClassAttribute(className, std::make_shared<UMLField>(fieldName, fieldType)));
  if (ErrorStatus)
  {
    cout << "Failed to add field.\n";
    ErrorStatus = false;
    return false;
  }

  cout << "You have added the field \"" << fieldName << "\" to the class \"" << className << "\".\n";
  return true;
}



/*************************/


/**
 * @brief User types in the method name and type, and the method 
 * is created. User can also specify how many parameters to give
 * it, and they can name and assign types to them accordingly.
 * 
 * @param className 
 */
bool UMLCLI::add_method(string className, string methodName, string methodType)
{
  auto newMethod = std::make_shared<UMLMethod>(methodName, methodType, list<UMLParameter>());
  
  ERR_CATCH(Model.addClassAttribute(className, newMethod));
  if (ErrorStatus)
  {
    cout << "Error! Could not add new method.\n";
    ErrorStatus = false;
    return false;
  }

  cout << "You have added the method \"" << methodName << "\" to the class \"" << className << "\".\n";

  cout << "Overview:\n";
  display_method(className, newMethod);
  return true;
}

/*************************/

/**
 * @brief User types in parameter name and type, and the
 * parameter is created accordingly.
 * 
 * @param methodIter
 * @return true 
 * @return false 
 */
bool UMLCLI::add_parameter(string paramName, string paramType)
{
  ERR_CATCH(Model.addParameter(MethodClassName, SelectedMethod, paramName, paramType));
  if(ErrorStatus)
  {
    cout << "Error! The parameter \"" << paramName << "\" could not be created.\n";
    ErrorStatus = false;
    return false;
  }
  
  cout << "The parameter \"" << paramName << "\" was successfully created!\n";
  return true;
}

/**************************************************************/
//DELETING

/**
 * @brief User types in the name of the field, and it
 * gets deleted.
 * 
 * @param className 
 */
void UMLCLI::delete_field(string className, string fieldName)
{
  attr_ptr fieldIter;

  ERR_CATCH(fieldIter = select_field(className, fieldName));
  ERR_CATCH(Model.removeClassAttribute(className, fieldIter));
  if (ErrorStatus)
  {
    cout << "Error! Couldn't find field.\n";
    ErrorStatus = false;
    return;
  }
  cout << "The field \"" << fieldName << "\" was deleted.\n";
}


/*************************/


/**
 * @brief User types in the name of the method. If the
 * method is overloaded, they can specify which one (in
 * a different function). The method is then deleted.
 * 
 * @param className 
 */
void UMLCLI::delete_method()
{
  string methodName = SelectedMethod->getAttributeName();
  ERR_CATCH(Model.removeClassAttribute(MethodClassName, SelectedMethod));
  if (ErrorStatus)
  {
    cout << "Error! Could not delete method.\n";
    ErrorStatus = false;
    return;
  }
  cout << "The method \"" << methodName << "\" was deleted.\n";
}


/*************************/


/**
 * @brief User types in the name of the parameter and it
 * gets deleted.
 * 
 * @param methodIter
 */
void UMLCLI::delete_parameter(string paramName)
{
  ERR_CATCH(Model.deleteParameter(MethodClassName, SelectedMethod, paramName))
  if(ErrorStatus)
  {
    cout << "Error! Couldn't find parameter.\n";
    ErrorStatus = false;
    return;
  }
  cout << "The parameter \"" << paramName << "\" was deleted.\n";
}



/**************************************************************/
//RENAMING

/**
 * @brief Given a class name, an old field name, and a new field 
 * name, renames a given field named fieldNameFrom to a field 
 * with the name of fieldNameTo.
 * 
 * @param className 
 * @param fieldNameFrom
 * @param fieldNameTo
 */
void UMLCLI::rename_field(string className, string fieldNameFrom, string fieldNameTo)
{
  attr_ptr fieldIter;

  ERR_CATCH(fieldIter = select_field(className, fieldNameFrom));
  if (ErrorStatus)
  {
    cout << "Error! The field you typed does not exist. Aborting...\n";
    ErrorStatus = false;
    return;
  }
  else if (Model.doesFieldExist(className, fieldNameTo))
  {
    cout << "Error! That field already exists. Aborting...\n";
    return;
  }
  
  ERR_CATCH(Model.changeAttributeName(className, fieldIter, fieldNameTo))
  if (ErrorStatus)
  {
    cout << "Failed to change name. Aborting...\n";
    ErrorStatus = false;
    return;
  }

  cout << "Field successfully renamed!\n";
}

/*************************/

/**
 * @brief User types in the old name of the method. If the
 * method is overloaded, they can specify which one (in
 * a different function). Then they type in the new name,
 * and it gets renamed.
 * 
 * @param newMethodName
 */
void UMLCLI::rename_method(string newMethodName)
{
  ERR_CATCH(Model.changeAttributeName(MethodClassName, SelectedMethod, newMethodName));
  if (ErrorStatus)
  {
    cout << "Failed to rename method. Aborting...\n";
    ErrorStatus = false;
    return;
  }

  cout << "Method successfully renamed!\n";
}

/*************************/

/**
 * @brief User types in the old name, then the new name, and
 * then it gets renamed.
 * 
 * @param methodIter
 */
void UMLCLI::rename_parameter(string paramNameOld, string paramNameNew)
{
  ERR_CATCH(Model.changeParameterName(SelectedMethod, paramNameOld, paramNameNew));
  if (ErrorStatus)
  {
    cout << "Error! Could not change name.\n";
    ErrorStatus = false;
    return;
  }

  cout << "Parameter sucessfully renamed!\n";
}

/**************************************************************/
//TYPE-CHANGING

/**
 * @brief User types in the name, and then the new type.
 * The field's type is then changed accordingly.
 * 
 * @param className 
 * @param fieldName
 * @param newFieldType
 */
void UMLCLI::change_field(string className, string fieldName, string newFieldType)
{
  attr_ptr fieldIter;

  ERR_CATCH(fieldIter = select_field(className, fieldName));
  ERR_CATCH(Model.changeAttributeType(fieldIter, newFieldType));
  if(ErrorStatus)
  {
    cout << "Couldn\'t change type.\n";
    ErrorStatus = false;
    return;
  }

  cout << "The type of your field was changed successfully!\n";
}

/*************************/

/**
 * @brief User types in the name. If the method is overloaded, 
 * they can specify which one (in a different function). The 
 * user then types in the new type. The field's type is then
 * changed accordingly.
 * 
 * @param newMethodType 
 */
void UMLCLI::change_method(string newMethodType)
{
  ERR_CATCH(Model.changeAttributeType(SelectedMethod, newMethodType));
  if (ErrorStatus)
  {
    cout << "Couldn\'t change method.\n";
    ErrorStatus = false;
    return;
  }

  cout << "The type of your method was changed successfully!\n";
}

/*************************/

/**
 * @brief User types in the name, and then the new type.
 * The parameter's type is then changed accordingly.
 * 
 * @param className
 * @param methodIter 
 */
void UMLCLI::change_parameter(string paramName, string newParamType)
{
  ERR_CATCH(Model.changeParameterType(MethodClassName, SelectedMethod, paramName, newParamType));
  if (ErrorStatus)
  {
    cout << "Couldn\'t change parameter type.\n";
    ErrorStatus = false;
    return;
  }

  cout << "The type of your parameter was changed successfully!\n";
}

/**************************************************************/
//DISPLAY FUNCTIONS

/**
 * @brief Takes in a UMLClass object, and displays it in
 * a format like this:
 * 
 * CLASS: c1 {
 *   Fields:
 *      int f1
 *      int f2
 *      string f3
 *   Methods:
 *      void m1(int p1, string p2, bool p3)
 *      int m2()
 *      bool m3(int p1)
 * }
 * 
 * @param currentClass 
 */
void UMLCLI::display_class(UMLClass currentClass)
{ 
  string className = currentClass.getName();


  cout << "CLASS: " << className << "{\n";
  cout << "  Fields:\n";
  
  //Fields
  for(auto fieldIter : currentClass.getAttributes())
  {
    if(fieldIter->identifier() == "field")
      cout << "     " << fieldIter->getType() << " " << fieldIter->getAttributeName() << "\n";
  }

  cout << "  Methods:\n";
  
  //Methods
  for(auto methodIter : currentClass.getAttributes())
  {
    if(methodIter->identifier() == "method") {
      shared_ptr<UMLMethod> castMethodIter = std::dynamic_pointer_cast<UMLMethod>(methodIter);
      display_method(currentClass.getName(), castMethodIter);
    }
  } 
  
  cout << "}\n";
}


/*************************/


/**
 * @brief Prints out methods in the following format:
 * 
 * void m1(int p1, string p2, bool p3) (num)
 * Num represents the count of overloads, to be used in selecting
 * an overload within the CLI's select_method option.
 * 
 * @param className
 * @param methodIter 
 */
void UMLCLI::display_method(string className, method_ptr methodIter)
{
  cout << "     ";
  cout << methodIter->getType() << " " << methodIter->getAttributeName() << "(";
  
  //Parameters
  size_t paramCount = 0;
  for (auto param : (std::dynamic_pointer_cast<UMLMethod>(methodIter))->getParam())
  {
    paramCount++;
    if (paramCount > 1)
      cout << ", ";
    
    cout << param.getType() << " " << param.getName();
  }
  cout << ") (" << method_number(className, std::dynamic_pointer_cast<UMLMethod>(methodIter)) << ")\n";
}

/*************************/

/**
 * @brief Prints out relationships in the following format:
 * 
 * TYPE        : Aggregation
 * SOURCE      : C1
 * DESTINATION : C2
 * 
 * @param source 
 * @param destination 
 * @param rType 
 */
void UMLCLI::display_relationship(string source, string destination, string rType)
{
  cout << "TYPE        : " << rType << "\n";
  cout << "SOURCE      : " << source << "\n";
  cout << "DESTINATION : " << destination << "\n";
}

/**************************************************************/
//INPUT PARSING

/**
 * @brief Takes in user input and makes sure it's
 * an unsigned int (size_t).
 * 
 * @return size_t 
 */
size_t UMLCLI::user_int_input()
{
  size_t num;

  while(!(cin >> num))
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input. Try again (input a number): ";
  }
  return num;
}

/**************************************************************/
//UNDO/REDO

/**
 * @brief Undo the most recent thing you've done.
 */
void UMLCLI::undo()
{
  Model = History.undo();
  cout << "You\'ve undone your last action.\n";
}

/*************************/

/**
 * @brief Redo your most recently undone action.
 */
void UMLCLI::redo()
{
  Model = History.redo();
  cout << "You\'ve redone your last undo.\n";
}

/**************************************************************/
//MISC.

/*************************/

/**
 * @brief Takes in a name and returns the attribute pointer to that
 * field.
 * 
 * @param className 
 * @param fieldName 
 * @return attr_ptr 
 */
attr_ptr UMLCLI::select_field(string className, string fieldName)
{
  vector<attr_ptr> allAttributes = Model.getClassAttributes(className);

  for(attr_ptr iter : allAttributes)
  {
    if(iter->identifier() == "field" && iter->getAttributeName() == fieldName)
      return iter;
  }

  throw std::runtime_error("Couldn\'t find field.");
  return nullptr;
}

/*************************/

/**
 * @brief Searches the entire vector of attributes by name.
 * 
 * If there is a match, store the reference in a new vector. If that
 * match also shares the same parameters, it should return the vector index
 * that the new method was stored into.
 * 
 * @param className 
 * @param methodName 
 * @return int
 */
int UMLCLI::method_number(string className, method_ptr method) 
{
  vector<method_ptr> methodMatches;
  vector<attr_ptr> allAttributes = Model.getClassAttributes(className);

  // Search the entire attribute vector and put matches in methodMatches
  for(auto attributeIter : allAttributes)
  {
    // Check if there was a match
    if(attributeIter->identifier() == "method" && attributeIter->getAttributeName() == method->getAttributeName())
    {
      method_ptr element = std::dynamic_pointer_cast<UMLMethod>(attributeIter);
      // If these share the same parameters, return the appropriate overload integer.
      
      if (element->getParam() == method->getParam()) {
        // Should be displaced by 1 postion of where it would be in the vector
        return ((int) methodMatches.size()) + 1;
      }
      // If no match, continue creation of array
      methodMatches.push_back(element);
    }
  }

  // If made past loop, the method cannot exist within the data.
  throw std::runtime_error("Couldn\'t find method.");
  return -1;
}

/*************************/

/**
 * @brief Searches the entire vector of attributes by name.
 * 
 * If there is a match, store the reference in a new vector. If that
 * match also shares the same parameters, it should return the vector index
 * that the new method was stored into.
 * 
 * @param className 
 * @param methodName 
 * @param methodNumber
 * @return method_ptr
 */
 method_ptr UMLCLI::select_overload(string className, string methodName, int methodNumber) 
 {
  vector<method_ptr> methodMatches;
  vector<attr_ptr> allAttributes = Model.getClassAttributes(className);

  //Search the entire attribute vector and put matches in methodMatches
  for(auto attributeIter : allAttributes)
  {
    if(attributeIter->identifier() == "method" && attributeIter->getAttributeName() == methodName)
    {
      method_ptr element = std::dynamic_pointer_cast<UMLMethod>(attributeIter);
      methodMatches.push_back(element);
      // Should have reached element when the number matches the size
      if(methodNumber == (int) methodMatches.size()) {
        return element;
      }
    }
  }

  // If made past loop, the method cannot exist within the data.
  throw std::runtime_error("Couldn\'t find method.");
  return nullptr;
 }

/*************************/

/**
 * @brief Stores the selected method within global variables and 
 * toggles global bool MethodSelected so that CLI functions can use
 * the selected method.
 * 
 * @param className 
 * @param method
 */
 void UMLCLI::store_selected_method(string className, method_ptr method)
 {
   MethodSelected = true;
   MethodClassName = className;
   SelectedMethod = method;
 }

 /*************************/

/**
 * @brief Clears selected method from global variables and untoggles
 * global bool MethodSelected so certain functions cannot be used.
 * 
 */
 void UMLCLI::clear_selected_method()
 {
   MethodSelected = false;
   MethodClassName = "";
   SelectedMethod = nullptr;
 }

  /*************************/