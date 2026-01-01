#include "Scene.h"
#include "GameEngine.h"
#include <iostream>

ScenePlay::ScenePlay(GameEngine * ge){
	gameEngine = ge;

	ge->window().clear(sf::Color::Blue);
	gameEngine->window().display();

	Scene::registerAction(sf::Keyboard::W, {JUMP, START});
	Scene::registerAction(sf::Keyboard::Space, {SHOOT, START});
	Scene::registerAction(sf::Keyboard::Escape, {PAUSE, START});
	Scene::registerAction(sf::Keyboard::D, {RIGHT, START});
	Scene::registerAction(sf::Keyboard::A, {LEFT, START});

	m_font.loadFromFile("include/BebasNeue-Regular.ttf");
	m_title.setFont(m_font);
	m_title.setString("The Gameplay");
	m_title.setPosition({200, 200});
	m_title.setCharacterSize(40);
	m_title.setFillColor(sf::Color::White);
	gameEngine->window().draw(m_title);
}


void ScenePlay::update(){
	gameEngine->window().clear(sf::Color::Blue);
	gameEngine->window().draw(m_title);
	gameEngine->window().display();
}

void ScenePlay::doAction(Action a){
	switch (a.name){
		case (JUMP):
			std::cout << "JUMP Action passed.\n";
			break;
		case (SHOOT):
			std::cout << "SHOOT Action passed.\n";
			break;
		case (LEFT):
			std::cout << "LEFT Action passed.\n";
			break;
		case (RIGHT):
			std::cout << "RIGHT Action passed.\n";
			break;
		case (PAUSE):
			std::cout << "PAUSE Action passed.\n";
			gameEngine->changeScene("MENU", gameEngine->getScene("MENU"));
			break;
	}
}
