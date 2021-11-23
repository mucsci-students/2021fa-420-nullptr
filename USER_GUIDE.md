# UML++ User Guide

Welcome to the UML++ user guide! This document provides a rundown on how to use UML++ to generate and modify UML class diagrams.

There are two user interfaces that are available for use in editing class diagrams -- the GUI (Graphical User Interface) and CLI (Command Line Interface). This guilde will describe how to use the features within each interface, as well as some general info consistent between interfaces.

## CLI
![Initial prompt](https://i.ibb.co/Bz3093X/Code-FVRtyd-QXS3.png)

The CLI provides a command line interface for those who wish to work with a text-based UML class diagram editor. It can be accessed with the "--cli" argument, as shown above.

---

### General Usage 

- Type in commands to edit your given UML class diagram, and press enter to input them. If you type an incorrect command, the CLI will display a "wrong command" error. If you are ever lost on what command you need to use, check this file or use the 'help' command to see a list of commands currently available to you.
- You can "tab complete" commands by typing a portion of command and pressing tab. If multiple commands share the same string of letters, the command line will display all valid completions for a command.
- Certain commands require you to input an argument, such as a name, or a type. Without these arguments, the command you are trying to use will not work. See below for an explanation for the arguments for each command.

---

### Universal Commands

Accessible while within any menu of the program.

![Universal commands](https://i.ibb.co/6BYgR3N/Code-PP2q-P1-Fc-OI.png)

**help**: Provides a list of all valid commands for the given menu or submenu that you are in. This document contains images of this specific command to show all commands within the interface.

**exit**: Exits the program. All unsaved progress will be lost.

---

### Main Commands

Accessible while within the main menu (uml>).

![Main commands](https://i.ibb.co/xgB3Lcv/Main.png)

**load <file_name>**: Loads a json file with the given filename. The json file must come from a UML class diagram and follow its save format, or else it will not work. The file name given should only be its name, and not with a .json extension.

- Example: load sock 
  - Attempts to load a file named sock.json

**save <file_name>**: Saves a json file with the given filename. This json file will be saved automatically to your build directory, and can be used again for future use.

- Example: save sock 
  - Saves a file named sock.json to your build directory

---

### Class Commands

Accessible when the class submenu (class>), or by adding 'class' to the operation while in the main menu (uml> class ...).

![Class commands](https://i.ibb.co/2SksJgK/Class.png)

---

### Relationship Commands

Accessible when the relationships submenu (relationships>), or by adding 'relationships' to the operation while in the main menu (uml> relationships ...).

![Relationship commands](https://i.ibb.co/d7Scvsc/Relationship.png)

---

### Field Commands

Accessible when the field submenu (field>), or by adding 'field' to the operation while in the main menu (uml> field ...).

![Field commands](https://i.ibb.co/9t5bhD5/Field.png)

---

### Method Commands (method>)

Accessible when the method submenu (method>), or by adding 'method' to the operation while in the main menu (uml> method ...).

![Method commands](https://i.ibb.co/pncZnQS/Method.png)

---

### Parameter Commands (parameter>)

Accessible when the parameter submenu (parameter>), by adding 'method' to the operation while in the method submenu (method> parameter ...), or by adding 'method parameter' to the operation while in the main menu (uml> method parameter ...).

![Parameter commands](https://i.ibb.co/VS4NHK6/Parameter.png)
