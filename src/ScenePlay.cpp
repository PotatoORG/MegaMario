#include "Scene.h"
#include "GameEngine.h"
#include <iostream>

ScenePlay::ScenePlay(GameEngine * ge, const std::string & levelConfigPath){
	gameEngine = ge;

	ge->window().clear(sf::Color::Blue);
	gameEngine->window().display();

	Scene::registerAction(sf::Keyboard::W, {JUMP, START});
	Scene::registerAction(sf::Keyboard::Space, {SHOOT, START});
	Scene::registerAction(sf::Keyboard::Escape, {PAUSE, START});
	Scene::registerAction(sf::Keyboard::D, {RIGHT, START});
	Scene::registerAction(sf::Keyboard::A, {LEFT, START});

	m_font = *(gameEngine->getAssets().getFont("FONT"));
	m_title.setFont(m_font);
	m_title.setString("The Gameplay");
	m_title.setPosition({200, 200});
	m_title.setCharacterSize(40);
	m_title.setFillColor(sf::Color::White);
	std::cout << "Spawning the player...\n";
	spawnPlayer();
	std::cout << "Player spawned\n";
	//m_player.setTexture(*(gameEngine->getAssets().getTexture("MEGA")));
	gameEngine->window().draw(m_title);

	auto coin = m_entityManager.addEntity(tile);
	coin->cAnimation = gameEngine->getAssets().getAnimation("COINSPIN");
}

void ScenePlay::spawnPlayer(){
	auto entity = m_entityManager.addEntity(player);

	// texture here should be a shared pointer to the Texture object
	auto texture = gameEngine->getAssets().getTexture("MEGA");
	int frameCount = 1;
	int duration = 10;

	Vec2 position = {200, 200};
	Vec2 velocity = {200, 200};
	float angle = 0.0;
	entity->cTransform = std::make_shared<CTransform>(position, velocity, angle);
	entity->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(64, 64));
	//entity->cAnimation = std::make_shared<CAnimation>(*texture, frameCount, duration);
	entity->cAnimation = gameEngine->getAssets().getAnimation("COINSPIN");

	m_player = entity;
}


void ScenePlay::update(){
	gameEngine->window().clear(sf::Color::Blue);
	gameEngine->window().draw(m_title);
	std::cout << "Getting player's sprite\n";
	//gameEngine->window().draw(m_player->cAnimation->animation.getSprite());

	auto & entities = m_entityManager.getEntities(tile);
	for (auto & tile : entities){
		tile->cAnimation->update();
		gameEngine->window().draw(tile->cAnimation->getSprite());
		std::cout << "Entity drawn\n";
	}
	//gameEngine->window().draw(m_entityManager.getEntities())
	//std::cout << "player drawn\n";
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
