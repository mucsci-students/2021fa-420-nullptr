#pragma once
/*
  Filename   : CLI.hpp
  Description: File which generates the command line interface
  for the user to create UML diagrams
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
#include "UMLData.hpp"
#include "UMLFile.hpp"
#include "UMLMethod.hpp"
#include "UMLField.hpp"
#include "UMLParameter.hpp"
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
 using std::list;
 using std::shared_ptr;
//-------------------------------------------------------------------

class CLI
{
  private:

    /********************/
    //Typedefs
    
    typedef shared_ptr<UMLAttribute> attr_ptr;
    typedef shared_ptr<UMLMethod> method_ptr;
    typedef unsigned int size_t;

    /********************/
    //Global variables

    UMLData Model;
    bool ErrorStatus;

    /********************/
    //Print-help functions
    
    void print_main_commands();
    void print_field_commands();
    void print_method_commands();
    void print_parameter_commands();

    /********************/
    //Adding

    void add_field(string className);
    void add_method(string className);
    bool add_parameter(method_ptr methodIter);


    /********************/
    //Deleting
    
    void delete_field(string className);
    void delete_method(string className);
    void delete_parameter(method_ptr methodIter);


    /********************/
    //Renaming
    
    void rename_field(string className);
    void rename_method(string className);
    void rename_parameter(method_ptr methodIter);

    /********************/
    //Type changing

    void change_field(string className);
    void change_method(string className);
    void change_parameter(method_ptr methodIter);

    /********************/
    //Display functions

    void display_class(UMLClass currentClass);
    void display_method(attr_ptr methodIter); 
    void display_relationship(string source, string destination, string rType);

    /********************/
    //Misc.

    size_t user_int_input();
    method_ptr select_method(string className, string methodName);
    attr_ptr select_field(string className, string fieldName);
    //Tab completion will also go here

  public:

    // Takes in user input and calls different functions based on
    // what command the user typed.
    void cli_menu();

    // Lists all classes the user has created.
    void list_classes();

    // Lists all relationships the user has created.
    void list_relationships();

    // User creates and names a class and may give it any number
    // of attributes.
    void create_class();

    // Creates a new relationship between classes.
    void create_relationship();

    // User will be prompted to type in the class name,
    // and if it exists, it will be deleted.
    void delete_class();

    // User will be prompted to type in the source and destination,
    // and if the relationship exists, it will be deleted.
    void delete_relationship();

    // User types in the current class name, and then the name
    // they'd like to change it to. Then it gets renamed.
    void rename_class();

    // User will be prompted to type in the source, destination,
    // and NEW type. Then the relationship type will be changed.
    void change_relationship();

    // Does various things with fields based on user input.
    void edit_fields();

    // Does various things with methods based on user input.
    void edit_methods();

    // Does various things with parameters based on user input.
    void edit_parameters(string className);

    // Saves the user's progress into a json file.
    void save_uml();

    // Loads a json save file, overwriting the current session.
    void load_uml();
}
    