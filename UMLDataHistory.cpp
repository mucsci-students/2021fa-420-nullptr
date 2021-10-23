/*
  Filename   : UMLDataHistory.cpp
  Description: Implementation of the caretaker for UMLDataSnapshot objects.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLDataHistory.hpp"
//--------------------------------------------------------------------

// Constructor that adds the originator to the history
UMLDataHistory::UMLDataHistory(UMLData& data)
:originator(&data) 
{   
}

// Saves snapshot in undo stack, call before changes to UMLData
void UMLDataHistory::save()
{
    undos.push(originator->make_snapshot());
}

// Restores from previous snapshot save
void UMLDataHistory::undo()
{
    if (is_undo_empty())
        return;
    redos.push(originator->make_snapshot());
    originator->restore(undos.top());
    undos.pop();
}

// Restores snapshot before last undo
void UMLDataHistory::redo()
{
    if (is_redo_empty())
        return;
    undos.push(originator->make_snapshot());
    originator->restore(redos.top());
    redos.pop();
}

// Returns true if there are no undo snapshots
bool UMLDataHistory::is_undo_empty() { 
    return undos.empty(); 
}

// Returns true if there are no redo snapshots
bool UMLDataHistory::is_redo_empty() { 
    return redos.empty(); 
}

// Returns size of undo stack
size_t UMLDataHistory::undo_size() { 
    return undos.size(); 
}

// Returns size of redo stack
size_t UMLDataHistory::redo_size() { 
    return redos.size(); 
}