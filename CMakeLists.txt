cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Sets the project name
project(project CXX)

# Code Coverage
set(CMAKE_CXX_FLAGS --coverage)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(INJA_USE_EMBEDDED_JSON On CACHE Bool "" FORCE) # Allows use of json and inja as submodule
set(BUILD_BENCHMARK Off CACHE Bool "" FORCE)
set(BUILD_TESTING Off CACHE Bool "" FORCE)
add_subdirectory(external/inja)
add_subdirectory(external/cpp-httplib)
add_subdirectory(external/cli)

add_library(umllib
  umllib/UMLAttribute.cpp
  umllib/UMLClass.cpp
  umllib/UMLData.cpp
  umllib/UMLDataHistory.cpp
  umllib/UMLField.cpp
  umllib/UMLFile.cpp
  umllib/UMLMethod.cpp
  umllib/UMLParameter.cpp
  umllib/UMLRelationship.cpp
  umllib/UMLServer.cpp
  umllib/UMLCLI.cpp
  umllib/CLITest.cpp)

target_include_directories(umllib PUBLIC "${PROJECT_SOURCE_DIR}/umllib/include")

target_link_libraries(umllib PUBLIC 
  inja
  httplib
  cli)

add_executable(project main.cpp)

target_link_libraries(project PUBLIC umllib)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Tests Tests.cpp)

target_link_libraries(Tests PUBLIC gtest_main umllib)

include(GoogleTest)
gtest_discover_tests(Tests)
