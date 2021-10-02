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

using json = nlohmann::json;
//--------------------------------------------------------------------

int main()
{ 
    // UMLData data;
    // data.addClass("test");
    // std::cout << data.getJson() << std::endl;
    // inja::Environment env;
    // inja::Template temp = env.parse_template("../templates/test.html");
    // env.render(temp, data.getJson());
    umlserver::start(8080);
    CLI newInterface;
    newInterface.displayCLI();
    return 0;
};