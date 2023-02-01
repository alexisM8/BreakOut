#include "../include/SaveScore.hpp"
#include "../include/helperLogic.hpp"
#include "../include/MainMenu.hpp"
#include <string>
#include <iostream>

SaveScore::SaveScore(std::shared_ptr<Engine::Context> &context, 
                     int score, float soundVolume, float musicVolume)
                     : m_context(context),
                       m_score(score),
                       m_soundVolume(soundVolume),
                       m_musicVolume(musicVolume),
                       m_isMainMenuButtonSelected(true),
                       m_isMainMenuButtonPressed(false),
                       m_isExitButtonSelected(false),
                       m_isExitButtonPressed(false){/*empty*/}
void SaveScore::Init(){
    m_textbox.setContext(m_context);
    m_gameTitle.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_exitButton.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_menuButton.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_textbox.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));

    //title
    m_gameTitle.setString("Enter display name and return to Main Menu \nto save your score of: " + std::to_string(m_score));
    m_gameTitle.setCharacterSize(70);
    m_gameTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_gameTitle.getGlobalBounds().width / 2.0, 50.0));
    m_gameTitle.setFillColor(sf::Color::Black);

    //textbox
    m_textbox.setCharacterSize(50);
    m_textbox.setSize({1200, 60});  
    m_textbox.setColor(sf::Color(79, 79, 79, 100), sf::Color::Black);
    m_textbox.setPosition({(float)m_context->m_window->getSize().x / 2 - m_textbox.getSize().x / 2, m_gameTitle.getPosition().y + m_gameTitle.getGlobalBounds().height + 40});

    //menu button
    m_menuButton.setString("Main Menu");
    m_menuButton.setCharacterSize(50);
    m_menuButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_menuButton.getGlobalBounds().width / 2.0, m_textbox.getPosition().y + 3 * m_textbox.getSize().y ));
    m_menuButton.setFillColor(sf::Color::Black);

    //exit button
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(50);
    m_exitButton. setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_exitButton.getGlobalBounds().width / 2.0, m_menuButton.getPosition().y + 60.0f ));
    m_exitButton.setFillColor(sf::Color::Black);

    
    //backcround
    m_context->m_assest->AddTexture(SCOREBACKGROUND,"../assets/textures/Clouds 6.png");
    m_background.setTexture(m_context->m_assest->getTexture(AssetID::SCOREBACKGROUND));
    m_background.setScale(3.35, 3.35);
    m_background.setPosition(0,0);

    m_context->m_music->openFromFile(m_context->m_assest->getMusic(AssetID::CONTROLMUSIC));
    m_context->m_music->play();

}

void SaveScore::ProcessInput(){
    sf::Event ev;
    while (m_context->m_window->pollEvent(ev)) {
        if(ev.type == sf::Event::TextEntered && m_textbox.typable){
            m_textbox.addChar(ev.text.unicode);
            break;
        }else if(ev.type == sf::Event::Closed){
            m_context->m_window->close();
            break;
        }else if(ev.type == sf::Event::KeyPressed){
            switch (ev.key.code) {
                case sf::Keyboard::Up:{
                    if(m_isExitButtonSelected){
                        m_isMainMenuButtonSelected = true;
                        m_isExitButtonSelected = false;
                        m_context->m_sound->play();
                    }
                    break;
                }
                case sf::Keyboard::Down:{
                    if(m_isMainMenuButtonSelected){
                        m_isMainMenuButtonSelected = false;
                        m_isExitButtonSelected = true;
                        m_context->m_sound->play();
                    }
                    break;
                }
                case sf::Keyboard::Slash:{
                    m_textbox.typable = (m_textbox.typable == true) ? false : true; 
                    break;
                }
                case sf::Keyboard::Return:{
                    m_isExitButtonPressed = false;
                    m_isMainMenuButtonPressed = false;
                    m_context->m_sound->play();
                    
                    if(m_isMainMenuButtonSelected){
                        m_isMainMenuButtonPressed = true;
                    }else if(m_isExitButtonSelected){
                        m_isExitButtonPressed = true;
                    }
                    break;
                }
                default: break;
            }
        }
    }
}
       
void SaveScore::Update(sf::Time deltatime){
    if(m_isMainMenuButtonSelected){
        m_menuButton.setFillColor(sf::Color(62, 118, 185));
        m_exitButton.setFillColor(sf::Color::Black);
    }else if(m_isExitButtonSelected){
        m_exitButton.setFillColor(sf::Color(62, 118, 185));
        m_menuButton.setFillColor(sf::Color::Black);
    }

    if(m_isMainMenuButtonPressed){
        m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);
        // m_context->m_states->popCurrent();
    }else if(m_isExitButtonPressed){
       m_context->m_window->close();
    }
}
        
void SaveScore::Draw(){

    m_context->m_window->clear();
    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_gameTitle);
    m_textbox.draw();
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->draw(m_menuButton);
    m_context->m_window->display();
}
