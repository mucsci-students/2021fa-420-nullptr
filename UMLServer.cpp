/*
  Filename   : UMLServer.cpp
  Description: Implementation of a GUI controller/server.
*/

#include <memory>
#include <string>

#include "UMLAttribute.hpp"
#include "UMLData.hpp"
#include "UMLDataHistory.hpp"
#include "UMLField.hpp"
#include "UMLFile.hpp"
#include "UMLMethod.hpp"
#include "include/UMLServer.hpp"

#include <httplib.h>
#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Catch for functions to protect from invalid inputs
#define ERR_ADD(fun)                      \
  try                                     \
  {                                       \
    fun;                                  \
    history.save (data);                  \
  }                                       \
  catch (const std::runtime_error& error) \
  {                                       \
    errors += error.what();               \
  }                                       \

// Controller management for the GUI
void UMLServer::start (int port)
{
  httplib::Server svr;
  svr.set_mount_point ("/", "../static");
  UMLData data;
  UMLDataHistory history (data);
  json errors = json::array();
  json success = json::array();

  svr.Get ("/", [&] (const httplib::Request& req, httplib::Response& res) {
    inja::Environment env;
    inja::Template temp = env.parse_template ("../templates/index.html");
    json j = data.getJson();
    //for each for all the attributes in each class add the index number to the json object
    addAttributeIndexes (j, data);
    j["errors"] = errors;
    errors.clear();
    j["success"] = success;
    success.clear();
    j["files"] = UMLFile::listSaves();
    res.set_content (env.render (temp, j), "text/html");
  });

  svr.Get ("/add/class",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string name = req.params.find ("cname")->second;
            ERR_ADD (data.addClass (name));
            res.set_redirect ("/");
          });

  svr.Get (R"(/add/field/(\w+))",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
            std::string fieldName = req.params.find ("fname")->second;
            std::string fieldType = req.params.find ("ftype")->second;
            ERR_ADD (data.addClassAttribute (
              className, std::make_shared<UMLField> (fieldName, fieldType)));
            res.set_redirect ("/");
          });

  svr.Get (R"(/add/method/(\w+))", [&] (const httplib::Request& req,
                                        httplib::Response& res) {
    std::string className = req.matches[1].str();
    std::string methodName = req.params.find ("mname")->second;
    std::string methodType = req.params.find ("mtype")->second;
    ERR_ADD (data.addClassAttribute (
      className, std::make_shared<UMLMethod> (methodName, methodType,
                                              std::list<UMLParameter>{})));
    res.set_redirect ("/");
  });

  svr.Get (R"(/add/parameter/(\w+)/(\d+))", [&] (const httplib::Request& req,
                                                httplib::Response& res) {
    std::string className = req.matches[1].str();
    int methodIndex = std::stoi (req.matches[2].str());
    std::string paramName = req.params.find ("pname")->second;
    std::string paramType = req.params.find ("ptype")->second;

    auto attr = data.getClassCopy (className).getAttributes()[methodIndex];
    ERR_ADD (data.addParameter (std::static_pointer_cast<UMLMethod> (attr),
                                paramName, paramType));
    res.set_redirect ("/");
  });
  //delete/parameter/classname/methodindex/paramname
  svr.Get (R"(/delete/parameter/(\w+)/(\d+)/(\w+))",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
            int methodIndex = std::stoi (req.matches[2].str());
            std::string paramName = req.matches[3].str();

            auto attr =
              data.getClassCopy (className).getAttributes()[methodIndex];
            ERR_ADD (data.deleteParameter (
              std::static_pointer_cast<UMLMethod> (attr), paramName));
            res.set_redirect ("/");
          });

  //edit/parameter/classname/methodINDEX/parametername/
  svr.Get (
    R"(/edit/parameter/(\w+)/(\d+)/(\w+))",
    [&] (const httplib::Request& req, httplib::Response& res) {
      std::string className = req.matches[1].str();
      
      int methodIndex = std::stoi (req.matches[2].str());
      std::string oldParamName = req.matches[3].str();

      std::string newParamName = req.params.find ("pname")->second;
      std::string newParamType = req.params.find ("ptype")->second;

      auto attr = data.getClassCopy (className).getAttributes()[methodIndex];
      ERR_ADD (data.deleteParameter (std::static_pointer_cast<UMLMethod> (attr),
                                    oldParamName));
      ERR_ADD (data.addParameter (std::static_pointer_cast<UMLMethod> (attr),
                                  newParamName, newParamType));
      res.set_redirect ("/");
    });

  svr.Get ("/add/relationship",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string source = req.params.find ("source")->second;
            std::string dest = req.params.find ("dest")->second;
            std::string type = req.params.find ("reltype")->second;
            ERR_ADD (data.addRelationship (source, dest, std::stoi (type)));
            res.set_redirect ("/");
          });
  //edit/relationship/source/dest
  svr.Get (R"(/edit/relationship/(\w+)/(\w+))",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string source = req.matches[1].str();
            std::string dest = req.matches[2].str();
            std::string type = req.params.find ("reltype")->second;
            ERR_ADD (
              data.changeRelationshipType (source, dest, std::stoi (type)));
            res.set_redirect ("/");
          });

  //source/dest
  svr.Get (R"(/delete/relationship/(\w+)/(\w+))",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string source = req.matches[1].str();
            std::string dest = req.matches[2].str();
            ERR_ADD (data.deleteRelationship (source, dest));
            res.set_redirect ("/");
          });

  //class/attribute
  svr.Get (R"(/delete/attribute/(\w+)/(\w+))",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string uclass = req.matches[1].str();
            std::string attribute = req.matches[2].str();
            
            ERR_ADD (data.removeClassAttribute (uclass, attribute));
            res.set_redirect ("/");
          });

  svr.Get (R"(/delete/class/(\w+))",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string uclass = req.matches[1].str();
            ERR_ADD (data.deleteClass (uclass));
            res.set_redirect ("/");
          });

  svr.Get (R"(/edit/class/(\w+))",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string oldClassName = req.matches[1].str();
            std::string newClassName = req.params.find ("cname")->second;
            ERR_ADD (data.changeClassName (oldClassName, newClassName));
            res.set_redirect ("/");
          });

  //edit/attribute/classname/(method/field INDEX)
  svr.Get (R"(/edit/attribute/(\w+)/(\d+))", [&] (const httplib::Request& req,
                                                  httplib::Response& res) {
    std::string className = req.matches[1].str();
    int attrIndex = std::stoi (req.matches[2].str());
    std::string newName = req.params.find ("name")->second;
    std::string newType = req.params.find ("type")->second;
    auto attr = data.getClassCopy (className).getAttributes()[attrIndex];
    ERR_ADD (data.changeAttributeType (attr, newType));
    ERR_ADD (data.changeAttributeName (className, attr, newName));
    res.set_redirect ("/");
  });

  svr.Get ("/index", [&] (const httplib::Request& req, httplib::Response& res) {
    inja::Environment env;
    inja::Template temp = env.parse_template ("../templates/index.html");
    json j = data.getJson();
    j["errors"] = errors;
    errors.clear();
    res.set_content (env.render (temp, j), "text/html");
  });
  svr.Get ("/help", [&] (const httplib::Request& req, httplib::Response& res) {
    inja::Environment env;
    inja::Template temp = env.parse_template ("../helpGUI.html");
    json j = data.getJson();
    j["errors"] = errors;
    errors.clear();
    res.set_content (env.render (temp, j), "text/html");
  });

  svr.Get ("/save", [&] (const httplib::Request& req, httplib::Response& res) {
    std::string fileName = req.params.find ("save")->second;
    UMLFile file (fileName + ".json");
    ERR_ADD (file.save (data));
    success += "File Saved!";
    res.set_redirect ("/");
  });

  svr.Get ("/load", [&] (const httplib::Request& req, httplib::Response& res) {
    std::string fileName = req.params.find ("load")->second;
    UMLFile file (fileName + ".json");
    ERR_ADD (data = file.load());
    success += "File Loaded!";
    res.set_redirect ("/");
  });

  svr.Get ("/undo", [&] (const httplib::Request& req, httplib::Response& res) {
    data = history.undo();
    res.set_redirect ("/");
  });

  svr.Get ("/redo", [&] (const httplib::Request& req, httplib::Response& res) {
    data = history.redo();
    res.set_redirect ("/");
  });

  ///position/className/x/y
  svr.Get (R"(/position/(\w+)/(\d+)/(\d+))",
          [&] (const httplib::Request& req, httplib::Response& res) {
            std::string className = req.matches[1].str();
           
            int x = std::stoi (req.matches[2].str());
            int y = std::stoi (req.matches[3].str());
          
          
            data.getClass (className).setX (x);
            data.getClass (className).setY (y);
            history.save (data);
            res.set_redirect ("/");
          });

  

  std::cout << "running at http:://localhost:60555/" << std::endl;

  svr.listen ("localhost", port);
}

// Attribute index management
void UMLServer::addAttributeIndexes (json& j, const UMLData& data)
{
  for (auto uclass : data.getClasses())
  {
    int index = 0;
    //assign vector element id for each attribute
    for (auto attr : uclass.getAttributes())
    {
      //for field, match the name
      if (attr->identifier() == "field")
      {
        for (int classID = 0; classID < j["classes"].size(); ++classID)
        {
          for (int fieldID = 0;
              fieldID < j["classes"][classID]["fields"].size(); ++fieldID)
          {
            if (j["classes"][classID]["fields"][fieldID]["name"] ==
                attr->getAttributeName())
            {
              j["classes"][classID]["fields"][fieldID]["index"] = index;
            }
          }
        }
      }
      else if (attr->identifier() ==
              "method") //for method, match  name and parameters
      {

        for (int classID = 0; classID < j["classes"].size(); ++classID)
        {
          for (int methodID = 0;
              methodID < j["classes"][classID]["methods"].size(); ++methodID)
          {
            //check params match as methods have same name
            if (j["classes"][classID]["methods"][methodID]["name"] ==
                attr->getAttributeName())
            {
              std::list<UMLParameter> params =
                std::dynamic_pointer_cast<UMLMethod> (attr)->getParam();
              bool containsParameter = false;
              for (auto param : params)
              {
                for (int k = 0;
                    k < j["classes"][classID]["methods"][methodID]["params"]
                          .size();
                    ++k)
                {
                  if (param.getType() == j["classes"][classID]["methods"]
                                          [methodID]["params"][k]["type"])
                  {
                    containsParameter = true;
                  }
                }
                if (!containsParameter)
                {
                  break;
                }
              }

              if (containsParameter ||
                  (params.size() == 0 &&
                  j["classes"][classID]["methods"][methodID]["params"]
                      .size() == 0))
              {
                j["classes"][classID]["methods"][methodID]["index"] = index;
              }
            }
          }
        }
      }
      ++index;
    }
  }
}
