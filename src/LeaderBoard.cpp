#include "../include/LeaderBoard.hpp"
#include "../include/helperLogic.hpp"  
#include "../include/MainMenu.hpp"
#include <algorithm>
#include <cstdio>
#include <string>
#include <type_traits>
#include <iostream>

LeaderBoard::LeaderBoard(std::shared_ptr<Engine::Context> &context)
        :   m_context(context),
            m_musicVolume(100.0f),
            m_soundVolume(100.0f),
            m_isMainMenuButtonSelected(true),
            m_isMainMenuButtonPressed(false),
            m_isExitButtonSelected(false),
            m_isExitButtonPressed(false)
            {/*empty*/}

LeaderBoard::LeaderBoard(std::shared_ptr<Engine::Context> &context, float soundVolume, float musicVolume)
        :   m_context(context),
            m_musicVolume(musicVolume),
            m_soundVolume(soundVolume),
            m_isMainMenuButtonSelected(true),
            m_isMainMenuButtonPressed(false),
            m_isExitButtonSelected(false),
            m_isExitButtonPressed(false)
            {/*empty*/}

void LeaderBoard::Init(){
    int count{0};
    std::string outputUsername{};
    std::string outputScoures{};
    m_gameTitle.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_exitButton.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_menuButton.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_scoresText.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_userNameText.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_userNames.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));
    m_scores.setFont(m_context->m_assest->getFont(AssetID::MAIN_FONT));

    m_gameTitle.setString("Leader Board Top 5");
    m_gameTitle.setCharacterSize(80.0f);
    m_gameTitle.setPosition({(float)m_context->m_window->getSize().x / 2 - m_gameTitle.getGlobalBounds().width / 2, 2 * m_gameTitle.getGlobalBounds().height - 100.0f});
    m_gameTitle.setFillColor(sf::Color::Black);

    m_horizontalLine.setSize({m_context->m_window->getSize().x * 0.80f, 9.0f});
    m_horizontalLine.setPosition({(float)m_context->m_window->getSize().x / 2 - m_horizontalLine.getSize().x / 2, m_gameTitle.getPosition().y + 3 * m_gameTitle.getGlobalBounds().height});
    m_horizontalLine.setFillColor(sf::Color::Black);

    m_verticalLine.setSize({9.0f, (float)m_context->m_window->getSize().y / 2});
    m_verticalLine.setPosition({(float)m_context->m_window->getSize().x / 2 - m_verticalLine.getSize().x / 2, m_horizontalLine.getPosition().y - 50.0f});
    m_verticalLine.setFillColor(sf::Color::Black);

    m_context->m_assest->AddTexture(LEADERBACKGROUND, "../assets/textures/Clouds 8.png");
    m_background.setTexture(m_context->m_assest->getTexture(AssetID::LEADERBACKGROUND));
    m_background.setScale(3.35f, 3.35f);

    m_userNameText.setString("User Name");
    m_userNameText.setCharacterSize(50);
    m_userNameText.setPosition({m_verticalLine.getPosition().x / 2 - m_userNameText.getGlobalBounds().width / 2 + 55.0f, m_horizontalLine.getPosition().y - m_userNameText.getGlobalBounds().height - 20.0f});
    m_userNameText.setFillColor(sf::Color::Black);

    m_scoresText.setString("Score");
    m_scoresText.setCharacterSize(50);
    m_scoresText.setPosition({m_verticalLine.getPosition().x + m_verticalLine.getGlobalBounds().width + ((m_horizontalLine.getPosition().x + m_horizontalLine.getGlobalBounds().width) - (m_verticalLine.getPosition().x + m_verticalLine.getGlobalBounds().width)) / 2  - m_scoresText.getGlobalBounds().width / 2, m_userNameText.getPosition().y});
    m_scoresText.setFillColor(sf::Color::Black);

    sortScores();
    setUsersAndScores();
    
    m_userNames.setCharacterSize(50);
    m_userNames.setFillColor(sf::Color::Black);
    m_userNames.setPosition({m_horizontalLine.getPosition().x  + 30.0f, m_horizontalLine.getPosition().y + 30.0f});

    m_scores.setCharacterSize(50);
    m_scores.setFillColor(sf::Color::Black);
    m_scores.setPosition({m_scoresText.getPosition().x, m_horizontalLine.getPosition().y + 30.0f});

    m_menuButton.setString("Main Menu");
    m_menuButton.setPosition({(float)m_context->m_window->getSize().x / 2 - m_menuButton.getGlobalBounds().width / 2, m_verticalLine.getPosition().y + m_verticalLine.getGlobalBounds().height + 50});
    m_menuButton.setCharacterSize(50);
    m_menuButton.setFillColor(sf::Color::Black);

    m_exitButton.setString("Exit");
    m_exitButton.setPosition({(float)m_context->m_window->getSize().x / 2 - m_exitButton.getGlobalBounds().width / 2, m_menuButton.getPosition().y + 60.0f});
    m_exitButton.setCharacterSize(50.0f);
    m_exitButton.setFillColor(sf::Color::Black);
}

void LeaderBoard::ProcessInput(){

    sf::Event ev;
    while(m_context->m_window->pollEvent(ev)){
        if(ev.type == sf::Event::Closed){
            m_context->m_window->close();
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
                case sf::Keyboard::Escape:{
                    m_context->m_window->close();
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

void LeaderBoard::Update(sf::Time deltatime){
    if(m_isMainMenuButtonSelected){
        m_menuButton.setFillColor(sf::Color(62, 118, 185));
        m_exitButton.setFillColor(sf::Color::Black);
    }else if(m_isExitButtonSelected){
        m_exitButton.setFillColor(sf::Color(62, 118, 185));
        m_menuButton.setFillColor(sf::Color::Black);
    }

    if(m_isMainMenuButtonPressed){
        m_context->m_states->popCurrent();
    }else if(m_isExitButtonPressed){
       m_context->m_window->close();
    }
}

void LeaderBoard::Draw(){
    m_context->m_window->clear();
    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_verticalLine);
    m_context->m_window->draw(m_horizontalLine);
    m_context->m_window->draw(m_userNameText);
    m_context->m_window->draw(m_scoresText);
    m_context->m_window->draw(m_userNames);
    m_context->m_window->draw(m_scores);
    m_context->m_window->draw(m_menuButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}

void LeaderBoard::sortScores(){
    std::ifstream getData("../assets/scores/scores.txt");
    std::vector<std::string> nameVec;
    std::vector<std::string> scoreVec;
    std::string name;
    std::string score;
    
    getData >> name >> score;
    while(!getData.eof()){
        nameVec.push_back(name);
        scoreVec.push_back(score);
        getData >> name >> score;
    }

    getData.close();

	int i{}, j{};
	for(i = 0; i < scoreVec.size(); i++){
		int max = std::stoi(scoreVec[i]);
		int maxIDX = i;
		for(j = i; j < scoreVec.size(); j++){
			if(std::stoi(scoreVec[j]) > max){
				max = std::stoi(scoreVec[j]);
				maxIDX = j;
			}
		}
        std::swap(scoreVec[i], scoreVec[maxIDX]);
        std::swap(nameVec[i], nameVec[maxIDX]);
	}
    
    std::remove("../assets/scores/scores.txt");

    std::fstream setData("../assets/scores/scores.txt", std::ios::out);
    if(setData.fail()){
        throw "error: failed to create scores file";
    }
    for(int x = 0; x < nameVec.size(); x++){
        setData << nameVec[x] << ' ' << scoreVec[x] << std::endl;
    }
    setData.close();
}

void LeaderBoard::setUsersAndScores(){
    std::ifstream infileScores("../assets/scores/scores.txt");
    int count = 0;
    std::string outputUsername{};
    std::string outputScoures{};
    if(infileScores.fail()){
        throw "error: failed to open high scores file!\n";
    }
    infileScores >> m_rowNames >> m_rowScores;
    while(!infileScores.eof() && count < 5){
        outputUsername += (m_rowNames + "\n");
        outputScoures += (m_rowScores + "\n");
        count++;
        infileScores >> m_rowNames >> m_rowScores;
    }
    infileScores.close();

    m_userNames.setString(outputUsername);
    m_scores.setString(outputScoures);
}

