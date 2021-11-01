/*
  Filename   : UMLDataHistory.cpp
  Description: Implementation of the caretaker for UMLDataSnapshot objects.
*/

//--------------------------------------------------------------------
// System includes
#include "include/UMLDataHistory.hpp"
#include "include/UMLFile.hpp"
//--------------------------------------------------------------------

// Constructor that adds the originator to the history
UMLDataHistory::UMLDataHistory(UMLData& data)
{ 
    current = data.getJson();
}

// Saves snapshot in undo stack, call before changes to UMLData
void UMLDataHistory::save(UMLData& data)
{
    if (data.getJson() == current)
        return;
    undos.push(current);
    current = data.getJson();
}

// Returns from previous snapshot save
UMLData UMLDataHistory::undo()
{
    if (!is_undo_empty())
    {
        redos.push(current);
        current = undos.top();
        undos.pop();
    }

    return load_current();
}

// Returns snapshot before last undo
UMLData UMLDataHistory::redo()
{
    if (!is_redo_empty())
    {
        undos.push(current);
        current = redos.top();
        redos.pop();
    }

    return load_current();
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

UMLData UMLDataHistory::load_current()
{
    UMLData data;
    UMLFile::addClasses(data, current);
    UMLFile::addRelationships(data , current);

    return data;
}