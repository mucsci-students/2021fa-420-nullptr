cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(project CXX)

# find_package (Threads REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(INJA_USE_EMBEDDED_JSON On CACHE Bool "" FORCE)
set(BUILD_BENCHMARK Off CACHE Bool "" FORCE)
set(BUILD_TESTING Off CACHE Bool "" FORCE)
add_subdirectory(inja)
add_subdirectory(cpp-httplib)
add_subdirectory(cli)

add_library(umllib
  UMLAttribute.cpp
  UMLClass.cpp
  UMLData.cpp
  UMLDataHistory.cpp
  UMLField.cpp
  UMLFile.cpp
  UMLMethod.cpp
  UMLParameter.cpp
  UMLRelationship.cpp
  UMLServer.cpp
  CLI.cpp)

# Included to increase functionality of CLI library
target_link_libraries(cli INTERFACE Boost::system)
target_compile_definitions(cli INTERFACE BOOST_ASIO_NO_DEPRECATED=1)

target_include_directories(umllib PUBLIC "${PROJECT_SOURCE_DIR}/include")

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
