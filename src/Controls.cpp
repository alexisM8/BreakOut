#include "../include/helperLogic.hpp"
#include "../include/Controls.hpp"
#include "../include/MainMenu.hpp"
#include "../include/GameLogic.hpp"
#include "SFML/Graphics/Rect.hpp"
#include <iostream>
#include <memory>

Control::Control(std::shared_ptr<Engine::Context> &context): 
                            m_context(context),
                            m_isMenuButtonSelected(true),
                            m_isMenuButtonPressed(false),
                            m_isExitButtonSelected(false),
                            m_isExitButtonPressed(false){/*empty*/}
Control::~Control(){/*empty*/}

void Control::Init(){
    // m_context->m_assest->AddFont(MAIN_FONT, "../assets/fonts/Monaco.ttf");
    m_gameTitle.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_menuButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_exitButton.setFont(m_context->m_assest->getFont(MAIN_FONT));
    //instructions
    m_upArrowInstuctions.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_leftArrowInstructions.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_oneInstructions.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_twoInstructions.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_nineInstructions.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_zeroInstructions.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_spaceInstructions.setFont(m_context->m_assest->getFont(MAIN_FONT));
    m_pInstructions.setFont(m_context->m_assest->getFont(MAIN_FONT));

    //name
    m_gameTitle.setString("Controls");
    m_gameTitle.setCharacterSize(80);
    m_gameTitle.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_gameTitle.getGlobalBounds().width / 2.0, 50.0));
    //exit button
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(50);
    m_exitButton. setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_exitButton.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y  - (m_exitButton.getGlobalBounds().height + m_exitButton.getGlobalBounds().height )));
    //controls button
    m_menuButton.setString("Main Menu");
    m_menuButton.setCharacterSize(50);
    m_menuButton.setPosition(sf::Vector2f((m_context->m_window->getSize().x / 2.0) - m_exitButton.getGlobalBounds().width / 2.0, m_context->m_window->getSize().y - (m_exitButton.getGlobalBounds().height * 2 + m_exitButton.getGlobalBounds().height * 2)));
    //Background
    m_context->m_assest->AddTexture(MENUBACKGROUND, "../assets/textures/Clouds 8.png");
    m_background.setTexture(m_context->m_assest->getTexture(MENUBACKGROUND));
    m_background.setScale(3.35, 3.35);
    m_background.setPosition(0,0);
    //sprites 
    m_context->m_assest->AddTexture(SPACE, "../assets/textures/key_sprites/SPACEALTERNATIVE.png");
    m_context->m_assest->AddTexture(P, "../assets/textures/key_sprites/P.png");
    m_context->m_assest->AddTexture(UPARROW, "../assets/textures/key_sprites/ARROWUP.png");
    m_context->m_assest->AddTexture(DOWNARROW, "../assets/textures/key_sprites/ARROWDOWN.png");
    m_context->m_assest->AddTexture(LEFTARROW, "../assets/textures/key_sprites/ARROWLEFT.png");
    m_context->m_assest->AddTexture(RIGHTARROW, "../assets/textures/key_sprites/ARROWRIGHT.png");
    m_context->m_assest->AddTexture(ONE, "../assets/textures/key_sprites/1.png");
    m_context->m_assest->AddTexture(TWO, "../assets/textures/key_sprites/2.png");
    m_context->m_assest->AddTexture(NINE, "../assets/textures/key_sprites/9.png");
    m_context->m_assest->AddTexture(ZERO, "../assets/textures/key_sprites/0.png");
    //positions
    m_leftArrowPosition = sf::IntRect(0,0,16,16);
    m_rightArrowPosition = sf::IntRect(0,0,16,16);
    m_spacePosition = sf::IntRect(0,0,67,16);
    m_pPosition = sf::IntRect(0,0,16,16);
    m_onePosition = sf::IntRect(0,0,16,16);
    m_twoPosition = sf::IntRect(0,0,16,16);
    m_ninePosition = sf::IntRect(0,0,16,16);
    m_zeroPosition = sf::IntRect(0,0,16,16);
    m_upArrowPosition = sf::IntRect(0,0,16,16);
    m_downArrowPosition = sf::IntRect(0,0,16,16);
    //applying textures
    m_leftArrow = sf::Sprite(m_context->m_assest->getTexture(LEFTARROW), m_leftArrowPosition);
    m_rightArrow = sf::Sprite(m_context->m_assest->getTexture(RIGHTARROW), m_rightArrowPosition);
    m_space = sf::Sprite(m_context->m_assest->getTexture(SPACE), m_spacePosition);
    m_keyp = sf::Sprite(m_context->m_assest->getTexture(P), m_pPosition);
    m_zero = sf::Sprite(m_context->m_assest->getTexture(ZERO), m_zeroPosition);
    m_one = sf::Sprite(m_context->m_assest->getTexture(ONE), m_onePosition);
    m_two = sf::Sprite(m_context->m_assest->getTexture(TWO), m_twoPosition);
    m_nine = sf::Sprite(m_context->m_assest->getTexture(NINE), m_ninePosition);
    m_upArrow = sf::Sprite(m_context->m_assest->getTexture(UPARROW), m_upArrowPosition);
    m_downArrow = sf::Sprite(m_context->m_assest->getTexture(DOWNARROW), m_downArrowPosition);
    //setting position
    m_keyp.setPosition(600, 200);
    m_keyp.setScale(4.0, 4.0);

    m_upArrow.setPosition(600, m_keyp.getPosition().y + 20 + m_keyp.getGlobalBounds().height);
    m_upArrow.setScale(4.0, 4.0);

    m_downArrow.setPosition(605 + m_upArrow.getGlobalBounds().width, m_keyp.getPosition().y + 20 + m_keyp.getGlobalBounds().height);
    m_downArrow.setScale(4.0, 4.0);

    m_leftArrow.setPosition(600, m_upArrow.getPosition().y + 20 + m_downArrow.getGlobalBounds().height);
    m_leftArrow.setScale(4.0, 4.0);

    m_rightArrow.setPosition(605 + m_upArrow.getGlobalBounds().width, m_downArrow.getPosition().y + 20 + m_keyp.getGlobalBounds().height);
    m_rightArrow.setScale(4.0, 4.0);

    m_one.setPosition(600, m_rightArrow.getPosition().y + 20 + m_downArrow.getGlobalBounds().height);
    m_one.setScale(4.0, 4.0);

    m_two.setPosition(600, m_one.getPosition().y + 20 + m_downArrow.getGlobalBounds().height);
    m_two.setScale(4.0, 4.0);

    m_nine.setPosition(600, m_two.getPosition().y + 20 + m_downArrow.getGlobalBounds().height);
    m_nine.setScale(4.0,4.0);

    m_zero.setPosition(600, m_nine.getPosition().y + 20 + m_downArrow.getGlobalBounds().height);
    m_zero.setScale(4.0,4.0);

    m_space.setPosition(600, m_zero.getPosition().y + 20 + m_downArrow.getGlobalBounds().height);
    m_space.setScale(4.0,4.0);

    //sound
    m_scroll.setBuffer(m_context->m_assest->getSound(SCROLL));

    //clock
    m_context->m_clock->restart();
    
    //set up instructions
    m_upArrowInstuctions.setString("press to navigate between text options");
    m_upArrowInstuctions.setCharacterSize(40);
    m_upArrowInstuctions.setPosition({m_downArrow.getPosition().x + m_downArrow.getGlobalBounds().width + 40, m_upArrow.getPosition().y});

    m_leftArrowInstructions.setString("press to move player character left and right");
    m_leftArrowInstructions.setCharacterSize(40);
    m_leftArrowInstructions.setPosition({m_rightArrow.getPosition().x + m_rightArrow.getGlobalBounds().width + 40, m_rightArrow.getPosition().y});

    m_oneInstructions.setString("press to decrease music volume");
    m_oneInstructions.setCharacterSize(40);
    m_oneInstructions.setPosition({m_one.getPosition().x + m_one.getGlobalBounds().width + 40, m_one.getPosition().y});

    m_twoInstructions.setString("press to increse music volume");
    m_twoInstructions.setCharacterSize(40);
    m_twoInstructions.setPosition({m_two.getPosition().x + m_two.getGlobalBounds().width + 40, m_two.getPosition().y});

    m_nineInstructions.setString("press to decrease sfx volume");
    m_nineInstructions.setCharacterSize(40);
    m_nineInstructions.setPosition({m_nine.getPosition().x + m_nine.getGlobalBounds().width + 40, m_nine.getPosition().y});

    m_zeroInstructions.setString("press to increase sfx volume");
    m_zeroInstructions.setCharacterSize(40);
    m_zeroInstructions.setPosition({m_zero.getPosition().x + m_zero.getGlobalBounds().width + 40, m_zero.getPosition().y});

    m_pInstructions.setString("press to pause game");
    m_pInstructions.setCharacterSize(40);
    m_pInstructions.setPosition({m_keyp.getPosition().x + m_keyp.getGlobalBounds().width + 40, m_keyp.getPosition().y});

    m_spaceInstructions.setString("press to launch ball of destruction");
    m_spaceInstructions.setCharacterSize(40);
    m_spaceInstructions.setPosition({m_space.getPosition().x + m_space.getGlobalBounds().width + 40, m_space.getPosition().y});

}
void Control::ProcessInput(){
    sf::Event ev;
    while(m_context->m_window->pollEvent(ev)){
        if(ev.type == sf::Event::Closed){
            m_context->m_window->close();
        }else if(ev.type == sf::Event::KeyPressed){
            switch (ev.key.code) {
                case sf::Keyboard::Up:{
                    if(m_isExitButtonSelected){
                        m_isMenuButtonSelected = true;
                        m_isExitButtonSelected = false;
                        m_scroll.play();
                    }
                    break;
                }
                case sf::Keyboard::Down:{
                    if(m_isMenuButtonSelected){
                        m_isMenuButtonSelected = false;
                        m_isExitButtonSelected = true;
                        m_scroll.play();
                    }
                    break;
                }
                case sf::Keyboard::Escape:{
                    m_context->m_window->close();
                    break;
                }
                case sf::Keyboard::Return:{
                    m_isExitButtonPressed = false;
                    m_isMenuButtonPressed = false;
                    m_scroll.play();
                    
                    if(m_isMenuButtonSelected){
                        m_isMenuButtonPressed = true;
                    }else if(m_isExitButtonSelected){
                        m_isExitButtonPressed = true;
                    }
                    break;
                    case sf::Keyboard::Num1:{
                       m_music.setVolume(10.0f);
                    }
                }
                default:
                    break;
            }
        }
    }
}
void Control::Update(sf::Time deltatime){
    if(m_context->m_clock->getElapsedTime().asSeconds() >= 1.0f){
        if(m_pPosition.left >= 16){
            m_pPosition.left = 0;
        }else{
            m_pPosition.left += 16;
        }
        if(m_onePosition.left >= 16){
            m_onePosition.left = 0;
        }else{
            m_onePosition.left += 16;
        }
        if(m_twoPosition.left >= 16){
            m_twoPosition.left = 0;
        }else{
            m_twoPosition.left += 16;
        }
        if(m_ninePosition.left >= 16){
            m_ninePosition.left = 0;
        }else{
            m_ninePosition.left += 16;
        }
        if(m_zeroPosition.left >= 16){
            m_zeroPosition.left = 0;
        }else{
            m_zeroPosition.left += 16;
        }
        if(m_leftArrowPosition.left >= 16){
            m_leftArrowPosition.left = 0;
        }else{
            m_leftArrowPosition.left += 16;
        }
        if(m_rightArrowPosition.left >= 16){
            m_rightArrowPosition.left = 0;
        }else{
            m_rightArrowPosition.left += 16;
        }
        if(m_upArrowPosition.left >= 16){
            m_upArrowPosition.left = 0;
        }else{
            m_upArrowPosition.left += 16;
        }
        if(m_downArrowPosition.left >= 16){
            m_downArrowPosition.left = 0;
        }else{
            m_downArrowPosition.left += 16;
        }

        if(m_spacePosition.left >= 67){
            m_spacePosition.left = 0;
        }else{
            m_spacePosition.left += 67;
        }
        m_keyp.setTextureRect(m_pPosition);
        m_upArrow.setTextureRect(m_upArrowPosition);
        m_downArrow.setTextureRect(m_downArrowPosition);
        m_rightArrow.setTextureRect(m_rightArrowPosition);
        m_leftArrow.setTextureRect(m_leftArrowPosition);
        m_one.setTextureRect(m_onePosition);
        m_two.setTextureRect(m_twoPosition);
        m_nine.setTextureRect(m_ninePosition);
        m_zero.setTextureRect(m_zeroPosition);
        m_space.setTextureRect(m_spacePosition);
        m_context->m_clock->restart();
    }
    if(m_isMenuButtonSelected){
        m_menuButton.setFillColor(sf::Color::Yellow);
        m_exitButton.setFillColor(sf::Color::White);
    }else if(m_isExitButtonSelected){
        m_exitButton.setFillColor(sf::Color::Yellow);
        m_menuButton.setFillColor(sf::Color::White);
    }

    if(m_isMenuButtonPressed){
        // m_context->m_states->add(std::make_unique<MainMenu>(m_context), true);
        m_context->m_states->popCurrent();
    }else if(m_isExitButtonPressed){
       m_context->m_window->close();
    }
    std::cout << "in controls state stack size: " << m_context->m_states->getSize() << "\n";
}
void Control::Draw(){
    m_context->m_window->clear();
    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_keyp);
    m_context->m_window->draw(m_upArrow);
    m_context->m_window->draw(m_downArrow);
    m_context->m_window->draw(m_zero);
    m_context->m_window->draw(m_one);
    m_context->m_window->draw(m_two);
    m_context->m_window->draw(m_nine);
    m_context->m_window->draw(m_space);
    m_context->m_window->draw(m_leftArrow);
    m_context->m_window->draw(m_rightArrow);
    m_context->m_window->draw(m_spaceInstructions);
    m_context->m_window->draw(m_upArrowInstuctions);
    m_context->m_window->draw(m_leftArrowInstructions);
    m_context->m_window->draw(m_oneInstructions);
    m_context->m_window->draw(m_twoInstructions);
    m_context->m_window->draw(m_nineInstructions);
    m_context->m_window->draw(m_zeroInstructions);
    m_context->m_window->draw(m_pInstructions);
    m_context->m_window->draw(m_menuButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}
