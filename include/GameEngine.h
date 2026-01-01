#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "Scene.h"
#include <SFML/Window.hpp>
#include <memory>

typedef std::map<const std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine{
	sf::RenderWindow m_window;
	SceneMap m_sceneMap;
	bool m_isRunning = true;
	size_t m_currentFrame;
	std::shared_ptr<Scene> m_currentScene;
public:
	GameEngine(const std::string & gameConfigPath);
	void run();
	void changeScene(const std::string & sceneName, std::shared_ptr<Scene> scene);
	void update();
	void sUserInput();
	void quit();
	sf::RenderWindow & window();
	std::shared_ptr<Scene> getScene(const std::string & sceneName);
};
#endif
