/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include "umllib/include/UMLCLI.hpp"
#include "umllib/include/UMLAttribute.hpp"
#include "umllib/include/UMLClass.hpp"
#include "umllib/include/UMLData.hpp"
#include "umllib/include/UMLDataHistory.hpp"
#include "umllib/include/UMLMethod.hpp"
#include "umllib/include/UMLParameter.hpp"
#include "umllib/include/UMLServer.hpp"
#include <memory>
//--------------------------------------------------------------------

int main(int argc, char** argv)
{
    // Parameter check to see if user wants CLI or GUI
    if (argc > 1) {
        if (string(argv[1]) == "--cli") {
          UMLCLI newInterface;
          newInterface.start();
      }
    } else {
      UMLServer newServer;
      newServer.start(60555);
    }   

    return 0;
};