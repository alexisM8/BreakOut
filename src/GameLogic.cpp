#include "../include/helperLogic.hpp"
#include "../include/GameLogic.hpp"
#include "../include/PauseGame.hpp"
#include "../include/WinOrLose.hpp"
#include <string>
#include <time.h>
#include <iostream>
#include <cmath>

GameLogic::GameLogic(std::shared_ptr<Engine::Context> &context)
                : m_context(context),
                  m_musicVolume(100.0f),
                  m_soundVolume(100.0f),
                  m_score(0),  
                  m_isPasued(false),
                  m_lives(3),
                  m_globalVelocity(1.5f),
                  m_velocityIncrement(m_globalVelocity/20),
                  m_playerVelocity(m_globalVelocity), 
                  m_ballVelocity(m_globalVelocity*0.5f){ srand(time(nullptr)) ;}
GameLogic::GameLogic(std::shared_ptr<Engine::Context> &context, float soundVolume, float musicVolume)
                : m_context(context),
                  m_musicVolume(musicVolume),
                  m_soundVolume(soundVolume),
                  m_score(0),  
                  m_isPasued(false),
                  m_lives(3),
                  m_globalVelocity(1.5f),
                  m_velocityIncrement(m_globalVelocity/20),
                  m_playerVelocity(m_globalVelocity), 
                  m_ballVelocity(m_globalVelocity*0.5f){ srand(time(nullptr)) ;}

GameLogic::~GameLogic(){/*empty*/}

void GameLogic::Init(){
    //background
    m_context->m_assest->AddTexture(GAMEBACKGROUND, "../assets/textures/Clouds 4.png"); 
    m_background.setScale(3.35f, 3.35f);
    m_background.setTexture(m_context->m_assest->getTexture(GAMEBACKGROUND));
    m_background.setPosition({0.0f, 0.0f});
    
    //Player Info
    m_context->m_assest->AddTexture(PLAYER, "../assets/textures/player.png");
    m_player.setTexture(m_context->m_assest->getTexture(PLAYER));
    m_player.setScale(0.5f, 0.5f);
    m_player.setPosition((float)m_context->m_window->getSize().x / 2 
                         - m_player.getGlobalBounds().width,
                         m_context->m_window->getSize().y - 2 * 
                         m_player.getGlobalBounds().height);

    //Ball
    m_context->m_assest->AddTexture(BALL, "../assets/textures/ball.png");
    m_ball.ball.setTexture(m_context->m_assest->getTexture(BALL));
    m_ball.ball.setScale(0.1, 0.1);
    m_ball.ball.setPosition({m_player.getPosition().x + 
                                m_player.getGlobalBounds().width/2 - 
                                m_ball.ball.getGlobalBounds().width/2,
                                m_context->m_window->getSize().y - 
                                2 * m_player.getGlobalBounds().height - 
                                m_ball.ball.getGlobalBounds().height});
    
    //Bricks
    m_context->m_assest->AddTexture(BRICK, "../assets/textures/wall-surface-texture.jpg");
    float ypos = 40;
    for(int r = 0; r < row; r++){
        colorStruct color = HSItoRGB(r, row);      
        float xpos = bhspace*4;
        for(int c = 0; c < col; c++){
            m_bricks[r * col + c].brick.setTexture(m_context->m_assest->getTexture(BRICK));
            m_bricks[r * col + c].brick.setScale({bwidth*0.000099f, bheight*0.000099f});
            m_bricks[r * col + c].brick.setColor(sf::Color(color.r, color.g, color.b));
            m_bricks[r * col + c].brick.setPosition({xpos, ypos});
            xpos += bhspace + bwidth;
        }
        ypos += bvspace + bheight;
    }
    //score
    m_scoreTxt.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_scoreTxt.setPosition({0.0f, 0.0f});
    m_scoreTxt.setString("Score : " + std::to_string(m_score) + "\t\tLives: " + std::to_string(m_lives));
    m_scoreTxt.setFillColor(sf::Color::Black);

    //sound
    m_context->m_sound->setBuffer(m_context->m_assest->getSound(SOUNDC));
    m_context->m_music->openFromFile(m_context->m_assest->getMusic(GAMEMUSIC));
    m_context->m_music->setLoop(true);
    m_context->m_music->play();
}

void GameLogic::ProcessInput(){
    sf::Event ev;
    while(m_context->m_window->pollEvent(ev)){
        if(ev.type == sf::Event::Closed){
            m_context->m_window->close();
        }else if(ev.type == sf::Event::KeyPressed){
            switch(ev.key.code){
                case sf::Keyboard::Left:
                    m_playerVelocity = -1.0f * 2 * m_ballVelocity * 0.8f;  
                    break;
                case sf::Keyboard::Right:
                    m_playerVelocity = 1.0f * 2 * m_ballVelocity * 0.8f;
                    break;
                case sf::Keyboard::R:
                    m_ball.bound = true;
                    m_ball.ball.setPosition({m_player.getPosition().x + 
                                                m_player.getGlobalBounds().width/2 - 
                                                m_ball.ball.getGlobalBounds().width/2,
                                                m_context->m_window->getSize().y - 
                                                2 * m_player.getGlobalBounds().height - 
                                                m_ball.ball.getGlobalBounds().height});
                    break;
                case sf::Keyboard::A:
                    break;
                case sf::Keyboard::Space:
                    if(m_ball.bound){
                        m_ball.bound = false;
                        m_ball.xvel = m_ballVelocity;
                        m_ball.yvel = -1 * m_ballVelocity;
                    }
                    break;
                case sf::Keyboard::Num1:{
                    if(m_musicVolume <= 0) m_musicVolume = 0;
                    else m_musicVolume -= 10.0f;
                    m_context->m_music->setVolume(m_musicVolume);
                    break;
                }
                case sf::Keyboard::Num2:{
                    if(m_musicVolume >= 100) m_musicVolume = 100.0f;
                    else m_musicVolume  += 10.0f;
                    m_context->m_music->setVolume(m_musicVolume);
                    break;
                }
                case sf::Keyboard::Num9:{
                    if(m_soundVolume <= 0) m_soundVolume = 0;
                    else m_soundVolume -= 10.0f;
                    m_context->m_sound->setVolume(m_soundVolume);
                    break;
                }
                case sf::Keyboard::Num0:{
                    if(m_soundVolume >= 100) m_soundVolume = 100;
                    else m_soundVolume += 10.0f;
                    m_context->m_sound->setVolume(m_soundVolume);
                    break;
                }
                case sf::Keyboard::P:
                    m_context->m_states->add(std::make_unique<PauseGame>(m_context), false);
                    break;
                default: break;
            }
        }else if(ev.type == sf::Event::KeyReleased){
            m_playerVelocity = 0.0f;
        }
    }
}

void GameLogic::Update(sf::Time deltatime){
    if(!m_isPasued){
        if(m_lives < 0 || nobricks(m_bricks)){
            m_score = (m_lives > 1) ? m_score * m_lives : m_score;
            m_context->m_states->add(std::make_unique<WinOrLose>(m_context, m_score, m_lives, m_soundVolume, m_musicVolume), true);
        }
        //controlling player bounds
        if(m_player.getPosition().x < 0){
            m_player.setPosition({0, m_player.getPosition().y});
        }else if(m_player.getPosition().x + m_player.getGlobalBounds().width > 
                    m_context->m_window->getSize().x){
            m_player.setPosition({m_context->m_window->getSize().x -
                                    m_player.getGlobalBounds().width, 
                                    m_player.getPosition().y});
        }

        m_player.move(m_playerVelocity, 0);
        if(m_ball.bound){
            m_ball.ball.setPosition({m_player.getPosition().x + 
                                        m_player.getGlobalBounds().width/2, 
                                        m_ball.ball.getPosition().y});
        }

        if(!m_ball.bound){
            for(auto &b : m_bricks){
                if(b.visible && b.brick.getGlobalBounds().intersects(m_ball.ball.getGlobalBounds())){
                    b.visible = false;
                    m_ballVelocity += m_velocityIncrement;
                    m_ball.yvel = m_ballVelocity ;
                    m_score += std::ceil(100 * m_ballVelocity);
                    m_context->m_sound->play();
                }
            }

            if(m_ball.ball.getGlobalBounds().intersects(m_player.getGlobalBounds())){
                m_ball.yvel =  -1.0f * m_ballVelocity;
                m_context->m_sound->play();
            }

            if(m_ball.ball.getPosition().x + 
                m_ball.ball.getGlobalBounds().width > 
                m_context->m_window->getSize().x){
                    m_ball.xvel = -1.0f * m_ballVelocity;
            } 
            if(m_ball.ball.getPosition().x < 0){
                m_ball.xvel = m_ballVelocity;
            }
            if(m_ball.ball.getPosition().y + m_ball.ball.getGlobalBounds().height * 
                    2 > screenHeight){
                m_ball.yvel = -1.0f * m_ballVelocity;
            }
            if(m_ball.ball.getPosition().y < 0){
                m_ball.yvel = m_ballVelocity;
            }
            if(m_ball.ball.getPosition().y + 
                ((m_ball.ball.getGlobalBounds().height) - 10) >
                m_player.getPosition().y){
                m_ball.bound = true;
                m_ball.ball.setPosition({m_player.getPosition().x + 
                                            m_player.getGlobalBounds().width/2 - 
                                            m_ball.ball.getGlobalBounds().width/2,
                                            m_context->m_window->getSize().y - 
                                            2 * m_player.getGlobalBounds().height - 
                                            m_ball.ball.getGlobalBounds().height});
                m_ballVelocity = m_globalVelocity * 0.5f;
                m_lives--;
            }else{
                m_ball.ball.move({m_ball.xvel, m_ball.yvel});
            }
        }
        m_scoreTxt.setString("Score: " + std::to_string(m_score) + "\t\tLives: " + std::to_string(m_lives));
    }
}
void GameLogic::Draw(){
    m_context->m_window->clear();
    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_player);
    for(auto &b: m_bricks){
        if(b.visible)
            m_context->m_window->draw(b.brick);
    }
    m_context->m_window->draw(m_ball.ball);
    m_context->m_window->draw(m_scoreTxt);
    m_context->m_window->display();
}

void GameLogic::Pause(){
    m_isPasued = true;
}
void GameLogic::Start(){
    m_isPasued = false;
}

bool GameLogic::nobricks(const std::array<Brick, row*col> &bricks){
    bool done = true;
    for(auto &brk : bricks){
        if(brk.visible){
            done = false;
            break;
        }
    }
    return done;
}


