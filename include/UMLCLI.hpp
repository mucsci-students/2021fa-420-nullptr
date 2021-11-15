#pragma once
/*
  Filename   : UMLCLI.hpp
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
#include "UMLDataHistory.hpp"
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
 using std::map;
//--------------------------------------------------------------------

/********************/
//Typedefs

typedef shared_ptr<UMLAttribute> attr_ptr;
typedef shared_ptr<UMLMethod> method_ptr;
typedef long unsigned int size_t;

class UMLCLI
{
  private:
    
    /********************/
    //Global variables

    // Error check to prevent 'success' print 
    bool ErrorStatus;

    // Main UML data object storing UML stuff
    UMLData Model;

    // Allows for undo/redo
    UMLDataHistory History {Model};

    /********************/
    //Adding

    bool add_field(string className, string fieldName, string fieldType);
    bool add_method(string className);
    bool add_parameter(string className, method_ptr methodIter);


    /********************/
    //Deleting
    
    void delete_field(string className, string fieldName);
    void delete_method(string className);
    void delete_parameter(string className, method_ptr methodIter);


    /********************/
    //Renaming
    
    void rename_field(string className, string fieldNameFrom, string fieldNameTo);
    void rename_method(string className);
    void rename_parameter(method_ptr methodIter);

    /********************/
    //Type changing

    void change_field(string className, string fieldName, string newFieldType);
    void change_method(string className);
    void change_parameter(string className, method_ptr methodIter);

    /********************/
    //Display functions

    void display_class(UMLClass currentClass);
    void display_method(attr_ptr methodIter); 
    void display_relationship(string source, string destination, string rType);
    
    /********************/
    //Input parsing

    size_t user_int_input();
    string tab_completion();


    /********************/
    //Undo/Redo

    void undo();
    void redo();

    /********************/
    //Misc.

    method_ptr select_method(string className, string methodName);
    attr_ptr select_field(string className, string fieldName);

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
    void create_class(string className);

    // Creates a new relationship between classes.
    void create_relationship(string source, string destination, string relshipType);

    // User will be prompted to type in the class name,
    // and if it exists, it will be deleted.
    void delete_class(string className);

    // User will be prompted to type in the source and destination,
    // and if the relationship exists, it will be deleted.
    void delete_relationship(string source, string destination);

    // User types in the current class name, and then the name
    // they'd like to change it to. Then it gets renamed.
    void rename_class(string oldClassName, string newClassName);

    // User will be prompted to type in the source, destination,
    // and NEW type. Then the relationship type will be changed.
    void change_relationship(string source, string destination, string relshipType);

    // Saves the user's progress into a json file.
    void save_uml(string fileName);

    // Loads a json save file, overwriting the current session.
    void load_uml(string fileName);
   
};