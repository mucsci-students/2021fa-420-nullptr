#pragma once
/*
  Filename   : UMLDataHistory.hpp
  Description: Serves as caretaker for UMLDataSnapshot objects.
  When undo or redo is called, this is used to restore UMLData 
  to its previous state.
*/

//--------------------------------------------------------------------
#include "httplib/httplib.h"
#include "inja/inja.hpp"
#include <stack>
#include "UMLData.hpp"
#include "UMLFile.hpp"
//--------------------------------------------------------------------

class UMLDataHistory 
{
    private: 
        UMLData* originator = nullptr;
        std::stack<UMLDataSnapshot> undos;
        std::stack<UMLDataSnapshot> redos;

    public: 
        // Constructor that adds the originator to the history
        UMLDataHistory(UMLData& data);
        
        // Saves snapshot in undo stack, call before changes to UMLData
        void save();

        // Restores from previous snapshot save
        void undo();

        // Restores snapshot before last undo
        void redo();

        // Returns true if there are no undo snapshots
        bool is_undo_empty();

        // Returns true if there are no redo snapshots
        bool is_redo_empty();

        // Returns size of undo stack
        size_t undo_size();

        // Returns size of redo stack
        size_t redo_size();
};