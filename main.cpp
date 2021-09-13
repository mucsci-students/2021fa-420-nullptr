/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include <string>
#include <iostream>
#include "UMLFile.hpp"
#include <vector>
#include "UMLClass.hpp"
#include "UMLData.hpp"

int main()
{

    //testing UMLDATA 
    
    UMLData data;
    UMLClass test("test");
    UMLClass woof("woof");
    UMLClass bird("bird");
    UMLClass cat("cat");
    UMLClass rat("rat");
    data.addClass(test);
    data.addClass(woof);
    data.addClass(bird);
    data.addClass(cat);
    data.addClass(rat);
    data.addClass("tree");

    for (UMLClass uClass : data.getClasses())
    {
        std::cout << uClass.getName() << std::endl;
    }

    data.addRelationship("cat", "rat");

    data.addRelationship("bird", "cat");

    for (UMLRelationship r : data.getRelationships())
    {
        std::cout << "source: " << r.getSource().getName() << " dest: " << r.getDestination().getName() << std::endl;
    }
    data.deleteRelationship("bird", "cat");

   for (UMLRelationship r : data.getRelationships())
    {
        std::cout << "source: " << r.getSource().getName() << " dest: " << r.getDestination().getName() << std::endl;
    }

    return 0;
};