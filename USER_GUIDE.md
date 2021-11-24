# UML++ User Guide

Welcome to the UML++ user guide! This document provides a rundown on how to use UML++ to generate and modify UML class diagrams.

There are two user interfaces that are available for use in editing class diagrams -- the GUI (Graphical User Interface) and CLI (Command Line Interface). This guilde will describe how to use the features within each interface, as well as some general info consistent between interfaces.

---

## UML Guide

Before using UML++, it is important to know the components of a UML class diagram, alongside specific rules that come with each component. These are all general features of a typical UML class diagram.

- **Class**: Represents a blueprint for an object, with their own fields, methods, and relationships with other classes. Two classes cannot have the same name. 
- **Field**: Represent variables within a given class, and will always have a type. An example field is "int foo". A field cannot share a name with any other fields or parameters.
- **Method**: Represent functions within a given class, and will have its own return type. Methods can be overloaded by other methods with the same name, but no two methods can have a set of parameters with the same types in the same order.
- **Parameter**: Represent components which would be passed in when a method is called. A parameter cannot share a name with any other parameters within the method.
- **Relationships**: Represent connections between different classes. Every relationship has a "source" class that relates to a "destination" class. UML++ supports four specific relationship types:
  - **Aggregation**: shared, ownerless collection.
  - **Composition**: unshared, 'has-a' relationship collection. A class can only be the destination for one composition. 
  - **Generalization**: inheritance relationship. A class cannot be a generalization of itself.
  - **Realization**: interface implementation relationship. A class cannot be a realization of itself.

All of these components must have names that can be validly represented: the first character of the name must be a letter, with any character afterwards allowed to be a letter, number, or underscore. 

With these rules, its possible to create representations of programs from different languages using these abstractions. 

---

## GUI

### Getting Started
Once you've built the program, you can access the GUI by running the program with no arguments within the build folder. 
```
./project
```
The message below should appear, and the server should be running. 

```
running at http:://localhost:60555/
```
Now, open up a web browser and type ```http:://localhost:60555/``` into the address bar. 

### The Layout
![image](https://user-images.githubusercontent.com/89749149/143141094-e17375bc-f38c-4572-b807-b0149c9736ec.png)

On the left side is the Editor Panel. This panel is used to edit and modify classes and relationships within the UML Diagram. You can show/hide this panel at any time. To this, use the "Toggle Editor Panel" button located to the right of the panel.

On the right, there is a large white area. This is the Diagram View, where you'll be able to move class boxes and relationship arrows within your diagram. 

### General Usage 

When you create a class using the Editor Panel, it appears in the Diagram View at a set spot (Note: when you add more than one class at a time, the boxes will stack on top of each other). Then, you can drag the boxes around on the Diagram View as you wish. You can pan and zoom around the diagram view, and you can double click on a class box show the class details in the Editor Panel. 

When you create a relationship in the Editor Panel, an arrow connecting the two related class boxes will appear in the Diagram View. The arrow will follow the class boxes as you move them and double clicking an arrow will show the relationship details in the Editor Panel. 

### The Editor Panel

#### Creating a Class
A class can be creating using the add class form under the “Classes:” heading. 

![image](https://user-images.githubusercontent.com/89749149/143143435-3dd7223a-1378-4d75-a003-551be37f715a.png)

After adding the class, it will appear under the "Classes:" heading. A class box will, also, appear in the Diagram View.

![image](https://user-images.githubusercontent.com/89749149/143143697-52d6a9be-b2ec-43e4-a081-60db6cb770f3.png)

To delete the class, select the "Delete" button next to the class name. 

To edit details about a class such as the name, fields, and methods, enter the class detail view. To do this, click the edit button next to the class name. Alternatively, you can double click the class box within the Diagram View.

![image](https://user-images.githubusercontent.com/89749149/143143981-c948948a-cd36-4c1b-8b43-5b147b473684.png)

While in the class detail view, the back button can be used to return to the view with all classes within the diagram. 

#### Adding a Field
A field can be added by using the add field form. After submission, the type and name will be displayed under the “Fields:” heading. 

![image](https://user-images.githubusercontent.com/89749149/143144777-9b6ce157-0b5f-4403-be9f-3564146f7072.png)

To edit the name or type of a field, use the edit button next to the name of the field. 

To delete a field, use the delete button next to the name of the field. 

#### Adding a Method

A method can be added by using the add method form. 

![image](https://user-images.githubusercontent.com/89749149/143145356-bed83679-8adb-4bed-b864-a5754b597c82.png)

After submitting the form, you should see the type and method name displayed (note: the parens () are added onto the name automatically). 
To edit the name/return type of the method or delete the method, use the buttons to the right of the method. 

After a method is added, an add parameter form should show up under the method, use this form to add parameters to the method. 

#### Creating a Relationship 
A relationship between two classes can be created using the relationship form found on the all view within the Editor Panel. Specify the classes to be added and the type of relationship. 

![image](https://user-images.githubusercontent.com/89749149/143155503-fb9eb706-6f20-48e7-90d4-b8cf45ab9cef.png)

After submission, the relationship will show under the “Relationships” heading. To edit the type of the relationship, select the edit button next to the relationship. 
To delete the relationship, select delete next to the relationship. 
When a class is deleted that is in a relationship, all relationships with that class are also deleted.

#### Undo/Redo
![image](https://user-images.githubusercontent.com/89749149/143155794-0616c91d-c67c-4b2b-81a4-f6b31b170e56.png)

You can undo/redo any actions using the undo redo buttons situated at the top of the Editor Panel. These buttons will also undo and redo dragging changes and file loads. 
#### Saving/Loading
The saving and loading form can be accessed at the bottom of the all-classes view or by clicking the Save/Load button at the top of the Editor Panel.

![image](https://user-images.githubusercontent.com/89749149/143155977-5ecd0fca-7704-4c32-8f6c-0681be657fc3.png)

Here, you can choose to save the diagram as a JSON file and a PNG file. Saving as a JSON file allows you to reload the file into the editor to edit the diagram again. You can reload the file into the editor by using the “Load File” form. 
Click “Choose File” and select a valid JSON file with a valid format, and the diagram will be filled in according to the values in the file. 

#### Accessing Help
![image](https://user-images.githubusercontent.com/89749149/143156196-0795023c-ca87-4c46-8776-ceeb82d0c6f8.png)

Additional help tips can be found by selecting the help button, which is located at the top of the editor panel.

### Diagram Window 

The diagram windows allow for dragging of class boxes. Elements will appear here after added via the Editor Panel. 
The Relationship arrows will follow the shortest path to the class box, and the arrows will update when the box is moved. 

![image](https://user-images.githubusercontent.com/89749149/143156624-a57469eb-bf32-4fa6-bfce-2c0afe8eda80.png)

You can double click the lines and boxes, and that action will bring up the class or relationship detail view within the Editor Panel.

---

## CLI
![Initial prompt](https://i.ibb.co/Bz3093X/Code-FVRtyd-QXS3.png)

The CLI provides a command line interface for those who wish to work with a text-based UML class diagram editor. It can be accessed with the "--cli" argument, as shown above.

---

### General CLI Usage 

- Type in commands to edit your given UML class diagram, and press enter to input them. If you type an incorrect command, the CLI will display a "wrong command" error. If you are ever lost on what command you need to use, check this file or use the 'help' command to see a list of commands currently available to you.
- You can "tab complete" commands by typing a portion of command and pressing tab. If multiple commands share the same string of letters, the command line will display all valid completions for a command.
- Certain commands require you to input an argument, such as a name, or a type. Without these arguments, the command you are trying to use will not work. See below for an explanation for the arguments for each command.
- Certain commands, such as class list, display numbers next to methods. The numbers displayed next to methods represent their "method number", which is used to aid in selecting overloaded methods for various operations. Methods that are not overloaded will always have a number 1, while methods that are overloaded will have numbers from 1 up to the count of overloads.
- Certain commands may require you to select a method beforehand by using "method select". These have been labeled to be as such within the help information of each command.

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

**load <file_name>**: Loads a json file with the given filename from the run directory. The json file must come from a UML class diagram and follow its save format, or else it will not work. The file name given should only be its name, and not with a .json extension.

- Example: load sock 
  - Attempts to load a file named sock.json

**save <file_name>**: Saves a json file with the given filename. This json file will be saved automatically to the directory you ran the program from, and can be used again for future use.

- Example: save sock 
  - Saves a file named sock.json

**undo**: Undoes your most recent action. To prevent potential errors, this will also clear your most recently selected method (see Method Commands).

**redo**: Redoes your most recently undone action. To prevent potential errors, this will also clear your most recently selected method (see Method Commands).

**class | relationships | field | method**: Enters a submenu containing commands that allows you to manipulate the given component of a UML class diagram. Alternatively, you can use this to call a command from the given submenu while in the main menu.

- Example 1: class
  - Brings you to the submenu "class"
- Example 2: class add bob 
  - Attempts to add bob while still remaining in the main menu

---

### Class Commands

Accessible when the class submenu (class>), or by adding 'class' to the operation while in the main menu (uml> class ...).

![Class commands](https://i.ibb.co/2SksJgK/Class.png)

**list:** Displays all classes within the UML class diagram. An example is shown below.

![List example](https://i.ibb.co/887SXKH/Code-cn-Zvxkj6-D3.png)

**add <class_name>**: Adds a class, and shows an empty representation of the newly made class.

- Example: add bob
  - Adds the class bob

**delete <class_name>**: Deletes the class given to the argument if it exists.

- Example: delete bob
  - Deletes the class bob

**rename <old_class_name> <new_class_name>**: Renames the class put in at old_class_name to the name of new_class_name, if possible.

- Example: rename bob jim
  - Renames class bob to jim

**uml**: Return to the main menu if you are currently in the submenu.

---

### Relationship Commands

Accessible when the relationships submenu (relationships>), or by adding 'relationships' to the operation while in the main menu (uml> relationships ...).

![Relationship commands](https://i.ibb.co/d7Scvsc/Relationship.png)

**add \<source> \<destination> <relship_type>**: Creates a relationship between two classes with the given relationship type.

- Example: add bob jim aggregation
  - Creates an aggregation between source class bob and destination class jim

**delete \<source> \<destination>**: Deletes the relationship between the source class and the destination class

- Example: delete bob jim
  - Deletes the relationship source class bob has with destination class jim

**change \<source> \<destination> <relship_type>**: Changes the relationship type between a preexisting relationship

- Example: change bob jim inheritance
  - Changes the relationship between source class bob and relationship class jim to an inheritance relationship

**uml**: Return to the main menu if you are currently in the submenu.

---

### Field Commands

Accessible when the field submenu (field>), or by adding 'field' to the operation while in the main menu (uml> field ...).

![Field commands](https://i.ibb.co/9t5bhD5/Field.png)

**add \<class_name> \<field_type> <field_name>**: Adds to the class placed in class_name the field of type field_type and name field_name, if it does not conflict with any other fields or methods.

- Example: add bob int sarah
  - Adds to bob the field "int sarah"

**delete \<class_name> \<field_name>**: Deletes the given field from the class, if it exists.

- Example: delete bob sarah
  - Deletes the field sarah from bob

**rename \<class_name> \<field_name> \<new_field_name>**: Renames the field given in field name to the new field name.

- Example: rename bob sarah alex
  - Field sarah in bob will now be named alex instead

**change \<class_name> \<field_name> \<new_field_type>**: Within the class given, changes the type of the field given.

- Example: change bob sarah string 
  - Field sarah in bob now has a type string, being "string sarah"

**uml**: Return to the main menu if you are currently in the submenu.

---

### Method Commands

Accessible when the method submenu (method>), or by adding 'method' to the operation while in the main menu (uml> method ...).

![Method commands](https://i.ibb.co/pncZnQS/Method.png)

**select \<class_name> \<method_name> \<method_number>**: Selects a method that exists in the class for use in various operations. The method number for a given method within a class can be found when the method is inserted into a class, or when viewing a given class. This is to handle the situation of overloads.

- Example: select bob jessica 2
  - Selects within bob the overloaded method 'jessica', specifically the second method stored within the diagram in the class with its name.

**view_select**: Allows you to view your currently selected method to verify that it is correct.

**view_method \<class_name> \<method_name> \<method_number>**: Similar in operation to select, but instead only gives you a view of that specific overload of the method.

- Example: view_method bob jessica 2
  - Views within bob the overloaded method 'jessica', specifically the second method stored within the diagram in the class with its name. Its parameters and return type will be displayed.

**add \<class_name> \<method_type> \<method_name>**: Creates a method within the class specified with the given type and name, and then displays the method (alongside its method number).

- Example: add bob int jessica 
  - Adds method jessica with return type int to the class bob. As an example, if there are two "jessica" methods already in bob, the method will be displayed after addition with the method number of 3.

**delete**: Deletes your currently selected method.

**rename <new_method_name>**: Renames the currently selected method to the new method name.

- Example (Currently selected method's name: jessica): rename samantha
  - jessica will now have the name samantha, and will have a new method number to reflect the amount of overloads the name "samantha" has in the class that it is in.

**change <new_method_type>**: Changes the currently selected method's return type.

- Example (Currently selected method's type: int): change string 
  - The method selected will now have type string instead of int. This will not affect method number counts.

**parameter**: Enters a submenu containing commands that allows you to manipulate the parameters of a method. Alternatively, you can use this to call a command from the given submenu while in the method menu.

- Example 1: parameter
  - Brings you to the parameter submenu
- Example 2: parameter add int foo
  - Attempts to add parameter "int foo" to the selected method while still remaining in the method submenu

**uml**: Return to the main menu if you are currently in the submenu.

---

### Parameter Commands

Accessible when the parameter submenu (parameter>), by adding 'method' to the operation while in the method submenu (method> parameter ...), or by adding 'method parameter' to the operation while in the main menu (uml> method parameter ...).

Operations involving parameters require a selected method, which should be done by accessing a command in the method submenu (described previously).

![Parameter commands](https://i.ibb.co/VS4NHK6/Parameter.png)

**add \<param_type> \<param_name>**: Adds a parameter of the given type and name to the selected method.

- Example (Currently selected method: jessica): add int height
  - The selected method jessica now has parameter "int height".

**delete \<param_name>**: Deletes the parameter of the given name from the selected method, if it exists.

- Example (Currently selected method: jessica): delete height
  - Jessica no longer has the parameter "height", if it exists.

**rename \<param_name_old> \<param_name_new>**: Renames the parameter of the given name in the selected method to the new name given.

- Example (Currently selected method: jessica): rename height weight
  - Jessica's parameter of "height" will now be "weight", while still having the same type.

**change \<param_name> \<new_param_type>**: Changes the type of the given parameter in the selected method to the new parameter type.

- Example (Currently selected method: jessica): change height string
  - Jessica's parameter of "height" will now hold the type "string" instead of whatever type it had before.

**method**: Return to the method submenu if you are currently in the parameter submenu.
