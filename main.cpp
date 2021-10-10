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
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "server.hpp"
#include <memory>
//--------------------------------------------------------------------

int main(int argc, char** argv)
{

     inja::Environment env;
     inja::Template temp = env.parse_template("../templates/test.html");
     UMLData data;
     data = UMLFile("save.json").load();
     json j = data.getJson();
     j["errors"] = json::array();
     j["success"] = json::array();
     j["files"] = json::array();
     
    

          std::cout << j << std::endl;
          int count = 0;
          for (auto attr : data.getClassAttributes("fish"))
          {
            std::cout << count << ". " <<  attr->getAttributeName() << std::endl;
            ++count;
          }



    // Parameter check to see if user wants CLI or GUI
    if (argc > 1) {
        if (string(argv[1]) == "--cli") {
          CLI newInterface;
          newInterface.displayCLI();
      }
    } else {
      umlserver::start(8080);
    }   

    return 0;
};