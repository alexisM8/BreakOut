#include "../include/helperLogic.hpp"
#include "../include/WinOrLose.hpp"
#include "../include/GameLogic.hpp"
#include "../include/SaveScore.hpp"
#include <iostream>

WinOrLose::WinOrLose(std::shared_ptr<Engine::Context> &context, 
                     int score, int lvlbeat, float soundVolume, float musicVolume):
                            m_context(context), 
                            m_score(score),
                            m_lives(lvlbeat),
                            m_soundVolume(soundVolume),
                            m_musicVolume(musicVolume),
                            m_isSaveScoreButtonSelected(true),
                            m_isSaveScoreButtonPressed(false), 
                            m_isRestartGameButtonSelected(false),
                            m_isRestartGameButtonPressed(false),    
                            m_isExitButtonSelected(false), 
                            m_isExitButtonPressed(false){/*empty*/}

WinOrLose::~WinOrLose(){/*empty*/}

void WinOrLose::Init(){
    m_context-> m_assest->AddTexture(AssetID::WOLBACKGROUND, "../assets/textures/Clouds 7.png");
    m_wolBackground.setTexture(m_context->m_assest->getTexture(AssetID::WOLBACKGROUND));
    m_wolBackground.setScale(3.35, 3.35);

    m_statusTitle.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_saveScoreButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_restartGameButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_exitButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_scoreTxt.setFont(m_context->m_assest->getFont(MAIN_FONT));
    //name
    if(m_lives >= 0){
        m_statusTitle.setString("congratulations You Win!");
    }else{
        m_statusTitle.setString("Game Failed");
    }
     
    m_statusTitle.setCharacterSize(80);
    m_statusTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_statusTitle.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_statusTitle.getGlobalBounds().height / 2.0 - 150.0));
    m_statusTitle.setFillColor(sf::Color::Black);
    //Save Score button
    m_saveScoreButton.setString("Save Score");
    m_saveScoreButton.setCharacterSize(50);
    m_saveScoreButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_saveScoreButton.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_saveScoreButton.getGlobalBounds().height / 2.0 - 30.0f));
    m_saveScoreButton.setFillColor(sf::Color::Black);

    //restart game button
    m_restartGameButton.setString("Restart Game");
    m_restartGameButton.setCharacterSize(50);
    m_restartGameButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_restartGameButton.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_restartGameButton.getGlobalBounds().height / 2.0 + 30.0f));
    m_restartGameButton.setFillColor(sf::Color::Black);

    //exit button
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(50);
    m_exitButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_exitButton.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y / 2.0 - m_exitButton.getGlobalBounds().height / 2.0 + 90.0f));
    m_exitButton.setFillColor(sf::Color::Black);

    m_context->m_sound->setBuffer(m_context->m_assest->getSound(AssetID::SCROLL));

}
void WinOrLose::ProcessInput(){
    sf::Event ev;
    while(m_context->m_window->pollEvent(ev)){
        if(ev.type == sf::Event::Closed){
            m_context->m_window->close();
        }else if(ev.type == sf::Event::KeyPressed){
            switch (ev.key.code) {
                case sf::Keyboard::Up:{
                    if(m_isExitButtonSelected){
                        m_isSaveScoreButtonSelected = false;
                        m_isRestartGameButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }else if(m_isRestartGameButtonSelected){
                        m_isSaveScoreButtonSelected = true;
                        m_isRestartGameButtonSelected = false;
                        m_isExitButtonSelected = false;
                    }
                    m_context->m_sound->play();
                    break;
                }
                case sf::Keyboard::Down:{
                    if(m_isSaveScoreButtonSelected){
                        m_isSaveScoreButtonSelected = false;
                        m_isRestartGameButtonSelected = true;
                        m_isExitButtonSelected = false;
                    }else if(m_isRestartGameButtonSelected){
                        m_isSaveScoreButtonSelected = false;
                        m_isRestartGameButtonSelected = false;
                        m_isExitButtonSelected = true;
                    }
                    m_context->m_sound->play();
                    break;
                }
                case sf::Keyboard::Escape:{
                    m_context->m_window->close();
                    break;
                }
                case sf::Keyboard::Return:{
                    m_isExitButtonPressed = false;
                    m_isSaveScoreButtonPressed = false;
                    m_isRestartGameButtonPressed = false;
                    
                    if(m_isSaveScoreButtonSelected){
                        m_isSaveScoreButtonPressed = true;
                    }else if(m_isRestartGameButtonSelected){
                        m_isRestartGameButtonPressed = true;
                    }else{
                        m_isExitButtonPressed = true;
                    }
                    m_context->m_sound->play();
                    break;
                }
                case sf::Keyboard::Num1:{
                    if(m_musicVolume <= 0) m_musicVolume = 0;
                    else m_musicVolume -= 10.0f;
                    m_context->m_music->setVolume(m_musicVolume);
                    break;
                }
                case sf::Keyboard::Num2:{
                    if(m_musicVolume >= 100) m_musicVolume = 100.0f;
                    else m_musicVolume  += 10.0f;
                    m_context->m_music->setVolume(m_musicVolume);
                    break;
                }
                case sf::Keyboard::Num9:{
                    if(m_soundVolume <= 0) m_soundVolume = 0;
                    else m_soundVolume -= 10.0f;
                    m_context->m_sound->setVolume(m_soundVolume);
                    break;
                }
                case sf::Keyboard::Num0:{
                    if(m_soundVolume >= 100) m_soundVolume = 100;
                    else m_soundVolume += 10.0f;
                    m_context->m_sound->setVolume(m_soundVolume);
                    break;
                }
                default:
                    break;
            }
        }
    }
}
void WinOrLose::Update(sf::Time deltatime){
    if(m_isSaveScoreButtonSelected){
        m_saveScoreButton.setFillColor(sf::Color(62, 118, 185));
        m_exitButton.setFillColor(sf::Color::Black);
        m_restartGameButton.setFillColor(sf::Color::Black);
    }else if(m_isRestartGameButtonSelected){  
        m_restartGameButton.setFillColor(sf::Color(62, 118, 185));
        m_exitButton.setFillColor(sf::Color::Black);
        m_saveScoreButton.setFillColor(sf::Color::Black);
    }else{
        m_restartGameButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color(62, 118, 185));
        m_saveScoreButton.setFillColor(sf::Color::Black);
    }
    
    if(m_isSaveScoreButtonPressed){
        m_context->m_states->add(std::make_unique<SaveScore>(m_context, m_score, m_soundVolume, m_musicVolume), true);
    }else if(m_isRestartGameButtonPressed){
        m_context->m_states->add(std::make_unique<GameLogic>(m_context), true);
    }else if(m_isExitButtonPressed){
       m_context->m_window->close();
    }
}
void WinOrLose::Draw(){
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_wolBackground);
    m_context->m_window->draw(m_statusTitle);
    m_context->m_window->draw(m_saveScoreButton);
    m_context->m_window->draw(m_restartGameButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}

