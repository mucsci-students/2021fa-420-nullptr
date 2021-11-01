#pragma once
/*
  Filename   : UMLFile.hpp
  Description: Serves as an object for which information about a class
  in the UML diagram is stored in a JSON file. 
*/

//--------------------------------------------------------------------
// System includes
#include <vector>
#include <string>
#include <fstream>

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>

#include "UMLClass.hpp"
#include "UMLData.hpp"
#include "UMLAttribute.hpp"
#include "UMLRelationship.hpp"
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using std::string;
using std::vector;
using json = nlohmann::json;
//--------------------------------------------------------------------

class UMLFile
{
    private:
        json jsonFile;
        string path;

    public:
        // Constructor: takes in the name of the file to save
        UMLFile(const string&);

        // Saves information from UML diagram to JSON
        void save(UMLData& data);

        // Loads a system file and returns a UML data object
        UMLData load();  

        // Makes a list of all JSON files in the build directory that can be used for loading.
        static json listSaves();

        // Gets the classes from the json file and adds them to the UMLData object
        static void addClasses(UMLData& data, const json& j);
        
        // Gets the relationships from the json file and adds them to the UMLData object
        static void addRelationships(UMLData& data, const json& j); 
};