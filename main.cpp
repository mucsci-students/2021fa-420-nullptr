/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include "include/CLI.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLData.hpp"
#include "server.hpp"
#include "include/CLI.hpp"
//--------------------------------------------------------------------

int main()
{ 
    umlserver::start(8080);
    CLI newInterface;
    newInterface.displayCLI();
    return 0;
};