#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

using namespace std;

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();

	CollisionManager::AABBCheck(m_pSpaceShip, m_pObstacle);
	if(CollisionManager::circleAABBsquaredDistance(m_pTarget->getTransform()->position, 150, 
		m_pSpaceShip->getTransform()->position, m_pSpaceShip->getWidth(), m_pSpaceShip->getHeight())<= 0)
	{
		m_pSpaceShip->setIsArriveRange(true);
	}


	if (CollisionManager::lineRectCheck(m_pSpaceShip->getTransform()->position, m_pSpaceShip->getTransform()->position + (m_pSpaceShip->getOrientation() * 125.0f),
		m_pObstacle->getTransform()->position,100,200 /*m_pObstacle->getWidth(), m_pObstacle->getHeight()*/) == true && m_pSpaceShip->getState() == OBSTACLE_STATE)
	{
		
		m_pSpaceShip->setMaxSpeed(/*m_pSpaceShip->getMaxSpeed() / 3*/1.0f);
		m_pSpaceShip->setAccelerationRate(10.0f);
		m_pSpaceShip->setDestination(m_pSpaceShip->getTransform()->position + (m_pSpaceShip->getOrientation() * 100.0f)+glm::vec2(-100.0f,500.0f));
	}
	else if(CollisionManager::lineRectCheck(m_pSpaceShip->getTransform()->position, getTransform()->position + (m_pSpaceShip->getOrientation() + (Util::setAngle(90)) * 80.0f),
		m_pObstacle->getTransform()->position, m_pObstacle->getWidth(), m_pObstacle->getHeight()-20) == false && m_pSpaceShip->getState() == OBSTACLE_STATE)
	{
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip->setMaxSpeed(10.0f);
		m_pSpaceShip->setAccelerationRate(10.0f);
		m_pSpaceShip->setTurnRate(10.0f);
	}
	if (CollisionManager::lineRectCheck(m_pSpaceShip->getTransform()->position, getTransform()->position + (m_pSpaceShip->getOrientation() + (Util::setAngle(60)) * 150.0f),
		m_pObstacle->getTransform()->position, m_pObstacle->getWidth(), m_pObstacle->getHeight()) == true && m_pSpaceShip->getState() == OBSTACLE_STATE)
	{
		m_pSpaceShip->setAccelerationRate(10.0f);
		//m_pSpaceShip->setDestination(m_pSpaceShip->getTransform()->position + (m_pSpaceShip->getOrientation() * 100.0f) + glm::vec2(-50.0f, 100.0f));
	}
	if (CollisionManager::lineRectCheck(m_pSpaceShip->getTransform()->position, getTransform()->position + (m_pSpaceShip->getOrientation() - (Util::setAngle(60)) * 150.0f),
		m_pObstacle->getTransform()->position, m_pObstacle->getWidth(), m_pObstacle->getHeight()) == true && m_pSpaceShip->getState() == OBSTACLE_STATE)
	{
		m_pSpaceShip->setAccelerationRate(10.0f);
		//m_pSpaceShip->setDestination(m_pSpaceShip->getTransform()->position + (m_pSpaceShip->getOrientation() * 100.0f) + glm::vec2(-50.0f, 100.0f));
	}

	else
	{
		
	}
	
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		m_pSpaceShip->setState(SEEK_STATE);
		
		m_pSpaceShip->setMaxSpeed(10.0f);
		m_pSpaceShip->setAccelerationRate(10.0f);
		m_pSpaceShip->setTurnRate(10.0f);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setAngle(0.0f);

		SoundManager::Instance().setSoundVolume(1);
		SoundManager::Instance().playSound("explode1");
		
		
		m_pSpaceShip->getTransform()->position = glm::vec2(/*(Util::RandomRange(-100.0f, 0.0f))*/-10, 
			/*Util::RandomRange(-100.0f, 700.0f)*/-10 );
		m_pSpaceShip->setEnabled(true);
		m_pTarget->setEnabled(true);
		
		m_pTarget->getTransform()->position = glm::vec2(450.f,300.0f/*Util::RandomRange(200.0f, 600.0f), Util::RandomRange(150.0f, 450.0f*/);

		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pObstacle->setEnabled(false);

		
		//currentState = seek;
	} 
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		m_pSpaceShip->setState(FLEE_STATE);

		m_pSpaceShip->setMaxSpeed(5.0f);
		m_pSpaceShip->setAccelerationRate(5.0f);
		m_pSpaceShip->setTurnRate(2.0f);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setAngle(0.0f);

		SoundManager::Instance().setSoundVolume(8);
		SoundManager::Instance().playSound("laser1");
		
		m_pSpaceShip->getTransform()->position = glm::vec2(400.0f,300.0f);

		m_pTarget->getTransform()->position = glm::vec2(350.0f,300.0f);

		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);

		m_pSpaceShip->setEnabled(true);
		m_pTarget->setEnabled(true);
		m_pObstacle->setEnabled(false);
		//currentState = flee;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		m_pSpaceShip->setState(ARRIVE_STATE);

		m_pSpaceShip->getTransform()->position = glm::vec2(10.0f, 150.0f);
		
		SoundManager::Instance().setSoundVolume(10);
		SoundManager::Instance().playSound("laser2");
		
		m_pSpaceShip->setIsArriveRange(false);
		m_pSpaceShip->setMaxSpeed(8.0f);
		m_pSpaceShip->setAccelerationRate(8.0f);
		m_pSpaceShip->setTurnRate(8.0f);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);

		m_pTarget->getTransform()->position = glm::vec2(450.0f, 300.0f);

		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		
		m_pSpaceShip->setAngle(0.0f);


		m_pObstacle->setEnabled(false);
		m_pTarget->setEnabled(true);
		m_pSpaceShip->setEnabled(true);

	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		m_pSpaceShip->setState(OBSTACLE_STATE);

		SoundManager::Instance().setSoundVolume(1);
		SoundManager::Instance().playSound("explode2");
		
		m_pSpaceShip->setMaxSpeed(5.0f);
		m_pSpaceShip->setAccelerationRate(3.0f);
		m_pSpaceShip->setTurnRate(5.0f);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setAngle(0.0f);

		m_pObstacle->setEnabled(true);
		

		m_pSpaceShip->getTransform()->position = glm::vec2(/*(Util::RandomRange(-100.0f, 0.0f))*/10.0f,
			/*Util::RandomRange(-100.0f, 700.0f)*/300.0f);
		m_pSpaceShip->setEnabled(true);
		m_pTarget->setEnabled(true);

		m_pTarget->getTransform()->position = glm::vec2(650.f, 300.0f);

		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);


		//currentState = seek;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0))
	{
		m_pSpaceShip->setEnabled(false);
		m_pTarget->setEnabled(false);
		m_pTarget->getTransform()->position = glm::vec2(Util::RandomRange(0.0f, 700.0f), Util::RandomRange(100.0f, 700.0f));
//		currentState = reset;
	}
	
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	
	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press 1 for Seek Behavior", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 25.0f);
	addChild(m_pInstructionsLabel);
	m_pInstructionsLabel = new Label("Press 2 for Flee Behavior", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 50.0f);
	addChild(m_pInstructionsLabel);
	m_pInstructionsLabel = new Label("Press 3 for Arrive Behavior", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 75.0f);
	addChild(m_pInstructionsLabel);
	m_pInstructionsLabel = new Label("Press 4 for Obstacle Avoidance Behavior", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 100.0f);
	addChild(m_pInstructionsLabel);
	
	
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(Util::RandomRange(200.0f, 500.0f), Util::RandomRange(100.0f, 500.0f));
	addChild(m_pTarget);
	m_pTarget->setEnabled(false);

	m_pObstacle = new Obstacle;
	m_pObstacle->getTransform()->position = glm::vec2(300.0f, 200.0f);
	addChild(m_pObstacle);
	m_pObstacle->setEnabled(false);

	//Space ship sprite
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(100, 100);
	addChild(m_pSpaceShip);
	m_pSpaceShip->setEnabled(false);
	m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	
	SoundManager::Instance().setMusicVolume(10.0f);
	SoundManager::Instance().setSoundVolume(3);
	SoundManager::Instance().load("../Assets/audio/explosion.wav", "explode1", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Laser.wav", "laser1", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Laser2.wav", "laser2", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Explosion2.wav", "explode2", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/FincaTenda.mp3", "bom", SOUND_MUSIC);

	SoundManager::Instance().playMusic("bom", -1, 0);
	




	
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float angleInRad = m_pSpaceShip->getAngle();
	if(ImGui::SliderAngle("Orientation Angle",&angleInRad))
	{
		m_pSpaceShip->setAngle(angleInRad * Util::Rad2Deg);
	}

	static float acceleration_rate = 2.0f;
	if (ImGui::SliderFloat("Acceleration Rate", &acceleration_rate, 0.0f, 50.0f))
	{
		m_pSpaceShip->setAccelerationRate((acceleration_rate));
	}

	static float turn_rate = 5.0f;
	if(ImGui::SliderFloat("Turn Rate",&turn_rate,0.0f,20.0f))
	{
		m_pSpaceShip->setTurnRate(turn_rate);
	}
	
	static float speed = 5.0f;
	if(ImGui::SliderFloat("Max Speed", &speed, 0.0f, 100.0f))
	{
		m_pSpaceShip->setMaxSpeed(speed);
	}
	if(ImGui::Button("Start"))
	{
		m_pSpaceShip->setEnabled(true);
	}

	ImGui::SameLine(100.0f);

	if (ImGui::Button("Reset"))
	{
		m_pSpaceShip->setEnabled(false);
		m_pSpaceShip->getTransform()->position = glm::vec2(100, 100);
		m_pSpaceShip->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pSpaceShip->setAngle(0.0f);
		angleInRad = m_pSpaceShip->getAngle();
		turn_rate = 5.0f;
		acceleration_rate = 2.0f;
		speed = 10.0f;
	
	}
	ImGui::Separator();

	static float targetPos[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if(ImGui::SliderFloat2("Target", targetPos, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPos[0], targetPos[1]);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}
	
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
