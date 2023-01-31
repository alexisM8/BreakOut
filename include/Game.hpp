#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <cmath>
#include "AssetManager.hpp"
#include "StateManager.hpp"

namespace  Engine{
    struct Context{
        std::unique_ptr<Engine::AssetManager> m_assest;
        std::unique_ptr<Engine::StateManager> m_states;
        std::unique_ptr<sf::RenderWindow> m_window;
        std::unique_ptr<sf::Clock> m_clock;
        std::unique_ptr<sf::Music> m_music;
        std::unique_ptr<sf::Sound> m_sound;
        
        Context(){
            m_assest = std::make_unique<Engine::AssetManager>();
            m_states = std::make_unique<Engine::StateManager>();
            m_window = std::make_unique<sf::RenderWindow>();
            m_clock  = std::make_unique<sf::Clock>(); 
            m_music  = std::make_unique<sf::Music>();
            m_sound  = std::make_unique<sf::Sound>();
        }
    };
}

class Game{
    private:
        std::shared_ptr<Engine::Context> m_context;
        const sf::Time timePerFrame = sf::seconds(1/500.0f);
        
    public:
        Game();
        ~Game();
        void run();

};



