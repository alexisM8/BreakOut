#pragma once
#include <memory>
#include "SFML/Graphics/Sprite.hpp"
#include "State.hpp"
#include "Game.hpp"

class MainMenu : public Engine::State{
    private:
        std::shared_ptr<Engine::Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_playButton;
        sf::Text m_exitButton;
        sf::Text m_controlButton;
        sf::Text m_leaderboardButton;

        bool m_isPlayButtonSelected;
        bool m_isPlayButtonPressed;
    
        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;

        bool m_isControlButtonSelected;
        bool m_isControlButtonPressed;

        bool m_isLeaderboardButtonSelected;
        bool m_isLeaderboardButtonPressed;

        bool m_isPaused;

        //background
        sf::Sprite m_background;

        //sound
        float m_soundVolume;
        float m_musicVolume;
        // sf::Sound m_scroll;
        // sf::Music m_music;
    public:
        MainMenu(std::shared_ptr<Engine::Context> &context);
        MainMenu(std::shared_ptr<Engine::Context> &context, float soundVolume, float musicVolume);
        ~MainMenu();
    
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltatime) override;
        void Draw() override;
        void Pause() override;
        void Start() override;
};


