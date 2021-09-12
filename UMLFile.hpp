#include <vector>
#include <string>
#include <json.hpp>
#include <fstream>

using json = nlohmann::json;

struct UMLAttribute
{
    std::string name;
};

struct UMLClass
{
    std::string name;
    std::vector<UMLAttribute> attributes;
};

class UMLFile
{
    public:
        UMLFile(const std::string&);

        //saving file
        void addUMLClassVec(const std::vector<UMLClass>&);
        void addUMLRelationshipVec();
        void save();

        //loading file
        void load();
        std::vector<UMLClass> getUMLClassVec();
        void getUMLRelationshipVec();

    private:
        json data;
        std::string path;
};