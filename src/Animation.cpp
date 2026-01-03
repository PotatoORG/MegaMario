#include "Animation.h"

Animation::Animation() {}

Animation::Animation(sf::Texture & texture, size_t frameCount, size_t duration)
	: m_frameCount(frameCount), m_frameDuration(duration){
	m_sprite.setTexture(texture);
	m_frameWidth = texture.getSize().x/frameCount;
	m_frameLength =  texture.getSize().y;
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameLength));
}

void Animation::update(){
	m_gameFrame++;
	m_currentFrame = (m_gameFrame/m_frameDuration) % m_frameCount;
	auto rectangle = sf::IntRect(m_currentFrame * m_frameWidth, 0, m_frameWidth, m_frameLength);
	m_sprite.setTextureRect(rectangle);
}

sf::Sprite	& Animation::getSprite(){
	return m_sprite;
}

Vec2 & Animation::getSize(){
	return m_size;
}

//const std::string & Animation::getName(){
	//return m_name;
//}

bool Animation::hasEnded(){
	return 0;
}
