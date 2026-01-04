#ifndef SCENE_H
#define SCENE_H

#include "Action.h"
#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>

typedef std::map<sf::Keyboard::Key, Action> ActionMap;


class GameEngine;

class Scene{
	ActionMap	m_actionMap;
	bool m_paused = false;
	bool m_hasEnded = false;
	 // private because will be called only by update() function.
public:
	GameEngine	*gameEngine;
	EntityManager	m_entityManager;
	virtual void update() = 0; // Will be overrided by the derived class
	virtual void doAction(Action) = 0; // Will be overrided by the derived class
	//virtual void m_sRender() = 0;
	void registerAction(sf::Keyboard::Key, Action);
	ActionMap & getActionMap();
	virtual ~Scene() = default;
};

#endif // SCENE_H
