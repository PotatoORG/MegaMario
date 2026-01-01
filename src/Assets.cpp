#include "Assets.h"
#include <fstream>
#include <iostream>

Assets::Assets(const std::string & path){
	std::ifstream file;
	std::string temp, N, P, T;
	int F, S;

	while (file){
		file >> temp;
		if (temp == "texture"){
			file >> N >> P;
			addTexture(N, P);
		} else  if (temp == "font"){
			file >> N >> P;
			addFont(N, P);
		} else if (temp == "animation"){
			;
		} else {
			std::cerr << "Invalid asset format in config file :" << temp << "\n";
		}
	}
}

void Assets::addFont(const std::string & name, std::string & path){
	auto font = m_fonts[name];
	font.loadFromFile(path);
	m_fonts[name] = font;
}

void Assets::addTexture(const std::string & name, std::string & path){
	auto texture = m_textures[name];
	texture.loadFromFile(path);
	m_textures[name] = texture;
}

sf::Font & Assets::getFont(const std::string & name){
	if (m_fonts.find(name) == m_fonts.end()){
		// Font not found.
		std::cerr << "No font found in Assets with name " << name << ".\n";
	}
	return m_fonts[name];
}

sf::Texture & Assets::getTexture(const std::string & name){
	if (m_textures.find(name) == m_textures.end()){
		// Font not found.
		std::cerr << "No texture found in Assets with name " << name << ".\n";
	}
	return m_textures[name];
}
