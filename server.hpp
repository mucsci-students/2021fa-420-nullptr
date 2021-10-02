#include "UMLAttribute.hpp"
#include "UMLData.hpp"
#include "UMLFile.hpp"
#include <fstream>
#include "include/httplib/httplib.h"
#include "include/json/json.hpp"
#include "include/inja/inja.hpp"

using json = nlohmann::json;

namespace umlserver
{
    void start (int port)
    {
        httplib::Server svr;
        UMLData data;

        svr.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
            inja::Environment env;
            inja::Template temp = env.parse_template("../templates/test.html");
            res.set_content(env.render(temp, data.getJson()), "text/html");
        });

        svr.Get(R"(/hi/(\w+)/(\w+))", [](const httplib::Request& req, httplib::Response& res) {
            std::string a = req.matches[1].str();
            std::string b = req.matches[2].str();
            auto c = req.params.find("hello")->second;
            res.set_content(c, "text/plain");
         });

        svr.Get("/add/class", [&](const httplib::Request& req, httplib::Response& res) {
            std::string name = req.params.find("cname")->second;
            data.addClass(name);
            res.set_redirect("/");
         });

        svr.Get(R"(/add/attribute/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
            std::string attributeName = req.params.find("aname")->second;
            UMLAttribute attribute (attributeName);
            data.addClassAttribute(className, attribute);
            res.set_redirect("/");
         }); 

        svr.Get("/add/relationship", [&](const httplib::Request& req, httplib::Response& res) {
            std::string source = req.params.find("source")->second;
            std::string dest = req.params.find("dest")->second;
            data.addRelationship(source, dest);
            res.set_redirect("/");
         });

        //source/dest
        svr.Get(R"(/delete/relationship/(\w+)/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string source = req.matches[1].str();
            std::string dest = req.matches[2].str();
            data.deleteRelationship(source, dest);
            res.set_redirect("/");
         });

        //class/attribute 
        svr.Get(R"(/delete/attribute/(\w+)/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string uclass = req.matches[1].str();
            std::string attribute = req.matches[2].str();
            data.removeClassAttribute(uclass, attribute);
            res.set_redirect("/");
         });

        svr.Get(R"(/delete/class/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
            std::string uclass = req.matches[1].str();
            data.deleteClass(uclass);
            res.set_redirect("/");
         });

        svr.Get(R"(/edit/class/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
        std::string oldClassName = req.matches[1].str();
        std::string newClassName = req.params.find("cname")->second;
        data.changeClassName(oldClassName, newClassName);
        res.set_redirect("/");
        });


        std::cout << "running at http:://localhost:8080/" << std::endl;

        svr.listen("localhost", port);
    }
};