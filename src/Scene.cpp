#include "Scene.h"

// pressed is true for pressed and false for release
void Scene::registerAction(sf::Keyboard::Key key, bool pressed, Action a){
	std::pair<sf::Keyboard::Key, bool> actionWithType{key, pressed};
	m_actionMap[actionWithType] = a;
}

ActionMap & Scene::getActionMap(){
	return m_actionMap;
}
