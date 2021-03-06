#include "Obstacle.h"


#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"

Obstacle::Obstacle()
{
	TextureManager::Instance()->load("../Assets/textures/obstacle.png","obstacle");

	auto size = TextureManager::Instance()->getTextureSize("obstacle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(300.0f, 300.0f);

	setType(OBSTACLE);

	getRigidBody()->isColliding = false;

	SoundManager::Instance().load("../Assets/audio/yay.ogg", "yay",SOUND_SFX);
}

Obstacle::~Obstacle()
{
}

void Obstacle::draw()
{
	TextureManager::Instance()->draw("obstacle", getTransform()->position.x, getTransform()->position.y,
		90, 255, false);
}

void Obstacle::update()
{
}

void Obstacle::clean()
{
}
