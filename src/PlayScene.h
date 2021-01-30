#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"

#include "Enemy.h"
#include "Obstacle.h"
#include "SpaceShip.h"
#include "Target.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Target* m_pTarget;

	SpaceShip* m_pSpaceShip;

	Label* m_pInstructionsLabel;

	Obstacle* m_pObstacle;

	/*enum m_states {seek,flee,arrive,reset};
	m_states currentState = reset;*/
};

#endif /* defined (__PLAY_SCENE__) */