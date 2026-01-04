#include "GameEngine.h"
#include "SceneMenu.h"
#include "ScenePlay.h"
#include <iostream>

SceneMenu::SceneMenu(GameEngine *ge){
	gameEngine = ge;

	gameEngine->window().clear(sf::Color::Blue);
	gameEngine->window().display();

	Scene::registerAction(sf::Keyboard::W, {UP, START});
	Scene::registerAction(sf::Keyboard::S, {DOWN, START});
	Scene::registerAction(sf::Keyboard::Escape, {EXIT, START});
	Scene::registerAction(sf::Keyboard::D, {PLAY, START});

	m_font = *(gameEngine->getAssets().getFont("FONT"));
	//m_font.loadFromFile("include/BebasNeue-Regular.ttf");
	m_title.setFont(m_font);
	m_title.setString("The Game");
	m_title.setPosition({200, 200});
	m_title.setCharacterSize(40);
	m_title.setFillColor(sf::Color::White);
	gameEngine->window().draw(m_title);
	std::cout << "Scene Menu instantiated\n";
}

void SceneMenu::update(){
	gameEngine->window().clear(sf::Color::Blue);
	gameEngine->window().draw(m_title);
	gameEngine->window().display();
}

void SceneMenu::doAction(Action a){
	switch (a.name){
		case (UP):
			std::cout << "UP Action passed.\n";
			break;
		case (DOWN):
			std::cout << "DOWN Action passed.\n";
			break;
		case (EXIT):
			std::cout << "EXIT Action passed.\n";
			break;
		case (PLAY):
			std::cout << "PLAY Action passed.\n";
			gameEngine->changeScene("PLAY", std::make_shared<ScenePlay>(gameEngine, "levelConf.txt"));
			break;
	}
}
