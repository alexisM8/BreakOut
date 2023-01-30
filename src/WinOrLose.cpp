#include "../include/helperLogic.hpp"
#include "../include/WinOrLose.hpp"
// #include "leveltwo.hpp"
#include "../include/GameLogic.hpp"
#include <iostream>

WinOrLose::WinOrLose(std::shared_ptr<Engine::Context> &context, bool stateWoL, int score, int lvlbeat): m_context(context), m_statewol(stateWoL), m_score(score), m_lvlBeat(lvlbeat), m_isNextlvlButtonSelected(true),
m_isNextlvlButtonPressed(false), m_isRestartGameButtonSelected(false), m_isRestartGameButtonPressed(false),m_isExitButtonSelected(false), m_isExitButtonPressed(false){
    
}

WinOrLose::~WinOrLose(){/*empty*/}

void WinOrLose::Init(){

    m_statusTitle.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_nextlvlButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_restartGameButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_exitButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_scoreTxt.setFont(m_context->m_assest->getFont(MAIN_FONT));
    //name
    if(m_statewol){
        m_statusTitle.setString("LVL " + std::to_string(m_lvlBeat) + " complete");
        m_statusTitle.setCharacterSize(80);
        m_statusTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_statusTitle.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_statusTitle.getGlobalBounds().height / 2.0 - 150.0));
    }else{
        m_statusTitle.setString("Game Failed");
        m_statusTitle.setCharacterSize(80);
        m_statusTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_statusTitle.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_statusTitle.getGlobalBounds().height / 2.0 - 150.0));
    }
    
    //next level button
    m_nextlvlButton.setString("Next Level");
    m_nextlvlButton.setCharacterSize(50);
    m_nextlvlButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_nextlvlButton.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_nextlvlButton.getGlobalBounds().height / 2.0 - 30.0f));
    //restart game button
    m_restartGameButton.setString("Restart Game");
    m_restartGameButton.setCharacterSize(50);
    m_restartGameButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_restartGameButton.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_restartGameButton.getGlobalBounds().height / 2.0 + 30.0f));
    //exit button
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(50);
    m_exitButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_exitButton.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_exitButton.getGlobalBounds().height / 2.0 + 90.0f));
}
void WinOrLose::ProcessInput(){
    sf::Event ev;
    while(m_context->m_window->pollEvent(ev)){
        if(ev.type == sf::Event::Closed){
            m_context->m_window->close();
        }else if(ev.type == sf::Event::KeyPressed){
            switch (ev.key.code) {
                case sf::Keyboard::Up:{
                    if(m_isExitButtonSelected){
                        m_isNextlvlButtonSelected = false;
                        m_isRestartGameButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }else if(m_isRestartGameButtonSelected){
                        m_isNextlvlButtonSelected = true;
                        m_isRestartGameButtonSelected = false;
                        m_isExitButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:{
                    if(m_isNextlvlButtonSelected){
                        m_isNextlvlButtonSelected = false;
                        m_isRestartGameButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }else if(m_isRestartGameButtonSelected){
                        m_isNextlvlButtonSelected = false;
                        m_isRestartGameButtonSelected = false;
                        m_isExitButtonSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Escape:{
                    m_context->m_window->close();
                    break;
                }
                case sf::Keyboard::Return:{
                    m_isExitButtonPressed = false;
                    m_isNextlvlButtonPressed = false;
                    m_isRestartGameButtonPressed = false;
                    
                    if(m_isNextlvlButtonSelected){
                        m_isNextlvlButtonPressed = true;
                    }else if(m_isRestartGameButtonSelected){
                        m_isRestartGameButtonPressed = true;
                    }else{
                        m_isExitButtonPressed = true;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
}
void WinOrLose::Update(sf::Time deltatime){
    if(m_isNextlvlButtonSelected){
        m_nextlvlButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setFillColor(sf::Color::White);
        m_restartGameButton.setFillColor(sf::Color::White);
    }else if(m_isRestartGameButtonSelected){  m_restartGameButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setFillColor(sf::Color::White);
        m_nextlvlButton.setFillColor(sf::Color::White);
    }else{
        m_restartGameButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Yellow);
        m_nextlvlButton.setFillColor(sf::Color::White);
    }
    
    if(m_isNextlvlButtonPressed){
        switch(m_lvlBeat){
            case 1:
                //TODO: make lvl 2
                // m_context->m_states->add(std::make_unique<LevelTwo>(m_context, m_score), true);
                break;
        }
        
    }else if(m_isRestartGameButtonPressed){
        m_context->m_states->add(std::make_unique<GameLogic>(m_context), true);
    }else if(m_isExitButtonPressed){
       m_context->m_window->close();
    }
}
void WinOrLose::Draw(){
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_statusTitle);
    m_context->m_window->draw(m_nextlvlButton);
    m_context->m_window->draw(m_restartGameButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}

