/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include "CLI.hpp"
#include "include/httplib/httplib.h"
//--------------------------------------------------------------------

int main()
{
   /*
    httplib::Server svr;
    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
      res.set_redirect("/hi");
    });
    svr.Get("/hi", [](const httplib::Request&, httplib::Response& res) {
      res.set_content("<h1>hello there!</h1>", "text/html");
    });

    std::cout << "running at http:://localhost:8080/" << std::endl;


    svr.listen("localhost", 8080);

    
*/
    CLI newInterface;
    newInterface.displayCLI();
    return 0;
};