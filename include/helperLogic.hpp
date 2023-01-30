#pragma once
#include <SFML/Graphics.hpp>

constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;
constexpr int row = 4;//7
constexpr int col = 5;//9
constexpr int bhspace = 10;
constexpr int bvspace = 5;
constexpr float bwidth = (screenWidth - (col + 1) * bhspace) / float(col);
constexpr float bheight = (((float)screenHeight / 3) - (row + 1) * bvspace) / float(row);
constexpr int frames = 50;

struct Brick{
    sf::Sprite brick;
    bool visible{true};
};

struct Ball{
    sf::Sprite ball;
    bool bound{true};
    float xvel{0.0f};
    float yvel{0.0f};
};  

struct colorStruct{
    double r;
    double g;
    double b;
};

enum AssetID{
    MAIN_FONT = 0,
    PLAYER,
    BRICK,
    BALL,
    GAMEBACKGROUND,
    MENUBACKGROUND,
    SOUNDC,
    GAMEMUSIC,
    MENUMUSIC,
    SCROLL,
    LEFTARROW,
    RIGHTARROW,
    SPACE,
    ZERO,
    ONE,
    TWO,
    NINE,
    DOWNARROW, 
    UPARROW,
    P


};

colorStruct HSItoRGB(int i, int numElem);
