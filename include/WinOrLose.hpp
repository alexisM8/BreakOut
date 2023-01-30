#pragma once
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "State.hpp"
#include "Game.hpp"

class WinOrLose : public Engine::State{
    private:
        std::shared_ptr<Engine::Context> m_context;
        sf::Text m_statusTitle;
        sf::Text m_nextlvlButton;
        sf::Text m_restartGameButton;
        sf::Text m_exitButton;
        sf::Text m_scoreTxt;
        int m_score;
        int m_lvlBeat;
        bool m_statewol;
        
        bool m_isNextlvlButtonSelected;
        bool m_isNextlvlButtonPressed;
    
        bool m_isRestartGameButtonSelected;
        bool m_isRestartGameButtonPressed;
        
        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;
    public:
        WinOrLose(std::shared_ptr<Engine::Context> &m_context, bool stateWoL, int score, int lvlbeat);
        ~WinOrLose();
    
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltatime) override;
        void Draw() override;
    
};


