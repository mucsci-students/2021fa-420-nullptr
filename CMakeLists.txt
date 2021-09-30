cmake_minimum_required(VERSION 3.10)
# set the project name
project(project C CXX)

add_subdirectory(include/json)

add_executable(project main.cpp UMLClass.cpp UMLAttribute.cpp UMLRelationship.cpp UMLData.cpp UMLFile.cpp CLI.cpp)

target_link_libraries(project PUBLIC json)



target_include_directories(project PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/include/json"
                          )

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Tests Tests.cpp UMLClass.cpp UMLAttribute.cpp UMLRelationship.cpp UMLData.cpp UMLFile.cpp CLI.cpp)
target_link_libraries(Tests gtest_main)
include(GoogleTest)
gtest_discover_tests(Tests)
