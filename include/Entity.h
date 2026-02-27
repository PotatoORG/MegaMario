#ifndef ENTITY_H
#define ENTITY_H
#include  "Components.h"
#include "Animation.h"
#include <memory>


class Entity{
	size_t m_id = 0;
	CTag m_tag = defaultTag;
	bool m_alive = true;
public:
	Entity(const size_t id, const CTag tag);

	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CBoundingBox> cBoundingBox;
	std::shared_ptr<CLifeSpan> 	cLifeSpan;
	std::shared_ptr<Animation> cAnimation;
	std::shared_ptr<CGravity> cGravity;

	size_t id() const;
	const CTag& tag() const;
	bool isAlive() const;
	bool isOnGround = false;
	void destroy();
};
#endif
