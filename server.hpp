#include "include/UMLAttribute.hpp"
#include "include/UMLData.hpp"
#include "include/httplib/httplib.h"
#include "include/json/json.hpp"
#include "include/inja/inja.hpp"
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

        svr.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
            inja::Environment env;
            inja::Template temp = env.parse_template("../templates/test.html");
            json j = data.getJson();
            j["errors"] = errors;
            errors.clear();
            res.set_content(env.render(temp, j), "text/html");
        });

        svr.Get("/add/class", [&](const httplib::Request& req, httplib::Response& res) {
            std::string name = req.params.find("cname")->second;
            ERR_ADD(data.addClass(name));
            res.set_redirect("/");
         });

        svr.Get(R"(/add/attribute/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
            std::string attributeName = req.params.find("aname")->second;
            UMLAttribute attribute (attributeName);
            ERR_ADD(data.addClassAttribute(className, attribute));
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
            std::string newAttributeName = req.params.find("aname")->second;
            ERR_ADD(data.changeAttributeName(className, oldAttributeName, newAttributeName));
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


        std::cout << "running at http:://localhost:8080/" << std::endl;

        svr.listen("localhost", port);
    }
};