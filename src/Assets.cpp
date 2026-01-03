#include "Assets.h"
#include "Animation.h"
#include <fstream>
#include <iostream>


Assets::Assets(const std::string & path){
	std::ifstream file(path);
	std::string temp, N, P, T;
	int F, D;

	while (file){
		file >> temp;
		if (temp == "texture"){
			file >> N >> P;
			addTexture(N, P);
		} else  if (temp == "font"){
			file >> N >> P;
			addFont(N, P);
		} else if (temp == "animation"){
			file >> N >> T >> F >> D;
			addAnimation(N, T, F, D);
		} else {
			std::cerr << "Invalid asset format in config file :" << temp << "\n";
		}
	}
	std::cout << "Assets loaded from the file\n";
}

std::shared_ptr<Animation> Assets::addAnimation(const std::string & name, const std::string & texture, int frameCount, int frameDuration){

	auto animation = std::make_shared<Animation>(*getTexture(texture), frameCount, frameDuration);


	m_animations[name] = animation;
	return animation;
}

std::shared_ptr<sf::Font> Assets::addFont(const std::string & name, const std::string & path){

	auto font = std::make_shared<sf::Font>();

	if (!font->loadFromFile(path)){
		std::cerr << "Could not load the font named " << name << " from the path " << path << "\n";
	} else {
		std::cout << "Font loaded from path :" << path << "\n";
	}

	m_fonts[name] = font;
	return font;
}

std::shared_ptr<sf::Texture> Assets::addTexture(const std::string & name, const std::string & path){

	auto texture = std::make_shared<sf::Texture>();

	if (!texture->loadFromFile(path)){
		std::cerr << "Could not load the texture named " << name << " from the path " << path << "\n";
	}
	m_textures[name] = texture;
	return texture;
}

std::shared_ptr<sf::Font> Assets::getFont(const std::string & name){
	if (m_fonts.find(name) == m_fonts.end()){
		// Font not found.
		std::cerr << "No font found in Assets with name " << name << ".\n";
	}
	return m_fonts[name];
}

std::shared_ptr<sf::Texture> Assets::getTexture(const std::string & name){
	if (m_textures.find(name) == m_textures.end()){
		// Font not found.
		std::cerr << "No texture found in Assets with name " << name << ".\n";
	}
	return m_textures[name];
}

std::shared_ptr<Animation> Assets::getAnimation(const std::string & name){
	if (m_animations.find(name) == m_animations.end()){
		// Font not found.
		std::cerr << "No animation found in Assets with name " << name << ".\n";
	}
	return m_animations[name];
}
