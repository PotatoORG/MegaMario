#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Animation.h"

class Assets{
	std::map<std::string, std::shared_ptr<sf::Font>> m_fonts;
	std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
	std::map<std::string, std::shared_ptr<Animation>> m_animations;
public:
	std::shared_ptr<sf::Font> addFont(const std::string & name,const std::string & path);
	std::shared_ptr<sf::Texture> addTexture(const std::string & name, const std::string & path);
	std::shared_ptr<Animation> addAnimation(const std::string & name, const std::string & texture, int frameCount, int frameDuration);

	std::shared_ptr<sf::Font> getFont(const std::string & name);
	std::shared_ptr<sf::Texture> getTexture(const std::string & name);
	std::shared_ptr<Animation> getAnimation(const std::string & name);

	Assets(const std::string & path);
	Assets() {}
};
#endif
