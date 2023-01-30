#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <map>
#include <string>

namespace Engine{
    class AssetManager{
        private:
            std::map<int, std::unique_ptr<sf::Texture>> m_Textures;
            std::map<int, std::unique_ptr<sf::Font>> m_Fonts;
            std::map<int, std::unique_ptr<sf::SoundBuffer>> m_Sounds;
            std::map<int, std::unique_ptr<std::string>> m_Musics;
    
        public:
            AssetManager();
            ~AssetManager();
            void AddTexture(int id, const std::string &filePath, bool wantRepeated = false);
            void AddFont(int id, const std::string &filePath);
            void AddSound(int id, const std::string &filepath);
            void AddMusic(int id, const std::string &filePath);
            const sf::Texture& getTexture(int id) const;
            const sf::Font& getFont(int id) const;
            const sf::SoundBuffer& getSound(int id) const;
            const std::string& getMusic(int id) const;
    };
}

