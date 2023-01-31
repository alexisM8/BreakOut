#pragma once
#include <memory>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "State.hpp"
#include "Game.hpp"

class Control : public Engine::State{
    private:
        std::shared_ptr<Engine::Context> m_context;
        sf::Text m_gameTitle;
        sf::Text m_menuButton;
        sf::Text m_exitButton;

        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;

        bool m_isMenuButtonSelected;
        bool m_isMenuButtonPressed;

        //sprites
        sf::Sprite m_background;
        sf::Sprite m_leftArrow;
        sf::Sprite m_rightArrow;
        sf::Sprite m_space;
        sf::Sprite m_keyp;
        sf::Sprite m_zero;
        sf::Sprite m_one;
        sf::Sprite m_two;
        sf::Sprite m_nine;
        sf::Sprite m_upArrow;
        sf::Sprite m_downArrow;

        //sprite pos animaiton
        sf::IntRect m_leftArrowPosition;
        sf::IntRect m_rightArrowPosition;
        sf::IntRect m_spacePosition;
        sf::IntRect m_pPosition;
        sf::IntRect m_onePosition;
        sf::IntRect m_twoPosition;
        sf::IntRect m_ninePosition;
        sf::IntRect m_zeroPosition;
        sf::IntRect m_upArrowPosition;
        sf::IntRect m_downArrowPosition;

        //text instructions
        sf::Text m_upArrowInstuctions;
        sf::Text m_leftArrowInstructions;
        sf::Text m_oneInstructions;
        sf::Text m_twoInstructions;
        sf::Text m_nineInstructions;
        sf::Text m_zeroInstructions;
        sf::Text m_spaceInstructions;
        sf::Text m_pInstructions;

        //sound
        float m_soundVolume;
        float m_musicVolume;
        // sf::Sound m_scroll;
        // sf::Music m_music;
    public:
        Control(std::shared_ptr<Engine::Context> &m_context);
        Control(std::shared_ptr<Engine::Context> &m_context, float soundVolume, float musicVolume);
        ~Control();
    
        void Init() override;
        void ProcessInput() override;
        void Update(sf::Time deltatime) override;
        void Draw() override;
};


