#pragma once
/*
  Filename   : UMLServer.hpp
  Description: Controller for the GUI.
*/

//--------------------------------------------------------------------
// System includes
#include "UMLData.hpp"
#include <nlohmann/json.hpp>
//--------------------------------------------------------------------

//--------------------------------------------------------------------
// Using declarations
using json = nlohmann::json;
//--------------------------------------------------------------------


class UMLServer
{
  private:

    // No private methods

  public:
    //holds screen position for gui

    // Controller management for the GUI
    void start (int port);
    
    // Attribute index management
    void addAttributeIndexes (json& j, const UMLData& data);

    UMLData load_json(json j);
};