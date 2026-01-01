#ifndef SCENE_H
#define SCENE_H

#include "Action.h"
//#include "EntityManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

typedef std::map<sf::Keyboard::Key, Action> ActionMap;
class GameEngine;

class Scene{
	//EntityManager	m_entityManager;
	ActionMap	m_actionMap;
	bool m_paused = false;
	bool m_hasEnded = false;
	void m_sRender(); // private because will be called only by update() function.
public:
	GameEngine	*gameEngine;
	virtual void update() = 0; // Will be overrided by the derived class
	virtual void doAction(Action) = 0; // Will be overrided by the derived class
	void registerAction(sf::Keyboard::Key, Action);
	ActionMap & getActionMap();
	virtual ~Scene() = default;
};

class SceneMenu : public Scene{
	sf::Text m_title;
	sf::Text m_text;
	sf::Font m_font;
public:
	void update(); // Will be overrided by the derived class
	void doAction(Action a); // Will be overrided by the derived class
	//void registerAction(sf::Keyboard::Key, Action);
	SceneMenu(GameEngine * ge);
};

class ScenePlay : public Scene{
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_title;
public:
	void update(); // Will be overrided by the derived class
	void doAction(Action a); // Will be overrided by the derived class
	void registerAction(sf::Keyboard::Key, Action);
	ScenePlay(GameEngine * ge);
};
#endif
