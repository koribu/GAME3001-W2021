#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

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
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(700, 300);
	addChild(m_pTarget);

	m_pObstacle = new Obstacle;
	m_pObstacle->getTransform()->position = glm::vec2(500.0f, 300.0f);
	addChild(m_pObstacle);
	
	//Space ship sprite
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(100, 100);
	addChild(m_pSpaceShip);
	m_pSpaceShip->setEnabled(false);
	m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	//addChild(m_pInstructionsLabel);

	
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
		turn_rate = 5.0f;
		acceleration_rate = 2.0f;
		speed = 10.0f;
		angleInRad = m_pSpaceShip->getAngle();
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
