#include "../include/Textbox.hpp"
#include "../include/helperLogic.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include <memory>


Textbox::Textbox(std::shared_ptr<Engine::Context> &context) :
        m_context(context), m_limit(15){
    m_text = "";
    m_username.setString(">>> Enter UserName: " + m_text + "_");
    m_box = sf::RectangleShape();
}

Textbox::Textbox() : m_limit(15){
    m_text = "";
    m_username.setString(">>> Enter UserName: " + m_text + "_");
    m_box = sf::RectangleShape();
}

void Textbox::setContext(std::shared_ptr<Engine::Context> &context){
    m_context = context;
}

void Textbox::addChar(char ch){
   if(ch == '\b'){
        if(m_text.length() >= 1){
            m_text.pop_back();
            this->setString(m_text);
            m_strUsername = m_text;
        }

    }else if(ch == '\n'){
        ;
    }else{
        if(m_text.length() < m_limit){
            m_text.push_back(ch);
            this->setString(m_text);
            m_strUsername = m_text;
        }
    } 
}

void Textbox::setPosition(const sf::Vector2f& pos){
    m_username.setPosition(pos);
    m_box.setPosition(pos);
}

const sf::Vector2f& Textbox::getPosition(){
    return m_box.getPosition();
}

void Textbox::setSize(const sf::Vector2f& size){
    m_box.setSize(size);
}
        
const sf::Vector2f& Textbox::getSize(){
    return m_box.getSize();
}
    
void Textbox::setString(const std::string& text){
    m_username.setString(">>> Enter UserName: " + text + "_");
}
        
void Textbox::setCharacterSize(unsigned int size){
    m_username.setCharacterSize(size);
}

void Textbox::setColor(const sf::Color& background, const sf::Color& foreground){
    m_box.setFillColor(background);
    m_username.setFillColor(foreground);
}

void Textbox::draw(){
    m_context->m_window->draw(m_box);
    m_context->m_window->draw(m_username);
}


void Textbox::setFont(const sf::Font& font){
    m_username.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
}

std::string &Textbox::getString(){
    return m_strUsername;
}
