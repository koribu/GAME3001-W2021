#include "SpaceShip.h"


#include "TextureManager.h"
#include "Util.h"

SpaceShip::SpaceShip()
{
	TextureManager::Instance()->load("../Assets/textures/spaceship.png", "spaceship");
	auto size = TextureManager::Instance()->getTextureSize("spaceship");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SPACE_SHIP);

	setAngle(0.0f);
	setMaxSpeed(5.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::draw()
{
	TextureManager::Instance()->draw("spaceship", getTransform()->position.x, getTransform()->position.y,
		m_angle, 255, true);

	Util::DrawLine(getTransform()->position, getTransform()->position + (m_orientation * 100.0f));
}

void SpaceShip::update()
{
	m_Move();
}

void SpaceShip::clean()
{
}

void SpaceShip::setMaxSpeed(const float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

void SpaceShip::setDestination(const glm::vec2 destination)
{
	 m_destination = destination;
}

void SpaceShip::setOrientation(const glm::vec2 orientation)
{
	m_orientation = orientation;
}

void SpaceShip::setAngle(const float angle)
{
	m_angle = angle;
}

float SpaceShip::getAngle() const
{
	return m_angle;
}

glm::vec2 SpaceShip::getOrientation() const
{
	return m_orientation;
}

float SpaceShip::getTurnRate() const
{
	return m_turnRate;
}

void SpaceShip::setTurnRate(float rate)
{
	m_turnRate = rate;
}

float SpaceShip::getAccelerationRate() const
{
	return m_accelerationRate;
}

void SpaceShip::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void SpaceShip::m_Move()
{
	//magnitude
	m_targetDirection = m_destination - getTransform()->position;
	//normalized
	m_targetDirection = Util::normalize(m_targetDirection);

	getRigidBody()->velocity = m_targetDirection * m_maxSpeed;

	getTransform()->position += getRigidBody()->velocity;
}
