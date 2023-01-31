#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "SFML/Audio/SoundBuffer.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "helperLogic.hpp"
#include <memory>
#include <array>
#include <stdio.h>
#include <list>

class GameLogic : public Engine::State {
    private:
        //states
        std::shared_ptr<Engine::Context> m_context;
        //velocity  of objects
        float m_globalVelocity;
        float m_velocityIncrement;

        //player
        sf::Sprite m_player;
        float m_playerVelocity;
        int m_lives;

        //ball 
        Ball m_ball;
        float m_ballVelocity;

        //bricks
        std::array<Brick, row*col> m_bricks;
        
        //ui
        int m_score;
        sf::Text m_scoreTxt;
        bool m_isPasued;

        //sounds
        float m_soundVolume;
        float m_musicVolume;

        //background
        sf::Sprite m_background;
    public:
    GameLogic(std::shared_ptr<Engine::Context> &context);
    GameLogic(std::shared_ptr<Engine::Context> &context, float soundVolume, float musicVolume);
    ~GameLogic();
    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltatime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
    bool nobricks(const std::array<Brick, row*col> &);

    
};

