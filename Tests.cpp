#include <gtest/gtest.h>
#include "UMLData.hpp"
#include "CLI.hpp"
#include "UMLRelationship.hpp"
#include "UMLClass.hpp"
#include <string>
#include <iostream>

// TEST(TestSuiteName, TestName) {
//   ... test body ...
// }

//Tests for UMLData.hpp
TEST(UMLDataAddClassTest, AddClassAndGetCopy) {
    UMLData data;
    data.addClass("test");
    ASSERT_EQ("test", data.getClassCopy("test").getName());
}

TEST(UMLDataAddClassTest, AddClassThatAlreadyExists) {
    UMLData data;
    data.addClass("test");
    ASSERT_ANY_THROW(data.addClass("test"));
}

TEST(UMLDataRemoveClassTest, RemoveClassThatDoesntExist) {
    UMLData data;
    ASSERT_ANY_THROW(data.deleteClass("test"));
}

TEST(UMLDataRenameClassTest, RenameAClassWorks) {
    UMLData data;
    string oldName;
    string updatedName;
    oldName = "test";
    updatedName = "testtest";
    data.addClass(oldName);
    data.changeClassName(oldName, updatedName);
    ASSERT_EQ(updatedName, updatedName);
}

TEST(UMLDataRenameClassTest, RenameClassIntoClassThatAlreadyExists) {
    UMLData data;
    data.addClass("test");
    ASSERT_ANY_THROW(data.changeClassName("test", "test"));
}

TEST(UMLDataAttributeTest, AddAttributeWorks) {
    UMLData data;
    data.addClass("test");
    UMLAttribute attribute("hastest");
    data.addClassAttribute("test", attribute);
       for (UMLAttribute attr : data.getClassAttributes("test")) {
           if(attr.getAttributeName() == "hastest"){
               ASSERT_EQ(attr.getAttributeName(), "hastest");
           }
       }
}

TEST(UMLDataAttributeTest, ChangeAttributeNameWorks) {
   
    bool hasTestGone;
    hasTestGone == true;
    bool newHasTestPresent;
    newHasTestPresent == false;

    UMLData data;
    data.addClass("test");
    UMLAttribute attribute("hastest");
    data.addClassAttribute("test", attribute);
    data.changeAttributeName("test", "hastest", "newHasTest");

        for (UMLAttribute attr : data.getClassAttributes("test")) {
           if(attr.getAttributeName() == "hastest"){
               hasTestGone == false;
           }
            if(attr.getAttributeName() == "newHasTest"){
              newHasTestPresent == true;
           }
       }
      ASSERT_EQ(hasTestGone, newHasTestPresent);  
}


TEST(UMLDataAttributeTest, RemovingNonExistantAttribute) {
    UMLData data;
    data.addClass("test");
    UMLAttribute attribute("hastestt");
    ASSERT_ANY_THROW(data.removeClassAttribute("test", "hastestt"));
}


/*
TEST(UMLDataRelationshipTest, AddingRelationshipWorks) {
   
    bool haveRelationship;
    haveRelationship == false;
    UMLData data;
    data.addClass("test");
    data.addClass("test1");
    vector<UMLRelationship> rel = data.getRelationships();
    


    data.addRelationship("test", "test1");
   



   for(auto i = rel.begin(); i != rel.end(); ++i){

           if(&(rel[i].getSource()) == "test1"){
          
             haveRelationship == true;
           }
           else if(&(rel[i].getDestination()) == "test1"){
               haveRelationship == true;
           }
   }
  


    ASSERT_EQ(haveRelationship, true); 

}
*/


/*
TEST(UMLDataAttributeTest, RemovingAttributeWorks) {
      
    bool hasTestGone;
    hasTestGone == true;
    
    UMLData data;
    data.addClass("test");
    UMLAttribute attribute("hastest");
    data.addClassAttribute("test", attribute);
    data.removeClassAttribute("test", "hastest");
  
  
   for (UMLAttribute attr : data.getClassAttributes("test")) {
           if(attr.getAttributeName() == "hastest"){
              hasTestGone == false;
              
           
           }
       }
    ASSERT_EQ(hasTestGone, true); 
 */
    





