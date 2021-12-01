#pragma once
/*
  Filename   : CLITest.hpp
  Description: File that contains functions that can be used in
  order to test a given CLI.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include "cli/cli.h"
#include "cli/clifilesession.h"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::stringstream;
using namespace std;
using namespace cli;
//--------------------------------------------------------------------

class CLITest 
{
  private:
    // No private methods 
  
  public:
    /* Takes

    cli> sub> foo
    bar
    sub> 

    and gives

    foo
    bar

    */
    string extract_content(const stringstream& o);

    // Function used for management of user input
    void user_input(Cli& cli, std::stringstream& oss, const string& input);
};