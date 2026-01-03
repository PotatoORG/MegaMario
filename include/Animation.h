#ifndef ANIMATION_H
#define ANIMATION_H

#include "Vec2.h"
#include <SFML/Graphics.hpp>

class Animation{
	sf::Sprite m_sprite;
	Vec2 m_size; // Size of rectangle in the texture given to the animation.
	//std::string & m_name = "LOL";
	size_t m_frameCount; // Number of frames in animation in which it will be looping.
	size_t m_currentFrame = 0; // frame of animation to display in this frame of game.
	size_t m_gameFrame = 0; // Number of game frames this animation has been alive.
	size_t m_frameDuration; // Number of game frames one frame of animation will be displayed.
	size_t m_frameWidth;
	size_t m_frameLength;
public:

	sf::Sprite	& 		getSprite();
	Vec2		& 		getSize();
	const std::string & getName();
	bool hasEnded();
	void update(); // Will update the sprite.

	Animation(sf::Texture & texture, size_t frameCount, size_t duration);
	Animation();
};

#endif
