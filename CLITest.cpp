/*
  Filename   : CLITest.cpp
  Description: Implementation of a CLI tester.
*/

//--------------------------------------------------------------------
// System includes
#include "include/CLITest.hpp"
//--------------------------------------------------------------------

// Extracts first prompt of the CLI
string CLITest::extract_first_prompt(const stringstream& o)
{
    auto content = o.str();
    std::size_t pos = content.find_first_of('>');
    return content.substr(0, pos);
}

// Extracts last prompt of the CLI
string CLITest::extract_last_prompt(const stringstream& o)
{
    auto content = o.str();
    std::size_t pos = content.find_last_of('\n');
    content = content.substr(pos+1);
    pos = content.find_last_of('>');
    return content.substr(0, pos);
}

/* Takes

cli> sub> foo
bar
sub> 

and gives

foo
bar

*/
string CLITest::extract_content(const stringstream& o)
{
    auto content = o.str();
    // last line
    auto lastNL = content.find_last_of('\n');
    auto lastLine = content.substr(lastNL+1);
    content = content.substr(0, lastNL);
    auto pos = content.find(lastLine);
    return content.substr(pos+lastLine.size());
}

// Function used for management of user input
void CLITest::user_input(Cli& cli, std::stringstream& oss, const string& input) 
{
    oss.str("");
    oss.clear();

    std::stringstream iss;
    iss.str(input + '\n');
    CliFileSession session(cli, iss, oss);
    session.Start();
}