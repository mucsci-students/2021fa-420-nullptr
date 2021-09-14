/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include <iostream>
#include <vector>
#include "UMLClass.hpp"
#include "UMLFile.hpp"
#include "UMLData.hpp"
#include "CLI.hpp"
//--------------------------------------------------------------------

int main()
{
    CLI newInterface;
    newInterface.displayCLI();
    return 0;
};