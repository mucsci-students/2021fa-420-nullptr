#include <iostream>
#include <string>
#include "UMLFile.hpp"
#include <vector>

int main()
{
    std::cout << "Hello world." << std::endl;

    UMLFile file("save.json");
    file.load();  
    std::vector<UMLClass> gg = file.getUMLClassVec();

    return 0;
};