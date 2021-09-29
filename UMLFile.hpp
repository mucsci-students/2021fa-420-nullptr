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
#include "include/json/json.hpp"
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
        void save(const UMLData& data);

        // loads a system file and returns a UML data object
        UMLData load();  

    private:

        // takes in vector of classes and adds a json string to the jsonFile
        void addUMLClassVec(const vector<UMLClass>& umlclasses);

        // takes in vector of relationships and adds them to the jsonFile
        void addUMLRelationshipVec(const vector<UMLRelationship>& relationships);

        // gets the classes from the json file and returns classes vector
        vector<UMLClass> getUMLClassVec();
        
        // gets the relationships from the json file and adds them to the UMLData object
        void getUMLRelationshipVec(UMLData& data);
};