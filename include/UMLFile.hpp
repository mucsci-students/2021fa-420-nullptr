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
#include "json/json.hpp"
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
        // constructor: takes in the name of the file to save
        UMLFile(const string&);

        // saving file
        void save(UMLData& data);

        // loads a system file and returns a UML data object
        UMLData load();  

        static json listSaves();


    private:
         // gets the classes from the json file and adds them to the UMLData object
        vector<UMLClass> getUMLClassVec();
        void addClasses(UMLData& data, const json& j);
         // gets the relationships from the json file and adds them to the UMLData object
        void addRelationships(UMLData& data, const json& j);
        

        
       
};