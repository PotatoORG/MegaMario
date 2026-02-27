#include "GameEngine.h"
#include "SceneMenu.h"
#include <iostream>

GameEngine::GameEngine(const std::string & gameConfigPath){
	int W = 1280;
	int H = 720;

	m_assets = Assets(gameConfigPath);
	m_window.create(sf::VideoMode({W, H}), "Game Window");
	m_window.setFramerateLimit(60);

	//m_assets.addFont("FONT", "include/BebasNeue-Regular.ttf");
	changeScene("MENU", std::make_shared<SceneMenu>(this));
	//std::cout << "menu scene made and back to gameEngine\n";
}

void GameEngine::run(){
	std::cout << "Game starting...\n";
	while (m_isRunning){
		update();
	}
	std::cout << "Game exiting...\n";
}

void GameEngine::update(){
	m_currentScene->update();
	sUserInput();
	m_currentFrame++;
}

void GameEngine::changeScene(const std::string & sceneName, std::shared_ptr<Scene> s){
	m_sceneMap[sceneName] = s;
	m_currentScene = s;
}

std::shared_ptr<Scene> GameEngine::getScene(const std::string & sceneName){
	return m_sceneMap[sceneName];
}

Assets & GameEngine::getAssets(){
	return m_assets;
}

void GameEngine::sUserInput(){
	sf::Event event{};
	while (m_window.pollEvent(event)) {

		if (event.type == sf::Event::Closed){quit();}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::X) {
				sf::Texture texture;
				texture.create(m_window.getSize().x, m_window.getSize().y);
				texture.update(m_window);
				if (texture.copyToImage().saveToFile("screenshots/test.png"))
					std::cout << "screenshot saved to " << "screenshots/test.png" << std::endl;
			}
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
			// if the current scene does not have an action associated with this key,
			// skip the event
			if (m_currentScene->getActionMap().find(std::make_pair(event.key.code, event.type == sf::Event::KeyPressed)) == m_currentScene->getActionMap().end()){
				continue;
			}

			// determinate start or end action whether it was pres or release
			eActionType actionType = (event.type == sf::Event::KeyPressed) ? eActionType::START : eActionType::END;

			// look up the action and send the action to the scene
			m_currentScene->doAction(Action(m_currentScene->getActionMap()[std::make_pair(event.key.code, event.type == sf::Event::KeyPressed)].name, actionType));
		}
	}

}

void GameEngine::quit(){
	m_isRunning = false;
}

sf::RenderWindow & GameEngine::window(){
	return m_window;
}
