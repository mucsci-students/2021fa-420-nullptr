#include <gtest/gtest.h>
#include "UMLData.hpp"
// TEST(TestSuiteName, TestName) {
//   ... test body ...
// }

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