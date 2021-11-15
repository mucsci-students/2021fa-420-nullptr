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
#include <algorithm> // std::copy
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
  |                           ROOT MENU                          |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Setup CLI's initial root menu
  auto rootMenu = make_unique<Menu>("cli");

  // List Classes
  rootMenu -> Insert(
    "list_classes",
    [&](std::ostream& out){ list_classes(); },
    "Lists all classes the user has created, as well as their attributes.");

  // List Relationships
  rootMenu -> Insert(
    "list_relationships",
    [&](std::ostream& out){ list_relationships(); },
    "Lists all relationships created by the user. (e.g. [source -> destination])");

  // Create Class
  rootMenu -> Insert(
    "create_class", {"class_name"},
    [&](std::ostream& out, string className)
    {
      create_class(className);
    },
    "Create a class with the name of the given argument.");

  // Create Relationship
  rootMenu -> Insert(
    "create_relationship", {"source", "destnation", "relship_type"},
    [&](std::ostream& out, string source, string destination, string relshipType)
    {
      create_relationship(source, destination, relshipType);
    },
    "Creates a relationship using a source class, destination class, and relationship type (options: aggregation, composition, generalization, realization).");

  // Delete Class
  rootMenu -> Insert(
    "delete_class", {"class_name"},
    [&](std::ostream& out, string className)
    {
      delete_class(className);
    },
    "Delete a class with the name of the given argument.");

  // Delete Relationship
  rootMenu -> Insert(
    "delete_relationship", {"source", "destnation"},
    [&](std::ostream& out, string source, string destination)
    {
      delete_relationship(source, destination);
    },
    "Deletes a relationship between a given source class and destination class.");

  // Rename Class
  rootMenu -> Insert(
    "create_class", {"old_class_name", "new_class_name"},
    [&](std::ostream& out, string oldClassName, string newClassName)
    {
      rename_class(oldClassName, newClassName);
    },
    "Renames class of old_class_name to new_class_name.");

  // Change Relationship
  rootMenu -> Insert(
    "change_relationship", {"source", "destnation", "relship_type"},
    [&](std::ostream& out, string source, string destination, string relshipType)
    {
      change_relationship(source, destination, relshipType);
    },
    "Changes a relationship given a source class and destination class to a new relationship type (options: aggregation, composition, generalization, realization).");

  // Undo
  rootMenu -> Insert(
    "undo",
    [&](std::ostream& out){ undo(); },
    "Undo the most recent thing you\'ve done.");

  // Redo 
  rootMenu -> Insert(
    "redo",
    [&](std::ostream& out){ redo(); },
    "Redo your most recently undone action.");
  
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

  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                          FIELD MENU                          |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Create submenu for editing fields
  auto fieldMenu = make_unique<Menu>("edit_fields");

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
      "add", {"class_name", "field_name", "field_type"},
      [&](std::ostream& out, string className, string fieldName, string fieldType)
      {
          if (Model.doesClassExist(className)) {
            add_field(className, fieldName, fieldType);
          }
          else{
            out << "Class does not exist. Cannot add fields.\n";
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
            out << "Class does not exist. Cannot delete fields.\n";
          };
      },
      "Deletes an existing field.");
  
  // Rename Field
  fieldMenu -> Insert(
      "rename", {"class_name", "field_name_from", "field_name_to"},
      [&](std::ostream& out, string className, string fieldNameFrom, string fieldNameTo)
      {
          if (Model.doesClassExist(className)) {
            rename_field(className, fieldNameFrom, fieldNameTo);
          }
          else{
            out << "Class does not exist. Cannot rename fields.\n";
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
            out << "Class does not exist. Cannot change field types.\n";
          };
      },
      "Changes the type of an existing field.");
    
  // Undo
  fieldMenu -> Insert(
      "undo",
      [&](std::ostream& out){ undo(); },
      "Undo the most recent thing you\'ve done.");

  // Redo 
  fieldMenu -> Insert(
      "redo",
      [&](std::ostream& out){ redo(); },
      "Redo your most recently undone action.");

  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                         METHOD MENU                          |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Create submenu for editing methods
  auto methodMenu = make_unique<Menu>("edit_methods");

  // View Class
  methodMenu -> Insert(
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
  
  // Add Method
  methodMenu -> Insert(
      "add", {"class_name"},
      [&](std::ostream& out, string className)
      {
          if (Model.doesClassExist(className)) {
            add_method(className);
          }
          else{
            out << "Class does not exist. Cannot add fields.\n";
          };
      },
      "Add a new method.");
  
  // Delete Method
  methodMenu -> Insert(
      "delete", {"class_name"},
      [&](std::ostream& out, string className)
      {
          if (Model.doesClassExist(className)) {
            delete_method(className);
          }
          else{
            out << "Class does not exist. Cannot delete fields.\n";
          };
      },
      "Deletes an existing method.");
  
  // Rename Method
  methodMenu -> Insert(
      "rename", {"class_name"},
      [&](std::ostream& out, string className)
      {
          if (Model.doesClassExist(className)) {
            rename_method(className);
          }
          else{
            out << "Class does not exist. Cannot rename fields.\n";
          };
      },
      "Renames an existing method.");
  
  // Change Method
  methodMenu -> Insert(
      "change", {"class_name"},
      [&](std::ostream& out, string className)
      {
          if (Model.doesClassExist(className)) {
            change_method(className);
          }
          else{
            out << "Class does not exist. Cannot change field types.\n";
          };
      },
      "Changes the type of an existing method.");
    
  // Undo
  methodMenu -> Insert(
      "undo",
      [&](std::ostream& out){ undo(); },
      "Undo the most recent thing you\'ve done.");

  // Redo 
  methodMenu -> Insert(
      "redo",
      [&](std::ostream& out){ redo(); },
      "Redo your most recently undone action.");

  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                        PAREMETER MENU                        |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Create sub-submenu for editing parameters
  auto parameterMenu = make_unique<Menu>("edit_parameters");

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
      "view_method", {"class_name", "method_name"},
      [&](std::ostream& out, string className, string methodName)
      {
          // Only perform method find if class was found
          if (Model.doesClassExist(className)) {
            // Check if method exists and store into pointer.
            method_ptr methodIter;
            ERR_CATCH(methodIter = select_method(className, methodName));
            // Only perform action if method was found
            if(!ErrorStatus) {
              display_method(methodIter);
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
      "add", {"class_name", "method_name"},
      [&](std::ostream& out, string className, string methodName)
      {
          // Only perform method find if class was found
          if (Model.doesClassExist(className)) {
            // Check if method exists and store into pointer.
            method_ptr methodIter;
            ERR_CATCH(methodIter = select_method(className, methodName));
            // Only perform action if method was found
            if(!ErrorStatus) {
              add_parameter(className, methodIter);
            }
            else {
              out << "Method does not exist. Cannot add parameters.\n";
              ErrorStatus = false;
            }
          }
          else{
            out << "Class does not exist. Cannot add parameters.\n";
          };
      },
      "Add a new parameter to a given method.");
  
  // Delete Parameter
  parameterMenu -> Insert(
      "delete", {"class_name", "method_name"},
      [&](std::ostream& out, string className, string methodName)
      {
          // Only perform method find if class was found
          if (Model.doesClassExist(className)) {
            // Check if method exists and store into pointer.
            method_ptr methodIter;
            ERR_CATCH(methodIter = select_method(className, methodName));
            // Only perform action if method was found
            if(!ErrorStatus) {
              delete_parameter(className, methodIter);
            }
            else {
              out << "Method does not exist. Cannot delete parameters.\n";
              ErrorStatus = false;
            }
          }
          else{
            out << "Class does not exist. Cannot delete parameters.\n";
          };
      },
      "Delete an existing parameter of a given method.");
  
  // Change Parameter
  parameterMenu -> Insert(
      "change", {"class_name", "method_name"},
      [&](std::ostream& out, string className, string methodName)
      {
          // Only perform method find if class was found
          if (Model.doesClassExist(className)) {
            // Check if method exists and store into pointer.
            method_ptr methodIter;
            ERR_CATCH(methodIter = select_method(className, methodName));
            // Only perform action if method was found
            if(!ErrorStatus) {
              change_parameter(className, methodIter);
            }
            else {
              out << "Method does not exist. Cannot change parameter types.\n";
              ErrorStatus = false;
            }
          }
          else{
            out << "Class does not exist. Cannot change parameter types.\n";
          };
      },
      "Changes an existing parameter's type within a given method.");
  
  // Undo
  parameterMenu -> Insert(
      "undo",
      [&](std::ostream& out){ undo(); },
      "Undo the most recent thing you\'ve done.");

  // Redo 
  parameterMenu -> Insert(
      "redo",
      [&](std::ostream& out){ redo(); },
      "Redo your most recently undone action.");
  
  //--------------------------------------------------------------------

  /*
  ////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  |**************************************************************|
  |                        INITIALIZATION                        |
  |**************************************************************|
  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
  */

  // Initialize menus in order of submenuing.
  methodMenu -> Insert(std::move(parameterMenu));
  rootMenu -> Insert(std::move(fieldMenu));
  rootMenu -> Insert(std::move(methodMenu));
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
 * This one might be difficult. I may have to
 * fundamentally change this code, rather than simply
 * making a few changes.
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
bool UMLCLI::add_method(string className)
{
  string methodName;
  string methodType;

  cout << "Type a name for the method you\'d like to add. -> ";
  cin >> methodName;

  cout << "What type would you like to give it? -> ";
  cin >> methodType;
  
  auto newMethod = std::make_shared<UMLMethod>(methodName, methodType, list<UMLParameter>());
  
  ERR_CATCH(Model.addClassAttribute(className, newMethod));
  if (ErrorStatus)
  {
    cout << "Error! Could not add new method.\n";
    ErrorStatus = false;
    return false;
  }

  cout << "You have added the method \"" << methodName << "\" to the class \"" << className << "\".\n";
  cout << "How many parameters would you like to give this method? -> ";
  size_t parameterCount = user_int_input();

  for(int i = 0; i < parameterCount; i++)
  {
    cout << "Parameter " << (i+1) << ":\n";
    if(!add_parameter(className, newMethod))
      i--;
  }

  cout << "Overview:\n";
  display_method(newMethod);
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
bool UMLCLI::add_parameter(string className, method_ptr methodIter)
{
  string paramName;
  string paramType;

  cout << "Type a name for your parameter -> ";
  cin >> paramName;

  while(Model.doesParameterExist(methodIter, paramName))
  {
    cout << "That name is already taken.\nTry a different name. -> ";
    cin >> paramName;
  }

  cout << "What type would you like to give it? -> ";
  cin >> paramType;
  

  ERR_CATCH(Model.addParameter(className, methodIter, paramName, paramType));
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
void UMLCLI::delete_method(string className)
{
  method_ptr methodIter;
  string methodName;

  cout << "Type the name of the method you\'d like to delete. -> ";
  cin >> methodName;

  ERR_CATCH(methodIter = select_method(className, methodName));
  if(ErrorStatus)
  {
    cout << "Error! The method you typed does not exist.\n";
    ErrorStatus = false;
    return;
  }

  attr_ptr attIter = std::dynamic_pointer_cast<UMLAttribute>(methodIter);
  
  ERR_CATCH(Model.removeClassAttribute(className, attIter));
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
void UMLCLI::delete_parameter(string className, method_ptr methodIter)
{
  string paramName;
  cout << "Type the name of the parameter you\'d like to delete. -> ";
  cin >> paramName;

  ERR_CATCH(Model.deleteParameter(className, methodIter, paramName))
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
 * @brief User types in the old name, then the new name, and
 * then it gets renamed.
 * 
 * @param className 
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
 * @param className 
 */
void UMLCLI::rename_method(string className)
{
  method_ptr methodIter;
  string methodNameFrom;
  string methodNameTo;

  cout << "Type the name of the method you\'d like to rename FROM -> ";
  cin >> methodNameFrom;

  ERR_CATCH(methodIter = select_method(className, methodNameFrom))
  if(ErrorStatus)
  {
    cout << "Error! The method you typed does not exist.\n";
    ErrorStatus = false;
    return;
  }

  cout << "Type the name of the method you\'d like to rename TO -> ";
  cin >> methodNameTo;

  attr_ptr attIter = std::dynamic_pointer_cast<UMLAttribute>(methodIter);

  ERR_CATCH(Model.changeAttributeName(className, attIter, methodNameTo));
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
void UMLCLI::rename_parameter(method_ptr methodIter)
{
  string paramNameFrom;
  string paramNameTo;

  cout << "Type the name of the parameter you\'d like to rename FROM -> ";
  cin >> paramNameFrom;
  
  cout << "Type the name of the parameter you\'d like to rename TO -> ";
  cin >> paramNameTo;
  
  ERR_CATCH(Model.changeParameterName(methodIter, paramNameFrom, paramNameTo));
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
 * @param className 
 */
void UMLCLI::change_method(string className)
{
  method_ptr methodIter;
  string methodName;
  string newMethodType;
 
  cout << "Type the name of the method whose type you\'d like to change. -> ";
  cin >> methodName;
  
  cout << "Enter the NEW type you want to give it. -> ";
  cin >> newMethodType;

  ERR_CATCH(methodIter = select_method(className, methodName));
  if(ErrorStatus)
  {
    cout << "Method couldn\'t be found.\n";
    ErrorStatus = false;
    return;
  }

  attr_ptr attIter = std::dynamic_pointer_cast<UMLAttribute>(methodIter);

  ERR_CATCH(Model.changeAttributeType(attIter, newMethodType));
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
 * @param methodIter 
 */
void UMLCLI::change_parameter(string className, method_ptr methodIter)
{
  string paramName;
  string newParamType;

  cout << "Type the name of the parameter whose type you\'d like to change. -> ";
  cin >> paramName;

  cout << "Enter the NEW type you want to give it. -> ";
  cin >> newParamType;

  ERR_CATCH(Model.changeParameterType(className, methodIter, paramName, newParamType));
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
    display_method(methodIter);
  } 
  
  cout << "}\n";
}


/*************************/


/**
 * @brief Prints out methods in the following format:
 * 
 * void m1(int p1, string p2, bool p3)
 * 
 * @param methodIter 
 */
void UMLCLI::display_method(attr_ptr methodIter)
{
  if(methodIter->identifier() == "method")
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
    cout << ")\n";
  }
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

/**
 * IMPORTANT: In Sprint 4, this function will be split in 2. The part that
 * takes in user input remain here, and the other portion will be relocated
 * to UMLData and return a map of unsigned ints and shared method pointers.
 * 
 * @brief Searches the entire vector of attributes by name.
 * 
 * If there is a match, store the reference in a new vector.
 * 
 * Iterate through the NEW vector and print each method with its parameters.
 * - A number will be labeled next to each method, and the user will choose
 *   by typing in the corresponding number.
 * 
 * @param className 
 * @param methodName 
 * @return method_ptr
 */
method_ptr UMLCLI::select_method(string className, string methodName)
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
    }
  }

  if (methodMatches.size() == 0)
  {
    throw std::runtime_error("Couldn\'t find method.");
    return nullptr;
  }

  else if (methodMatches.size() == 1)
    return methodMatches[0];

  cout << "This method is overloaded. Which one would you like to choose?\n";
  for(size_t i = 0; i < methodMatches.size(); i++)
  {
    cout << "[" << i+1 << "] ";
    display_method(methodMatches[i]);
    cout << "\n";
  }
 
  while(1)
  {
    size_t userChoice = user_int_input();

    if(userChoice > methodMatches.size() || userChoice == 0)
    {
      cout << "Invalid input! Please enter a number between 1 and "
      << methodMatches.size() << "\n";
    }
    else
      return methodMatches[userChoice-1];
  }
}

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