#include "include/UMLAttribute.hpp"
#include "include/UMLData.hpp"
#include "include/UMLFile.hpp"
#include "include/httplib/httplib.h"
#include "include/json/json.hpp"
#include "include/inja/inja.hpp"
#include "include/UMLField.hpp"
#include "include/UMLMethod.hpp"
#include <memory>
#include <string>

using json = nlohmann::json;


// Catch for functions to protect from invalid inputs
#define ERR_ADD(fun)                           \
    try {                                        \
        fun;                                     \
    }                                            \
    catch (const char* error) {                  \
        errors += error;                         \
                                                 \
    }

namespace umlserver
{
    void start (int port)
    {
        httplib::Server svr;
        UMLData data;
        json errors = json::array();
        json success = json::array();

        svr.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
            inja::Environment env;
            inja::Template temp = env.parse_template("../templates/test.html");
            json j = data.getJson();
            j["errors"] = errors;
            errors.clear();
            j["success"] = success;
            success.clear();
            j["files"] = UMLFile::listSaves();
            res.set_content(env.render(temp, j), "text/html");
        });

        svr.Get("/add/class", [&](const httplib::Request& req, httplib::Response& res) {
            std::string name = req.params.find("cname")->second;
            ERR_ADD(data.addClass(name));
            res.set_redirect("/");
         });

        svr.Get(R"(/add/field/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
            std::string fieldName = req.params.find("fname")->second;
            std::string fieldType = req.params.find("ftype")->second;
            ERR_ADD(data.addClassAttribute(className, std::make_shared<UMLField>(fieldName, fieldType)));
            res.set_redirect("/");
         }); 

         svr.Get(R"(/add/method/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
            std::string methodName = req.params.find("mname")->second;
            std::string methodType = req.params.find("mtype")->second;
            ERR_ADD(data.addClassAttribute(className, std::make_shared<UMLMethod>(methodName, methodType, std::vector<UMLParameter>{})));
            res.set_redirect("/");
         }); 

         svr.Get(R"(/add/parameter/(\w+)/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
            std::string methodName = req.matches[2].str();
            std::string paramName = req.params.find("pname")->second;
            std::string paramType = req.params.find("ptype")->second;
            std::shared_ptr<UMLAttribute> attr = data.getClassCopy(className).getAttribute(methodName);
            std::static_pointer_cast<UMLMethod>(attr)->addParam(UMLParameter(paramName, paramType));
            res.set_redirect("/");
         }); 


        svr.Get("/add/relationship", [&](const httplib::Request& req, httplib::Response& res) {
            std::string source = req.params.find("source")->second;
            std::string dest = req.params.find("dest")->second;
            std::string type = req.params.find("reltype")->second;
            ERR_ADD(data.addRelationship(source, dest, std::stoi(type)));
            res.set_redirect("/");
         });

        //source/dest
        svr.Get(R"(/delete/relationship/(\w+)/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string source = req.matches[1].str();
            std::string dest = req.matches[2].str();
            ERR_ADD(data.deleteRelationship(source, dest));
            res.set_redirect("/");
         });

        //class/attribute 
        svr.Get(R"(/delete/attribute/(\w+)/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string uclass = req.matches[1].str();
            std::string attribute = req.matches[2].str();
            ERR_ADD(data.removeClassAttribute(uclass, attribute));
            res.set_redirect("/");
         });

        svr.Get(R"(/delete/class/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string uclass = req.matches[1].str();
            ERR_ADD(data.deleteClass(uclass));
            res.set_redirect("/");
         });

        svr.Get(R"(/edit/class/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string oldClassName = req.matches[1].str();
            std::string newClassName = req.params.find("cname")->second;
            ERR_ADD(data.changeClassName(oldClassName, newClassName));
            res.set_redirect("/");
        });
        
        svr.Get(R"(/edit/attribute/(\w+)/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
            std::string oldAttributeName = req.matches[2].str();
            std::string newName = req.params.find("name")->second;
            std::string newType = req.params.find("type")->second;
            std::shared_ptr<UMLAttribute> attr = data.getClassCopy(className).getAttribute(oldAttributeName);
            attr->changeName(newName);
            attr->changeType(newType);
            res.set_redirect("/");
        });


         svr.Get("/index", [&](const httplib::Request& req, httplib::Response& res) {
            inja::Environment env;
            inja::Template temp = env.parse_template("../templates/index.html");
            json j = data.getJson();
            j["errors"] = errors;
            errors.clear();
            res.set_content(env.render(temp, j), "text/html");
        });

        svr.Get("/save", [&](const httplib::Request& req, httplib::Response& res) {
            std::string fileName = req.params.find("save")->second;
            UMLFile file (fileName + ".json");
            ERR_ADD(file.save(data));
            success += "File Saved!";
            res.set_redirect("/");
        });

        svr.Get("/load", [&](const httplib::Request& req, httplib::Response& res) {
            std::string fileName = req.params.find("load")->second;
            UMLFile file (fileName + ".json");
            ERR_ADD(data = file.load());
            success += "File Loaded!";
            res.set_redirect("/");
        });


        std::cout << "running at http:://localhost:8080/" << std::endl;

        svr.listen("localhost", port);
    }
};