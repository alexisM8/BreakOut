#pragma once
#include <fstream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include "State.hpp"
#include "Game.hpp"


class LeaderBoard : public Engine::State{
    private:
        int m_score;
        
        std::shared_ptr<Engine::Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_exitButton;
        sf::Text m_menuButton;
        sf::Text m_scoresText;
        sf::Text m_userNameText;
        sf::Text m_userNames;
        sf::Text m_scores;

        std::string m_rowNames;
        std::string m_rowScores;

        sf::RectangleShape m_verticalLine;
        sf::RectangleShape m_horizontalLine;
        
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
        LeaderBoard(std::shared_ptr<Engine::Context> &context);
        LeaderBoard(std::shared_ptr<Engine::Context> &context, float soundVolume, float musicVolume);

        void sortScores();
        void setUsersAndScores();

        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltatime) override;
        void Draw() override;

};
