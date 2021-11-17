/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLCLI.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLData.hpp"
#include "include/UMLDataHistory.hpp"
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "include/UMLServer.hpp"
#include <memory>
//--------------------------------------------------------------------

int main(int argc, char** argv)
{
    // Parameter check to see if user wants CLI or GUI
    if (argc > 1) {
        if (string(argv[1]) == "--cli") {
          UMLCLI newInterface;
          newInterface.cli_menu();
      }
    } else {
      UMLServer newServer;
      newServer.start(60555);
    }   

    return 0;
};