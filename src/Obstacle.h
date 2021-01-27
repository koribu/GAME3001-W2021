#pragma once
#ifndef  __OBSTACLE__
#define __OBSTACLE__
#include "DisplayObject.h"

class Obstacle:public DisplayObject
{
public:
	//constructor
	Obstacle();
	//destructor
	~Obstacle();

	void draw() override;
	void update() override;
	void clean() override;
private:
	

};

#endif


