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
    struct screenPos
    {
      int zoomLevel = 1;
      int x = 0;
      int y = 0;
    };

    // Controller management for the GUI
    void start (int port);
    
    // Attribute index management
    void addAttributeIndexes (json& j, const UMLData& data);
};