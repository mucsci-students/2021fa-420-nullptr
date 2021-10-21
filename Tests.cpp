/*
  Filename   : Tests.cpp
  Description: UML++ unit tests using the GoogleTest framework.
  When compiled, performs all tests and displays any errors that occur.
*/

#include <gtest/gtest.h>

#include "include/UMLData.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLRelationship.hpp"
#include "include/UMLParameter.hpp"
#include "include/CLI.hpp"

#include <memory>
#include <string>
#include <iostream>

// Test Format
// **************************
// Describe what the point of the test is in a comment.
// TEST(TestSuiteName, TestName) 
// {
//   ... test body ...
// }
// **************************

// ****************************************************

// Tests for UMLData.hpp involing classes
// **************************

// Checks to see if getting a copy of a class has the same name
// TODO: See if it has the same contents. Also see if this method is still necessary.
TEST(UMLDataAddClassTest, AddClassAndGetCopy) 
{
    UMLData data;
    data.addClass("test");
    ASSERT_EQ("test", data.getClassCopy("test").getName());
}

// Shouldn't be able to add a class that already exists
// TODO: proper error catching beyond ASSERT_ANY_THROW
TEST(UMLDataAddClassTest, AddClassThatAlreadyExists) 
{
    UMLData data;
    data.addClass("test");
    ASSERT_ANY_THROW(data.addClass("test"));
}

// Shouldn't be able to remove a class that doesn't exist
// TODO: proper error catching beyond ASSERT_ANY_THROW
TEST(UMLDataRemoveClassTest, RemoveClassThatDoesntExist) 
{
    UMLData data;
    ASSERT_ANY_THROW(data.deleteClass("test"));
}

// Renaming the class in the data model should = the operation in UMLClass
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

// Shouldn't be allowed to rename a class to one that already exists in te data model
TEST(UMLDataRenameClassTest, RenameClassIntoClassThatAlreadyExists) 
{
    UMLData data;
    data.addClass("test");
    ASSERT_ANY_THROW(data.changeClassName("test", "test"));
}

// ****************************************************

// Tests for UMLData.hpp involving attributes (method/field)
// **************************

// Checks to see if adding method in UMLData works. 
// TODO: Clean up variable names.
TEST(UMLDataAttributeTest, AddMethodWorks) 
{
    UMLData data;
    data.addClass("test");
    UMLMethod attribute("hastest", "type", {});
    data.addClassAttribute("test", attribute);
       for (auto attr : data.getClassAttributes("test")) {
           if(attr->getAttributeName() == "hastest"){
               ASSERT_EQ(attr->getAttributeName(), "hastest");
           }
       }
}

// Checks to see if adding a field in UMLData works. 
// TODO: Clean up variable names.
TEST(UMLDataAttributeTest, AddFieldWorks) 
{
    UMLData data;
    data.addClass("test");
    UMLField attribute("hastest", "type");
    data.addClassAttribute("test", attribute);
       for (auto attr : data.getClassAttributes("test")) {
           if(attr->getAttributeName() == "hastest"){
               ASSERT_EQ(attr->getAttributeName(), "hastest");
           }
       }
}

// Checks to see if changing the name of a field in UMLData works. 
// TODO: Clean up variable names.
TEST(UMLDataAttributeTest, ChangeMethodNameWorks) 
{
    bool hasTestGone;
    hasTestGone = true;
    bool newHasTestPresent;
    newHasTestPresent = false;

    UMLData data;
    data.addClass("test");
    UMLMethod attribute("hastest", "type", {});
    data.addClassAttribute("test", attribute);
    data.changeAttributeName("test", "hastest", "newHasTest");

        for (auto attr : data.getClassAttributes("test")) {
           if(attr->getAttributeName() == "hastest"){
               hasTestGone = false;
           }
            if(attr->getAttributeName() == "newHasTest"){
              newHasTestPresent = true;
           }
       }
      ASSERT_EQ(hasTestGone, newHasTestPresent);  
}

// Checks to see if changing the name of a field in UMLData works. 
// TODO: Clean up variable names.
TEST(UMLDataAttributeTest, ChangeFieldNameWorks) 
{
    bool hasTestGone;
    hasTestGone = true;
    bool newHasTestPresent;
    newHasTestPresent = false;

    UMLData data;
    data.addClass("test");
    UMLField attribute("hastest", "type");
    data.addClassAttribute("test", attribute);
    data.changeAttributeName("test", "hastest", "newHasTest");

        for (auto attr : data.getClassAttributes("test")) {
           if(attr->getAttributeName() == "hastest"){
               hasTestGone = false;
           }
            if(attr->getAttributeName() == "newHasTest"){
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

// ****************************************************

// Tests for UMLData.hpp involving relationships
// **************************

// Basic check to see if adding a relationship to the data model works.
// It should appear in the vector and have the same source, destination, and type.
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

// Error check to see if adding invalid types causes a throw.
// Correct exceptions to see if it's doing a proper throw.
// Also see if it's possible to change this so it doesn't use magic numbers.
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

// Error check to see if adding self inheritance causes an error.
// Correct exceptions to see if it's doing a proper throw.
TEST(UMLDataRelationshipTest, AddingSelfInheritance) 
{
    UMLData data;

    data.addClass("test");
    data.addClass("test1");
    // Cannot have self-generalization or self-realization
    ASSERT_ANY_THROW(data.addRelationship("test", "test", 2));
    ASSERT_ANY_THROW(data.addRelationship("test1", "test1", 3));
}

// Error check to see if adding multiple compositions causes an error.
// Correct exceptions to see if it's doing a proper throw.
// Also check and see if this actually needs to be relaxed.
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

// Sees if deleting a relationship works. 
// When a relationship is deleted, it shouldn't be in UMLData's vector.
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

// Makes sure that you can't delete a relationship that doesn't exist. 
// Find some way to read what is thrown for the sake of proper error checking.
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

// Sees if getting the proper relationship type works after adding a relationship.
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

// Sees if getting a vector of relationships by class works. 
// Extend test to have a case where the two vectors should NOT be the same.
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

// Sees if changing the relationship type works at all.
TEST(UMLDataRelationshipTest, ChangeRelationshipTypeWorks)
{
    UMLData data;

    data.addClass("test");
    data.addClass("test1");

    // Test to see if relationship was changed
    data.addRelationship("test", "test1", 0);
    data.changeRelationshipType("test", "test1", 1);
    ASSERT_EQ(data.getRelationship("test", "test1").getType(), composition);
}

// Tests all errors that currently exist for changing a relationship type.
// Currently only checks to see a throw will happen.
// Potential update to have readable exceptions instead to find the right error?
TEST(UMLDataRelationshipTest, ChangeRelationshipTypeErrors)
{
    UMLData data;

    data.addClass("test");
    data.addClass("test1");
    data.addClass("test2");

    data.addRelationship("test", "test1", 0);
    // Test for bounds
    ASSERT_ANY_THROW(data.changeRelationshipType("test", "test1", 4));
    ASSERT_ANY_THROW(data.changeRelationshipType("test", "test1", -1));
    // Test for self-inheritance
    data.addRelationship("test", "test", 0);
    ASSERT_ANY_THROW(data.changeRelationshipType("test", "test", 2));
    ASSERT_ANY_THROW(data.changeRelationshipType("test", "test", 3));
    // Test for multiple compositions
    data.addRelationship("test2", "test1", 1);
    ASSERT_ANY_THROW(data.changeRelationshipType("test", "test1", 1));
}

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

// Tests for UMLClass.hpp
// **************************

// Basic getter test to see if it gets the proper name
TEST(UMLClassTest, GetNameWorks) 
{
    UMLClass class1("test");
    ASSERT_EQ(class1.getName(), "test");
}

// Basic rename test to see if the name is properly changed
TEST(UMLClassTest, ChangeNameWorks) 
{
    UMLClass class1("test");
    class1.changeName("newTest");
    ASSERT_EQ(class1.getName(), "newTest");
}

// Test to see if the proper attribute with the right name is added
TEST(UMLClassTest, AddAttributeWorks) 
{
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    bool attrFound = false;

    for(auto attr : class1.getAttributes())
    {
        if(attr->getAttributeName() == "testattribute")
        {
            attrFound = true;
        }
    }

    ASSERT_EQ(attrFound, true);
}

// Tests to see if an attribute inside of a class properly gets modified based on name.
TEST(UMLClassTest, ChangeAttributeWorks) 
{
    UMLClass class1("test");
    UMLAttribute attribute("testattributeOld");
    class1.addAttribute(attribute);
    class1.changeAttributeName("testattributeOld", "testattributeNew");
    bool attrFound = false;

    for(auto attr : class1.getAttributes())
    {
        if(attr->getAttributeName() == "testattributeNew")
        {
            attrFound = true;
        }
    }

    ASSERT_EQ(attrFound, true);

    for(auto attr : class1.getAttributes())
    {
        if(attr->getAttributeName() == "testattributeOld")
        {
            attrFound = false;
        }
    }

    ASSERT_EQ(attrFound, true);
}

// Tests to see if an attribute inside of a class properly gets modified based on an attribute reference.
TEST(UMLClasstest, ChangeAttributeReferenceWorks)
{
    UMLClass class1("test");
    UMLAttribute attribute("testattributeOld");
    class1.addAttribute(attribute);
   
    // Make reference attribute and add
    auto attributeRef = std::make_shared<UMLAttribute>();
    class1.changeAttributeName(attributeRef, "testattributeNew");

    bool attrFound = false;

    for(auto attr : class1.getAttributes())
    {
        if(attr->getAttributeName() == "testattributeNew")
        {
            attrFound = true;
        }
    }

    ASSERT_EQ(attrFound, true);

    for(auto attr : class1.getAttributes())
    {
        if(attr->getAttributeName() == "testattributeOld")
        {
            attrFound = false;
        }
    }

    ASSERT_EQ(attrFound, true);
}

// Checks if deleting attribute based on name works.
TEST(UMLClassTest, DeleteAttributeWorks) 
{
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    class1.deleteAttribute("testattribute");

    // See if attribute still exists
    bool attrFound = false;
    for(auto attr : class1.getAttributes())
    {
        if(attr->getAttributeName() == "testattribute")
        {
            attrFound = true;
        }
    }

    ASSERT_EQ(attrFound, false);
}

// Checks if deleting attribute based on its reference works.
TEST(UMLClassTest, DeleteAttributeReferenceWorks) 
{
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    
    // Create reference and delete based on it
    auto attributeRef = std::make_shared<UMLAttribute>();
    class1.deleteAttribute(attributeRef);

    // See if attribute still exists
    bool attrFound = false;
    for(auto attr : class1.getAttributes())
    {
        if(attr->getAttributeName() == "testattribute")
        {
            attrFound = true;
        }
    }

    ASSERT_EQ(attrFound, false);
}

// Check if finding attribute based on name works.
// This test is outdated and must be replaced entirely alongside modifications to UMLClass.cpp.
TEST(UMLClassTest, FindAttributeWorks) 
{
    UMLClass class1("test");
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    
    ASSERT_EQ(class1.getAttribute("testattribute")->getAttributeName(), attribute.getAttributeName());
}

// Test that sees that adding a test attribute works as intended.
TEST(UMLClassTest, GetAttributesWorks) 
{
    UMLClass class1("test");
    // Basic constructor used as type should not matter
    UMLAttribute attribute("testattribute");
    class1.addAttribute(attribute);
    
    vector<UMLAttribute> test;
    test.push_back(attribute);
    
    bool isEqual = true;
    vector<std::shared_ptr<UMLAttribute>> test2 = class1.getAttributes();

    // Expand test later to check deeper if two attributes are equal
    for(int i = 0; i < test.size(); i++)
    {
        if(test[i].getAttributeName() != test2[i]->getAttributeName())
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

// Tests for UMLMethod
// **************************

// Basic getter test to see if it gets the proper name
TEST(UMLMethodTest, GetMethodNameTest) 
{
    UMLMethod attribute("test", "type", {});
    ASSERT_EQ(attribute.getAttributeName(), "test");
}

// Basic rename test to see if the name is properly changed
TEST(UMLMethodTest, RenameMethodNameTest) 
{
    UMLMethod attribute("test", "type", {});
    attribute.changeName("test2");
    ASSERT_EQ(attribute.getAttributeName(), "test2");
}

// ****************************************************


// Tests for UMLAttribute
// **************************

// Basic getter test to see if it gets the proper name
TEST(UMLAttributeTest, GetAttributeNameTest) 
{
    UMLField attribute("test", "type");
    ASSERT_EQ(attribute.getAttributeName(), "test");
}

// Basic rename test to see if the name is properly changed
TEST(UMLAttributeTest, RenameAttributeNameTest) 
{
    UMLField attribute("test", "type");
    attribute.changeName("test2");
    ASSERT_EQ(attribute.getAttributeName(), "test2");
}

// ****************************************************
