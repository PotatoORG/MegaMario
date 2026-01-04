#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "Vec2.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <memory>

#ifndef ENUM_CTAG
#define ENUM_CTAG
enum CTag{
	defaultTag,
	bullet,
	enemy,
	player,
	text,
	tile,
	decoration
};
#endif

class CTransform{
	public:
		Vec2 pos = {0.0, 0.0};
		Vec2 prevPos = {0.0, 0.0};
		Vec2 velocity = {0.0, 0.0};
		float angle = 0.0;

		CTransform(Vec2 pos, Vec2 vel, float angle)
			: pos (pos), velocity (vel), angle (angle) {}

		CTransform(Vec2 pos)
			: pos (pos) {}
};

class CAnimation{
	public:
		std::shared_ptr<Animation> animation;
		//CAnimation(sf::Texture & texture, size_t frameCount, size_t duration) : animation(texture, frameCount, duration){}
		CAnimation() {}
};

class CBoundingBox{
	public:
		Vec2 box;
		CBoundingBox(Vec2 box) : box(box) {}
};

class CLifeSpan{
public:
	float initial;
	float remaining;

	CLifeSpan(float span)
		: remaining (span), initial (span) {}
};

#endif
