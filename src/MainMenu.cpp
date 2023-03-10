#include "../include/helperLogic.hpp"
#include "../include/MainMenu.hpp"
#include "../include/Controls.hpp"
#include "../include/GameLogic.hpp"
#include "../include/LeaderBoard.hpp"
#include <iostream>
#include <memory>

MainMenu::MainMenu(std::shared_ptr<Engine::Context> &context): 
                            m_context(context),
                            m_musicVolume(100.0f),
                            m_soundVolume(100.0f),
                            m_isPaused(false), 
                            m_isPlayButtonSelected(true),
                            m_isPlayButtonPressed(false),
                            m_isControlButtonSelected(false),
                            m_isControlButtonPressed(false),
                            m_isLeaderboardButtonSelected(false),
                            m_isLeaderboardButtonPressed(false),
                            m_isExitButtonSelected(false),
                            m_isExitButtonPressed(false){/*empty*/}
MainMenu::MainMenu(std::shared_ptr<Engine::Context> &context, float soundVolume, float musicVolume): 
                            m_context(context),
                            m_musicVolume(musicVolume),
                            m_soundVolume(soundVolume),
                            m_isPaused(false), 
                            m_isPlayButtonSelected(true),
                            m_isPlayButtonPressed(false),
                            m_isControlButtonSelected(false),
                            m_isControlButtonPressed(false),
                            m_isLeaderboardButtonSelected(false),
                            m_isLeaderboardButtonPressed(false),
                            m_isExitButtonSelected(false),
                            m_isExitButtonPressed(false){/*empty*/}
MainMenu::~MainMenu(){/*empty*/}

void MainMenu::Init(){
    m_context->m_assest->AddFont(MAIN_FONT, "../assets/fonts/Monaco.ttf");
    m_gameTitle.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_playButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_controlButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_leaderboardButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_exitButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    //name
    m_gameTitle.setString("Break Out!");
    m_gameTitle.setCharacterSize(80);
    m_gameTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_gameTitle.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_gameTitle.getGlobalBounds().height / 2.0 - 150.0));
    m_gameTitle.setFillColor(sf::Color::Black);
    //play button
    m_playButton.setString("Play");
    m_playButton.setCharacterSize(50);
    m_playButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) 
                                          - m_playButton.getGlobalBounds().width /
                                          2.0, m_context->m_window->getSize().y /
                                          2.0 - m_playButton.getGlobalBounds().height
                                          / 2.0 - 30.0));
    m_playButton.setFillColor(sf::Color::Black);

    //controls button
    m_controlButton.setString("Controls");
    m_controlButton.setCharacterSize(50);
    m_controlButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_controlButton.getGlobalBounds().width / 2.0, m_playButton.getPosition().y + 60.0f));
    m_controlButton.setFillColor(sf::Color::Black);

    //leaderboard
    m_leaderboardButton.setString("Leaderboard");
    m_leaderboardButton.setCharacterSize(50);
    m_leaderboardButton.setPosition({(float)m_context->m_window->getSize().x / 2 - m_leaderboardButton.getGlobalBounds().width / 2, m_controlButton.getPosition().y + 60.0f});
    m_leaderboardButton.setFillColor(sf::Color::Black);
    //exit button
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(50);
    m_exitButton. setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_exitButton.getGlobalBounds().width / 2.0, m_leaderboardButton.getPosition().y + 60.0f));
    m_exitButton.setFillColor(sf::Color::Black);


    //Background
    m_context->m_assest->AddTexture(MENUBACKGROUND, "../assets/textures/Clouds 2.png");
    m_background.setTexture(m_context->m_assest->getTexture(MENUBACKGROUND));
    m_background.setScale(3.35, 3.35);
    m_background.setPosition(0,0);
 

    //sound
    m_context->m_assest->AddSound(SCROLL,"../assets/sound/scroll.wav" );
    m_context->m_assest->AddSound(SOUNDC, "../assets/sound/collide.wav");
    m_context->m_sound->setBuffer(m_context->m_assest->getSound(SCROLL));

    m_context->m_assest->AddMusic(MENUMUSIC,"../assets/sound/menu.wav" );
    m_context->m_assest->AddMusic(GAMEMUSIC, "../assets/sound/pixle_perfect.wav");
    m_context->m_assest->AddMusic(CONTROLMUSIC, "../assets/sound/control.wav");
    m_context->m_music->openFromFile(m_context->m_assest->getMusic(MENUMUSIC));
    m_context->m_music->setVolume(m_musicVolume);
    m_context->m_music->setLoop(true);
    m_context->m_music->play();
}
void MainMenu::ProcessInput(){
    sf::Event ev;
    while(m_context->m_window->pollEvent(ev)){
        if(ev.type == sf::Event::Closed){
            m_context->m_window->close();
        }else if(ev.type == sf::Event::KeyPressed){
            switch (ev.key.code) {
                case sf::Keyboard::Up:{
                    if(m_isExitButtonSelected){
                        m_isPlayButtonSelected = false;
                        m_isControlButtonSelected = false;
                        m_isExitButtonSelected = false;
                        m_isLeaderboardButtonSelected = true;
                    }else if(m_isControlButtonSelected){
                        m_isPlayButtonSelected = true;
                        m_isControlButtonSelected = false;
                        m_isExitButtonSelected = false;
                        m_isLeaderboardButtonSelected = false;
                    }else if(m_isLeaderboardButtonSelected){
                        m_isControlButtonSelected = true;
                        m_isLeaderboardButtonSelected = false;
                        m_isExitButtonSelected = false;
                        m_isPlayButtonSelected = false;
                    }
                    m_context->m_sound->play();
                    break;
                }
                case sf::Keyboard::Down:{
                    if(m_isPlayButtonSelected){
                        m_isPlayButtonSelected = false;
                        m_isControlButtonSelected = true;
                        m_isExitButtonSelected = false;
                        m_isLeaderboardButtonSelected = true;
                    }else if(m_isControlButtonSelected){
                        m_isPlayButtonSelected = false;
                        m_isControlButtonSelected = false;
                        m_isExitButtonSelected = false;
                        m_isLeaderboardButtonSelected = true;
                    }else if(m_isLeaderboardButtonSelected){
                        m_isExitButtonSelected = true;
                        m_isLeaderboardButtonSelected = false;
                        m_isPlayButtonSelected = false;
                        m_isControlButtonSelected = false;
                    }
                    m_context->m_sound->play();
                    break;
                }
                case sf::Keyboard::Escape:{
                    m_context->m_window->close();
                    break;
                }
                case sf::Keyboard::Return:{
                    m_isExitButtonPressed = false;
                    m_isPlayButtonPressed = false;
                    m_isControlButtonPressed = false;
                    m_isLeaderboardButtonPressed = false; 
                    m_context->m_sound->play();
                    
                    if(m_isPlayButtonSelected){
                        m_isPlayButtonPressed = true;
                    }else if(m_isControlButtonSelected){
                        m_isControlButtonPressed = true;
                    }else if(m_isExitButtonSelected){
                        m_isExitButtonPressed = true;
                    }else if(m_isLeaderboardButtonSelected){
                        m_isLeaderboardButtonPressed = true;
                    }
                    break;
                }

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
                default:
                    break;
            }
        }
    }
}
void MainMenu::Update(sf::Time deltatime){
    if(!m_isPaused){
        if(m_isPlayButtonSelected){
            m_playButton.setFillColor(sf::Color(62, 118, 185));
            m_exitButton.setFillColor(sf::Color::Black);
            m_controlButton.setFillColor(sf::Color::Black);
            m_leaderboardButton.setFillColor(sf::Color::Black);
        }else if(m_isExitButtonSelected){
            m_exitButton.setFillColor(sf::Color(62, 118, 185));
            m_playButton.setFillColor(sf::Color::Black);
            m_controlButton.setFillColor(sf::Color::Black);
            m_leaderboardButton.setFillColor(sf::Color::Black);
        }else if(m_isControlButtonSelected){
            m_playButton.setFillColor(sf::Color::Black);
            m_controlButton.setFillColor(sf::Color(62, 118, 185));
            m_exitButton.setFillColor(sf::Color::Black);
            m_leaderboardButton.setFillColor(sf::Color::Black);
        }else if(m_isLeaderboardButtonSelected){
            m_leaderboardButton.setFillColor(sf::Color(62, 118, 185));
            m_exitButton.setFillColor(sf::Color::Black);
            m_playButton.setFillColor(sf::Color::Black);
            m_controlButton.setFillColor(sf::Color::Black);
        }

        if(m_isPlayButtonPressed){
            m_isPlayButtonPressed = false;
            m_context->m_states->add(std::make_unique<GameLogic>(m_context, m_soundVolume, m_musicVolume), true);
        }else if(m_isExitButtonPressed){
           m_context->m_window->close();
        }else if(m_isControlButtonPressed){
            m_isControlButtonPressed = false;
            m_context->m_states->add(std::make_unique<Control>(m_context, m_soundVolume, m_musicVolume), false);
        }else if(m_isLeaderboardButtonPressed){
            m_isLeaderboardButtonPressed = false;
            m_context->m_states->add(std::make_unique<LeaderBoard>(m_context, m_soundVolume, m_musicVolume), false);
        }
    }
}
void MainMenu::Draw(){
    m_context->m_window->clear();
    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_controlButton);
    m_context->m_window->draw(m_leaderboardButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
    
}

void MainMenu::Pause(){
    m_isPaused = true;
}
void MainMenu::Start(){
    m_isPaused = false;
}
