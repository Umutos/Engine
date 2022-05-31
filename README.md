# ModernOpenGL

## Presentation


### Introduction
-----------
`ModernOpenGL`<br>
The objective of this project is to implement the graphic architecture of a game engine.<br>
This module started on `April 27` and finished on `May 25`.<br>

### Control
-----------
Camera Move: <br>
- `Z`,  
- `S`,  
- `A`, 
- `D`. 
- `Shift` = Speed Up.<br>
- `Space` = Go Up.<br>
- `Left Control` = Go Down.<br>

Camera Rotation: <br>
- `Mouse`

### Behavior
-----------
 - 1 : Draw <br>
   To display the models, click on All Model in Draw and the models will appear. Except that there is no light.
   ![png](OpenGLVeryStart/OpenGL/Assets/1.PNG)
-----------
 - 2 : Lights <br>
    To display the lights, click on `DirctionalLight`, `PointLight` or/and `SpotLight` . Then you can change the intensity with the sliders.
   ![png](OpenGLVeryStart/OpenGL/Assets/2.PNG)
-----------
 - 3 : Transform <br>
    To change the rotation, change the position or change the scale, we first choose the model we want to change in the model list. Then with the sliders we can change the rotation, position and scale.
   ![png](OpenGLVeryStart/OpenGL/Assets/3.PNG)
-----------
## ResourceManager and IResources

There are two types of resources:

### Model

    - Loaded from an .obj,
    - Parsed into an index array and a vertex array,

### Texture

    - Loaded from a .png,
    - Generated from OpenGL specific functions,
    - No .mtl parser so only one texture per mesh 

### Model

    - There is no graphic scene and therefore no parent-child link

## Building

To run the project, you can debug with F5.

## Credit

This project was made by `Umut Osmanoglu`.

