#include "ScenePlay.h"
#include "GameEngine.h"
#include <iostream>
#include <fstream>
#include <cmath>

ScenePlay::ScenePlay(GameEngine * ge, const std::string & levelConfigPath){
	gameEngine = ge;

	registerActions();

	gameEngine->window().clear(sf::Color::Blue);
	gameEngine->window().display();

	makeLevel(levelConfigPath);


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

	//auto coin = m_entityManager.addEntity(decoration);
	//coin->cAnimation = gameEngine->getAssets().getAnimation("EXPLOSION");
}


void ScenePlay::makeLevel(const std::string & levelConfigPath){
	std::ifstream file(levelConfigPath);
	std::string temp, N;
	int GX, GY;
	float X, Y;

	while (file){
		file >> temp;
		if (temp == "tile"){
			file >> N >> GX >> GY;
			spawnTile(N, GX, GY);

		} else if (temp == "dec"){
			file >> N >> X >> Y;
			spawnDecoration(N, X, Y);

		} else if (temp == "player"){
			file >> m_playerConfig.GX \
				>> m_playerConfig.GY \
				>> m_playerConfig.CW \
				>> m_playerConfig.CH \
				>> m_playerConfig.SX \
				>> m_playerConfig.SY \
				>> m_playerConfig.SM \
				>> m_playerConfig.G \
				>> m_playerConfig.B;
		} else {
			std::cout << "Invalid config for level : " << temp << " \n";
		}
	}
}

void ScenePlay::spawnTile(const std::string & animationName, int GX, int GY){
	auto t = m_entityManager.addEntity(tile);
	t->cAnimation = gameEngine->getAssets().getAnimation(animationName);
	int x = 64*GX + 64/2;
	int y = 720 - 64 - 64*GY + 64/2;
	t->cTransform = std::make_shared<CTransform>(Vec2(x, y));
	t->cAnimation->getSprite().setPosition(x, y);
	//std::cout << "Tile created at (" << GX << ", " << GY << ") in grid and (" << x << ", " << y << ") in window\n"; 
	t->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(64, 64));
	t->cAnimation->getSprite().setOrigin(t->cAnimation->getSprite().getTextureRect().width/2, t->cAnimation->getSprite().getTextureRect().height/2);
	//t->cAnimation->getSprite().setOrigin(x + t->cBoundingBox->box.x/2, y + t->cBoundingBox->box.y/2);
}

void ScenePlay::spawnDecoration(const std::string & animationName, float x, float y){
	auto d = m_entityManager.addEntity(decoration);
	d->cAnimation = gameEngine->getAssets().getAnimation(animationName);
	d->cTransform = std::make_shared<CTransform>(Vec2(x, y));
	d->cAnimation->getSprite().setPosition(x, y);
	std::cout << "Decoration created at (" << x << ", " << y << ") in window\n"; 
}

void ScenePlay::spawnPlayer(){
	auto entity = m_entityManager.addEntity(player);

	// texture here should be a shared pointer to the Texture object
	//auto texture = gameEngine->getAssets().getTexture("MEGA");
	//int frameCount = 1;
	//int duration = 10;

	Vec2 position = {200, 200};
	entity->cTransform = std::make_shared<CTransform>(position);
	entity->cBoundingBox = std::make_shared<CBoundingBox>(Vec2(40, 40));
	entity->cGravity = std::make_shared<CGravity>(0.8);
	std::cout << "Getting the standing animation from assets\n";
	entity->cAnimation = gameEngine->getAssets().getAnimation("MEGARUN");
	entity->cAnimation->getSprite().setOrigin(entity->cAnimation->getSprite().getTextureRect().width/2, entity->cAnimation->getSprite().getTextureRect().height/2);

	m_player = entity;
}


void ScenePlay::update(){
	sMovement();
	sCollision();
	sRender();
}

void ScenePlay::sCollision(){
	auto & tiles = m_entityManager.getEntities(tile);
	m_player->isOnGround = false;

	for (auto & t : tiles){
//		if (doCollide(m_player, t)){
//			Vec2 overlap = getOverlap(m_player, t);
//			std::cout << "Collision horizontal : " << overlap.x << " vertical : " << overlap.y << "\n";
//		}
		if (doCollide(m_player, t) && getPreviousOverlap(m_player, t).y <= 0){
			//std::cout << "collision from top detected\n";
			m_player->cTransform->velocity.y = 0;
			m_player->cTransform->pos.y -= getOverlap(m_player, t).y;

			if (m_player->cTransform->pos.y < t->cTransform->pos.y){
				m_player->isOnGround = true;
			}
		}
		//&& getOverlap(m_player, t).x > 0)
		if (doCollide(m_player, t) && getPreviousOverlap(m_player, t).x <= 0) {
			//std::cout << "collision from top detected\n";
			m_player->cTransform->velocity.x = 0;
			if (m_player->cTransform->pos.x  > t->cTransform->pos.x){
				m_player->cTransform->pos.x += getOverlap(m_player, t).x;
			} else {
				m_player->cTransform->pos.x -= getOverlap(m_player, t).x;
			}
		}
	}
}

bool ScenePlay::doCollide(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2){
	// Vertical collision
	bool hCollision = (e1->cTransform->pos.y  - e1->cBoundingBox->box.y/2 < e2->cTransform->pos.y + e2->cBoundingBox->box.y/2 && \
	e2->cTransform->pos.y - e2->cBoundingBox->box.y/2 < e1->cTransform->pos.y + e1->cBoundingBox->box.y/2);

	// Horizontal collision
	bool vCollision = (e1->cTransform->pos.x + e1->cBoundingBox->box.x/2 > e2->cTransform->pos.x - e2->cBoundingBox->box.x/2 && \
	e2->cTransform->pos.x + e2->cBoundingBox->box.x/2 > e1->cTransform->pos.x - e1->cBoundingBox->box.x/2);

	return (vCollision && hCollision);
}

bool ScenePlay::didCollide(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2){
	// Vertical collision
	bool hCollision = (e1->cTransform->prevPos.y  - e1->cBoundingBox->box.y/2 < e2->cTransform->prevPos.y + e2->cBoundingBox->box.y/2 && \
	e2->cTransform->prevPos.y - e2->cBoundingBox->box.y/2 < e1->cTransform->prevPos.y + e1->cBoundingBox->box.y/2);

	// Horizontal collision
	bool vCollision = (e1->cTransform->prevPos.x + e1->cBoundingBox->box.x/2 > e2->cTransform->prevPos.x - e2->cBoundingBox->box.x/2 && \
	e2->cTransform->prevPos.x + e2->cBoundingBox->box.x/2 > e1->cTransform->prevPos.x - e1->cBoundingBox->box.x/2);

	return (vCollision && hCollision);
}

Vec2 ScenePlay::getOverlap(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2){
	Vec2 delta = e1->cTransform->pos - e2->cTransform->pos;
	delta = {std::abs(delta.x), std::abs(delta.y)};
	Vec2 overlap = e1->cBoundingBox->box/2 + e2->cBoundingBox->box/2 - delta;
	return overlap;
}

Vec2 ScenePlay::getPreviousOverlap(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2){
	Vec2 delta = e1->cTransform->prevPos - e2->cTransform->prevPos;
	delta = {std::abs(delta.x), std::abs(delta.y)};
	Vec2 overlap = e1->cBoundingBox->box/2 + e2->cBoundingBox->box/2 - delta;
	return overlap;
}
// Negative overlap means no collision and positive overlap means collision. Also, the axis with smaller positive overlap is the axis of collision.

void ScenePlay::sMovement(){
	auto & entities =  m_entityManager.getEntities();
	for (auto & e : entities){
		if (e->cTransform){
			e->cTransform->prevPos = e->cTransform->pos;
			if (e->cGravity){e->cTransform->velocity.y += e->cGravity->gravity;}
			e->cTransform->pos += e->cTransform->velocity;
			// TODO
			// cap velocity at max velocity
		}
	}
}

void ScenePlay::sRender(){
	gameEngine->window().clear(sf::Color::Blue);
	gameEngine->window().draw(m_title);
	//std::cout << "Getting player's sprite\n";
	//gameEngine->window().draw(m_player->cAnimation->animation.getSprite());

	auto & decorations = m_entityManager.getEntities(decoration);
	for (auto & dec : decorations){
		dec->cAnimation->update();
		if (dec->cTransform){
			Vec2 pos = dec->cTransform->pos;
			dec->cAnimation->getSprite().setPosition(pos.x, pos.y);
		}
		gameEngine->window().draw(dec->cAnimation->getSprite());
		//std::cout << "Entity drawn\n";
	}

	auto & entities = m_entityManager.getEntities(tile);
	for (auto & tile : entities){
		tile->cAnimation->update();
		if (tile->cTransform){
			Vec2 pos = tile->cTransform->pos;
			tile->cAnimation->getSprite().setPosition(pos.x, pos.y);
		}
		gameEngine->window().draw(tile->cAnimation->getSprite());
		//std::cout << "Entity drawn\n";
	}
	m_player->cAnimation->update();
	Vec2 pos = m_player->cTransform->pos;
	m_player->cAnimation->getSprite().setPosition(pos.x, pos.y);
	gameEngine->window().draw(m_player->cAnimation->getSprite());

	//gameEngine->window().draw(m_entityManager.getEntities())
	//std::cout << "player drawn\n";
	gameEngine->window().display();
	;
}

void ScenePlay::registerActions(){
	Scene::registerAction(sf::Keyboard::W, true, {JUMP, START});
	Scene::registerAction(sf::Keyboard::Space, true, {SHOOT, START});
	Scene::registerAction(sf::Keyboard::Escape, true,  {PAUSE, START});
	Scene::registerAction(sf::Keyboard::D, true,  {RIGHT, START});
	Scene::registerAction(sf::Keyboard::A, true,  {LEFT, START});

	Scene::registerAction(sf::Keyboard::W, false, {JUMP, END});
	Scene::registerAction(sf::Keyboard::Space, false, {SHOOT, END});
	//Scene::registerAction(sf::Keyboard::Escape, false,  {PAUSE, END});
	Scene::registerAction(sf::Keyboard::D, false,  {RIGHT, END});
	Scene::registerAction(sf::Keyboard::A, false,  {LEFT, END});
}

void ScenePlay::doAction(Action a){
	switch (a.name){
		case (JUMP):
			std::cout << "JUMP Action passed.\n";
			//bool collisionFromTop = doCollide(m_player, t) && getPreviousOverlap(m_player, t).y <= 0 && getOverlap(m_player, t).y > 0;
			if (a.type == eActionType::START){
				//if (m_player->cTransform->pos.y == m_player->cTransform->prevPos.y){
				if (m_player->isOnGround){
					m_player->cTransform->velocity.y = -20;
					std::cout << "Player jumped\n";
				} else {
					std::cout << "Player cannot jump (Not on Ground)\n";
				}
			} else {
				if(m_player->cTransform->velocity.y < 0){
					m_player->cTransform->velocity.y = 0;
				}
			}
			break;
		case (SHOOT):
			std::cout << "SHOOT Action passed.\n";
			break;
		case (LEFT):
			std::cout << "LEFT Action passed.\n";
			if (a.type == eActionType::START){
				m_player->cTransform->velocity.x = -4;
			} else {
				m_player->cTransform->velocity.x = 0;
			}
			break;
		case (RIGHT):
			std::cout << "RIGHT Action passed.\n";
			if (a.type == eActionType::START){
				m_player->cTransform->velocity.x = 4;
			} else {
				m_player->cTransform->velocity.x = 0;
			}
			break;
		case (PAUSE):
			std::cout << "PAUSE Action passed.\n";
			gameEngine->changeScene("MENU", gameEngine->getScene("MENU"));
			break;
	}
}

