/*
Authors: Tyler York(pilot), Briar Sauble(copilot)
Date: 9/9/2021
Description: Implementing a UML class template.
*/

//--------------------------------------------------------------------
// System Includes
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <iterator>
#include <stdexcept>
//--------------------------------------------------------------------
// Using Declarations
 using std::cin;
 using std::cout;
 using std::endl;
 using std::string;
 using std::vector;
 using std::list;
 using std::invalid_argument;

//--------------------------------------------------------------------
// Useful code snippets
/*
  vector:    vector<int> g1;
 
  Pushing back into vector:    
  for (int i = 1; i <= 5; i++)
        g1.push_back(i);

*/
 //vector<string> classContainer;
 //vector<string> attributes;
class UMLClass{


    private:
/*
vector<UMLAttribute> classAttributes;
vector<UMLRelationship> classRelationships;
*/
        String className;
        vector<UMLAttribute> classAttributes;
        
       

    public:
// Constructor for class objects
      UMLClass(String  newClass){

        className = newClass;

      }

      String getName(){
        return className;
      }

      void changeName(String newClassName){
          className = newClassName;
      }

      void addAttribute( UMLAttribute attribute){
        classAttributes.push_back(attribute);
      }

      vector<UMLattribute> getAttributes(){
        return classAttributes;
      }
      void deleteAttribute(UMLAttribute attribute){
        try{
            for (vector<UMLAtribute>::iterator ptr = classAttributes.begin(); ptr != classAttributes.end(); ++ptr){
           
             if(ptr->getname() == attribute.getName()){
             ptr->delete();
             classAttribute.erase(ptr);
             }
                else{
                throw ptr->getName();
                }
            }
        }

        catch (String attributeName) {
           cout<<attributeName << " is not a valid attribute in this class!" << endl;
        }



      }





try {
  // Block of code to try
  throw exception; // Throw an exception when a problem arise
}
catch () {
  // Block of code to handle errors
}

}
 
