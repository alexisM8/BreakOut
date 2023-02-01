#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "Textbox.hpp"


class SaveScore : public Engine::State{
    private:
        int m_score;
        
        std::shared_ptr<Engine::Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_exitButton;
        sf::Text m_menuButton;
        
        Textbox m_textbox;

        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;

        bool m_isMainMenuButtonSelected;
        bool m_isMainMenuButtonPressed;
    
        //background
        sf::Sprite m_background;

        //sound
        float m_musicVolume;
        float m_soundVolume;
    public:
        SaveScore(std::shared_ptr<Engine::Context> &context);
        SaveScore(std::shared_ptr<Engine::Context> &context, int score, float soundVolume, float musicVolume);

        void updateLeaderBoard();

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltatime) override;
        void Draw() override;

};
