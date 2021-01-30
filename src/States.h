#pragma once
#ifndef __STATES_H__
#define __STATES_H__
class State
{
public:
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
	virtual ~State();
protected:
	State() {};
};

class TitleState:public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class SeekState : public State
{
public:
	SeekState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

};
class FleeState : public State
{
public:
	FleeState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

};
class ArriveState : public State
{
public:
	ArriveState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();

};
#endif
