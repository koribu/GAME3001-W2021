#pragma once
#ifndef __SPACE_SHIP__
#define __SPACE_SHIP__
#include "DisplayObject.h"
#include "TextureManager.h"

#include "BehaviorState.h"
class SpaceShip final : public DisplayObject
{
public:
	SpaceShip();
		~SpaceShip();
	
	void draw() override;
	void update() override;
	void clean() override;

	void setMaxSpeed(const float maxSpeed);
	void setDestination(const glm::vec2 destination);
	void setOrientation(const glm::vec2 orientation);
	void setAngle(const float angle);
	
	float getAngle() const;
	glm::vec2 getOrientation() const;
	float getTurnRate() const;
	float getMaxSpeed() const;
	void setTurnRate(float rate);
	float getAccelerationRate() const;
	void setAccelerationRate(float rate);
	void setIsArriveRange(bool a)
	{
		m_isArriveRange = a;
	}
	bool getIsArriveRange()
	{
		return m_isArriveRange;
	}
	
	void setState(BehaviorState state);


private:
	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_angle;
	float m_turnRate;
	float m_accelerationRate;
	bool m_isArriveRange;
	
	void m_SeekMove();
	void m_FleeMove();
	void m_ArriveMove();

	
	BehaviorState m_state = SEEK_STATE;
	float m_maxSpeed;
};

#endif
