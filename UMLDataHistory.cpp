#include "include/UMLDataHistory.hpp"

UMLDataHistory::UMLDataHistory(UMLData& data) { originator = &data; }

void UMLDataHistory::save()
{
    undos.push(originator->make_snapshot());
}

void UMLDataHistory::undo()
{
    if (is_undo_empty())
        return;
    redos.push(originator->make_snapshot());
    originator->restore(undos.top());
    undos.pop();
}

void UMLDataHistory::redo()
{
    if (is_redo_empty())
        return;
    undos.push(originator->make_snapshot());
    originator->restore(redos.top());
    redos.pop();
}

bool UMLDataHistory::is_undo_empty() { return undos.empty(); }

bool UMLDataHistory::is_redo_empty() { return redos.empty(); }

size_t UMLDataHistory::undo_size() { return undos.size(); };

size_t UMLDataHistory::redo_size() { return redos.size(); };