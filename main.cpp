/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include "include/CLI.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLData.hpp"
#include "include/UMLDataHistory.hpp"
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "server.hpp"
#include <memory>
//--------------------------------------------------------------------

int main(int argc, char** argv)
{
    // UMLData data;
    // UMLDataHistory history(data);
    // history.save();
    // data.addClass("fish2");
    // history.save();
    // data.addClass("test");
    // history.save();
    // data.addRelationship("fish2", "test", 0);
    // history.save();
    // data.deleteClass("test");
    // std::cout << data.getJson();
    // std::cout << "deleted" << std::endl;
    // history.undo();
    // std::cout << "undo";
    // std::cout << data.getJson();

    // Parameter check to see if user wants CLI or GUI
    if (argc > 1) {
        if (string(argv[1]) == "--cli") {
          CLI newInterface;
          newInterface.cli_menu();
      }
    } else {
      umlserver::start(8080);
    }   

    return 0;
};