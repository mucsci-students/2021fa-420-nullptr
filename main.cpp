/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include "CLI.hpp"
#include "UMLAttribute.hpp"
#include "UMLData.hpp"
#include "server.hpp"
#include "include/json/json.hpp"
#include <filesystem>

using json = nlohmann::json;
//--------------------------------------------------------------------

int main()
{ 
    umlserver::start(8080);
    CLI newInterface;
    newInterface.displayCLI();
    return 0;
};