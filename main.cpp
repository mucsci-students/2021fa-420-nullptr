/*
  Filename   : main.cpp
  Description: Main driver program that runs the routines necessary
  to run the UML editor.
*/

//--------------------------------------------------------------------
// System includes
#include "include/CLI.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLData.hpp"
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "server.hpp"
#include <memory>
//--------------------------------------------------------------------

int main(int argc, char** argv)
{

     inja::Environment env;
     inja::Template temp = env.parse_template("../templates/test.html");
     UMLData data;
     data = UMLFile("save.json").load();
     json j = data.getJson();
     j["errors"] = json::array();
     j["success"] = json::array();
     j["files"] = json::array();
     
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
                            for (int fieldID = 0; fieldID < j["classes"][classID]["fields"].size(); ++fieldID )
                            {
                                if ( j["classes"][classID]["fields"][fieldID]["name"] == attr->getAttributeName())
                                {
                                    j["classes"][classID]["fields"][fieldID]["index"] = index;
                                }
                            }
                        }
                    }
                    else if (attr->identifier() == "method") //for method, match  name and parameters
                    {

                        for (int classID = 0; classID < j["classes"].size(); ++classID)
                        {
                            for (int methodID = 0; methodID < j["classes"][classID]["methods"].size(); ++methodID )
                            {
                                //check params match as methods have same name 
                                if ( j["classes"][classID]["methods"][methodID]["name"] == attr->getAttributeName())
                                {
                                  std::vector<UMLParameter> params = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
                                  bool containsParameter = false;
                                  for (int i = 0; i < params.size(); ++i)
                                  {                  
                                    for (int k = 0; k < j["classes"][classID]["methods"][methodID]["params"].size(); ++k)
                                    {
                                        if (params[i].getType() == j["classes"][classID]["methods"][methodID]["params"][k]["type"])
                                        {
                                          containsParameter = true;
                                        }
                                    }
                                    if (!containsParameter)
                                    {
                                      break;
                                    }
                                  }

                                  if (containsParameter || (params.size() == 0 && j["classes"][classID]["methods"][methodID]["params"].size() == 0))
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

          std::cout << j << std::endl;
          int count = 0;
          for (auto attr : data.getClassAttributes("fish"))
          {
            std::cout << count << ". " <<  attr->getAttributeName() << std::endl;
            ++count;
          }



    // Parameter check to see if user wants CLI or GUI
    if (argc > 1) {
        if (string(argv[1]) == "--cli") {
          CLI newInterface;
          newInterface.displayCLI();
      }
    } else {
      umlserver::start(8080);
    }   

    return 0;
};