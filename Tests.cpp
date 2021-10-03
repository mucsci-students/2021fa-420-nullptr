/*
  Filename   : Tests.cpp
  Description: UML++ unit tests using the GoogleTest framework.
  When compiled, performs all tests and displays any errors that occur.
*/

#include <gtest/gtest.h>

#include "include/UMLData.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLRelationship.hpp"
#include "include/UMLAttribute.hpp"
#include "include/UMLParameter.hpp"
#include "include/CLI.hpp"

#include <string>
#include <iostream>

// Test Format
// **************************
// TEST(TestSuiteName, TestName) 
// {
//   ... test body ...
// }
// **************************

// ****************************************************

// Tests for UMLData.hpp
// **************************

TEST(UMLDataAddClassTest, AddClassAndGetCopy) 
{
    UMLData data;
    data.addClass("test");
    ASSERT_EQ("test", data.getClassCopy("test").getName());
}

TEST(UMLDataAddClassTest, AddClassThatAlreadyExists) 
{
    UMLData data;
    data.addClass("test");
    ASSERT_ANY_THROW(data.addClass("test"));
}

TEST(UMLDataRemoveClassTest, RemoveClassThatDoesntExist) 
{
    UMLData data;
    ASSERT_ANY_THROW(data.deleteClass("test"));
}

TEST(UMLDataRenameClassTest, RenameAClassWorks) 
{
    UMLData data;
    string oldName;
    string updatedName;
    oldName = "test";
    updatedName = "testtest";
    data.addClass(oldName);
    data.changeClassName(oldName, updatedName);
    ASSERT_EQ(updatedName, updatedName);
}

TEST(UMLDataRenameClassTest, RenameClassIntoClassThatAlreadyExists) 
{
    UMLData data;
    data.addClass("test");
    ASSERT_ANY_THROW(data.changeClassName("test", "test"));
}

TEST(UMLDataAttributeTest, AddAttributeWorks) 
{
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

TEST(UMLDataAttributeTest, ChangeAttributeNameWorks) 
{
    bool hasTestGone;
    hasTestGone = true;
    bool newHasTestPresent;
    newHasTestPresent = false;

    UMLData data;
    data.addClass("test");
    UMLAttribute attribute("hastest");
    data.addClassAttribute("test", attribute);
    data.changeAttributeName("test", "hastest", "newHasTest");

        for (UMLAttribute attr : data.getClassAttributes("test")) {
           if(attr.getAttributeName() == "hastest"){
               hasTestGone = false;
           }
            if(attr.getAttributeName() == "newHasTest"){
              newHasTestPresent = true;
           }
       }
      ASSERT_EQ(hasTestGone, newHasTestPresent);  
}

TEST(UMLDataAttributeTest, RemovingNonExistantAttribute) 
{
    UMLData data;
    data.addClass("test");
    UMLAttribute attribute("hastestt");
    ASSERT_ANY_THROW(data.removeClassAttribute("test", "hastestt"));
}

TEST(UMLDataRelationshipTest, AddingRelationshipWorks) 
{
    bool haveRelationship = false;
    UMLData data;
    data.addClass("test");
    data.addClass("test1");
    // Relationship type doesn't matter for this test
    data.addRelationship("test", "test1", 0);
    
    vector<UMLRelationship> rel = data.getRelationships();
   // Loop through vector to find proper relationship
    for(auto i = rel.begin(); i != rel.end(); ++i){
        // Check and see if the valid relationship was added
        if(i->getSource().getName() == "test" && 
        i->getDestination().getName() == "test1" && 
        i->getType() == aggregation){
            haveRelationship = true;
        }
    }

    // Relationship should exist
    ASSERT_EQ(haveRelationship, true);
    // Only one relationship should have been added
    ASSERT_EQ(rel.size(), std::size_t(1));
}

TEST(UMLDataRelationshipTest, AddingInvalidType) 
{
    UMLData data;

    data.addClass("test");
    data.addClass("test1");
    // Relationship type shouldn't be over 3
    ASSERT_ANY_THROW(data.addRelationship("test", "test1", 4));

    data.addClass("test2");
    data.addClass("test3");
    // Relationship type shouldn't be less than 0
    ASSERT_ANY_THROW(data.addRelationship("test2", "test3", -1));
}

TEST(UMLDataRelationshipTest, AddingSelfInheritance) 
{
    UMLData data;

    data.addClass("test");
    data.addClass("test1");
    // Cannot have self-generalization or self-realization
    ASSERT_ANY_THROW(data.addRelationship("test", "test", 2));
    ASSERT_ANY_THROW(data.addRelationship("test1", "test1", 3));
}

TEST(UMLDataRelationshipTest, AddingMultipleCompositions) 
{
    UMLData data;

    data.addClass("test");
    data.addClass("test1");
    data.addClass("test2");
    data.addRelationship("test", "test1", 1);
    // Cannot be the destination of multiple compositions
    ASSERT_ANY_THROW(data.addRelationship("test2", "test1", 1));
} 

TEST(UMLDataRelationshipTest, DeletingRelationshipWorks)
{
    bool haveRelationship = false;
    UMLData data;
    data.addClass("test");
    data.addClass("test1");
    // Relationship type doesn't matter for this test
    data.addRelationship("test", "test1", 0);
    data.deleteRelationship("test", "test1");
    
    vector<UMLRelationship> rel = data.getRelationships();
    // Loop through vector to find proper relationship
    for(auto i = rel.begin(); i != rel.end(); ++i){
        // Check and see if the valid relationship still exists
        if(i->getSource().getName() == "test" && 
        i->getDestination().getName() == "test1" && 
        i->getType() == aggregation){
            haveRelationship = true;
        }
    }

    // Relationship should be deleted
    ASSERT_EQ(haveRelationship, false);

    // Vector should now be empty
    ASSERT_EQ(rel.size(), std::size_t(0));
}

TEST(UMLDataRelationshipTest, DeletingNonexistentRelationship)
{
    UMLData data;

    // Attempt to delete relationship that does not exist
    ASSERT_ANY_THROW(data.deleteRelationship("test", "test"));
    
    // Same as above, but with the class existing and two different classes
    data.addClass("test");
    data.addClass("test1");
    ASSERT_ANY_THROW(data.deleteRelationship("test", "test"));
    ASSERT_ANY_THROW(data.deleteRelationship("test", "test1"));
}

TEST(UMLDataRelationshipTest, GetRelationshipTypeWorks)
{
    bool foundRelationship = false;
    UMLData data;
    data.addClass("test");
    data.addClass("test1");
    // Check for aggregation
    data.addRelationship("test", "test1", 0);
    ASSERT_EQ(data.getRelationshipType("test", "test1"), "aggregation");
    data.deleteRelationship("test", "test1");
    // Check for composition
    data.addRelationship("test", "test1", 1);
    ASSERT_EQ(data.getRelationshipType("test", "test1"), "composition");
    data.deleteRelationship("test", "test1");
    // Check for generalization
    data.addRelationship("test", "test1", 2);
    ASSERT_EQ(data.getRelationshipType("test", "test1"), "generalization");
    data.deleteRelationship("test", "test1");
    // Check for realization
    data.addRelationship("test", "test1", 3);
    ASSERT_EQ(data.getRelationshipType("test", "test1"), "realization");
}

TEST(UMLDataRelationshipTest, GetRelationshipByClassWorks)
{
    UMLData data;

    data.addClass("test");
    data.addClass("test1");
    data.addClass("test2");
    data.addRelationship("test", "test1", 0);
    data.addRelationship("test", "test2", 0);
    
    // Vector obtained and relationship vector should be equivalent
    vector<UMLRelationship> vector1 = data.getRelationshipsByClass("test");
    vector<UMLRelationship> vector2 = data.getRelationships();

    // Check for identical vector size
    ASSERT_EQ(vector1.size(), vector2.size());
    // Check for identical vector contents
    for (size_t i = 0; i < vector1.size(); ++i) {
        ASSERT_EQ(vector1[i].getSource().getName(), vector2[i].getSource().getName());
        ASSERT_EQ(vector1[i].getDestination().getName(), vector2[i].getDestination().getName());
        ASSERT_EQ(vector1[i].getType(), vector2[i].getType());
    }
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
-Removing an attribute  that doestn exist should throw an error
-Renaming an attribute should work
-Renaming an attribute to another attribute that already exists should throw an error
*/

//adds class attribute to specified className
//void addClassAttribute(string className, UMLAttribute attribute);

/*
TEST(UMLDataAttributeTest, RemovingAttributeWorks) 
{
      
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

// ****************************************************

// Tests for UMLRelationship.hpp
// **************************

// Test to check if constructing a generic relationship works at all
TEST(UMLRelationshipTest, ConstructorTest) 
{
    UMLClass class1("class1");
    UMLClass class2("class2");
    ASSERT_NO_THROW(UMLRelationship relate(class1, class2, 0));
}

// Test to check if getting a source works at all
TEST(UMLRelationshipTest, GetSourceTest) 
{
    UMLClass class1("class1");
    UMLClass class2("class2");
    // Relationship type doesn't matter for this test
    UMLRelationship relate(class1, class2, 0);
    ASSERT_EQ(&relate.getSource(), &class1);
}

// Test to check if getting a destination works at all
TEST(UMLRelationshipTest, GetDestinationTest) 
{
    UMLClass class1("class1");
    UMLClass class2("class2");
    // Relationship type doesn't matter for this test
    UMLRelationship relate(class1, class2, 0);
    ASSERT_EQ(&relate.getDestination(), &class2);
}

// Test to see if the destination was simultaneously set as the source
TEST(UMLRelationshipTest, GetDestinationTest2) 
{
    UMLClass class1("class1");
    UMLClass class2("class2");
    // Relationship type doesn't matter for this test
    UMLRelationship relate(class1, class2, 0);
    bool test = &relate.getDestination() == &class1;
    ASSERT_EQ(test, false);
}

// Test to check if getting a type works at all
TEST(UMLRelationshipTest, GetTypeTest) {
    UMLClass class1("class1");
    UMLClass class2("class2");
    UMLRelationship relate(class1, class2, 0);
    ASSERT_EQ(relate.getType() == aggregation, true);
}

// Test to check if setting a type works at all
TEST(UMLRelationshipTest, SetTypeTest) {
    UMLClass class1("class1");
    UMLClass class2("class2");
    UMLRelationship relate(class1, class2, 0);
    relate.setType(composition);
    ASSERT_EQ(relate.getType() == composition, true);
}

// Make and set relationships of each type and see if they hold the correct type
TEST(UMLRelationshipTest, GetAllTypeTest) 
{
    UMLClass class1("class1");
    UMLClass class2("class2");
    UMLRelationship relate(class1, class2, 0);
    ASSERT_EQ(relate.getType() == aggregation, true);
    relate.setType(composition);
    ASSERT_EQ(relate.getType() == composition, true);
    relate.setType(generalization);
    ASSERT_EQ(relate.getType() == generalization, true);
    relate.setType(realization);
    ASSERT_EQ(relate.getType() == realization, true);
}

// ****************************************************

// Tests for UMLAttribute.hpp
// **************************

TEST(UMLAttributeTest, GetAttributeNameTest) 
{
    UMLAttribute attribute("test");
    ASSERT_EQ(attribute.getAttributeName(), "test");
}

TEST(UMLAttributeTest, RenameAttributeNameTest) 
{
    UMLAttribute attribute("test");
    attribute.changeName("test2");
    ASSERT_EQ(attribute.getAttributeName(), "test2");
}

// ****************************************************

// Tests for UMLClass.hpp
// **************************

TEST(UMLClassFileTest, GetNameWorks) 
{
    UMLClass class1("test");
    ASSERT_EQ(class1.getName(), "test");
}

TEST(UMLClassFileTest, ChangeNameWorks) 
{
    UMLClass class1("test");
    class1.changeName("newTest");
    ASSERT_EQ(class1.getName(), "newTest");
}

TEST(UMLClassFileTest, AddAttributeWorks) 
{
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

TEST(UMLClassFileTest, ChangeAttributeWorks) 
{
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

TEST(UMLClassFileTest, DeleteAttributeWorks) 
{
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

TEST(UMLClassFileTest, FindAttributeWorks) 
{
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    

    ASSERT_EQ(class1.findAttribute("testattribute")->getAttributeName(), attribute.getAttributeName());
}

TEST(UMLClassFileTest, GetAttributesWorks) 
{
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

// ****************************************************

// Tests for UMLParameter.hpp
// **************************

// Tests creation of a Parameter and getting it's name and type works
TEST(UMLParameterTest, GetParameterNameTest) 
{
    UMLParameter parameter("name","type");
    ASSERT_EQ(parameter.getName(), "name");
    ASSERT_EQ(parameter.getType(), "type");
}

// Tests renaming Parameter works
TEST(UMLParameterTest, RenameParameterNameTest) 
{
    UMLParameter parameter("name","type");
    parameter.changeName("name2");
    ASSERT_EQ(parameter.getName(), "name2");
}
// Tests changing Parameter type works
TEST(UMLParameterTest, ChangeParameterTypeTest) 
{
    UMLParameter parameter("name","type");
    parameter.changeType("type2");
    ASSERT_EQ(parameter.getType(), "type2");
}

// ****************************************************