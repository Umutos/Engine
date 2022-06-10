# PlatformerGL

## Presentation


### Introduction
-----------
`PlatformerGL`<br>
The goal of this project was to make a platformer using our own game engine.<br>
This project started on `May 31` and the beta will end on `June 10`. <br>

## Play Menu
-----------

- `New Game` = Play Game.<br>
- `Option` = Change Control.<br>
- `Quit` =  Quit the Game.<br>

## Control
-----------
Camera Move In Game: <br>
- `W`,  
- `S`,  
- `A`, 
- `D`,
- `Space` = Jump.<br>
- `Escape` = Pause.<br>
- `UP` = Camera follow In Z Positive,
- `DOWN` = Camera follow In Z Negative,
- `LEFT` = Camera follow In X Positive,
- `RIGHT` = Camera follow In X Negative.

Camera Move In Debug: <br>
- `W`,  
- `S`,  
- `A`, 
- `D`. 
- `Shift` = Speed Up.<br>
- `Space` = Go Up.<br>
- `Left Control` = Go Down.<br>
- `Escape` = Pause.<br>
- `Mouse` = Rotation.<br>

## Pause
-----------
In Pause Menu:
- `Resume` = Return to the game.<br>
- `Debug` = Open Debug Options.<br>
- `Quit` = Quit the Game.<br>

## Make Collision

### Model
-----------
To add models, go to main and add a new mesh with coordinates and textures.<br>


![png](PlatformerGL/OpenGL/Assets/4.PNG)

Then go to the 'SphereCol' funtion on app and initialise the Platform object using data pointer from the mesh you just created.

```cpp
	platform1 = OBBCollider(&mesh[1]->pos, OBB(&mesh[1]->scl,&mesh[1]->rot));
	platforms.push_back(Platform(platform1, &player2.colVisualisation));
    //player2.colVisualisation serves no purpose yet, it was made so that the platform could have different model
```
## Gravity
To change the gravity value in the Actor.h file

```cpp
#define GRAVITY     -1
```

## Building

To run the project, you can debug with F5.

## Credit

This project was made by `Umut Osmanoglu` and `Yann Dechaux`.

