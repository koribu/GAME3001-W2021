#pragma once
#ifndef __BEHAVIOR_STATE__
#define __BEHAVIOR_STATE__
enum BehaviorState
{
	NONE_STATE = -1,
	SEEK_STATE,
	FLEE_STATE,
	ARRIVE_STATE,
	OBSTACLE_STATE
};
#endif