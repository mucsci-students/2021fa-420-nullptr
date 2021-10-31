cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the project name
project(project C CXX)

# Add executables here

# Main executable, to be used by the client
add_executable(project main.cpp)

# Local Libraries

# Make constant cpp files into static library
add_library(local-library STATIC UMLClass.cpp UMLAttribute.cpp 
UMLRelationship.cpp UMLData.cpp UMLFile.cpp UMLParameter.cpp UMLMethod.cpp 
UMLField.cpp CLI.cpp UMLDataHistory.cpp)

# External Libraries

# Add and link threads for http library and local-library
find_package (Threads REQUIRED)
target_link_libraries(project PUBLIC Threads::Threads local-library)

# Include hpp files, don't add
target_include_directories(project INTERFACE include/)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executable, to be used by the client
add_executable(Tests Tests.cpp)

# Add and link threads for http library
find_package (Threads REQUIRED)
target_link_libraries(Tests PUBLIC Threads::Threads local-library gtest_main)

# Include hpp files, don't add
target_include_directories(Tests INTERFACE include/)

include(GoogleTest)
gtest_discover_tests(Tests)