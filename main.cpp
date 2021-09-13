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
#include <stdexcept>
#include "UMLClass.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
//--------------------------------------------------------------------

int main ()
{
    std::cout << "Hello world." << std::endl;

    UMLClass newClass("test");
    newClass.addAttribute(UMLAttribute("swag"));
    std::cout << "Attribute name: " << newClass.findAttribute("swag")->getAttributeName() << std::endl;
    std::cout << "Vector size before deleting swag: " << newClass.getAttributes().size() << std::endl;
    newClass.deleteAttribute("swag");
    std::cout << "Vector size after deleting swag: " << newClass.getAttributes().size() << std::endl;
    return 0;
}