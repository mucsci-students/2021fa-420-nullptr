#pragma once
/*
  Filename    : CLIView.hpp
  Author      : Matt Giacoponello
  Description : Takes in input from the user or the test queue, and passes 
                it into the CLI. Also takes information from the CLI and
                prints it out.

DESIGN PATTERNS USED:

-Command : Instead of the CLI printing and getting user input directly,
           it calls functions in this class to do it for the CLI.

-Proxy   : A derived class is created to

*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include <variant>
#include <typeinfo>

// We probably won't need these.
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
#include "UMLData.hpp"
#include "UMLDataHistory.hpp"
#include "UMLFile.hpp"
#include "UMLMethod.hpp"
#include "UMLField.hpp"
#include "UMLParameter.hpp"

//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
 using std::cin;
 using std::cout;
 using std::endl;
 using std::string;
 using std::queue;
 using std::variant;
 using std::shared_ptr;
 using std::invalid_argument;
 
 
//--------------------------------------------------------------------

//--------------------------------------------------------------------
//Typedefs

typedef long unsigned int size_t;
typedef variant<string, size_t> input_t;
//--------------------------------------------------------------------

//--------------------------------------------------------------------
//Class declarations

class CLIView
{
  private:

  void push_to_log();

    // A queue of strings and unsigned ints, which can be used 
    // instead of direct user input. (For testing purposes)
    queue<input_t> TestInputs;

    // Can be used to store the output instead of printing it out.
    queue<string> Outputs;
    
    // Keeps track of inputs and outputs in the order they are executed.
    queue<string> ioLog;

    // This bool will become false if anything is pushed to the queue. 
    bool PrintStuff = true;

  protected: // The tests can access these (through the proxy). The CLI cannot. 
    
    // Retrieves the bool associated with whether or not to print things out.
    bool get_print_bool();

    // Pushes strings and unsigned ints into the variant queue. PrintStuff 
    // also becomes false.
    void push_input(input_t testInput);

    // Prints all the outputs and inputs to the console in the correct order
    void print_log();

    // Gets the most recent item pushed into the output queue.
    string most_recent_output();

  public:
    
    // Prints to the console or pushes to the output queue.
    void display_message(string msg);
    
    // Gets input either from the user or the input queue.
    string get_user_input();

    int user_int_input();  
}

// This class will be called by Tests.cpp
class CLIViewProxy: public CLIView
{   

}