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
#include "cli/cli.h"
#include "cli/clifilesession.h"

#include "include/UMLCLI.hpp"
#include "include/UMLClass.hpp"
#include "include/UMLData.hpp"
#include "include/UMLDataHistory.hpp"
#include "include/UMLMethod.hpp"
#include "include/UMLParameter.hpp"
#include "include/UMLRelationship.hpp"
#include "include/CLITest.hpp"

#include <iostream>
#include <memory>
#include <string>

using namespace std;
using namespace cli;

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
CLI (## WIP ##)
Server (## WIP ##)
*/

// ****************************************************


/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                      Tests for UMLClass                      |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/


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

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                    Tests for UMLAttribute                    |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

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

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                      Tests for UMLField                      |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

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


/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                     Tests for UMLMethod                      |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

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

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                    Tests for UMLParameter                    |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

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

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                   Tests for UMLRelationship                  |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

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

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                      Tests for UMLFile                       |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

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

// Saving and loading a file should work
TEST (UMLFileTest, SaveLoadTest)
{
  remove("test.json");
  // Start with JSON string, add classes and relationships based on the JSON
  json j =
        "{\"classes\":[{\"fields\":[{\"name\":\"test\",\"type\":\"int\"}],\"methods\":[{\"name\":\"ff\",\"params\":[{\"name\":\"something\",\"type\":\"something\"}],\"return_type\":\"string\"}],\"name\":\"fish2\",\"position_x\":0,\"position_y\":0},{\"fields\":[],\"methods\":[],\"name\":\"test\",\"position_x\":0,\"position_y\":0}],\"relationships\":[{\"destination\":\"test\",\"source\":\"fish2\",\"type\":\"aggregation\"}]}"_json;
  UMLData data;
  UMLFile file_old ("test.json");
  file_old.addClasses (data, j);
  file_old.addRelationships (data, j);

  // Save file to json
  file_old.save(data);
  // Load json into a new UMLFile and put the contents into UMLData and check they're the same
  UMLFile file ("test.json");
  data = file.load();

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

  remove("test.json");
}

// Adding a parameter to a method that would cause overloading rules to fail should not work
TEST (CLITest, ParameterOverloadAdd)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Make method with one paramter
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");

  // Make method with zero parameters
  test.user_input(cli, oss, "method add bob int method");

  // Try to add a parameter to the second method of the same type as the first and it should fail
  test.user_input(cli, oss, "method select bob method 2");
  test.user_input(cli, oss, "method parameter add int param");

  auto attr = interface.return_model().getClassCopy("bob").getAttributes();
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr[1])->getParam();
  ASSERT_EQ(0, paramList.size());

  // Try to add a parameter to the second method of a different type but same name as the first and it should succede
  test.user_input(cli, oss, "method parameter add string param");

  attr = interface.return_model().getClassCopy("bob").getAttributes();
  paramList = std::dynamic_pointer_cast<UMLMethod>(attr[1])->getParam();
  ASSERT_EQ(1, paramList.size());
}

// ****************************************************

/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|                      Tests for UMLData                       |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

// Tests involving classes
// **************************

// Checks to see if getting a copy of a class has the same name
TEST (UMLDataAddClassTest, AddClassAndGetCopy)
{
  UMLData data;
  UMLClass testClass = UMLClass("test");
  data.addClassObject(testClass);

  attr_ptr attribute = std::make_shared<UMLField>("attrTest", "type");
  data.addClassAttribute("test", attribute);

  ASSERT_EQ(testClass, data.getClassCopy ("test"));
}

// Shouldn't be able to add a class that already exists
TEST (UMLDataAddClassTest, AddClassThatAlreadyExists)
{
  UMLData data;
  data.addClassObject(UMLClass ("test"));
  ERR_CHECK(data.addClassObject (UMLClass ("test")), "Class name already exists");
}

// Should be able to delete a class and then check with delete that it doesn't exist
TEST (UMLRemoveClassTest, RemoveClass) 
{
  UMLData data;
  data.addClassObject(UMLClass("test"));
  data.deleteClass("test");
  ERR_CHECK (data.deleteClass("test"), "Class not found");
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

// Tests involving attributes (method/field)
// **************************

// Checks to see if adding a method works (no parameters).
TEST(UMLDataAttributeTest, AddMethodTestNoParams)
{
  UMLData data;
  data.addClass("test");
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});

  std::list<UMLParameter> paramList = method->getParam();

  data.addClassAttribute("test", method);
  bool check = data.doesMethodExist("test", "testMethod", paramList);
  
  ASSERT_EQ(check, true);
}

// Checks to see if adding a method works (with parameters).
TEST(UMLDataAttributeTest, AddMethodTestWithParams)
{
  UMLData data;
  data.addClass("test");
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{
    UMLParameter("p1", "int"), UMLParameter("p2", "string")});

  std::list<UMLParameter> paramList = method->getParam();

  data.addClassAttribute("test", method);
  bool check = data.doesMethodExist("test", "testMethod", paramList);
  
  ASSERT_EQ(check, true);
}

// Checks to see if adding a field works
TEST(UMLDataAttributeTest, AddFieldTest)
{
  UMLData data;
  data.addClass("test");
  auto field = std::make_shared<UMLField>("testField", "type");
  
  data.addClassAttribute("test", field);
  bool check = data.doesFieldExist("test", "testField");

  ASSERT_EQ(check, true);
}


// Checks to see if deleting methods and fields works properly, along with any potential overload cases.
TEST (UMLDataAttributeTest, DeleteMethodFieldTest)
{
  UMLData data;
  data.addClass ("test");

  // Create field
  auto field = std::make_shared<UMLField> ("testField", "type"); 
  
  // Create first method, has params
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  method->addParam(param1);

  // Create second method that is an overload, no params
  auto method2 = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});

  // Add field and both methods to "test"
  data.addClassAttribute ("test", field);
  data.addClassAttribute ("test", method);
  data.addClassAttribute ("test", method2);

  // Verify that deleting field works
  EXPECT_NO_THROW(data.removeClassAttribute("test", field));
  for (auto attr : data.getClassAttributes ("test")) { 
    // Field should no longer exist
    ASSERT_NE(attr->getAttributeName(), "testField");
  }

  // Verify that deleting an overloaded method works properly
  EXPECT_NO_THROW(data.removeClassAttribute("test", method2));
  for (auto attr : data.getClassAttributes ("test")) { 
    // Only method left should be testMethod
    ASSERT_EQ(attr->getAttributeName(), "testMethod");
    // Check that the correct param is there
    for (auto param : std::dynamic_pointer_cast<UMLMethod>(attr)->getParam()) {
      ASSERT_EQ(param.getName(), "testParam");
      ASSERT_EQ(param.getType(), "type");
    }
  }

  // Verify deleting a method on its own works properly
  EXPECT_NO_THROW(data.removeClassAttribute("test", method));
  // Vector should be empty now
  ASSERT_EQ(data.getClassAttributes("test").empty(), true);
}

// Checks to see if changing the name of a method in UMLData works.
TEST (UMLDataAttributeTest, ChangeMethodNameTest)
{
  bool hasTestGone;
  hasTestGone = true;
  bool newHasTestPresent;
  newHasTestPresent = false;

  UMLData data;
  data.addClass ("test");
  auto method = std::make_shared<UMLMethod> ("hastest", "type", std::list<UMLParameter>{});
  data.addClassAttribute ("test", method);
  
  data.changeAttributeName ("test", method, "newHasTest");

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

  auto field = std::make_shared<UMLField> ("hastest", "type"); 
  data.addClassAttribute ("test", field);
  data.changeAttributeName ("test", field, "newHasTest");

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

// Checks to see if changing the type of a method in UMLData works.
TEST (UMLDataAttributeTest, ChangeMethodTypeTest)
{
  bool hasTestGone;
  hasTestGone = true;
  bool newHasTestPresent;
  newHasTestPresent = false;

  UMLData data;
  data.addClass ("test");
  auto method = std::make_shared<UMLMethod> ("hastest", "type", std::list<UMLParameter>{});
  data.addClassAttribute ("test", method);
  data.changeAttributeType (method, "type2");

  for (auto attr : data.getClassAttributes ("test"))
  {
    if (attr->getType() == "type")
    {
      hasTestGone = false;
    }
    if (attr->getType() == "type2")
    {
      newHasTestPresent = true;
    }
  }
  ASSERT_EQ (hasTestGone, newHasTestPresent);
}

// Checks to see if changing the type of a field in UMLData works.
TEST (UMLDataAttributeTest, ChangeFieldTypeTest)
{
  bool hasTestGone;
  hasTestGone = true;
  bool newHasTestPresent;
  newHasTestPresent = false;

  UMLData data;
  data.addClass ("test");
  auto field = std::make_shared<UMLField> ("hastest", "type"); 
  data.addClassAttribute ("test", field);
  data.changeAttributeType (field, "type2");

  for (auto attr : data.getClassAttributes ("test"))
  {
    if (attr->getType() == "type")
    {
      hasTestGone = false;
    }
    if (attr->getType() == "type2")
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
  attr_ptr attribute = std::make_shared<UMLAttribute>("testAttribute"); 
  ERR_CHECK (data.removeClassAttribute ("test", attribute), "Attribute not found");
}

// Checks if an error occurs when you attempt to remove a class method or field that isn't owned by the class.
TEST (UMLDataAttributeTest, RemovingNonExistantMethodOrField)
{
  UMLData data;
  data.addClass ("test");
  auto field = std::make_shared<UMLField> ("testField", "type"); 
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  // These should not be removed since they aren't found within the data model itself
  ERR_CHECK (data.removeClassAttribute ("test", field),
             "Attribute not found");
  ERR_CHECK (data.removeClassAttribute ("test", method),
             "Attribute not found");
}

// ****************************************************



// Tests involving parameters
// **************************

// Tests to see if adding a parameter works, as well as overload check in the case of one parameter.
TEST (UMLDataParameterTest, AddParameterTest1) {
  UMLData data;
  data.addClass ("test");
  
  // Create method 1, has params
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  method->addParam(param1);

  // Create second method that is an overload, no params
  auto method2 = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});

  // Add both methods to test
  data.addClassAttribute ("test", method);
  data.addClassAttribute ("test", method2);

  // Should throw if the type signature becomes the same when adding a parameter.
  // Parameter name should not affect this error.
  ERR_CHECK(data.addParameter("test", method2, "testParam2", "type"), 
    "This parameter cannot be created, as this would create duplicate methods.");
  ERR_CHECK(data.addParameter("test", method2, "testParam", "type"), 
    "This parameter cannot be created, as this would create duplicate methods.");
  
  // Shouldn't throw if the type signature is different.
  ASSERT_NO_THROW(data.addParameter("test", method2, "testParam", "type2"));
  
  // Check to see if parameter was added properly
  UMLParameter testParamCopy("testParam", "type2");
  for (auto attr : data.getClassAttributes ("test")) { 
    for (auto param : std::dynamic_pointer_cast<UMLMethod>(attr)->getParam()) {
      if (param.getType() == "type2") {
        ASSERT_EQ(param, testParamCopy);
      }
    }
  }
}

// Tests cases involving adding a parameter when there is overloads involving more than one parameter.
TEST (UMLDataParameterTest, AddParameterTest2) {
  UMLData data;
  data.addClass ("test");
  
  // Create method 1, has 2 params
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  auto param2 = UMLParameter("testParam2", "type2");
  method->addParam(param1);
  method->addParam(param2);

  // Create second method that is an overload, 1 param
  auto method2 = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1Copy = UMLParameter("testParam", "type");
  method2->addParam(param1Copy);

  // Add both methods to test
  data.addClassAttribute ("test", method);
  // There should not be an issue with adding this method
  ASSERT_NO_THROW(data.addClassAttribute ("test", method2));

  // Should throw if the type signature becomes the same when adding a parameter.
  // Parameter name should not affect this error.
  ERR_CHECK(data.addParameter("test", method2, "testParam2", "type2"), 
    "This parameter cannot be created, as this would create duplicate methods.");
  ERR_CHECK(data.addParameter("test", method2, "testParam3", "type2"), 
    "This parameter cannot be created, as this would create duplicate methods.");

  // Shouldn't throw if the type signature is different.
  ASSERT_NO_THROW(data.addParameter("test", method2, "testParam3", "type3"));

  // Check to see if parameter was added properly
  UMLParameter testParamCopy("testParam3", "type3");
  for (auto attr : data.getClassAttributes ("test")) { 
    for (auto param : std::dynamic_pointer_cast<UMLMethod>(attr)->getParam()) {
      if (param.getType() == "type3") {
        ASSERT_EQ(param, testParamCopy);
      }
    }
  }
}

// Tests if deleting a parameter works properly.
TEST (UMLDataParameterTest, DeleteParameterTest1) {
  UMLData data;
  data.addClass ("test");
  
  // Create method with a param
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  method->addParam(param1);

  // Add method to data
  data.addClassAttribute ("test", method);

  // Delete method 
  EXPECT_NO_THROW(data.deleteParameter("test", method, "testParam"));
  // Method should no longer have any parameters
  EXPECT_TRUE(method->getParam().empty());
}

// Tests if deleting a parameter works when there is multiple parameters.
TEST (UMLDataParameterTest, DeleteParameterTest2) {
  UMLData data;
  data.addClass ("test");
  
  // Create method with a param
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  auto param2 = UMLParameter("testParam2", "type2");
  method->addParam(param1);
  method->addParam(param2);

  // Add method to data
  data.addClassAttribute ("test", method);

  // Delete method 
  EXPECT_NO_THROW(data.deleteParameter("test", method, "testParam"));
  // Check to see if state of parameters is what it should be
  EXPECT_EQ(method->getParam().begin()->getName(), "testParam2");
  EXPECT_EQ(method->getParam().begin()->getType(), "type2");
}

// Tests if deleting a parameter will show an error if it would cause an overload conflict.
TEST (UMLDataParameterTest, DeleteParameterTest3) {
  UMLData data;
  data.addClass ("test");
  
  // Create method 1, has 2 params
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  auto param2 = UMLParameter("testParam2", "type2");
  method->addParam(param1);
  method->addParam(param2);

  // Create second method that is an overload, 1 param
  auto method2 = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1Copy = UMLParameter("testParam", "type");
  method2->addParam(param1Copy);

  // Add both methods to test
  data.addClassAttribute ("test", method);
  data.addClassAttribute ("test", method2);

  // Should not be able to delete this parameter, as it would cause overload break
  ERR_CHECK(data.deleteParameter("test", method, "testParam2"), "This parameter cannot be deleted now, as it would cause duplicate methods to exist.")
  // Should be able to delete this parameter, as it wouldn't cause overload break
  ASSERT_NO_THROW(data.deleteParameter("test", method, "testParam"));
}

// Tests to see if renaming a parameter works at a basic level.
TEST (UMLDataParameterTest, RenameParameterTest1) {
  UMLData data;
  data.addClass ("test");
  
  // Create method with a param
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  method->addParam(param1);

  // Add method to data
  data.addClassAttribute ("test", method);

  // Renaming this parameter should not cause problems
  ASSERT_NO_THROW(data.changeParameterName(method, "testParam", "testParam2"));
  for (auto attr : data.getClassAttributes ("test")) { 
    for (auto param : std::dynamic_pointer_cast<UMLMethod>(attr)->getParam()) {
      ASSERT_EQ(param.getName(), "testParam2");
    }
  }
}

// Tests to see if changing a parameter type works at a basic level.
TEST (UMLDataParameterTest, ChangeParameterTypeTest1) {
  UMLData data;
  data.addClass ("test");
  
  // Create method with a param
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  method->addParam(param1);

  // Add method to data
  data.addClassAttribute ("test", method);

  // Changing this parameter type should not cause problems
  ASSERT_NO_THROW(data.changeParameterType("test", method, "testParam", "type2"));
  for (auto attr : data.getClassAttributes ("test")) { 
    for (auto param : std::dynamic_pointer_cast<UMLMethod>(attr)->getParam()) {
      ASSERT_EQ(param.getType(), "type2");
    }
  }
}

// Tests to see if renaming a parameter works in a method with multiple parameters.
TEST (UMLDataParameterTest, RenameParameterTest2) 
{
  UMLData data;
  data.addClass ("test");
  
  // Create method 1, has 2 params
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  auto param2 = UMLParameter("testParam2", "type2");
  method->addParam(param1);
  method->addParam(param2);

  // Add method to data
  data.addClassAttribute ("test", method);

  // Cannot rename to same name as another parameter
  ERR_CHECK(data.changeParameterName(method, "testParam", "testParam2"), "That name is already taken.");
  // Should be able to change to a different name
  ASSERT_NO_THROW(data.changeParameterName(method, "testParam", "testParam3"));

  // Check to see if the proper parameter was renamed within shared_ptr
  for (auto param : method->getParam()) {
    if (param.getType() == "type") {
      ASSERT_EQ(param.getName(), "testParam3");
    }
  }
}

// Tests to see if overload checking with renaming parameters works properly.
TEST (UMLDataParameterTest, RenameParameterTest3) 
{
  UMLData data;
  data.addClass ("test");
  
  // Create method 1, has 1 param
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  method->addParam(param1);

  // Create second method that is an overload, 1 param
  auto method2 = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1Copy = UMLParameter("testParam2", "type2");
  method2->addParam(param1Copy);

  // Renaming a parameter should never cause overload errors, even if the names are identical
  ASSERT_NO_THROW(data.changeParameterName(method, "testParam", "testParam2"));

  // Check to see if the proper parameter was renamed within shared_ptr
  for (auto param : method->getParam()) {
    if (param.getType() == "type") {
      ASSERT_EQ(param.getName(), "testParam2");
    }
  }
}

// Tests to see if changing a parameter type works in a method with multiple parameters.
TEST (UMLDataParameterTest, ChangeParameterTypeTest2) 
{
  UMLData data;
  data.addClass ("test");
  
  // Create method 1, has 2 params
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  auto param2 = UMLParameter("testParam2", "type2");
  method->addParam(param1);
  method->addParam(param2);

  // Add method to data
  data.addClassAttribute ("test", method);

  // Changing to the same type as something already in the method shouldn't matter at all
  ASSERT_NO_THROW(data.changeParameterType("test", method, "testParam", "type2"));

  // Check to see if the proper parameter had its type changed within shared_ptr
  for (auto param : method->getParam()) {
    if (param.getName() == "testParam") {
      ASSERT_EQ(param.getType(), "type2");
    }
  }
}

// Tests to see if overload checking with changing parameter types works properly.
TEST (UMLDataParameterTest, ChangeParameterTypeTest3) 
{
  UMLData data;
  data.addClass ("test");
  
  // Create method 1, has 1 param
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  method->addParam(param1);

  // Create second method that is an overload, 1 param
  auto method2 = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1Copy = UMLParameter("testParam2", "type2");
  method2->addParam(param1Copy);

  // Add methods to data
  data.addClassAttribute ("test", method);
  data.addClassAttribute ("test", method2);

  // Changing to the same type signature should cause an error
  ERR_CHECK(data.changeParameterType("test", method, "testParam", "type2"), "Parameter type cannot be changed due to conflicts with other overloads");
  // Changing to a different one shouldn't matter
  ASSERT_NO_THROW(data.changeParameterType("test", method, "testParam", "type3"));

  // Check to see if the proper parameter had its type changed within shared_ptr
  for (auto param : method->getParam()) {
    if (param.getName() == "testParam") {
      ASSERT_EQ(param.getType(), "type3");
    }
  }
}

// Tests to see if invalid names are caught by each parameter function
TEST (UMLDataParameterTest, ParameterCatchInvalidNames) {
  string invalidName1 = "_";
  string invalidName2 = "1";
  string invalidName3 = "!";
  string invalidName4 = "a!";

  UMLData data;
  data.addClass ("test");
  
  // Create method, has 1 param
  auto method = std::make_shared<UMLMethod> ("testMethod", "type", std::list<UMLParameter>{});
  auto param1 = UMLParameter("testParam", "type");
  method->addParam(param1);

  // Add methods to data
  data.addClassAttribute ("test", method);

  // Add parameter, param name check
  ERR_CHECK(data.addParameter("test", method, invalidName1, "valid"), "Parameter name is not valid");
  ERR_CHECK(data.addParameter("test", method, invalidName2, "valid"), "Parameter name is not valid");
  ERR_CHECK(data.addParameter("test", method, invalidName3, "valid"), "Parameter name is not valid");
  ERR_CHECK(data.addParameter("test", method, invalidName4, "valid"), "Parameter name is not valid");

  // Add parameter, param type check
  ERR_CHECK(data.addParameter("test", method, "valid", invalidName1), "Parameter type is not valid");
  ERR_CHECK(data.addParameter("test", method, "valid", invalidName2), "Parameter type is not valid");
  ERR_CHECK(data.addParameter("test", method, "valid", invalidName3), "Parameter type is not valid");
  ERR_CHECK(data.addParameter("test", method, "valid", invalidName4), "Parameter type is not valid");

  // Rename parameter check
  ERR_CHECK(data.changeParameterName(method, "testParam", invalidName1), "New parameter name is not valid");
  ERR_CHECK(data.changeParameterName(method, "testParam", invalidName2), "New parameter name is not valid");
  ERR_CHECK(data.changeParameterName(method, "testParam", invalidName3), "New parameter name is not valid");
  ERR_CHECK(data.changeParameterName(method, "testParam", invalidName4), "New parameter name is not valid");

  // Change parameter type check
  ERR_CHECK(data.changeParameterType("test", method, "testParam", invalidName1), "New parameter type name is not valid");
  ERR_CHECK(data.changeParameterType("test", method, "testParam", invalidName2), "New parameter type name is not valid");
  ERR_CHECK(data.changeParameterType("test", method, "testParam", invalidName3), "New parameter type name is not valid");
  ERR_CHECK(data.changeParameterType("test", method, "testParam", invalidName4), "New parameter type name is not valid");
}

// ****************************************************

// Tests involving relationships
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
    "{\"classes\":[{\"fields\":[{\"name\":\"test\",\"type\":\"int\"}],\"methods\":[{\"name\":\"ff\",\"params\":[{\"name\":\"something\",\"type\":\"something\"}],\"return_type\":\"string\"}],\"name\":\"fish2\",\"position_x\":1000,\"position_y\":350},{\"fields\":[],\"methods\":[],\"name\":\"test\",\"position_x\":1000,\"position_y\":350}],\"relationships\":[{\"destination\":\"test\",\"source\":\"fish2\",\"type\":\"aggregation\"}]}"_json;
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


/*
////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
|**************************************************************|
|       Functions for tests for CLI (from test_cli.cpp)        |
|**************************************************************|
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\////////////////////////////////
*/

// Test if help command prints help
TEST (CLITest, HelpCommand)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "help");

  // See if help was displayed 
  ASSERT_NE(test.extract_content(oss).find("Commands available:"), string::npos); 
}

// Functions for CLI class add
// **************************

// Add a class
TEST (CLITest, AddClass)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");

  // See if Bob was added.
  ASSERT_EQ("bob", interface.return_model().getClassCopy("bob").getName());
}

// Add a class with invalid names should fail
TEST (CLITest, AddInvalidClassName)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;

  // Adding different invalid class names
  // start with valid _ character
  test.user_input(cli, oss, "class add _");
  ERR_CHECK (interface.return_model().getClassCopy("_"), "Class not found");

  // start with num
  test.user_input(cli, oss, "class add 1"); 
  ERR_CHECK (interface.return_model().getClassCopy("1"), "Class not found");

  // start with invalid character
  test.user_input(cli, oss, "class add !"); 
  ERR_CHECK (interface.return_model().getClassCopy("!"), "Class not found");

  // contain invalid character
  test.user_input(cli, oss, "class add a!"); 
  ERR_CHECK (interface.return_model().getClassCopy("a!"), "Class not found");
  
}

// Adding a class with existing name should fail
TEST (CLITest, AddDuplicateClass)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  // You can use multiple user_inputs for testing commands.
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "class add bob");

  // Shouldn't be able to add duplicate class, so test for only one bob
  test.user_input(cli, oss, "class delete bob");

  // Shouldn't be able to find bob
  ERR_CHECK (interface.return_model().getClassCopy("bob"), "Class not found");
}



// Tests for CLITest
// **************************

// General test of every component of the CLI test class.

TEST (CLITestTester, GeneralTest) {
  CLITest test;
  stringstream oss;

  // Create a sample menu for testing
  auto rootMenu = make_unique<Menu>("cli");
  Cli cli(move(rootMenu));
  
  ASSERT_NO_THROW(test.user_input(cli, oss, "help"));
}



// Functions for CLI class delete
// **************************

// Delete a class
TEST (CLITest, DeleteClass)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  // You can use multiple user_inputs for testing commands.
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "class delete bob");

  // Shouldn't be able to find bob
  ERR_CHECK (interface.return_model().getClassCopy("bob"), "Class not found");
}

// Deleting a nonexistant class should fail but not crash
TEST (CLITest, DeleteNonexistentClass)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class delete bob");

  // Shouldn't be able to delete class, so if you're still here it didn't crash
  ASSERT_TRUE(true);
}

// Functions for CLI class rename
// **************************

// Rename a class
TEST (CLITest, ClassRename)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "class rename bob test");

  // See if bob was renamed.
  ASSERT_EQ("test", interface.return_model().getClassCopy("test").getName());
  // Shouldn't be able to find bob
  ERR_CHECK (interface.return_model().getClassCopy("bob"), "Class not found");
}

// Renaming an existing class to an invalid name should follow same name rules
TEST (CLITest, ClassRenameToInvalidName)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Test renaming to invalid names
  // Start with valid _ character
  test.user_input(cli, oss, "class rename bob _");   
  ASSERT_EQ("bob", interface.return_model().getClassCopy("bob").getName());
  ERR_CHECK (interface.return_model().getClassCopy("_"), "Class not found");

  // Start with num
  test.user_input(cli, oss, "class rename bob 1"); 
  ASSERT_EQ("bob", interface.return_model().getClassCopy("bob").getName());
  ERR_CHECK (interface.return_model().getClassCopy("1"), "Class not found");

  // Start with invalid character
  test.user_input(cli, oss, "class rename bob ~"); 
  ASSERT_EQ("bob", interface.return_model().getClassCopy("bob").getName());
  ERR_CHECK (interface.return_model().getClassCopy("~"), "Class not found");

  // Contain invalid character
  test.user_input(cli, oss, "class rename bob a!"); 
  ASSERT_EQ("bob", interface.return_model().getClassCopy("bob").getName());
  ERR_CHECK (interface.return_model().getClassCopy("a!"), "Class not found");

  // Rename to duplicate class
  test.user_input(cli, oss, "class add bob2");
  test.user_input(cli, oss, "class rename bob bob2"); 
  ASSERT_EQ("bob", interface.return_model().getClassCopy("bob").getName());
  ASSERT_EQ("bob2", interface.return_model().getClassCopy("bob2").getName());
}

// Functions for CLI Field
// **************************

// Add field to a class
TEST (CLITest, FieldAdd)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  // Add field to class
  test.user_input(cli, oss, "field add bob int field");
  ASSERT_EQ(0, interface.return_model().getClassCopy("bob").findAttribute("field"));
  ASSERT_EQ("field", interface.return_model().getClassCopy("bob").getAttributes()[0]->identifier());
  ASSERT_EQ("field", interface.return_model().getClassCopy("bob").getAttributes()[0]->getAttributeName());
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
}

// Add field to a nonexistant class should fail
TEST (CLITest, FieldAddToNonexistantClass)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Add to nonexistant class should fail
  test.user_input(cli, oss, "field add bob2 int field");
  ERR_CHECK (interface.return_model().getClassCopy("bob2"), "Class not found");
}

// Add field to a class with same name but different type should succede
TEST (CLITest, FieldAddSameType)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "field add bob int field");

  // Add same type field to class should succede
  test.user_input(cli, oss, "field add bob int field2");
  ASSERT_EQ(1, interface.return_model().getClassCopy("bob").findAttribute("field2"));
  ASSERT_EQ("field", interface.return_model().getClassCopy("bob").getAttributes()[1]->identifier());
  ASSERT_EQ("field2", interface.return_model().getClassCopy("bob").getAttributes()[1]->getAttributeName());
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[1]->getType());
}

// Add field to a class with invalid name should fail
TEST (CLITest, FieldAddInvalidName)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Add invalid named field to class should fail
  // Start with valid special character
  test.user_input(cli, oss, "field add bob int _");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("_"));
  // Start with numbber
  test.user_input(cli, oss, "field add bob int 1");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("1"));
  // Start with invalid character
  test.user_input(cli, oss, "field add bob int !");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("!"));
  // Contain invalid character
  test.user_input(cli, oss, "field add bob int a!");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a!"));
}

// Add field to a class with invalid type should fail
TEST (CLITest, FieldAddInvalidType)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Add invalid type field to class should fail
  // Start with number
  test.user_input(cli, oss, "field add bob 1 a");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a"));
  // Contain invalid character
  test.user_input(cli, oss, "field add bob ! a");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a"));
  test.user_input(cli, oss, "field add bob int! a");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a"));
}

// Renaming a field
TEST (CLITest, FieldRename)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "field add bob int field2");

  // Rename field
  test.user_input(cli, oss, "field rename bob field2 field");

  ASSERT_EQ(0, interface.return_model().getClassCopy("bob").findAttribute("field"));
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("field2"));
}

// Renaming a field to an existing field should fail
TEST (CLITest, FieldRenameToExistingField)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "field add bob int field");
  test.user_input(cli, oss, "field add bob int field2");

  // Rename to existing field should fail
  test.user_input(cli, oss, "field rename bob field field2");
  ASSERT_EQ(0, interface.return_model().getClassCopy("bob").findAttribute("field"));
  ASSERT_EQ(1, interface.return_model().getClassCopy("bob").findAttribute("field2"));
}

// Renaming a field to an invalid name should follow the same name rules
TEST (CLITest, FieldRenameToInvalidName)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "field add bob int field");
  
  // Rename to invalid named should fail
  // Start with valid special character
  test.user_input(cli, oss, "field rename bob field _");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("_"));
  // Start with numbber
  test.user_input(cli, oss, "field rename bob field 1");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("1"));
  // Start with invalid character
  test.user_input(cli, oss, "field rename bob field !");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("!"));
  // Contain invalid character
  test.user_input(cli, oss, "field rename bob field a!");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a!"));
}

// Change the type of a field
TEST (CLITest, FieldChange)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "field add bob int field");
  
  // Change type of field
  test.user_input(cli, oss, "field change bob field string");

  ASSERT_EQ(0, interface.return_model().getClassCopy("bob").findAttribute("field"));
  ASSERT_EQ("field", interface.return_model().getClassCopy("bob").getAttributes()[0]->identifier());
  ASSERT_EQ("field", interface.return_model().getClassCopy("bob").getAttributes()[0]->getAttributeName());
  ASSERT_EQ("string", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
}

// Changing the type of a field to an invalid type should fail
TEST (CLITest, FieldChangeToInvalid)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "field add bob int field");
  
  // Change field to invalid type field should fail
  // Start with number
  test.user_input(cli, oss, "field change bob field 1");
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
  // Contain invalid character
  test.user_input(cli, oss, "field change bob field !");
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
  test.user_input(cli, oss, "field change bob field int!");
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
}

// Deleting a field
TEST (CLITest, FieldDelete)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "field add bob int field");
  
  // Delete field
  test.user_input(cli, oss, "field delete bob field");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("field"));
}


// Functions for CLI Method
// **************************

// Adding a method should be found in UMLData
TEST (CLITest, MethodAdd)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  // Add method to class
  test.user_input(cli, oss, "method add bob int method");
  ASSERT_EQ(0, interface.return_model().getClassCopy("bob").findAttribute("method"));
  ASSERT_EQ("method", interface.return_model().getClassCopy("bob").getAttributes()[0]->identifier());
  ASSERT_EQ("method", interface.return_model().getClassCopy("bob").getAttributes()[0]->getAttributeName());
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
}

// Adding a method to a nonexistant class should fail
TEST (CLITest, MethodAddToNonexistantClass)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Add to nonexistant class should fail
  test.user_input(cli, oss, "method add bob2 int method");
  ERR_CHECK (interface.return_model().getClassCopy("bob2"), "Class not found");
}

// Adding the same type method with different name should succede
TEST (CLITest, MethodAddSameType)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");

  // Add same type method with different name to class should succede
  test.user_input(cli, oss, "method add bob int method2");
  ASSERT_EQ(1, interface.return_model().getClassCopy("bob").findAttribute("method2"));
  ASSERT_EQ("method", interface.return_model().getClassCopy("bob").getAttributes()[1]->identifier());
  ASSERT_EQ("method2", interface.return_model().getClassCopy("bob").getAttributes()[1]->getAttributeName());
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[1]->getType());
}

// Adding a method with an invalid name should fail
TEST (CLITest, MethodAddInvalidName)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Add invalid named method to class should fail
  // Start with valid special character
  test.user_input(cli, oss, "method add bob int _");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("_"));
  // Start with numbber
  test.user_input(cli, oss, "method add bob int 1");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("1"));
  // Start with invalid character
  test.user_input(cli, oss, "method add bob int !");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("!"));
  // Contain invalid character
  test.user_input(cli, oss, "method add bob int a!");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a!"));
}

// Adding a method with an invalid type should fail
TEST (CLITest, MethodAddInvalidType)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Add invalid type method to class should fail
  // Start with number
  test.user_input(cli, oss, "method add bob 1 a");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a"));
  // Contain invalid character
  test.user_input(cli, oss, "method add bob ! a");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a"));
  test.user_input(cli, oss, "method add bob int! a");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a"));
}

// Renaming a method
TEST (CLITest, MethodRename)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method2");

  // Rename method
  test.user_input(cli, oss, "method select bob method2 1");
  test.user_input(cli, oss, "method rename method");

  ASSERT_EQ(0, interface.return_model().getClassCopy("bob").findAttribute("method"));
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("method2"));
}

// Renaming a method to an existing method should fail
TEST (CLITest, MethodRenameToExistingmethod)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method add bob int method2");

  // Rename to existing method should fail
  test.user_input(cli, oss, "method rename bob method method2");
  ASSERT_EQ(0, interface.return_model().getClassCopy("bob").findAttribute("method"));
  ASSERT_EQ(1, interface.return_model().getClassCopy("bob").findAttribute("method2"));
}

// Renaming a method to an invalid name should follow the same name rules
TEST (CLITest, MethodRenameToInvalidName)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  
  // Rename to invalid named should fail
  // Start with valid special character
  test.user_input(cli, oss, "method rename _");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("_"));
  // Start with numbber
  test.user_input(cli, oss, "method rename 1");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("1"));
  // Start with invalid character
  test.user_input(cli, oss, "method rename !");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("!"));
  // Contain invalid character
  test.user_input(cli, oss, "method rename a!");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("a!"));
}

// Changing the type of a method
TEST (CLITest, MethodChange)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  
  // Change type of method
  test.user_input(cli, oss, "method change string");

  ASSERT_EQ(0, interface.return_model().getClassCopy("bob").findAttribute("method"));
  ASSERT_EQ("method", interface.return_model().getClassCopy("bob").getAttributes()[0]->identifier());
  ASSERT_EQ("method", interface.return_model().getClassCopy("bob").getAttributes()[0]->getAttributeName());
  ASSERT_EQ("string", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
}

// Changing the type of a method to an invalid type should fail
TEST (CLITest, MethodChangeToInvalid)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  
  // Change method to invalid type method should fail
  // Start with number
  test.user_input(cli, oss, "method change 1");
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
  // Contain invalid character
  test.user_input(cli, oss, "method change !");
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
  test.user_input(cli, oss, "method change int!");
  ASSERT_EQ("int", interface.return_model().getClassCopy("bob").getAttributes()[0]->getType());
}

// Deleting a method
TEST (CLITest, MethodDelete)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  
  // Delete method
  test.user_input(cli, oss, "method delete");
  ASSERT_EQ(-1, interface.return_model().getClassCopy("bob").findAttribute("method"));
}

// Functions for CLI Parameter
// **************************

// Adding a parameter
TEST (CLITest, ParameterAdd)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");

  // Not having a selected parameter should fail so if you're still here it didn't crash
  test.user_input(cli, oss, "method parameter add int param");
  ASSERT_TRUE(true);

  test.user_input(cli, oss, "method select bob method 1");
  
  // Add parameter
  test.user_input(cli, oss, "method parameter add int param");

  // Check parameter list of class bob for paramter
  std::shared_ptr<UMLAttribute> attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  bool tester = false;
  auto param = paramList.begin();
  if(param->getName() == "param" && param->getType() == "int")
    tester = true;

  ASSERT_TRUE(tester);
}

// Adding a duplicate parameter should fail
TEST (CLITest, ParameterAddDuplicate)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");

  // Add duplicate parameter
  test.user_input(cli, oss, "method parameter add int param");

  // Check parameter list of class bob for multiple paramter
  std::shared_ptr<UMLAttribute> attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  ASSERT_EQ(1, paramList.size());

  // Add duplicate parameter with different type
  test.user_input(cli, oss, "method parameter add string param");
  attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  ASSERT_EQ(1, paramList.size());
}

// Adding a parameter of the same type but different name should succede
TEST (CLITest, ParameterAddSameType)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");

  // Add same type parameter with different name
  test.user_input(cli, oss, "method parameter add int param2");

  // Check parameter list of class bob for multiple paramter
  std::shared_ptr<UMLAttribute> attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  ASSERT_EQ(2, paramList.size());
}

// Deleting a parameter
TEST (CLITest, ParameterDelete)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");

  // Delete Parameter
  test.user_input(cli, oss, "method parameter delete param");

  // Check parameter list of class bob for multiple paramter
  std::shared_ptr<UMLAttribute> attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  ASSERT_EQ(0, paramList.size());
}

// Renaming a parameter
TEST (CLITest, ParameterRename)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");

  // Rename Parameter
  test.user_input(cli, oss, "method parameter rename param param2");

  // Check parameter list to see if it has new name
  std::shared_ptr<UMLAttribute> attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();

  ASSERT_EQ("param2", paramList.begin()->getName());
}

// Renaming a parameter to a duplicate name should fail
TEST (CLITest, ParameterRenameToDuplicate)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");
  test.user_input(cli, oss, "method parameter add int param2");

  // Rename Parameter
  test.user_input(cli, oss, "method parameter rename param param2");

  // Check parameter list to see if it has old name
  std::shared_ptr<UMLAttribute> attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();

  ASSERT_EQ("param", paramList.begin()->getName());
}

// Changing the type of a parameter
TEST (CLITest, ParameterChangeType)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");

  // Change carameter type
  test.user_input(cli, oss, "method parameter change param string");

  // Check parameter list to see if it has new type
  std::shared_ptr<UMLAttribute> attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();

  ASSERT_EQ("string", paramList.begin()->getType());
}

// Changing the type of a parameter to an invalid type should fail
TEST (CLITest, ParameterChangeToInvalidType)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add bob");
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");

  // Change to invalid type start with valid special character and check parameter list to see if it has old type
  test.user_input(cli, oss, "method parameter change param _");
  std::shared_ptr<UMLAttribute> attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  auto paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  ASSERT_EQ("int", paramList.begin()->getType());

  // Change to invalid type start with number
  test.user_input(cli, oss, "method parameter change param 1");
  attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  ASSERT_EQ("int", paramList.begin()->getType());

  // Change to invalid type start with invalid character
  test.user_input(cli, oss, "method parameter change param !");
  attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  ASSERT_EQ("int", paramList.begin()->getType());

  // Change to invalid type contain invalid character
  test.user_input(cli, oss, "method parameter change param a!");
  attr = interface.return_model().getClassCopy("bob").getAttribute("method");
  paramList = std::dynamic_pointer_cast<UMLMethod>(attr)->getParam();
  ASSERT_EQ("int", paramList.begin()->getType());
}

// Adding a method of the same name and type but different parameters should succede
TEST (CLITest, ParameterOverload)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  
  test.user_input(cli, oss, "class add bob");

  // Make method with one paramter
  test.user_input(cli, oss, "method add bob int method");
  test.user_input(cli, oss, "method select bob method 1");
  test.user_input(cli, oss, "method parameter add int param");

  // Make method with zero parameters
  test.user_input(cli, oss, "method add bob int method");

  auto attrList = interface.return_model().getClassCopy("bob").getAttributes();
  ASSERT_EQ(2, attrList.size());
}

// Functions for CLI Relationship
// **************************

// Basic check to see if adding a relationship to the data model works.
// It should appear in the vector and have the same source, destination, and type.
TEST (CLITest, AddingRelationshipTest)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  bool haveRelationship = false;
  test.user_input(cli, oss, "class add test");
  test.user_input(cli, oss, "class add test1");

  // Relationship type doesn't matter for this test
  test.user_input(cli, oss, "relationships add test test1 aggregation");

  UMLData data = interface.return_model();
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

// Error check to see if adding self inheritance causes an error.
TEST (CLITest, AddingSelfInheritance)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add test");
  test.user_input(cli, oss, "class add test1");
  
  // Relationship type doesn't matter for this test
  test.user_input(cli, oss, "relationships add test test generalization");
  test.user_input(cli, oss, "relationships add test1 test1 realization");

  UMLData data = interface.return_model();
  vector<UMLRelationship> rel = data.getRelationships();

  ASSERT_EQ(0, rel.size());
}

// Error check to see if adding multiple compositions causes an error.
TEST (CLITest, AddingMultipleCompositions)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add test");
  test.user_input(cli, oss, "class add test1");
  test.user_input(cli, oss, "class add test2");

  // Should work
  test.user_input(cli, oss, "relationships add test test1 composition");

  UMLData data = interface.return_model();
  vector<UMLRelationship> rel = data.getRelationships();

  ASSERT_EQ(1, rel.size());

  // Should fail so check if there are same number and type of relationships previously
  test.user_input(cli, oss, "relationships add test2 test1 composition");

  data = interface.return_model();
  rel = data.getRelationships();

  ASSERT_EQ(1, rel.size());

  ASSERT_EQ("test", rel[0].getSource().getName());
  ASSERT_EQ("test1", rel[0].getDestination().getName());
}

// Sees if deleting a relationship works.
// When a relationship is deleted, it shouldn't be in UMLData's vector.
TEST (CLITest, DeletingRelationshipTest)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add test");
  test.user_input(cli, oss, "class add test1");

  // Relationship type doesn't matter for this test
  test.user_input(cli, oss, "relationships add test test1 aggregation");
  test.user_input(cli, oss, "relationships delete test test1");

  // Loop through vector to find proper relationship
  bool haveRelationship = false;
  UMLData data = interface.return_model();
  vector<UMLRelationship> rel = data.getRelationships();
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

// Sees if getting the proper relationship type works after adding a relationship.
TEST (CLITest, GetRelationshipTypeTest)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add test");
  test.user_input(cli, oss, "class add test1");
  UMLData data;

  // Check for aggregation
  test.user_input(cli, oss, "relationships add test test1 aggregation");
  data = interface.return_model();
  ASSERT_EQ (data.getRelationshipType ("test", "test1"), "aggregation");
  test.user_input(cli, oss, "relationships delete test test1");

  // Check for composition
  test.user_input(cli, oss, "relationships add test test1 composition");
  data = interface.return_model();
  ASSERT_EQ (data.getRelationshipType ("test", "test1"), "composition");
  test.user_input(cli, oss, "relationships delete test test1");

  // Check for generalization
  test.user_input(cli, oss, "relationships add test test1 generalization");
  data = interface.return_model();
  ASSERT_EQ (data.getRelationshipType ("test", "test1"), "generalization");
  test.user_input(cli, oss, "relationships delete test test1");

  // Check for realization
  test.user_input(cli, oss, "relationships add test test1 realization");
  data = interface.return_model();
  ASSERT_EQ (data.getRelationshipType ("test", "test1"), "realization");
}

// Sees if changing the relationship type works at all.
TEST (CLITest, ChangeRelationshipTypeTest)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add test");
  test.user_input(cli, oss, "class add test1");
  
  // Test to see if relationship was changed
  test.user_input(cli, oss, "relationships add test test1 aggregation");
  test.user_input(cli, oss, "relationships change test test1 composition");
  UMLData data = interface.return_model();
  ASSERT_EQ (data.getRelationship ("test", "test1").getType(), aggregation);
}

// Tests all errors that currently exist for changing a relationship type.
TEST (CLITest, ChangeRelationshipTypeErrors)
{
  // Create interface and grab its menu and a stringstream
  UMLCLI interface;
  Cli cli = interface.cli_menu();
  stringstream oss;

  // Initialize test
  CLITest test;
  test.user_input(cli, oss, "class add test");
  test.user_input(cli, oss, "class add test1");
  test.user_input(cli, oss, "class add test2");

  // Test for self-inheritance
  // Should fail so check original relationship type
  test.user_input(cli, oss, "relationships add test test aggregation");
  test.user_input(cli, oss, "relationships change test test generalization");
  UMLData data = interface.return_model();
  ASSERT_EQ (data.getRelationship ("test", "test").getType(), aggregation);

  test.user_input(cli, oss, "relationships change test test realization");
  data = interface.return_model();
  ASSERT_EQ (data.getRelationship ("test", "test").getType(), aggregation);
}