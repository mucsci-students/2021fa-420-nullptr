#include <gtest/gtest.h>
#include "include/UMLData.hpp"
#include "include/CLI.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLRelationship.hpp"
#include "include/UMLAttribute.hpp"
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

TEST(UMLRelationshipTest, GetDestinationTest2) {
    UMLClass class1("class1");
    UMLClass class2("class2");
    UMLRelationship relate(class1, class2);
    bool test = &relate.getDestination() == &class1;
    ASSERT_EQ(test, false);

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

//Tests for UMLClass.hpp
TEST(UMLClassFileTest, GetNameWorks) {
    UMLClass class1("test");
    ASSERT_EQ(class1.getName(), "test");
}

TEST(UMLClassFileTest, ChangeNameWorks) {
    UMLClass class1("test");
    class1.changeName("newTest");
    ASSERT_EQ(class1.getName(), "newTest");
}

TEST(UMLClassFileTest, AddAttributeWorks) {
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    bool attrFound = false;

    for(UMLAttribute attr : class1.getAttributes())
    {
        if(attr.getAttributeName() == "testattribute")
        {
            attrFound = true;
        }
    }

    ASSERT_EQ(attrFound, true);
}

TEST(UMLClassFileTest, ChangeAttributeWorks) {
    UMLClass class1("test");
    UMLAttribute attribute("testattributeOld");
    class1.addAttribute(attribute);
    class1.changeAttributeName("testattributeOld","testattributeNew");
    bool attrFound = false;

    for(UMLAttribute attr : class1.getAttributes())
    {
        if(attr.getAttributeName() == "testattributeNew")
        {
            attrFound = true;
        }
    }

    ASSERT_EQ(attrFound, true);

    for(UMLAttribute attr : class1.getAttributes())
    {
        if(attr.getAttributeName() == "testattributeOld")
        {
            attrFound = false;
        }
    }

    ASSERT_EQ(attrFound, true);
}

TEST(UMLClassFileTest, DeleteAttributeWorks) {
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    bool attrFound = false;
    class1.deleteAttribute("testattribute");

    for(UMLAttribute attr : class1.getAttributes())
    {
        if(attr.getAttributeName() == "testattribute")
        {
            attrFound = true;
        }
    }

    ASSERT_EQ(attrFound, false);
}

TEST(UMLClassFileTest, FindAttributeWorks) {
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    

    ASSERT_EQ(class1.findAttribute("testattribute")->getAttributeName(), attribute.getAttributeName());
}

TEST(UMLClassFileTest, GetAttributesWorks) {
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    
    vector<UMLAttribute> test;
    test.push_back(attribute);
    
    bool isEqual = true;
    vector<UMLAttribute> test2 = class1.getAttributes();

    for(int i = 0; i < test.size(); i++)
    {
        if(test[i].getAttributeName() != test2[i].getAttributeName())
        {
            isEqual = false;
        }
    }
    ASSERT_EQ(isEqual, true);
}
