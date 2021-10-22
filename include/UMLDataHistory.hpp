/*
  Filename   : UMLDataHistory.hpp
  Description: Serves as caretaker for UMLDataSnapshot objects, when undo or redo is called
  restores UMLData with previous state
  in the UML diagram is stored in a JSON file. 
*/

#pragma once
#include "httplib/httplib.h"
#include "inja/inja.hpp"
#include <stack>
#include "UMLData.hpp"
#include "UMLFile.hpp"

class UMLDataHistory 
{
    private: 
        UMLData* originator = nullptr;
        std::stack<UMLDataSnapshot> undos;
        std::stack<UMLDataSnapshot> redos;

    public: 
        //adds the originator to the history
        UMLDataHistory(UMLData& data);
        //saves snapshot in undo stack, call before changes to UMLData
        void save();

        //restores from previous snapshot save
        void undo();

        //restores snapshot before last undo
        void redo();

        //returns true if there are no undo snapshots
        bool is_undo_empty();

        //returns true if there are no redo snapshots
        bool is_redo_empty();

        //returns size of undo stack
        size_t undo_size();

        //returns size of redo stack
        size_t redo_size();
};