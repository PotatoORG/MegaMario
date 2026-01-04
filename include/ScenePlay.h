#ifndef SCENEPLAY_H
#define SCENEPLAY_H

#include "Scene.h"

struct PlayerConfig{
	std::string B;
	int GX, GY;
	float CW, CH, SX, SY, SM, G;};

class ScenePlay : public Scene{
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_title;
	std::shared_ptr<Entity> m_player;
	PlayerConfig m_playerConfig;
public:
	void update(); // to be ran each iteration of game loop
	void doAction(Action a); // Will be overrided by the derived class
	void registerActions();
	void spawnPlayer();
	void spawnTile(const std::string & animationName, int GX, int GY);
	void spawnDecoration(const std::string & animationName, float x, float y);
	void makeLevel(const std::string & levelConfigPath);

	void sRender(); // Systems
	void sMovement();
	ScenePlay(GameEngine * ge, const std::string &);
};
#endif // SCENEPLAY_H
