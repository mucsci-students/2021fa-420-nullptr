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
    UMLAttribute ratEyes("2 eyes");
    UMLAttribute ratColor("red");
    rat.addAttribute(ratEyes);
    rat.addAttribute(ratColor);
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

    data.addRelationship("tree", "cat");
    data.addRelationship("rat", "cat");

    

    std::vector<UMLRelationship> fromClass = data.getRelationshipsByClass("tree");

     for (UMLRelationship r : data.getRelationships())
    {
        std::cout << "source: " << r.getSource().getName() << " dest: " << r.getDestination().getName() << std::endl;
    }

    data.deleteClass("tree");

    data.changeClassName("cat", "cat123");

    std::cout << "after changes" << std::endl;

    for (UMLRelationship r : data.getRelationships())
    {
        std::cout << "source: " << r.getSource().getName() << " dest: " << r.getDestination().getName() << std::endl;
    }

     for (UMLClass uClass : data.getClasses())
    {
        std::cout << uClass.getName() << std::endl;
    }

    UMLFile file("save.json");
    file.save(data);
    

    return 0;
};