#include "../include/Game.hpp"
#include "../include/MainMenu.hpp"
#include "SFML/Window/WindowStyle.hpp"

Game::Game(): m_context(std::make_shared<Engine::Context>()){
    m_context->m_window->create(sf::VideoMode(1920, 1080), "BreakOut!");
    //to do:
    m_context->m_states->add(std::make_unique<MainMenu>(m_context));
}
Game::~Game(){
    
}
void Game::run(){
    
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;
    
    while(m_context->m_window->isOpen()){
        timeSinceLastFrame += clock.restart();
        while(timeSinceLastFrame > timePerFrame){
            timeSinceLastFrame -= timePerFrame;
            m_context->m_states->processStateChange();
            m_context->m_states->getCurrentState()->ProcessInput();
            m_context->m_states->getCurrentState()->Update(timePerFrame);
            m_context->m_states->getCurrentState()->Draw();
                    
            
        }
    }
    
}
