/*
  Filename   : CLI.hpp
  Description: File which generates the command line interface
  for the user to create UML diagrams
*/

//--------------------------------------------------------------------
// System includes
#include <memory>
#include "include/CLIView.hpp"

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                       PUBLIC FUNCTIONS                       |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

/**
 * @brief 
 * 
 * @param msg 
 */
void CLIView::display_message(string msg)
{/*
  if (PrintStuff)
    cout << msg;
  else
    Outputs.push(msg);*/
}

/************************************/

/**
 * @brief 
 * 
 * @return string 
 */

string CLIView::get_user_input()
{/*
  
  string input;

  if(TestInputs.size() == 0)
    cin >> input;
  else
  { 
    while(Outputs.size() != 0)
    {
      ioLog.push("OUTPUT: " + Outputs.front())
      Outputs.pop()
    }
    
    if(std::holds_alternative<size_t>(TestInputs.front()))
      input = std::to_string(TestInputs.front());
    else
      input = TestInputs.front();
    
    TestInputs.pop();
    ioLog.push("INPUT: " + input);

  }
  return input;*/
  return "";
}


/************************************/

/**
 * @brief Takes in user input and makes sure it's
 * an unsigned int (size_t).
 * 
 * @return size_t 
 */
int CLIView::user_int_input()
{/*
  int num;
  if(TestInputs.size() == 0)
  {
    while(!(cin >> num))
    {
      cin.clear();
      cin.ignore(1000, '\n');
      display_message("Invalid input. Try again (input a number): ");
    }
  }
  else
  {
    if(typeid(TestInputs.front()) != size_t)
    {
      display_message("ERROR! Not an int.\n");
    }

    num = (int) TestInputs.front();
    TestInputs.pop();
  }
  return num;*/

  return 0;
}


/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                      PROTECTED FUNCTIONS                     |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/


/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool CLIView::get_print_bool()
{/*
  return PrintStuff;*/

  return false;
}


/************************************/


/**
 * @brief
 * 
 * @param testInput 
 */
void CLIView::push_input(input_t testInput)
{/*
  PrintStuff = false;
  TestInputs.push(testInput);*/
}


/************************************/


void CLIView::print_log()
{/*
  while(ioLog.size() != 0)
  {  
    cout << ioLog.front();
    ioLog.pop();
  }*/
}


/************************************/


string CLIView::most_recent_output()
{/*
  if(Outputs.size() == 0)
    return "";
  else
    return Outputs.front();*/

  return "";
}