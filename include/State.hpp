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
        //creates a state object, takes in a UMLdata object, and creates the 'start state
        State(UMLData& data) { currentState = data.getJson(); }

        //updates the state with the current state and stores the previous state
        void update(UMLData& data);

        //pulls the previous update and loads a new UMLData object from the state
        UMLData undo();

        //pulls the most recent redo state and loads a new UMLData object from the state
        UMLData redo();

        //returns size of undo stack
        size_t undo_size() { return undoStack.size(); };

        //returns size of redo stack
        size_t redo_size() { return redoStack.size(); };

        //**use these to determine if undo or redo should be called**
        //returns false if there are undo states available to go back to
        //returns true if there are no undo states
        bool is_undo_empty() { return undoStack.empty(); }

        //returns false if there are redo states available to go forward to
        //returns true if there are no redo states
        bool is_redo_empty() { return redoStack.empty(); }

        //loads the json in current_state and returns a UMLData object
        UMLData load_current_state();
};