![example workflow](https://github.com/mucsci-students/2021fa-420-nullptr/actions/workflows/cmake.yml/badge.svg)

# 2021fa-420-nullptr

UML++ is a C++ editor of UML class diagrams.

## Features

- Add, delete, and rename classes within a UML class diagram.
- Store methods (with parameters) and fields within classes.
- Add and delete four types of relationships between classes (aggregation, composition, generalization, realization).
- View classes and diagram through a command line or graphical interface.
- Save and load JSON files that store UML class diagram information.

## Dependencies

- A C++ compiler
- cmake (3.18.1+)
- git (2.28.0+)

## Build Instructions

1. Clone this repository locally.
```
git clone https://github.com/mucsci-students/2021fa-420-nullptr.git
```
2. Go to repository root directory.
```
cd 2021fa-420-nullptr
```
3. Create and move to build folder.
```
mkdir build
cd build
```
4. Create make file within build folder.
```
cmake ..
```
5. Run make to build program.
```
make project
```
6. For CLI, use "--cli argument." The interface will open in your command line.
```
./project --cli
```
7. For GUI, provide no argument. Open port 8080 and enter interface in your browser through localhost:8080.
```
./project
```
## Dependencies

[JSON for Modern C++ - Niels Lohmann](https://github.com/nlohmann/json) ([MIT License](https://raw.githubusercontent.com/nlohmann/json/develop/LICENSE.MIT))

[GoogleTest - Google](https://github.com/google/googletest) ([BSD-3-Clause](https://raw.githubusercontent.com/google/googletest/master/LICENSE))

[cpp-httplib - Yuji Hirose](https://github.com/yhirose/cpp-httplib) ([MIT License](https://raw.githubusercontent.com/yhirose/cpp-httplib/master/LICENSE))

[inja - pantor](https://github.com/pantor/inja) ([MIT License](https://raw.githubusercontent.com/pantor/inja/master/LICENSE))

## Authors
[DHDodo](https://github.com/DHDodo) - Briar Sauble

[jtsha](https://github.com/jtsha) - Jordan Shaffer

[ttpyork](https://github.com/ttpyork) - Tyler York

[NicatFire](https://github.com/NicatFire) -  Nick Wells

[lgnzg](https://github.com/lgnzg) - Logan Zug
