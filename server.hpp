#include "UMLAttribute.hpp"
#include "UMLData.hpp"
#include "UMLFile.hpp"
#include <fstream>
#include "include/httplib/httplib.h"
#include "include/json/json.hpp"
#include "include/inja/inja.hpp"

using json = nlohmann::json;

struct Server
{
    Server (int port)
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

        std::cout << "running at http:://localhost:8080/" << std::endl;

        svr.listen("localhost", port);
    }
};