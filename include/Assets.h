#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <SFML/Graphics.hpp>

class Assets{
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::Texture> m_textures;
public:
	void addFont(const std::string & name, std::string & path);
	void addTexture(const std::string & name, std::string & path);

	sf::Font & getFont(const std::string & name);
	sf::Texture & getTexture(const std::string & name);

	Assets(const std::string & path);
	Assets() {}
};
#endif
