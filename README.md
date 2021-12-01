# UML++ ![workflow](https://github.com/mucsci-students/2021fa-420-nullptr/actions/workflows/cmake.yml/badge.svg) [![codecov](https://codecov.io/gh/mucsci-students/2021fa-420-nullptr/branch/develop/graph/badge.svg?token=gjrjXBxxEO)](https://codecov.io/gh/mucsci-students/2021fa-420-nullptr)

UML++ is a C++ & Javascript editor and generator of UML class diagrams.

## Features

- Add, delete, and rename classes within a UML class diagram.
- Store methods (with parameters) and fields within classes.
- Add and delete four types of relationships between classes (aggregation, composition, generalization, realization).
- View classes and diagram through a command line or graphical interface.
- Save and load JSON files that store UML class diagram information.
- Save images of generated UML class diagrams within the GUI.

## Dependencies

- A C++ compiler
- cmake (3.18.1+)
- git (2.28.0+)

## Build Instructions

1. Clone this repository locally.
```
git clone --recurse-submodules -j8 https://github.com/mucsci-students/2021fa-420-nullptr.git
```
2. Go to repository root directory.
```
cd 2021fa-420-nullptr
```
3. Create and then build the project using the following commands.
```
cmake -B build 
cmake --build build --parallel
```
4. Navigate to the build folder that you have created. You must be in the build folder to run the program.
```
cd build
```
5. For CLI, use "--cli" argument. The interface will open in your command line. 
For help, type 'help' in the command line or see USER_GUIDE.md.
```
./project --cli
```
6. For GUI, provide no argument. Open port 60555 and enter interface in your browser through localhost:60555. When running, press "help" to enter a webpage that provides a user guide for using the GUI interface. Further information about the GUI can be found in USER_GUIDE.md.
```
./project
```
## Dependencies

[JSON for Modern C++ - Niels Lohmann](https://github.com/nlohmann/json) ([MIT License](https://raw.githubusercontent.com/nlohmann/json/develop/LICENSE.MIT))

[GoogleTest - Google](https://github.com/google/googletest) ([BSD-3-Clause](https://raw.githubusercontent.com/google/googletest/master/LICENSE))

[cpp-httplib - Yuji Hirose](https://github.com/yhirose/cpp-httplib) ([MIT License](https://raw.githubusercontent.com/yhirose/cpp-httplib/master/LICENSE))

[inja - pantor](https://github.com/pantor/inja) ([MIT License](https://raw.githubusercontent.com/pantor/inja/master/LICENSE))

[svg.js - svgdotjs](https://github.com/svgdotjs/svg.js) ([MIT License](https://raw.githubusercontent.com/svgdotjs/svg.js/master/LICENSE.txt))

[svg.draggable.js - svtdotjs](https://github.com/svgdotjs/svg.draggable.js) ([MIT License](https://raw.githubusercontent.com/svgdotjs/svg.draggable.js/master/LICENSE))

[svg-pan-zoom - bumbu](https://github.com/bumbu/svg-pan-zoom) ([BSD 2-Clause "Simplified" License](https://raw.githubusercontent.com/bumbu/svg-pan-zoom/master/LICENSE))

[cli - daniele77](https://github.com/daniele77/cli) ([Boost Software License 1.0](https://raw.githubusercontent.com/daniele77/cli/master/LICENSE))

## Authors
[DHDodo](https://github.com/DHDodo) - Briar Sauble

[jtsha](https://github.com/jtsha) - Jordan Shaffer

[ttpyork](https://github.com/ttpyork) - Tyler York

[NicatFire](https://github.com/NicatFire) -  Nick Wells

[lgnzg](https://github.com/lgnzg) - Logan Zug

[DragonArchon](https://github.com/DragonArchon) - Matt Giacoponello
