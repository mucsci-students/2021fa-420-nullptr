#include "include/State.hpp"

void State::update(UMLData& data)
{
    json newState = data.getJson();
    if (newState != currentState)
    {
        undoStack.push(currentState);
        currentState = newState;
    }
}

UMLData State::undo()
{
    if (!is_undo_empty())
    {
        redoStack.push(currentState);
        currentState = undoStack.top();
        undoStack.pop();
    }
    return load_current_state();
}

UMLData State::redo()
{
    if (!is_redo_empty())
    {
        undoStack.push(currentState);
        currentState = redoStack.top();
        redoStack.pop();
    }
    return load_current_state();
}

UMLData State::load_current_state()
{
    UMLData data;
    UMLFile::addClasses(data, currentState);
    UMLFile::addRelationships(data, currentState);
    return data;
}