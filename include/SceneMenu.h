#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "Scene.h"
class SceneMenu : public Scene{
	sf::Text m_title;
	sf::Text m_text;
	sf::Font m_font;
public:
	void update(); // Will be overrided by the derived class
	void doAction(Action a); // Will be overrided by the derived class
	void registerActions();
	SceneMenu(GameEngine * ge);
};

#endif // SCENEMENU_H
