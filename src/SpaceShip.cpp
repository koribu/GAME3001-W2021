#include "SpaceShip.h"
#include "Game.h"
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
	setMaxSpeed(10.0f);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
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
	
	switch (m_state)
	{
	case SEEK_STATE:
		m_SeekMove();
		break;
	case FLEE_STATE:
		m_FleeMove();
		break;

	case ARRIVE_STATE:
		if(!getIsArriveRange())
		{
			m_SeekMove();
		}
		else
		{
			m_ArriveMove();
		}
		
		break;
	
	default:
		break;
	}
	
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

	auto angle_in_radians = (angle - 90.0f) * Util::Deg2Rad;

	auto x = cos(angle_in_radians);
	auto y = sin(angle_in_radians);

	setOrientation(glm::vec2(x, y));
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

float SpaceShip::getMaxSpeed() const
{
	return m_maxSpeed;
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

void SpaceShip::setState(BehaviorState state)
{
	m_state = state;
}



void SpaceShip::m_SeekMove()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	
	//magnitude
	m_targetDirection = m_destination - getTransform()->position;
	//normalized
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensivity = 5.0f;

	if(abs(target_rotation)>turn_sensivity)
	{
		
		if (target_rotation > 0.0f)
		{
			setAngle(getAngle() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setAngle(getAngle() - getTurnRate());
		}

	}	

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	//using the formula pf=pi+vi*t+0.5ai*t^2
	getRigidBody()->velocity += getOrientation()*(deltaTime) +
		0.5f * getRigidBody()->acceleration*(deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}

void SpaceShip::m_FleeMove()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	//magnitude
	m_targetDirection = m_destination - getTransform()->position;
	//normalized
	m_targetDirection = Util::normalize(m_targetDirection * glm::vec2(-1,-1));

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensivity = 5.0f;

	if (abs(target_rotation) > turn_sensivity)
	{

		if (target_rotation > 0.0f)
		{
			setAngle(getAngle() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setAngle(getAngle() - getTurnRate());
		}

	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	//using the formula pf=pi+vi*t+0.5ai*t^2
	getRigidBody()->velocity += getOrientation() * (deltaTime)+
		0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;
}

void SpaceShip::m_ArriveMove()
{
	
	
	auto deltaTime = TheGame::Instance()->getDeltaTime();

	//magnitude
	m_targetDirection = m_destination - getTransform()->position;
	//normalized
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensivity = 5.0f;

	setTurnRate(0);

	if (abs(target_rotation) > turn_sensivity)
	{

		if (target_rotation > 0.0f)
		{
			setAngle(getAngle() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setAngle(getAngle() - getTurnRate());
		}

	}

	//getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	//using the formula pf=pi+vi*t+0.5ai*t^2
	
	//getRigidBody()->velocity += getOrientation() * (deltaTime)+
	//	0.5f * getRigidBody()->acceleration * (deltaTime);


	if(m_destination == getTransform()->position)
	{
		m_maxSpeed = 0;
		
	}
	
	std::cout << getRigidBody()->velocity.length() << std::endl;

	getTransform()->position += getRigidBody()->velocity * (m_maxSpeed/2);

	
}
