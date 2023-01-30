#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

namespace Engine{
    class State{
        public:
            State(){};
            virtual ~State(){};
            virtual void Init() = 0; //sprites text
            virtual void ProcessInput() = 0; //key press
            virtual void Update(sf::Time deltatime) = 0;
            virtual void Draw() = 0;
        
            virtual void Pause(){};
            virtual void Start(){};
    };
}

