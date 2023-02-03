#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "Game.hpp"
#include <algorithm>
#include <memory>
#include <string>

class Textbox{
    private:
        std::shared_ptr<Engine::Context> m_context;
        sf::Text m_username;
        sf::RectangleShape m_box;
        std::string m_text;
        std::string m_strUsername{};
        int m_limit;

    public:
        Textbox(std::shared_ptr<Engine::Context> &context);
        Textbox();
        
        bool typable{true};
        
        void setPosition(const sf::Vector2f& pos);
        const sf::Vector2f& getPosition();
        
        void setSize(const sf::Vector2f& pos);
        const sf::Vector2f& getSize();
    
        void setString(const std::string& text);
        std::string &getString();
        void setCharacterSize(unsigned int size);

        void setColor(const sf::Color& background, const sf::Color& foreground);

        void draw();

        void setContext(std::shared_ptr<Engine::Context> &context);
        
        void addChar(char ch);

        void setFont(const sf::Font& font);
};
