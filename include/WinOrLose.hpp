#pragma once
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "State.hpp"
#include "Game.hpp"

class WinOrLose : public Engine::State{
    private:
        std::shared_ptr<Engine::Context> m_context;
        sf::Text m_statusTitle;
        sf::Text m_saveScoreButton;
        sf::Text m_restartGameButton;
        sf::Text m_exitButton;
        sf::Text m_scoreTxt;
        int m_score;
        int m_lives;
        bool m_statewol;
        
        bool m_isSaveScoreButtonSelected;
        bool m_isSaveScoreButtonPressed;
    
        bool m_isRestartGameButtonSelected;
        bool m_isRestartGameButtonPressed;
        
        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;

        sf::Sprite m_wolBackground;
       
        float m_soundVolume;
        float m_musicVolume; 
    public:
        WinOrLose(std::shared_ptr<Engine::Context> &m_context, int score, int lvlbeat);
        ~WinOrLose();
    
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltatime) override;
        void Draw() override;
    
};


