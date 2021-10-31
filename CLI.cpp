/*
  Filename   : CLI.cpp
  Author(s)  : Matt Giacoponello
  Description: Implementation of the command line interface.
*/


/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                       NOTES & STARTUP                        |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////


BUGS & ISSUES:

  - 

*/


/************************************************************/
// Catch for functions to protect from invalid inputs
#define ERR_CATCH(fun)                                  \
    try {                                               \
        fun;                                            \
    }                                                   \
    catch (const std::runtime_error& error) {           \
        cout << endl << error.what() << endl << endl;   \
        ErrorStatus = true;                             \
    }
/************************************************************/

//--------------------------------------------------------------------
// System includes
#include <memory>
#include <list>
#include "include/CLI.hpp"
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
  ErrorStatus = false;

  cout << "Welcome to UML++!\n\n";
  cout << "Type \"help\" to view all available commands.\nType \"quit\" to quit your current session.\n";

  string userInput; 
  
  do
  {
    cout << "> ";
    cin >> userInput;

    if (userInput == "help")
      print_main_commands();

    else if(userInput == "list_classes")
      list_classes();
    
    else if(userInput == "list_relationships")
      list_relationships();
    
    else if(userInput == "create_class")
      create_class();
    
    else if(userInput == "create_relationship")
      create_relationship();
    
    else if(userInput == "delete_class")
      delete_class();
    
    else if(userInput == "delete_relationship")
      delete_relationship();
    
    else if(userInput == "rename_class")
      rename_class();
    
    else if(userInput == "change_relationship")
      change_relationship();

    else if(userInput == "edit_fields")
      edit_fields();
    
    else if(userInput == "edit_methods")
      edit_methods();
    
    else if(userInput == "load")
      save_uml();
    
    else if(userInput == "save")
      load_uml();
    
    else if (userInput == "quit")
      cout << "\n";
    
    else
    {
      cout << "Invalid command! Type \"help\" to view all available coommands.\n";
    }
  }
  while(userInput != "quit");
  
  cout << "See ya!\n";


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


/************************************/


/**
 * @brief User creates and names a class and may give it any number
 * of attributes.
 * 
 */
void CLI::create_class()
{

  string className;
  cout << "Choose a name for your class -> ";
  cin >> className;

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

  cout << "How many fields would you like to start with? -> ";
  size_t fieldCount = user_int_input();

  for(size_t i = 0; i < fieldCount; i++)
  {
    cout << "Field " << (i+1) << ":\n";
    if(!add_field(className))
      i--;
  }

  cout << "How many methods would you like to start with? -> ";
  size_t methodCount = user_int_input();

  for(size_t i = 0; i < methodCount; i++)
  {
    cout << "Method " << (i+1) << ":\n";
    if(!add_method(className))
    i--;
  }

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
void CLI::create_relationship()
{

  string sourceClassName;
  string destinationClassName;
  string relshipType;
  int typeIndex = -1;
  

  while(1)
  {
    cout << "Type in a class name you\'d like to use for the source -> ";
    cin >> sourceClassName;

    if(!Model.doesClassExist(sourceClassName))
      cout << "The class \"" << sourceClassName << "\" does not exist.\n";

    else
      break;
  }

  while(1)
  {
    cout << "Type in a class name you\'d like to use for the destination -> ";
    cin >> destinationClassName;

    if(!Model.doesClassExist(destinationClassName))
      cout << "The class \"" << destinationClassName << "\" does not exist.\n";
    
    else
      break;
  }


  
  if(Model.doesRelationshipExist(sourceClassName, destinationClassName))
  {
    cout << "A relationship already exists between " << sourceClassName << " and " << destinationClassName << ". Aborting.\n";
    return;
  }
  
  // Loop to grab string of type and convert into integer
  do
  {
    cout << "Choose the type of relationship:\n"
      << "\'A\' or \'Aggregation\'\n" 
      << "\'C\' or \'Composition\'\n" 
      << "\'G\' or \'Generalization\'\n" 
      << "\'R\' or \'Realization\'\n"; 
    
    cout << "\nChoice: ";
    cin >> relshipType;
    
    if(!strcasecmp(relshipType.c_str(), "A") || !strcasecmp(relshipType.c_str(), "Aggregation"))
      typeIndex = 0;

    else if(!strcasecmp(relshipType.c_str(), "C") || !strcasecmp(relshipType.c_str(), "Composition"))
      typeIndex = 1;

    else if(!strcasecmp(relshipType.c_str(), "G") || !strcasecmp(relshipType.c_str(), "Generalization"))
      typeIndex = 2;

    else if(!strcasecmp(relshipType.c_str(), "R") || !strcasecmp(relshipType.c_str(), "Realization"))
      typeIndex = 3;

    else
      cout << "Invalid type!\n";
     
  }while(typeIndex < 0 || typeIndex > 3);


  ERR_CATCH(Model.addRelationship(sourceClassName, destinationClassName, typeIndex));
  if(ErrorStatus)
  {
    cout << "Error! Could not add new relationship.\n";
    ErrorStatus = false;
    return;
  }

  cout << "Relationship added between " << sourceClassName << " and " << destinationClassName
  << " of type " << Model.getRelationshipType(sourceClassName, destinationClassName) << "\n";
  
}


/************************************/


/**
 * @brief User will be prompted to type in the class name,
 * and if it exists, it will be deleted.
 * 
 */
void CLI::delete_class()
{
  string className;
  cout << "Enter class name to be deleted -> ";
  cin >> className;
  
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
void CLI::delete_relationship()
{
  string sourceClassName;
  string destinationClassName;

  cout << "Enter the source of the relationship to be deleted -> ";
  cin >> sourceClassName;

  cout << "Enter the destination of the relationship to be deleted -> ";
  cin >> destinationClassName;

  ERR_CATCH(Model.deleteRelationship(sourceClassName, destinationClassName));

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
void CLI::rename_class()
{
  string oldClassName;
  string newClassName;
  

  cout << "Enter the CURRENT name of the class you\'d like to rename. -> ";
  cin >> oldClassName;

  if (!Model.doesClassExist(oldClassName))
  {
    cout << "Error! The class you typed does not exist.\n";
    return;
  }

  
  cout << "Enter the new name you\'d like to rename it to. -> ";
  cin >> newClassName;
  
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
void CLI::change_relationship()
{
  string source;
  string destination;
  string relshipType;
  int typeIndex = -1;

  cout << "Type in the source of the relationship whose type you\'d like to change. -> ";
  cin >> source;
  if (!Model.doesClassExist(source))
  {
    cout << "Error! The class you typed does not exist.\n";
    return;
  }

  cout << "Type in the destination. -> ";
  cin >> destination;

  if (!Model.doesClassExist(destination))
  {
    cout << "Error! The class you typed does not exist.\n";
    return;
  }

  
  do
  {
    cout << "Choose the type of relationship:\n"
      << "\'A\' or \'Aggregation\'\n" 
      << "\'C\' or \'Composition\'\n" 
      << "\'G\' or \'Generalization\'\n" 
      << "\'R\' or \'Realization\'\n"; 
    
    cout << "\nChoice: ";
    cin >> relshipType;
    
    if(!strcasecmp(relshipType.c_str(), "A") || !strcasecmp(relshipType.c_str(), "Aggregation"))
      typeIndex = 0;

    else if(!strcasecmp(relshipType.c_str(), "C") || !strcasecmp(relshipType.c_str(), "Composition"))
      typeIndex = 1;

    else if(!strcasecmp(relshipType.c_str(), "G") || !strcasecmp(relshipType.c_str(), "Generalization"))
      typeIndex = 2;

    else if(!strcasecmp(relshipType.c_str(), "R") || !strcasecmp(relshipType.c_str(), "Realization"))
      typeIndex = 3;

    else
      cout << "Invalid type!\n";
     
  }while(typeIndex < 0 || typeIndex > 3);


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
 * @brief Does various things with fields based on user input.
 * 
 * This one might be difficult.
 */
void CLI::edit_fields()
{
  string className;
  string input;
  
  cout << "Enter the name of the class whose fields and/or parameters you\'d like to edit.\n-> ";
  cin >> className;

  if (!Model.doesClassExist(className))
  {
    cout << "Error! The class you typed does not exist.\n";
    cout << "Returning to main menu.\n";
    return;
  }
  
  cout << "Type \"help\" to view all available editor commands.\n";
  do
  {
    cout << "-> ";

    cin >> input;
    
    if(input == "help")
      print_field_commands();
    
    else if(input == "view")
    {
      UMLClass currentClass = Model.getClassCopy(className);
      display_class(currentClass);
    }
    else if(input == "add")
      add_field(className);

    else if(input == "delete")
      delete_field(className);
    
    else if(input == "rename")
      rename_field(className);

    else if(input == "change")
      change_field(className);

    else if (input == "switch_class")
    {
      //recursive call
      edit_fields();
      return;
    }
    else if(input == "exit")
    {
      cout << "You have exited the field editor.\n";
      cout << "Returning to main menu.\n";
      return;
    }
    else
      cout << "Invadid command! Type \"help\" to view all available field editor commands.\n";
  
  }
  while(1);
}


/************************************/

/**
 * @brief Does various things with methods based on user input.
 * 
 */
void CLI::edit_methods()
{
  string className;
  string input;
  
  
  cout << "Enter the name of the class whose methods and/or parameters you\'d like to edit.\n-> ";
  cin >> className;

  if (!Model.doesClassExist(className))
  {
    cout << "Error! The class you typed does not exist.\n";
    cout << "Returning to main menu.\n";
    return;
  }

  cout << "Type \"help\" to view all available editor commands.\n";
  do
  {
    cout << "-> ";

    cin >> input;
    
    if(input == "help")
      print_method_commands();
    
    else if(input == "view")
    {
      UMLClass currentClass = Model.getClassCopy(className);
      display_class(currentClass);
    }
    else if(input == "add")
      add_method(className);

    else if(input == "delete")
      delete_method(className);

    else if(input == "rename")
      rename_method(className);

    else if(input == "change")
      change_method(className);
    
    else if (input == "edit_parameters")
      edit_parameters(className);

    else if (input == "switch_class")
    {
      //recursive call
      edit_methods();
      return;
    }
    else if(input == "exit")
    {
      cout << "You have exited the method editor.\n";
      cout << "Returning to main menu.\n";
      return;
    }
    else
      cout << "Invadid command! Type \"help\" to view all available method editor commands.\n";

  }
  while(1);
}

/************************************/

/**
 * @brief Does various things with parameters based on user input.
 * 
 * @param className 
 */
void CLI::edit_parameters(string className)
{
  string methodName;
  string input;
  method_ptr methodIter;

  cout << "Enter the name of the method whose parameters you\'d like to edit.\n-> ";
  cin >> methodName;
  
  ERR_CATCH(methodIter = select_method(className, methodName));
  if(ErrorStatus)
  {
    cout << "Error! The method you typed does not exist.\n";
    cout << "Returning to method editor.\n";
    ErrorStatus = false;
    return;
  }
  
  cout << "Type \"help\" to view all available editor commands.\n";
  while(1)
  {
    cout << "-> ";

    cin >> input;
    
    if(input == "help")
      print_parameter_commands();
    
    else if(input == "view")
    {
      cout << "Current Method:\n";
      display_method(methodIter);
    }
    else if(input == "add")
      add_parameter(className, methodIter); 
    
    else if(input == "delete")
      delete_parameter(className, methodIter);
    
    else if(input == "rename")
      rename_parameter(methodIter);

    else if(input == "change")
      change_parameter(className, methodIter);
    
    else if(input == "switch_method")
    {
      //recursive call
      edit_parameters(className);
      return;
    }
    else if(input == "exit")
    {
      cout << "You have exited the parameter editor.\n";
      cout << "Returning to method editor.\n";
      return;
    }
    else
      cout << "Invadid command! Type \"help\" to view all available parameter editor commands.\n";
  }
}


/************************************/

/**
 * @brief Saves the user's progress into a json file.
 * 
 */
void CLI::save_uml()
{
  // Saves UML diagram to a JSON file in the same directory as the executable
  cout << "Name of file: ";
  string fileName;
  cin >> fileName;

  UMLFile file(fileName + ".json");
  file.save(Model);
  cout << "Your file has been saved\n";
}

/************************************/


/**
 * @brief Loads a json save file, overwriting the current session.
 * 
 */
void CLI::load_uml()
{
  // Ask for name of file, and then load UML data given the proper format
  cout << "Name of file: ";
  string fileName;
  cin >> fileName;

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
//PRINT-HELP FUNCTIONS


/**
 * @brief Prints commands for the user to type, and explains
 * what each command does.
 * 
 */
void CLI::print_main_commands()
{
  cout << "COMMANDS:\n\n" 
  << "list_classes        : Lists all classes the user has created, as well as their attributes.\n\n"
  << "list_relationships  : Lists all relationships created by the user. (e.g. [source -> destination])\n\n"
  << "create_class        : User will be prompted to name the class, and then it\'ll be created.\n\n"
  << "create_relationship : User will be prompted to type in a source class and a destination class.\n\n"
  << "delete_class        : User will be prompted to type the name of the class they\'d like to delete.\n\n"
  << "delete_relationship : User will be prompted to type the source and destination. The relationship\n"
  << "                      will be no more, but the classes will still exist.\n\n"
  << "rename_class        : User will be prompted to type the existing class name, and then the new\n"
  << "                      name.\n\n"
  << "change_relationship : User will be prompted to type in source, destination, and the NEW type\n"
  << "                      of the relationship, and the type will be changed accordingly.\n\n"
  << "edit_fields         : User will be sent to a sub-menu, where they can enter in field editor\n"
  << "                      commands.\n\n"
  << "edit_methods        : User will be sent to a sub-menu, where they can enter in method editor\n"
  << "                      commands (including a parameter editor sub-sub-menu).\n\n" 
  << "load                : User will be prompted to type the name of the json file, and then it loads\n"
  << "                      the model from that file. WARNING! Existing progress will be overwritten!\n\n" 
  << "save                : User will be prompted to name the JSON file, which will contain their\n"
  << "                      current progress.\n\n" 
  << "quit                : Exit your current session.\n\n";
}

/************************************/

/**
 * @brief Prints commands for the user to type, and explains
 * what each command does.
 * 
 */
void CLI::print_field_commands()
{
  cout << "FIELD EDITOR COMMANDS:\n"
    << "view         : View the current class with its fields.\n"
    << "add          : Add a new field.\n"
    << "delete       : Delete an existing field.\n"
    << "rename       : Rename an existing field.\n"
    << "change       : Change the type of an existing field.\n"
    << "switch_class : Allows the user to switch to a different class.\n"
    << "exit         : Quit the field editor and return to the normal interface.\n\n";
}

/************************************/

/**
 * @brief Prints commands for the user to type, and explains
 * what each command does.
 * 
 */
void CLI::print_method_commands()
{
  cout << "METHOD EDITOR COMMANDS:\n"
    << "view            : View the current class with its methods.\n"
    << "add             : Add a new method.\n"
    << "delete          : Delete an existing method.\n"
    << "rename          : Rename an existing method.\n"
    << "change          : Change the type of an existing method.\n"
    << "switch_class    : Allows the user to switch to a different class.\n"
    << "edit_parameters : User will be sent to a sub menu to edit a method's parameters.\n"
    << "exit            : Quit the method editor and return to the normal interface.\n\n";
}

/************************************/

/**
 * @brief Prints commands for the user to type, and explains
 * what each command does.
 * 
 */
void CLI::print_parameter_commands()
{
  cout << "PARAMETER EDITOR COMMANDS:\n"
    << "view          : View the current method with its parameters.\n"
    << "add           : Add a new parameter.\n"
    << "delete        : Delete an existing parameter.\n"
    << "rename        : Rename an existing parameter\n"
    << "change        : Change the type of an existing parameter.\n"
    << "switch_method : Allows the user to switch to a different method.\n"
    << "exit          : Quit the parameter editor and return to the method editor.\n\n";
}

/**************************************************************/
//ADDING

/**
 * @brief User types in the name and type, and the field
 * is created.
 * 
 * @param className 
 */
bool CLI::add_field(string className)
{
  string fieldName;
  string fieldType;

  cout << "Type a name for the field you\'d like to add. -> ";
  cin >> fieldName;
  
  while(Model.doesFieldExist(className, fieldName))
  { 
    cout << "That name is already taken.\nTry a different name. -> ";
    cin >> fieldName;
  }

  cout << "What type would you like to give it? -> ";
  cin >> fieldType;

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
bool CLI::add_method(string className)
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
bool CLI::add_parameter(string className, method_ptr methodIter)
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
void CLI::delete_field(string className)
{
  
  attr_ptr fieldIter;
  string fieldName;
  cout << "Type the name of the field you\'d like to delete. -> ";
  cin >> fieldName;

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
void CLI::delete_method(string className)
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
void CLI::delete_parameter(string className, method_ptr methodIter)
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
void CLI::rename_field(string className)
{
  attr_ptr fieldIter;
  string fieldNameFrom;
  string fieldNameTo;

  cout << "Type the name of the field you\'d like to rename FROM -> ";
  cin >> fieldNameFrom;

  ERR_CATCH(fieldIter = select_field(className, fieldNameFrom));
  if (ErrorStatus)
  {
    cout << "Error! The field you typed does not exist. Aborting...\n";
    ErrorStatus = false;
    return;
  }

  cout << "Type the name of the field you\'d like to rename TO -> ";
  cin >> fieldNameTo;

  while(Model.doesFieldExist(className, fieldNameTo))
  {
    cout << "That name is already taken.\nTry a different name. -> ";
    cin >> fieldNameTo;
  }
  
  ERR_CATCH(Model.changeAttributeName(className, fieldIter, fieldNameTo))
  if(ErrorStatus)
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
void CLI::rename_method(string className)
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
void CLI::rename_parameter(method_ptr methodIter)
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
void CLI::change_field(string className)
{
  attr_ptr fieldIter;
  string fieldName;
  string newFieldType;

  cout << "Enter the name of the field whose type you\'d like to change. -> ";
  cin >> fieldName;

  cout << "Enter the NEW type you want to give it. -> ";
  cin >> newFieldType;

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
void CLI::change_method(string className)
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
void CLI::change_parameter(string className, method_ptr methodIter)
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


/**************************************************************/
//INPUT PARSING


/**
 * @brief Takes in user input and makes sure it's
 * an unsigned int (size_t).
 * 
 * @return size_t 
 */
size_t CLI::user_int_input()
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


/*************************/


/**
 * @brief (Sprint 4) Whatever goes on in here, I figured this method could replace
 * all instances of cin (except for the ones in here, or in user_int_input).
 * 
 * If that's not how it works, feel free to delete this function. Because
 * I currently have no idea
 * 
 * @return string 
 */
string CLI::tab_completion()
{
  string input;

  cin >> input; // Don't assume that this HAS to be above the implementation, or even has to exist at all. 
  
  //TODO
  
  return input;
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
method_ptr CLI::select_method(string className, string methodName)
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
attr_ptr CLI::select_field(string className, string fieldName)
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