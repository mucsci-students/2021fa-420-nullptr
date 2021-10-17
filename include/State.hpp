#include "inja/inja.hpp"
#include <stack>
#include "UMLData.hpp"
#include "UMLFile.hpp"

class State 
{
    private: 
        std::stack<json> undoStack;
        std::stack<json> redoStack;
        json currentState;

    public: 
        State(UMLData& data) { currentState = data.getJson(); }
        void update(UMLData& data);
        UMLData undo();
        UMLData redo();
        size_t undo_size() { return undoStack.size(); };
        size_t redo_size() { return redoStack.size(); };
        bool is_undo_empty() { return undoStack.empty(); }
        bool is_redo_empty() { return redoStack.empty(); }
        UMLData load_current_state();
};