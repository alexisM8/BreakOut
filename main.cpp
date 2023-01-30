#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include <string>
#include <random>
#include "include/Game.hpp"

// constexpr int screenWidth = 1920;
// constexpr int screenHeight = 1080;
// constexpr int row = 7;
// constexpr int col = 9;
// constexpr int bhspace = 10;
// constexpr int bvspace = 5;
// constexpr float bwidth = (screenWidth - (col + 1) * bhspace) / float(col);
// constexpr float bheight = ((screenHeight / 3) - (row + 1) * bvspace) / float(row);
// constexpr int frames = 50;

// struct Ball{
// public:
//     sf::CircleShape circ;
//     float xvel{0.0f};
//     float yvel{0.0f};
//     bool bound{true};
// };
//
// struct brick{
//     sf::RectangleShape b;
//     bool visible{true};
// };
//
//
// float rands(int low, int high){
//     std::random_device d{};
//     std::mt19937 engine{d()};
//     std::uniform_int_distribution<> range(low, high);
//     return range(engine);
// }
//
// float randfs(float low, float high){
//     std::random_device d{};
//     std::mt19937 engine{d()};
//     std::uniform_real_distribution<> range(low, high);
//     return range(engine);
// }
//
// struct colorStruct{
//     double r;
//     double g;
//     double b;
// };
//
// colorStruct HSItoRGB(int i, int numElem){
//     auto factor = 360.0f/numElem;
//     auto h = i * factor;
//     auto in = 78.0f;
//     auto hp = h/60.0;
//     auto s = 1.0f;
//     auto z = 1.0f - fabs(fmod(hp, 2)-1);
//     auto c = (3.0f * in * s)/1+z;
//     auto x = c*z;
//     double r = 0, g = 0, b = 0;
//     if(hp >= 0 && hp <= 1){
//         r = c;
//         g = x;
//         b = 0;
//     }else if(hp >= 1 && hp <= 2){
//         r = x;
//         g = c;
//         b = 0;
//     }else if(hp >= 2 && hp <= 3){
//         r = 0;
//         g = c;
//         b = x;
//     }else if(hp >= 3 && hp <= 4){
//         r = 0;
//         g = x;
//         b = c;
//     }else if(hp >= 4 && hp <= 5){
//         r = x;
//         g = 0;
//         b = c;
//     }else{
//         r = c;
//         g = 0;
//         b = x;
//     }
//     auto m = in * (1-s);
//     colorStruct result{r+m, g+m, b+m};
//     return result;
// }
//
// bool circAndRectCollision(sf::RectangleShape &rect, sf::CircleShape &circ){
//     sf::Vector2f originalOrig = circ.getOrigin();
//     circ.setOrigin({circ.getPosition().x+circ.getRadius(), circ.getPosition().y+circ.getRadius()});
//     float testX = circ.getPosition().x;
//     float testY = circ.getPosition().y;
//
//     sf::Vector2f cp = circ.getPosition();
//     sf::Vector2f rp = rect.getPosition();
//     sf::Vector2f rs = rect.getSize();
//
//     if(cp.x < rp.x) testX = rp.x;
//     else if(cp.x > rp.x + rs.x) testX = rp.x + rs.x;
//     if(cp.y < rp.y) testY = rp.y;
//     else if(cp.y > rp.y + rs.y) testY = rp.y + rs.y;
//
//     float distX = cp.x - testX;
//     float distY = cp.y - testY;
//     float distance = std::sqrt((distX*distX) + (distY*distY));
//    
//     circ.setOrigin(originalOrig);
//     if(distance <= circ.getRadius()){
//         return true;
//     }
//     return false;
// }
//
// int main(){
//     std::string fps = "FPS: ";
//     sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "BREAK OUT");
//     window.setFramerateLimit(frames);
//
//     std::array<brick, row*col> bricks;
//     
//     float ypos = 40;
//     for(int r = 0; r < row; r++){
//         colorStruct color = HSItoRGB(r, row);      
//         float xpos = bhspace;
//         for(int c = 0; c < col; c++){
//             bricks[r * col + c].b.setSize({bwidth, bheight});
//             bricks[r * col + c].b.setFillColor(sf::Color(color.r, color.g, color.b));
//             bricks[r * col + c].b.setPosition({xpos, ypos});
//             xpos += bhspace + bwidth;
//         }
//         ypos += bvspace + bheight;
//     }
//
//     sf::Font font;
//     if(!font.loadFromFile("./font/Andale Mono.ttf")){
//         std::cout << "ERROR: Failed to load font!\n";
//     }
//
//     sf::Text text;
//     text.setFont(font);
//     text.setString(fps);
//     text.setCharacterSize(20);
//     text.setFillColor(sf::Color::White);
//     text.setStyle(sf::Text::Bold);
//
//     float playerVel = 5.0f;
//     sf::RectangleShape player;
//     player.setSize({bwidth*2, bheight*2});
//     player.setFillColor(sf::Color(255, 255, 255));
//     player.setPosition({screenWidth / 2 - player.getSize().x / 2, screenHeight - player.getSize().y * 2});
//
//     float ballVel = 3.0f;
//     Ball ball;
//     ball.circ.setRadius(bheight);
//     ball.circ.setFillColor(sf::Color::White);
//     ball.circ.setPosition({screenWidth / 2 - ball.circ.getRadius(), screenHeight - player.getSize().y * 3});
//     auto ballLockPos = ball.circ.getPosition();
//
//     float velInc = 0.1f;
//
//     std::chrono::high_resolution_clock::time_point start;
//     std::chrono::high_resolution_clock::time_point end;
//     float FPS = 0;
//
//     while(window.isOpen()){
//         sf::Event ev;
//
//         while(window.pollEvent(ev)){
//             if(ev.type == sf::Event::Closed || ((ev.type == sf::Event::KeyPressed) && ev.key.code == sf::Keyboard::Escape)){
//                 window.close();
//            }
//
//             if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space){
//                 if(ball.bound){
//                     ball.bound = false;
//                     ball.xvel = ballVel;
//                     ball.yvel = -1 * ballVel;
//                 }
//             } 
//             if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::R){
//                 ball.bound = true;
//                 ball.circ.setPosition({player.getPosition().x + player.getSize().x/2 - ball.circ.getRadius(), screenHeight - 3 * player.getSize().y });
//                 ballVel = 3.0f;
//             }
//             // text.setString("Player corrdinates: (" + std::to_string(player.getPosition().x) + ", " + std::to_string(player.getPosition().y) + ")\n");
//         }
//
//         if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Left){
//             if(player.getPosition().x < 0){
//                 player.setPosition({0, player.getPosition().y});
//                 if(ball.bound) ball.circ.setPosition({player.getPosition().x + player.getSize().x/2, ball.circ.getPosition().y});
//             }else{
//                 if(!ball.bound){
//                     player.move({-1.0f * playerVel, 0});
//                 }else{
//                     player.move({-1.0f * playerVel, 0});
//                     ball.circ.move({-1.0f * playerVel, 0});
//                 }
//             }
//         }
//
//         if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Right){
//             if(player.getPosition().x + player.getSize().x > screenWidth){
//                 player.setPosition({screenWidth - player.getSize().x, player.getPosition().y});
//                 if(ball.bound) ball.circ.setPosition({player.getPosition().x + player.getSize().x/2, ball.circ.getPosition().y});
//             }else{
//                 if(!ball.bound){
//                     player.move({playerVel, 0});
//                 }else{
//                     player.move({playerVel, 0});
//                     ball.circ.move({playerVel, 0});
//                 }
//             }
//         }
//         
//         sf::RectangleShape temp({ball.circ.getRadius()*2, ball.circ.getRadius()*2});
//         temp.setPosition(ball.circ.getPosition());
//         temp.setFillColor(sf::Color::Red);
//
//         if(!ball.bound){
//             for(auto &b : bricks){
//                 if(b.visible && circAndRectCollision(b.b, ball.circ)){
//                     b.visible = false;
//                     ballVel += velInc;
//                     ball.yvel = ballVel ;
//                 }
//             }
//
//             if(circAndRectCollision(player, ball.circ)){
//                 ball.yvel =  -1.0f * ballVel;
//             }
//
//             if(ball.circ.getPosition().x + ball.circ.getRadius() * 2 > screenWidth) ball.xvel = -1.0f * ballVel;
//             if(ball.circ.getPosition().x < 0) ball.xvel = ballVel;
//             if(ball.circ.getPosition().y + ball.circ.getRadius() * 2 > screenHeight) ball.yvel = -1.0f * ballVel;
//             if(ball.circ.getPosition().y < 0) ball.yvel = ballVel;
//             if(ball.circ.getPosition().y + ((ball.circ.getRadius() * 2) - 10) > player.getPosition().y){
//                 ball.bound = true;
//                 ball.circ.setPosition({player.getPosition().x + player.getSize().x/2 - ball.circ.getRadius(), screenHeight - 3 * player.getSize().y });
//                 ballVel = 3.0f;
//             }else{
//                 ball.circ.move({ball.xvel, ball.yvel});
//             }
//         }
//         text.setString(fps + std::to_string(int(FPS)) + " ball velocity: " + std::to_string(float(ballVel)));
//         
//         start = std::chrono::high_resolution_clock::now();
//         window.clear(sf::Color(0, 0, 0));
//
//         for(auto &b : bricks){
//             if(b.visible) window.draw(b.b);
//         }
//
//         // window.draw(temp);
//         window.draw(ball.circ);
//         window.draw(player);
//         window.draw(text);
//         window.display();
//         end = std::chrono::high_resolution_clock::now();
//         FPS = (float)1e9/(float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
//     }
//
//     return 0;
// }

int main(){
    Game g;
    g.run();
    return 0;
}
