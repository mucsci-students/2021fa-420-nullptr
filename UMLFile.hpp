#include <vector>
#include <string>
#include <json.hpp>
#include <fstream>
#include "UMLData.hpp"

// using json = nlohmann::json;

// class UMLFile
// {
//     public:
//         UMLFile(const std::string&);

//         //saving file
//         void addUMLClassVec(const std::vector<UMLClass>&);
//         void addUMLRelationshipVec();
//         void save();

//         //loading file
//         void load();
//         std::vector<UMLClass> getUMLClassVec();
//         void getUMLRelationshipVec();

//     private:
//         json data;
//         std::string path;
// };