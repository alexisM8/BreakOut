#include "../include/AssetManager.hpp"

Engine::AssetManager::AssetManager(){/*empty*/}
Engine::AssetManager::~AssetManager(){/*empty*/}

void Engine::AssetManager::AddTexture(int id, const std::string &filePath, bool wantRepeated){
    auto texture = std::make_unique<sf::Texture>();
    if(texture->loadFromFile(filePath)){
        texture->setRepeated(wantRepeated);
        m_Textures[id] = std::move(texture);
    }
}
void Engine::AssetManager::AddFont(int id, const std::string &filePath){
    auto font = std::make_unique<sf::Font>();
    if(font->loadFromFile(filePath)){
        m_Fonts[id] = std::move(font);
    }
}
void Engine::AssetManager::AddSound(int id, const std::string &filePath){
    auto sound = std::make_unique<sf::SoundBuffer>();
    if(sound->loadFromFile(filePath)){
        m_Sounds[id] = std::move(sound);
    }
}
void Engine::AssetManager::AddMusic(int id, const std::string &filePath){
    auto music = std::make_unique<std::string>(filePath);
    if(music){
        m_Musics[id] = std::move(music);
    }
}
const sf::Texture& Engine::AssetManager::getTexture(int id) const{
    return *(m_Textures.at(id).get());
}
const sf::Font& Engine::AssetManager::getFont(int id) const{
    return *(m_Fonts.at(id).get());
}
const sf::SoundBuffer& Engine::AssetManager::getSound(int id) const{
    return *(m_Sounds.at(id).get());
}
const std::string& Engine::AssetManager::getMusic(int id) const{
    return *(m_Musics.at(id).get());
}
