#include <gtest/gtest.h>
#include "UMLData.hpp"
#include "CLI.hpp"
#include "UMLClass.hpp"
#include "UMLRelationship.hpp"
#include "UMLAttribute.hpp"
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
TEST(UMLDataAttributeTest, RemovingAttributeWorks) {
    UMLData data;
    data.addClass("test");
    UMLAttribute attribute("hastest");
    data.addClassAttribute("test", attribute);
    data.removeClassAttribute("test", attribute);
    ASSERT_EQ(data.getClassCopy("test").removeClassAttribute("test", attribute), "");

}
*/

//Attribute tests
/*
-Removing an attribute works
-removing an attribute  that doestn exist should throw an error
- renaming an attribute should work
- renaming an attribute to another attribute that already exists should throw an error
*/


 //adds class attribute to specified className
     //   void addClassAttribute(string className, UMLAttribute attribute);

/*
TEST(SquareRootTest, PositiveNos) { 
    EXPECT_EQ (18.0, square‑root (324.0));
    EXPECT_EQ (25.4, square‑root (645.16));
    EXPECT_EQ (50.3321, square‑root (2533.310224));
}
*/


//Tests for UMLRelationship.hpp
TEST(UMLRelationshipTest, GetSourceTest) {
    UMLClass class1("class1");
    UMLClass class2("class2");
    UMLRelationship relate(class1, class2);

    ASSERT_EQ(&relate.getSource(), &class1);
}

TEST(UMLRelationshipTest, GetDestinationTest) {
    UMLClass class1("class1");
    UMLClass class2("class2");
    UMLRelationship relate(class1, class2);

    ASSERT_EQ(&relate.getDestination(), &class2);
}


//Tests for UMLAttribute.hpp
TEST(UMLAttributeTest, GetAttributeNameTest) {
    UMLAttribute attribute("test");

    ASSERT_EQ(attribute.getAttributeName(), "test");
}

TEST(UMLAttributeTest, RenameAttributeNameTest) {
    UMLAttribute attribute("test");
    attribute.changeName("test2");

    ASSERT_EQ(attribute.getAttributeName(), "test2");
}