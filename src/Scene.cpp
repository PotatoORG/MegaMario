#include "Scene.h"

void Scene::registerAction(sf::Keyboard::Key key, Action a){
	m_actionMap[key] = a;
}

ActionMap & Scene::getActionMap(){
	return m_actionMap;
}
