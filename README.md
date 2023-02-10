<h1 align="center">
    BreakOut!
  <br>
</h1>

<h4 align="center"> 
A classic game remade in c++ using SFML
</h4>
<p align="center">
  <a href="#features">Features</a> •
  <a href="#how-to-play">How To Play</a> •
  <a href="#installing">Installing and Executing</a> •
  <a href="#images">Images</a> •
  <a href="#license">License</a>
</p>

## Description

BreakOut is a classic arcade game developed by Atari, Inc. This implementation of BreakOut is done in C++ and uses SFML for the graphics and audio. 

## Getting Started 

### Dependecies

* CMake version >= 3.14.4
* clangd version >= 9.00
* SFML

## Features

 - Main Menu
 - Pause and Resume Capabilites
 - End Title Screen
 - Key Board Controls
 - Leader Board
 - Music and SFX

## How to Play

 - 'p': pause game
 - 'left arrow': move player character left 
 - 'right arrow': move player character right
 - 'down arrow': navigate menu choices 
 - 'up arrow': navigate menu choices 
 - '1': turn music down
 - '2': turn music up
 - '9': turn sfx down
 - '0': turn sfx up
 - 'enter': make selection

### Installing

* Clone the repository in a desired location

### Executing Program

* Create a build directory: 
```
mkdir build
```
* Navigate to build directory
```
cd build
```
* execute the command:
```
cmake -S ../ -B .
```
* a makefile will be generated, compile the program:
```
make
```
* run the program:
```
./BreakOut
```
## Images 
![Main Menu](https://github.com/alexisM8/BreakOut/blob/main/images/mainmenu.png)
![Controls](https://github.com/alexisM8/BreakOut/blob/main/images/controls.png)
![Game Play](https://github.com/alexisM8/BreakOut/blob/main/images/gameplay.png)
![Paused Game](https://github.com/alexisM8/BreakOut/blob/main/images/paused.png)
![Game Over](https://github.com/alexisM8/BreakOut/blob/main/images/gameover.png)
![Save Score](https://github.com/alexisM8/BreakOut/blob/main/images/savescore.png)
![Leader Board](https://github.com/alexisM8/BreakOut/blob/main/images/leaderboard.png)

## Licence
This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/alexisM8/BreakOut/blob/main/LICENSE) file for details
