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
#include <cli/clifilesession.h>
#include <vector>
#include <algorithm> // std::copy
#include "include/CLI.hpp"
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
void CLI::cli_menu()
{
  //--------------------------------------------------------------------

  // Setup CLI's initial root menu
  auto rootMenu = make_unique<Menu>("cli");

  // List Classes
  rootMenu -> Insert(
      "list_classes",
      [&](){ list_classes(); },
      "Lists all classes the user has created, as well as their attributes.");

  // List Relationships
  rootMenu -> Insert(
      "list_relationships",
      [&](){ list_relationships(); },
      "Lists all relationships created by the user. (e.g. [source -> destination])");

  // Create Class
  rootMenu -> Insert(
      "create_class",
      [&](){ create_class(); },
      "User will be prompted to name the class, and then it\'ll be created.");

  // Create Relationship
  rootMenu -> Insert(
      "create_relationship",
      [&](){ create_relationship(); },
      "Type in a source class and a destination class to create a relationship between them.");

  // Delete Class
  rootMenu -> Insert(
      "delete_class",
      [&](){ delete_class(); },
      "User will be prompted to type the name of the class they\'d like to delete.");

  // Delete Relationship
  rootMenu -> Insert(
      "delete_relationship",
      [&](){ delete_relationship(); },
      "User will be prompted to type the source and destination. The relationship will be no more, but the classes will still exist.");

  // Rename Class
  rootMenu -> Insert(
      "rename_class",
      [&](){ rename_class(); },
      "User will be prompted to type an existing class name, and then the new name they'd like to replace it with.");

  // Change Relationship
  rootMenu -> Insert(
      "change_relationship",
      [&](){ change_relationship(); },
      "Supply a source, destination, and new type to replace a preexisting relationship with a new one.");

  // Undo
  rootMenu -> Insert(
      "undo",
      [&](){ undo(); },
      "Undo the most recent thing you\'ve done.");

  // Redo 
  rootMenu -> Insert(
      "redo",
      [&](){ redo(); },
      "Redo your most recently undone action.");
  
  // Load 
  rootMenu -> Insert(
      "load",
      [&](){ load_uml(); },
      "Enter the name of a json file within your build directory to override the current UML diagram with a new model.");

  // Save
  rootMenu -> Insert(
      "save",
      [&](){ save_uml(); },
      "Enter the name of your UML diagram to save a json representation of it within your build directory.");

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
  
  // Create submenu for editing fields
  auto fieldMenu = make_unique<Menu>("edit_fields");

  // View Class
  fieldMenu->Insert(
      "view", {"class_name"},
      [&](std::ostream& out, string className)
      {
          if (Model.doesClassExist(className)) {
            UMLClass currentClass = Model.getClassCopy(className);
            display_class(currentClass);
          }
          else{
            out << "Class does not exist. Cannot view.\n"
          };
      },
      "View a given class with its fields and methods.");
  
  // Add Field
  fieldMenu->Insert(
      "add", {"class_name"},
      [&](std::ostream& out, string className)
      {
          if (Model.doesClassExist(className)) {
            add_field(className);
          }
          else{
            out << "Class does not exist. Cannot add field.\n"
          };
      },
      "Add a new field.");
  
  fieldMenu -> Insert(
      "demo",
      [](std::ostream& out){ out << "This is a sample!\n"; },
      "Print a demo string" );

  //--------------------------------------------------------------------

  // Create submenu for editing methods
  auto methodMenu = make_unique<Menu>("edit_methods");

  //--------------------------------------------------------------------

  // Create sub-submenu for editing parameters
  auto parameterMenu = make_unique<Menu>("edit_parameters");

  
  // Initialize menus in order of submenuing.
  rootMenu -> Insert(std::move(fieldMenu));
  rootMenu -> Insert(std::move(methodMenu));
  methodMenu -> Insert(std::move(parameterMenu));
  Cli cli(std::move(rootMenu));

  // Global exit action
  cli.ExitAction( [](auto& out){ out << "See ya!\n"; } );

  // Initialize and run the local CLI session.
  // Until the exit action is called, the scheduler operates on a loop.
  LoopScheduler scheduler;
  CliLocalTerminalSession localSession(cli, scheduler, std::cout, 200);
  localSession.ExitAction(
    [&scheduler](auto& out) // session exit action
    {
      out << "Exiting CLI...\n";
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
void CLI::list_classes()
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
void CLI::list_relationships()
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
void CLI::display_class(UMLClass currentClass)
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
void CLI::display_method(attr_ptr methodIter)
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
void CLI::display_relationship(string source, string destination, string rType)
{
  cout << "TYPE        : " << rType << "\n";
  cout << "SOURCE      : " << source << "\n";
  cout << "DESTINATION : " << destination << "\n";
}