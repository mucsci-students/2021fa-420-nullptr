/*
  Filename   : Tests.cpp
  Description: UML++ unit tests using the GoogleTest framework.
  When compiled, performs all tests and displays any errors that occur.
*/

/************************************************************/
// Error checking macro for functions with expected errors
#define ERR_CHECK(fun, errorString)                     \
  EXPECT_THROW (                                        \
    try {                                               \
        fun;                                            \
    }                                                   \
    catch (const std::runtime_error& error) {           \
        EXPECT_STREQ(errorString, error.what());        \
        throw;                                          \
    },                                                  \
  std::runtime_error);                                  \
/************************************************************/

#include <gtest/gtest.h>

#include "include/CLI.hpp"
#include "include/CLIView.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLData.hpp"
#include "include/UMLDataHistory.hpp"
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "include/UMLRelationship.hpp"

#include <iostream>
#include <memory>
#include <string>

/* 
**************************
Test Format
**************************
Describe what the point of the test is in a comment.
TEST(TestSuiteName, TestName) 
{
  ... test body ...
}
************************** 
*/

/*
**************************
Ordering of Tests
**************************
UMLClass
UMLAttribute
UMLField 
UMLMethod
UMLParameter
UMLRelationship
UMLFile (## WIP ##)
UMLData - Classes
UMLData - Methods/Fields
UMLData - Relationships
UMLDataHistory
CLIView (## WIP ##)
CLI (## WIP ##)
Server (## WIP ##)
*/

// ****************************************************

// Tests for UMLClass
// **************************

// Basic getter test to see if it gets the proper name
TEST (UMLClassTest, GetNameTest)
{
  UMLClass class1 ("test");
  ASSERT_EQ (class1.getName(), "test");
}

// Basic rename test to see if the name is properly changed
TEST (UMLClassTest, ChangeNameTest)
{
  UMLClass class1 ("test");
  class1.changeName ("newTest");
  ASSERT_EQ (class1.getName(), "newTest");
}

// Test to see if the proper attribute with the right name is added
TEST (UMLClassTest, AddAttributeTest)
{
  UMLClass class1 ("test");
  UMLAttribute attribute ("testattribute");
  class1.addAttribute (attribute);
  bool attrFound = false;

  for (auto attr : class1.getAttributes())
  {
    if (attr->getAttributeName() == "testattribute")
    {
      attrFound = true;
    }
  }

  ASSERT_EQ (attrFound, true);
}

// Tests to see if an attribute inside of a class properly gets modified based on name.
TEST (UMLClassTest, ChangeAttributeNameTest)
{
  UMLClass class1 ("test");
  UMLAttribute attribute ("testattributeOld");
  class1.addAttribute (attribute);
  class1.changeAttributeName ("testattributeOld", "testattributeNew");
  bool attrFound = false;

  for (auto attr : class1.getAttributes())
  {
    if (attr->getAttributeName() == "testattributeNew")
    {
      attrFound = true;
    }
  }

  ASSERT_EQ (attrFound, true);

  for (auto attr : class1.getAttributes())
  {
    if (attr->getAttributeName() == "testattributeOld")
    {
      attrFound = false;
    }
  }

  ASSERT_EQ (attrFound, true);
}

// Tests to see if an attribute inside of a class properly gets modified based on an attribute reference.
TEST (UMLClasstest, ChangeAttributeNameReferenceTest)
{
  UMLClass class1 ("test");
  auto attribute = std::make_shared<UMLAttribute> ("oldName");
  class1.addAttribute (attribute);

  // See if attribute was changed based on reference modification
  class1.changeAttributeName (attribute, "newName");
  ASSERT_EQ (attribute->getAttributeName(), "newName");

  bool attrFound = false;

  for (auto attr : class1.getAttributes())
  {
    if (attr->getAttributeName() == "newName")
    {
      attrFound = true;
    }
    else if (attr->getAttributeName() == "oldName" && attrFound)
    {
      attrFound = false;
    }
  }

  ASSERT_EQ (attrFound, true);
}

// Checks if deleting attribute based on name works.
TEST (UMLClassTest, DeleteAttributeTest)
{
  UMLClass class1 ("test");
  UMLAttribute attribute ("test");
  class1.addAttribute (attribute);
  class1.deleteAttribute ("test");

  // See if attribute still exists
  bool attrFound = false;
  for (auto attr : class1.getAttributes())
  {
    if (attr->getAttributeName() == "test")
    {
      attrFound = true;
    }
  }

  ASSERT_EQ (attrFound, false);
}

// Checks if deleting attribute based on its reference works.
TEST (UMLClassTest, DeleteAttributeReferenceTest)
{
  UMLClass class1 ("test");
  auto attribute = std::make_shared<UMLAttribute> ("test");
  class1.addAttribute (attribute);

  // Create reference and delete based on it
  class1.deleteAttribute (attribute);

  // See if attribute still exists
  bool attrFound = false;
  for (auto attr : class1.getAttributes())
  {
    if (attr->getAttributeName() == "test")
    {
      attrFound = true;
    }
  }

  ASSERT_EQ (attrFound, false);
}

// Check if finding attribute based on name works.
// This test is outdated and must be replaced entirely alongside modifications to UMLClass.cpp.
TEST (UMLClassTest, FindAttributeTest)
{
  UMLClass class1 ("test");
  UMLAttribute attribute ("testattribute");
  class1.addAttribute (attribute);

  ASSERT_EQ (class1.getAttribute ("testattribute")->getAttributeName(),
             attribute.getAttributeName());
}

// Test that sees that adding a test attribute works as intended.
TEST (UMLClassTest, GetAttributesTest)
{
  UMLClass class1 ("test");
  // Basic constructor used as type should not matter
  UMLAttribute attribute ("testattribute");
  class1.addAttribute (attribute);

  vector<UMLAttribute> test;
  test.push_back (attribute);

  bool isEqual = true;
  vector<std::shared_ptr<UMLAttribute>> test2 = class1.getAttributes();

  // Expand test later to check deeper if two attributes are equal
  for (int i = 0; i < test.size(); i++)
  {
    if (test[i].getAttributeName() != test2[i]->getAttributeName())
    {
      isEqual = false;
    }
  }
  ASSERT_EQ (isEqual, true);
}

// Test to see if checking an attribute for valid insertion works
TEST (UMLClassTest, CheckAttributesTest)
{
  UMLClass class1 ("test");

  // Starting method to test basic situations
  shared_ptr<UMLMethod> method1 =
    std::make_shared<UMLMethod> ("test", "int", std::list<UMLParameter>{});
  class1.addAttribute (method1);

  // method2 should be identical to method1
  shared_ptr<UMLMethod> method2 =
    std::make_shared<UMLMethod> ("test", "int", std::list<UMLParameter>{});
  // Identical to method2 in name and type, but is a field
  shared_ptr<UMLField> field1 = std::make_shared<UMLField> ("test", "int");
  ASSERT_EQ (class1.checkAttribute (method2), true)
    << "Shouldn't overload method with empty parameter with empty parameter "
       "method";
  ASSERT_EQ (class1.checkAttribute (field1), true)
    << "Shouldn't add field with the same name as an already included method";

  // Create set of methods for the sake of testing with different sets of parameters
  UMLParameter param1 ("param", "type1");
  UMLParameter param2 ("param", "type2");
  UMLParameter param3 ("param2", "type1");
  UMLParameter param4 ("param2", "type2");

  // Default method to be compared with
  shared_ptr<UMLMethod> method3 = std::make_shared<UMLMethod> (
    "paramTest", "type", std::list<UMLParameter>{param1, param4});
  class1.addAttribute (method3);

  // Same as method3, but second parameter has different type
  shared_ptr<UMLMethod> method4 = std::make_shared<UMLMethod> (
    "paramTest", "type", std::list<UMLParameter>{param1, param3});
  // Same as method3, but both parameters have different types
  shared_ptr<UMLMethod> method5 = std::make_shared<UMLMethod> (
    "paramTest", "type", std::list<UMLParameter>{param2, param3});
  // Same as method3, but the method itself has a different name
  shared_ptr<UMLMethod> method6 = std::make_shared<UMLMethod> (
    "testParam", "type", std::list<UMLParameter>{param1, param4});
  // Same as method3, btu the method itself has a different type
  shared_ptr<UMLMethod> method7 = std::make_shared<UMLMethod> (
    "paramTest", "type2", std::list<UMLParameter>{param1, param4});

  ASSERT_EQ (class1.checkAttribute (method4), false)
    << "Swapping type signature of one parameter should overload regardless of "
       "param name";
  ASSERT_EQ (class1.checkAttribute (method5), false)
    << "Swapping type signature of two parameters should overload regardless "
       "of param name";
  ASSERT_EQ (class1.checkAttribute (method6), false)
    << "Methods have different names, so there shouldn't even be an overload";
  ASSERT_EQ (class1.checkAttribute (method7), true)
    << "Methods have different types, but params are same so it shouldn't work";
}

// ****************************************************

// Tests for UMLAttribute
// **************************

// TEST(UMLFieldTest, GetFieldNameTest)

// Basic getter test to see if it gets the proper name
TEST (UMLAttributeTest, GetAttributeNameTest)
{
  UMLAttribute attribute ("test", "type");
  ASSERT_EQ (attribute.getAttributeName(), "test");
}

// Basic getter test to see if it gets the proper type
TEST (UMLAttributeTest, GetAttributeTypeTest)
{
  UMLAttribute attribute ("test", "type");
  ASSERT_EQ (attribute.getType(), "type");
}

// Basic getter test to see if it gets the proper identifier
TEST (UMLAttributeTest, GetAttributeIdentifierTest)
{
  UMLAttribute attribute ("test", "type");
  ASSERT_EQ (attribute.identifier(), "attribute");
}

// Basic rename test to see if the name is properly changed
TEST (UMLAttributeTest, ChangeAttributeNameTest)
{
  UMLAttribute attribute ("test", "type");
  attribute.changeName ("test2");
  ASSERT_EQ (attribute.getAttributeName(), "test2");
}

// Basic rename test to see if the name is properly changed
TEST (UMLAttributeTest, ChangeAttributeTypeTest)
{
  UMLAttribute attribute ("test", "type");
  attribute.changeType ("type2");
  ASSERT_EQ (attribute.getType(), "type2");
}

// ****************************************************

// Tests for UMLField
// **************************

// Basic getter test to see if it gets the proper name
TEST (UMLFieldTest, GetFieldNameTest)
{
  UMLField field ("test", "type");
  ASSERT_EQ (field.getAttributeName(), "test");
}

// Basic getter test to see if it gets the proper type
TEST (UMLFieldTest, GetFieldTypeTest)
{
  UMLField field ("test", "type");
  ASSERT_EQ (field.getType(), "type");
}

// Basic getter test to see if it gets the proper identifier
TEST (UMLFieldTest, GetFieldIdentifierTest)
{
  UMLField field ("test", "type");
  ASSERT_EQ (field.identifier(), "field");
}

// Basic rename test to see if the name is properly changed
TEST (UMLFieldTest, ChangeFieldNameTest)
{
  UMLField field ("test", "type");
  field.changeName ("test2");
  ASSERT_EQ (field.getAttributeName(), "test2");
}

// Basic rename test to see if the name is properly changed
TEST (UMLFieldTest, ChangeFieldTypeTest)
{
  UMLField field ("test", "type");
  field.changeType ("type2");
  ASSERT_EQ (field.getType(), "type2");
}

// ****************************************************

// Tests for UMLMethod
// **************************

// Basic getter test to see if it gets the proper name
TEST (UMLMethodTest, GetMethodNameTest)
{
  UMLMethod method ("test", "type", std::list<UMLParameter>{});
  ASSERT_EQ (method.getAttributeName(), "test");
}

// Basic rename test to see if the name is properly changed
TEST (UMLMethodTest, ChangeMethodNameTest)
{
  UMLMethod method ("test", "type", std::list<UMLParameter>{});
  method.changeName ("test2");
  ASSERT_EQ (method.getAttributeName(), "test2");
}

// Basic rename test to see if the name is properly changed
TEST (UMLMethodTest, ChangeMethodTypeTest)
{
  UMLMethod method ("test", "type", std::list<UMLParameter>{});
  method.changeType ("type2");
  ASSERT_EQ (method.getType(), "type2");
}

// Basic getter test to see if it gets the proper identifier
TEST (UMLMethodTest, GetMethodIdentifierTest)
{
  UMLMethod method ("test", "type", std::list<UMLParameter>{});
  ASSERT_EQ (method.identifier(), "method");
}

// Checks to see if adding a parameter works properly
TEST (UMLMethodTest, AddParameterTest)
{
  // NOTE--this doesn't do any parameter checks on its own.
  // If you call addParam directly, it won't be tested!
  UMLMethod method ("test", "type", std::list<UMLParameter>{});
  UMLParameter param ("param", "type");
  method.addParam (param);
  auto paramList = method.getParam();
  bool paramExists = false;
  // Loop to see if param was added
  for (auto param : paramList)
  {
    if (param.getName() == "param")
      paramExists = true;
  }
  ASSERT_TRUE (paramExists) << "Parameter was not added into the method";
}

// Checks to see if changing a parameter name in a method works properly
TEST (UMLMethodTest, RenameParameterTest)
{
  UMLMethod method ("test", "type", std::list<UMLParameter>{});
  UMLParameter param ("param", "type");
  method.addParam (param);
  method.changeParameterName ("param", "newParam");
  auto paramList = method.getParam();
  bool test = false;
  // test if new name is there
  for (auto param : paramList)
  {
    if (param.getName() == "newParam")
      test = true;
  }
  // old name should be gone
  for (auto param : paramList)
  {
    if (param.getName() == "param")
      test = false;
  }
  ASSERT_TRUE (test) << "Parameter was not renamed correctly";
}

// Checks to see if changing a parameter type in a method works properly
TEST (UMLMethodTest, ChangeParameterTypeTest)
{
  UMLMethod method ("test", "type", std::list<UMLParameter>{});
  UMLParameter param ("param", "type");
  method.addParam (param);
  method.changeParameterType ("param", "newType");
  auto paramList = method.getParam();
  bool test = false;
  // test if new type is there
  for (auto param : paramList)
  {
    if (param.getType() == "newType")
      test = true;
  }
  // old type should be gone
  for (auto param : paramList)
  {
    if (param.getType() == "type")
      test = false;
  }
  ASSERT_TRUE (test) << "Parameter was not changed correctly";
}

// ****************************************************

// Tests for UMLParameter
// **************************

// Tests creation of a Pprameter and getting it's name and type works
TEST (UMLParameterTest, GetParameterValuesTest)
{
  UMLParameter parameter ("name", "type");
  ASSERT_EQ (parameter.getName(), "name");
  ASSERT_EQ (parameter.getType(), "type");
}

// Tests renaming Parameter works
TEST (UMLParameterTest, RenameParameterNameTest)
{
  UMLParameter parameter ("name", "type");
  parameter.changeName ("name2");
  ASSERT_EQ (parameter.getName(), "name2");
}

// Tests changing Parameter type works
TEST (UMLParameterTest, ChangeParameterTypeTest)
{
  UMLParameter parameter ("name", "type");
  parameter.changeType ("type2");
  ASSERT_EQ (parameter.getType(), "type2");
}

// ****************************************************

// Tests for UMLRelationship
// **************************

// Test to check if constructing a generic relationship works at all
TEST (UMLRelationshipTest, ConstructorTest)
{
  UMLClass class1 ("class1");
  UMLClass class2 ("class2");
  ASSERT_NO_THROW (UMLRelationship relate (class1, class2, 0));
}

// Test to check if getting a source works at all
TEST (UMLRelationshipTest, GetSourceTest)
{
  UMLClass class1 ("class1");
  UMLClass class2 ("class2");
  // Relationship type doesn't matter for this test
  UMLRelationship relate (class1, class2, 0);
  ASSERT_EQ (&relate.getSource(), &class1);
}

// Test to check if getting a destination works at all
TEST (UMLRelationshipTest, GetDestinationTest)
{
  UMLClass class1 ("class1");
  UMLClass class2 ("class2");
  // Relationship type doesn't matter for this test
  UMLRelationship relate (class1, class2, 0);
  ASSERT_EQ (&relate.getDestination(), &class2);
}

// Test to see if the destination was simultaneously set as the source
TEST (UMLRelationshipTest, GetDestinationTest2)
{
  UMLClass class1 ("class1");
  UMLClass class2 ("class2");
  // Relationship type doesn't matter for this test
  UMLRelationship relate (class1, class2, 0);
  bool test = &relate.getDestination() == &class1;
  ASSERT_EQ (test, false);
}

// Test to check if getting a type works at all
TEST (UMLRelationshipTest, GetTypeTest)
{
  UMLClass class1 ("class1");
  UMLClass class2 ("class2");
  UMLRelationship relate (class1, class2, 0);
  ASSERT_EQ (relate.getType() == aggregation, true);
}

// Test to check if setting a type works at all
TEST (UMLRelationshipTest, SetTypeTest)
{
  UMLClass class1 ("class1");
  UMLClass class2 ("class2");
  UMLRelationship relate (class1, class2, 0);
  relate.setType (composition);
  ASSERT_EQ (relate.getType() == composition, true);
}

// Make and set relationships of each type and see if they hold the correct type
TEST (UMLRelationshipTest, GetAllTypeTest)
{
  UMLClass class1 ("class1");
  UMLClass class2 ("class2");
  UMLRelationship relate (class1, class2, 0);
  ASSERT_EQ (relate.getType() == aggregation, true);
  relate.setType (composition);
  ASSERT_EQ (relate.getType() == composition, true);
  relate.setType (generalization);
  ASSERT_EQ (relate.getType() == generalization, true);
  relate.setType (realization);
  ASSERT_EQ (relate.getType() == realization, true);
}

// Test that sees if all strings are converting to the correct types
TEST (UMLRelationshipTest, StringToTypeTest)
{
  // The classes involved and its type doesn't matter.
  // This is just to have a relationship to test with.
  UMLClass class1 ("class1");
  UMLClass class2 ("class2");
  UMLRelationship relate (class1, class2, 0);

  // Check to see if each string to type call gives the correct type
  ASSERT_EQ (relate.string_to_type ("aggregation"), aggregation)
    << "Aggregation has incorrect string to type";
  ASSERT_EQ (relate.string_to_type ("composition"), composition)
    << "Composition has incorrect string to type";
  ASSERT_EQ (relate.string_to_type ("generalization"), generalization)
    << "Generalization has incorrect string to type";
  ASSERT_EQ (relate.string_to_type ("realization"), realization)
    << "Realization has incorrect string to type";
}

// ****************************************************

// Tests for UMLFile
// **************************

// TO BE IMPLEMENTED: File creation/deletion.

// If working properly, components should be added to the data model based on JSON
TEST (UMLFileTest, AddComponentsTest)
{
  // Start with JSON string, add classes and relationships based on the JSON
  json j =
        "{\"classes\":[{\"fields\":[{\"name\":\"test\",\"type\":\"int\"}],\"methods\":[{\"name\":\"ff\",\"params\":[{\"name\":\"something\",\"type\":\"something\"}],\"return_type\":\"string\"}],\"name\":\"fish2\",\"position_x\":0,\"position_y\":0},{\"fields\":[],\"methods\":[],\"name\":\"test\",\"position_x\":0,\"position_y\":0}],\"relationships\":[{\"destination\":\"test\",\"source\":\"fish2\",\"type\":\"aggregation\"}]}"_json;
  UMLData data;
  UMLFile file ("test.json");
  file.addClasses (data, j);
  file.addRelationships (data, j);
  // After adding, the JSON should be equal within UMLData.
  ASSERT_EQ (j, data.getJson())
    << "JSON generated from UMLFile is not equivalent to JSON string";

  // Test compared to equivalent data added normally
  UMLData data2;
  data2.addClass ("fish2");
  data2.addClass ("test");
  data2.addClassAttribute ("fish2", std::make_shared<UMLField> ("test", "int"));
  auto m =
    std::make_shared<UMLMethod> ("ff", "string", std::list<UMLParameter>{});
  data2.addClassAttribute ("fish2", m);
  data2.addParameter ("fish2", m, "something", "something");
  data2.addRelationship ("fish2", "test", 0);

  // Check for identical classes
  auto classes1 = data.getClasses();
  auto classes2 = data2.getClasses();
  auto class2 = classes2.begin();
  ASSERT_TRUE(std::equal(classes1.begin(), classes1.end(), classes2.begin()));

  // Check for identical relationships
  auto relationship1 = data.getRelationships();
  auto relationship2 = data2.getRelationships();
  ASSERT_TRUE(std::equal(relationship1.begin(), relationship1.end(), relationship2.begin()));
}

// ****************************************************

// Tests for UMLData involving classes
// **************************

// Checks to see if getting a copy of a class has the same name
// TODO: See if it has the same contents. Also see if this method is still necessary.
TEST (UMLDataAddClassTest, AddClassAndGetCopy)
{
  UMLData data;
  data.addClass (UMLClass ("test"));
  ASSERT_EQ ("test", data.getClassCopy ("test").getName());
}

// Shouldn't be able to add a class that already exists
TEST (UMLDataAddClassTest, AddClassThatAlreadyExists)
{
  UMLData data;
  data.addClass (UMLClass ("test"));
  ERR_CHECK (data.addClass (UMLClass ("test")), "Class name already exists");
}

// Shouldn't be able to remove a class that doesn't exist
TEST (UMLDataRemoveClassTest, RemoveClassThatDoesntExist)
{
  UMLData data;
  ERR_CHECK (data.deleteClass ("test"), "Class not found");
}

// Renaming the class in the data model should = the operation in UMLClass
TEST (UMLDataRenameClassTest, RenameAClassTest)
{
  UMLData data;
  string oldName;
  string updatedName;
  oldName = "test";
  updatedName = "testtest";
  data.addClass (oldName);
  data.changeClassName (oldName, updatedName);
  ASSERT_EQ (updatedName, updatedName);
}

// Shouldn't be allowed to rename a class to one that already exists in the data model
TEST (UMLDataRenameClassTest, RenameClassIntoClassThatAlreadyExists)
{
  UMLData data;
  data.addClass ("test");
  data.addClass ("test2");
  ERR_CHECK (data.changeClassName ("test", "test2"),
             "Class name already exists");
}

// ****************************************************

// Tests for UMLData involving attributes (method/field)
// **************************

// Checks to see if adding method in UMLData works.
// TODO: Clean up variable names.
TEST (UMLDataAttributeTest, AddMethodTest)
{
  UMLData data;
  data.addClass ("test");
  UMLMethod attribute ("hastest", "type", std::list<UMLParameter>{});
  data.addClassAttribute ("test", attribute);
  for (auto attr : data.getClassAttributes ("test"))
  {
    if (attr->getAttributeName() == "hastest")
    {
      ASSERT_EQ (attr->getAttributeName(), "hastest");
    }
  }
}

// Checks to see if adding a field in UMLData works.
// TODO: Clean up variable names.
TEST (UMLDataAttributeTest, AddFieldTest)
{
  UMLData data;
  data.addClass ("test");
  UMLField attribute ("hastest", "type");
  data.addClassAttribute ("test", attribute);
  for (auto attr : data.getClassAttributes ("test"))
  {
    if (attr->getAttributeName() == "hastest")
    {
      ASSERT_EQ (attr->getAttributeName(), "hastest");
    }
  }
}

// Checks to see if changing the name of a field in UMLData works.
// TODO: Clean up variable names.
TEST (UMLDataAttributeTest, ChangeMethodNameTest)
{
  bool hasTestGone;
  hasTestGone = true;
  bool newHasTestPresent;
  newHasTestPresent = false;

  UMLData data;
  data.addClass ("test");
  UMLMethod attribute ("hastest", "type", std::list<UMLParameter>{});
  data.addClassAttribute ("test", attribute);
  data.changeAttributeName ("test", "hastest", "newHasTest");

  for (auto attr : data.getClassAttributes ("test"))
  {
    if (attr->getAttributeName() == "hastest")
    {
      hasTestGone = false;
    }
    if (attr->getAttributeName() == "newHasTest")
    {
      newHasTestPresent = true;
    }
  }
  ASSERT_EQ (hasTestGone, newHasTestPresent);
}

// Checks to see if changing the name of a field in UMLData works.
// TODO: Clean up variable names.
TEST (UMLDataAttributeTest, ChangeFieldNameTest)
{
  bool hasTestGone;
  hasTestGone = true;
  bool newHasTestPresent;
  newHasTestPresent = false;

  UMLData data;
  data.addClass ("test");
  UMLField attribute ("hastest", "type");
  data.addClassAttribute ("test", attribute);
  data.changeAttributeName ("test", "hastest", "newHasTest");

  for (auto attr : data.getClassAttributes ("test"))
  {
    if (attr->getAttributeName() == "hastest")
    {
      hasTestGone = false;
    }
    if (attr->getAttributeName() == "newHasTest")
    {
      newHasTestPresent = true;
    }
  }
  ASSERT_EQ (hasTestGone, newHasTestPresent);
}

// Checks if an error occurs when you attempt to remove a class attribute that isn't owned by the class.
TEST (UMLDataAttributeTest, RemovingNonExistantAttribute)
{
  UMLData data;
  data.addClass ("test");
  UMLAttribute attribute ("testAttribute");
  ERR_CHECK (data.removeClassAttribute ("test", "testAttribute"),
             "Attribute does not exist");
}

// ****************************************************

// Tests for UMLData involving relationships
// **************************

// Basic check to see if adding a relationship to the data model works.
// It should appear in the vector and have the same source, destination, and type.
TEST (UMLDataRelationshipTest, AddingRelationshipTest)
{
  bool haveRelationship = false;
  UMLData data;
  data.addClass ("test");
  data.addClass ("test1");
  // Relationship type doesn't matter for this test
  data.addRelationship ("test", "test1", 0);

  vector<UMLRelationship> rel = data.getRelationships();
  // Loop through vector to find proper relationship
  for (auto i = rel.begin(); i != rel.end(); ++i)
  {
    // Check and see if the valid relationship was added
    if (i->getSource().getName() == "test" &&
        i->getDestination().getName() == "test1" &&
        i->getType() == aggregation)
    {
      haveRelationship = true;
    }
  }

  // Relationship should exist
  ASSERT_EQ (haveRelationship, true);
  // Only one relationship should have been added
  ASSERT_EQ (rel.size(), std::size_t (1));
}

// Error check to see if adding invalid types causes a throw.
// Correct exceptions to see if it's doing a proper throw.
// Also see if it's possible to change this so it doesn't use magic numbers.
TEST (UMLDataRelationshipTest, AddingInvalidType)
{
  UMLData data;

  data.addClass ("test");
  data.addClass ("test1");
  // Relationship type shouldn't be over 3
  ERR_CHECK (data.addRelationship ("test", "test1", 4), "Invalid type");

  data.addClass ("test2");
  data.addClass ("test3");
  // Relationship type shouldn't be less than 0
  ERR_CHECK (data.addRelationship ("test2", "test3", -1), "Invalid type");
}

// Error check to see if adding self inheritance causes an error.
// Correct exceptions to see if it's doing a proper throw.
TEST (UMLDataRelationshipTest, AddingSelfInheritance)
{
  UMLData data;

  data.addClass ("test");
  data.addClass ("test1");
  // Cannot have self-generalization or self-realization
  ERR_CHECK (
    data.addRelationship ("test", "test", 2),
    "Cannot have self-relationship of generalizations or realizations");
  ERR_CHECK (
    data.addRelationship ("test1", "test1", 3),
    "Cannot have self-relationship of generalizations or realizations");
}

// Error check to see if adding multiple compositions causes an error.
// Correct exceptions to see if it's doing a proper throw.
// Also check and see if this actually needs to be relaxed.
TEST (UMLDataRelationshipTest, AddingMultipleCompositions)
{
  UMLData data;

  data.addClass ("test");
  data.addClass ("test1");
  data.addClass ("test2");
  data.addRelationship ("test", "test1", 1);
  // Cannot be the destination of multiple compositions
  ERR_CHECK (data.addRelationship ("test2", "test1", 1),
             "Class can not be the destination for more than one composition");
}

// Sees if deleting a relationship works.
// When a relationship is deleted, it shouldn't be in UMLData's vector.
TEST (UMLDataRelationshipTest, DeletingRelationshipTest)
{
  bool haveRelationship = false;
  UMLData data;
  data.addClass ("test");
  data.addClass ("test1");
  // Relationship type doesn't matter for this test
  data.addRelationship ("test", "test1", 0);
  data.deleteRelationship ("test", "test1");

  vector<UMLRelationship> rel = data.getRelationships();
  // Loop through vector to find proper relationship
  for (auto i = rel.begin(); i != rel.end(); ++i)
  {
    // Check and see if the valid relationship still exists
    if (i->getSource().getName() == "test" &&
        i->getDestination().getName() == "test1" &&
        i->getType() == aggregation)
    {
      haveRelationship = true;
    }
  }

  // Relationship should be deleted
  ASSERT_EQ (haveRelationship, false);

  // Vector should now be empty
  ASSERT_EQ (rel.size(), std::size_t (0));
}

// Makes sure that you can't delete a relationship that doesn't exist.
// Find some way to read what is thrown for the sake of proper error checking.
TEST (UMLDataRelationshipTest, DeletingNonexistentRelationship)
{
  UMLData data;

  // Attempt to delete relationship that does not exist
  ERR_CHECK (data.deleteRelationship ("test", "test"), "Class not found");

  // Same as above, but with the class existing and two different classes
  data.addClass ("test");
  data.addClass ("test1");
  ERR_CHECK (data.deleteRelationship ("test", "test"),
             "Relationship not found");
  ERR_CHECK (data.deleteRelationship ("test", "test1"),
             "Relationship not found");
}

// Sees if getting the proper relationship type works after adding a relationship.
TEST (UMLDataRelationshipTest, GetRelationshipTypeTest)
{
  bool foundRelationship = false;
  UMLData data;
  data.addClass ("test");
  data.addClass ("test1");
  // Check for aggregation
  data.addRelationship ("test", "test1", 0);
  ASSERT_EQ (data.getRelationshipType ("test", "test1"), "aggregation");
  data.deleteRelationship ("test", "test1");
  // Check for composition
  data.addRelationship ("test", "test1", 1);
  ASSERT_EQ (data.getRelationshipType ("test", "test1"), "composition");
  data.deleteRelationship ("test", "test1");
  // Check for generalization
  data.addRelationship ("test", "test1", 2);
  ASSERT_EQ (data.getRelationshipType ("test", "test1"), "generalization");
  data.deleteRelationship ("test", "test1");
  // Check for realization
  data.addRelationship ("test", "test1", 3);
  ASSERT_EQ (data.getRelationshipType ("test", "test1"), "realization");
}

// Sees if getting a vector of relationships by class works.
// Extend test to have a case where the two vectors should NOT be the same.
TEST (UMLDataRelationshipTest, GetRelationshipByClassTest)
{
  UMLData data;

  data.addClass ("test");
  data.addClass ("test1");
  data.addClass ("test2");
  data.addRelationship ("test", "test1", 0);
  data.addRelationship ("test", "test2", 0);

  // Vector obtained and relationship vector should be equivalent
  vector<UMLRelationship> vector1 = data.getRelationshipsByClass ("test");
  vector<UMLRelationship> vector2 = data.getRelationships();

  // Check for identical vector size
  ASSERT_EQ (vector1.size(), vector2.size());
  // Check for identical vector contents
  for (size_t i = 0; i < vector1.size(); ++i)
  {
    ASSERT_EQ (vector1[i].getSource().getName(),
               vector2[i].getSource().getName());
    ASSERT_EQ (vector1[i].getDestination().getName(),
               vector2[i].getDestination().getName());
    ASSERT_EQ (vector1[i].getType(), vector2[i].getType());
  }
}

// Sees if changing the relationship type works at all.
TEST (UMLDataRelationshipTest, ChangeRelationshipTypeTest)
{
  UMLData data;

  data.addClass ("test");
  data.addClass ("test1");

  // Test to see if relationship was changed
  data.addRelationship ("test", "test1", 0);
  data.changeRelationshipType ("test", "test1", 1);
  ASSERT_EQ (data.getRelationship ("test", "test1").getType(), composition);
}

// Tests all errors that currently exist for changing a relationship type.
TEST (UMLDataRelationshipTest, ChangeRelationshipTypeErrors)
{
  UMLData data;

  data.addClass ("test");
  data.addClass ("test1");
  data.addClass ("test2");

  data.addRelationship ("test", "test1", 0);
  // Test for bounds
  ERR_CHECK (data.changeRelationshipType ("test", "test1", 4), "Invalid type");
  ERR_CHECK (data.changeRelationshipType ("test", "test1", -1), "Invalid type");
  // Test for self-inheritance
  data.addRelationship ("test", "test", 0);
  ERR_CHECK (
    data.changeRelationshipType ("test", "test", 2),
    "Cannot have self-relationship of generalizations or realizations");
  ERR_CHECK (
    data.changeRelationshipType ("test", "test", 3),
    "Cannot have self-relationship of generalizations or realizations");
  // Test for multiple compositions
  data.addRelationship ("test2", "test1", 1);
  ERR_CHECK (data.changeRelationshipType ("test", "test1", 1),
             "Class can not be the destination for more than one composition");
}

// Checks to see if JSON is being generated properly.
TEST (UMLDataJsonTest, ReturnedJSONIsCorrect)
{
  json j =
    "{\"classes\":[{\"fields\":[{\"name\":\"test\",\"type\":\"int\"}],\"methods\":[{\"name\":\"ff\",\"params\":[{\"name\":\"something\",\"type\":\"something\"}],\"return_type\":\"string\"}],\"name\":\"fish2\",\"position_x\":0,\"position_y\":0},{\"fields\":[],\"methods\":[],\"name\":\"test\",\"position_x\":0,\"position_y\":0}],\"relationships\":[{\"destination\":\"test\",\"source\":\"fish2\",\"type\":\"aggregation\"}]}"_json;
  UMLData data;
  data.addClass ("fish2");
  data.addClass ("test");
  data.addClassAttribute ("fish2", std::make_shared<UMLField> ("test", "int"));
  auto m =
    std::make_shared<UMLMethod> ("ff", "string", std::list<UMLParameter>{});
  data.addClassAttribute ("fish2", m);
  data.addParameter ("fish2", m, "something", "something");
  data.addRelationship ("fish2", "test", 0);

  ASSERT_EQ (j, data.getJson());
}

// ****************************************************

// Tests for undo and redo (UMLDataHistory)
// **************************

// Test to see if undoing the add of a single class works.
TEST (UndoRedoTest, UndoAfterAddOneClassTest)
{
  UMLData data;
  UMLDataHistory history (data);

  //collect json object beforre undo for comparison
  json beforeClassAddUndo = data.getJson();

  //save history before change
  history.save(data);
  data.addClass ("TestClass");

  //undo change
  data = history.undo();

  //collect new json object after undo
  json afterClassAddUndo = data.getJson();

  ASSERT_EQ (beforeClassAddUndo, afterClassAddUndo);
}

// Test to see if undoing the add of a two classes works.
TEST (UndoRedoTest, UndoAfterAddTwoClassesTest)
{
  UMLData data;
  UMLDataHistory history (data);

  data.addClass ("TestClass");
  history.save(data);

  // Collect json object beforre undo for comparison1
  json beforeClassAddUndo = data.getJson();

 
  data.addClass ("TestClass2");
  history.save(data);

  // Undo change
  data = history.undo();

  // Collect new json object after undo
  json afterClassAddUndo = data.getJson();

  ASSERT_EQ (beforeClassAddUndo, afterClassAddUndo);
}

// Undoing after adding a class should remove the class.
TEST (UndoRedoTest, UndoAfterAddClassMethod)
{
  UMLData data;
  UMLDataHistory history (data);

  data.addClass ("TestClass");
  history.save(data);

  data.addClass ("TestClass2");
  history.save(data);

  // Collect json object beforre undo for comparison1
  json beforeClassAddUndo = data.getJson();

  data.addClassAttribute (
    "TestClass",
    std::make_shared<UMLMethod> ("test", "int", std::list<UMLParameter>{}));
  history.save(data);
  // Undo change
  data = history.undo();

  // Collect new json object after undo
  json afterClassAddUndo = data.getJson();

  ASSERT_EQ (beforeClassAddUndo, afterClassAddUndo);
}

// Undoing then redoing it back should equal the same thing.
TEST (UndoRedoTest, RedoAfterClassDeletedUndo)
{
  UMLData data;
  UMLDataHistory history (data);

  data.addClass ("TestClass");
  history.save(data);

  data.addClass ("TestClass2");
  history.save(data);

  data.deleteClass ("TestClass");
  history.save(data);

  // Collect json object beforre undo for comparison1
  json beforeClassAddUndo = data.getJson();

  // Undo change
  data = history.undo();

  // Redo change
  data = history.redo();

  // Collect new json object after undo
  json afterClassAddUndo = data.getJson();

  ASSERT_EQ (beforeClassAddUndo, afterClassAddUndo);
}

// ****************************************************

// Tests for CLIView (CLIView.cpp)
// **************************

/*
// Testing the bool that determines whether the output is printed to the console or pushed to the output queue.
TEST() // <---- I'm not sure what parameters are supposed to go in there.
{
  CLIViewProxy Interface;
  bool preStackPush = Interface.get_print_bool();
  
  Interface.push_input("Boop!");
  bool postStackPush = Interface.get_print_bool();

  ASSERT_EQ(preStackPush, postStackPush);
}

// get_user_input()

TEST()
{
  CLIViewProxy Interface;
  string ds = "DARK SOULS!!!!!";
  
  Interface.push_input(ds);
  Interface.display_message("What\'s your favorite game?\n");
  string dsCopy = Interface.get_user_input();
  
  ASSERT_EQ(ds, dsCopy);
}

TEST()
{
  CLIViewProxy Interface;
  long unsigned int num = 69;
  
  Interface.push_input(num);
  Interface.display_message("Type a number: \n");
  string numCopy = Interface.get_user_input();

  ASSERT_EQ(numCopy, "69");
}


// user_int_input()

TEST()
{
  CLIViewProxy Interface;
  long unsigned int num = 69;
  
  Interface.push_input(num);
  Interface.display_message("Type a number: \n");
  int numCopy = Interface.get_user_input();

  ASSERT_EQ(numCopy, num);
}

TEST()
{
  CLIViewProxy Interface;
  string fakeNum = "Lol rekt!";
  
  Interface.push_input(fakeNum);
  Interface.display_message("Type a number: \n");
  int num = Interface.get_user_input();
  
  ASSERT_EQ(num, -1);
}



*/


// ****************************************************


// Tests for CLI (CLI.CPP)
// **************************

// Need a way to grab the stream of characters. (DONE!)

//Tab completion tests
/*
TEST()
{
  CLI Controller;
  CLIViewProxy ViewProxy; //Oh, shit. I actually have to access the CLI's instance of the CLIView. Fuck.

  ViewProxy.push_input("list_c\t");
  Controller.Interface = ViewProxy;

  Controller.cli_menu();
  ViewProxy = Controller.Interface;

  string test = ViewProxy.most_recent_output();

  ASSERT_EQ(test, "You have no classes.\n");
}

TEST()
{
  // Copy and paste the above test once it's fixed. Then change it to test for the list_relationships tab completion
}
*/