#pragma once
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "State.hpp"
#include "Game.hpp"

class PauseGame : public Engine::State{
    private:
        std::shared_ptr<Engine::Context> m_context;
        sf::Text m_pausedTitle;
        sf::Text m_resumeButton;
        sf::Text m_exitButton;
        sf::Text m_restartButton;

        bool m_isResumeButtonSelected;
        bool m_isResumeButtonPressed;
    
        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;

        bool m_isRestartButtonSelected;
        bool m_isRestartButtonPressed;
    public:
        PauseGame(std::shared_ptr<Engine::Context> &m_context);
        ~PauseGame();
    
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltatime) override;
        void Draw() override;
    
    
};


