#include "Game.h"

#include "Actor.h"
#include "FPSActor.h"
#include "FollowActor.h"

#include "Assets.h"
#include "MeshComponent.h"
#include "AudioComponent.h"

#include "Cube.h"
#include "Sphere.h"
#include "Plane.h"

#include "Timer.h"

// Game specific includes
#include "Consts.h"


bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isAudioInit = audioSystem.initialize();
	bool isInputInit = inputSystem.initialize();

	return isWindowInit && isRendererInit && isAudioInit && isInputInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	inputSystem.setMouseRelativeMode(true);

	//v =============================================================╗
	//v Load Shaders/Textures/Meshes                                 ║

	// SHADERS ==============================
	Assets::loadShader("Res\\Shaders\\Sprite.vert", "Res\\Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("Res\\Shaders\\Phong.vert", "Res\\Shaders\\Phong.frag", "", "", "", "Phong");
	Assets::loadShader("Res\\Shaders\\BasicMesh.vert", "Res\\Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");

	// TEXTURES =============================
	// -- Basic textures --
	Assets::loadTexture(renderer, "Res\\Textures\\Default.png", "Default");
	Assets::loadTexture(renderer, "Res\\Textures\\Cube.png", "Cube");
	Assets::loadTexture(renderer, "Res\\Textures\\Plane.png", "Plane");
	Assets::loadTexture(renderer, "Res\\Textures\\Sphere.png", "Sphere");

	// -- Game specific textures --
	Assets::loadTexture(renderer, "Res\\Textures\\DualPuzzleStarting.png", "GameImage");

	Assets::loadTexture(renderer, "Res\\Textures\\Background.png", "Background");

	Assets::loadTexture(renderer, "Res\\Textures\\A_Start.png", "A_Start");
	Assets::loadTexture(renderer, "Res\\Textures\\A_Start_0.png", "A_Start_0");
	Assets::loadTexture(renderer, "Res\\Textures\\A_Start_1.png", "A_Start_1");
	Assets::loadTexture(renderer, "Res\\Textures\\A_Start_2.png", "A_Start_2");
	Assets::loadTexture(renderer, "Res\\Textures\\A_End.png", "A_End");

	Assets::loadTexture(renderer, "Res\\Textures\\B_Start.png", "B_Start");
	Assets::loadTexture(renderer, "Res\\Textures\\B_Start_0.png", "B_Start_0");
	Assets::loadTexture(renderer, "Res\\Textures\\B_Start_1.png", "B_Start_1");
	Assets::loadTexture(renderer, "Res\\Textures\\B_Start_2.png", "B_Start_2");
	Assets::loadTexture(renderer, "Res\\Textures\\B_End.png", "B_End");

	Assets::loadTexture(renderer, "Res\\Textures\\Obstacle.png", "Obstacle");
	Assets::loadTexture(renderer, "Res\\Textures\\Limit.png", "Limit");
	Assets::loadTexture(renderer, "Res\\Textures\\Limit_0.png", "Limit_0");
	Assets::loadTexture(renderer, "Res\\Textures\\Limit_1.png", "Limit_1");
	Assets::loadTexture(renderer, "Res\\Textures\\Limit_2.png", "Limit_2");

	// MESHES ===============================
	// -- Basic meshes --
	Assets::loadMesh("Res\\Meshes\\BasicMeshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("Res\\Meshes\\BasicMeshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("Res\\Meshes\\BasicMeshes\\Sphere.gpmesh", "Mesh_Sphere");

	// -- Game specific meshes --
	Assets::loadMesh("Res\\Meshes\\Tile.gpmesh", "Mesh_Tile");
	Assets::loadMesh("Res\\Meshes\\GameCube.gpmesh", "GameCube_Tile");

	//^ Load Shaders/Textures/Meshes                                 ║
	//^ =============================================================╝

	loadStates();
}

void Game::processInput()
{
	inputSystem.preUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		isRunning = inputSystem.processEvent(event);
	}

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	//v Game states ==================================================
	if (state == GameState::MainMenu) {
		// Escape: quit game
		if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
		{
			isRunning = false;
		}

		// Enter: launch first level
		if (input.keyboard.getKeyState(SDL_SCANCODE_RETURN) == ButtonState::Released) {
			setState(GameState::Gameplay);
		}

		return;
	}

	if (state == GameState::Gameplay)
	{
		// Escape: go to main menu
		if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
		{
			setState(GameState::MainMenu);
		}

		// Actor input
		isUpdatingActors = true;
		for (auto actor : actors)
		{
			actor->processInput(input);
		}
		isUpdatingActors = false;
	
		return;
	}

	if (state == GameState::WinGame) {
		// Enter: launch first level
		if (input.keyboard.getKeyState(SDL_SCANCODE_RETURN) == ButtonState::Released) {
			setState(GameState::MainMenu);
		}
	}

	//^ Game states ==================================================
}

void Game::update(float dt)
{
	// Update audio
	audioSystem.update(dt);

	//v =============================================================╗
	//v Common actor management                                      ║

	// Update actors 
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		pendingActor->computeWorldTransform();
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}

	//^ Common actor management                                      ║
	//^ =============================================================╝
	//v =============================================================╗
	//v Main menu                                                    ║

	if (state == GameState::MainMenu) {

	}

	//^ Main menu                                                    ║
	//^ =============================================================╝
	//v =============================================================╗
	//v Gameplay                                                     ║

	else if (state == GameState::Gameplay)
	{
		// Update level
		level->update(dt);
	}

	//^ Gameplay                                                     ║
	//^ =============================================================╝
	//v =============================================================╗
	//v Win                                                          ║

	else if (state == GameState::WinGame) {

	}

	//^ Win                                                          ║
	//^ =============================================================╝

}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::loadStates()
{
	while (!actors.empty())
	{
		delete actors.back();
	}

	if (state == GameState::MainMenu) {
		Actor* test = new Actor{};
		test->setScale(1.0f);
		SpriteComponent* spriteComponent = new SpriteComponent{ test, Assets::getTexture("GameImage") };


		// Top view camera
		renderer.setViewMatrix(Matrix4::createLookAt(Vector3{ 0.0f, 0.0f, Consts::Camera::HEIGHT }, Vector3::negUnitY, Vector3::unitZ));
	
		return;
	}
	if (state == GameState::Gameplay)
	{
		// Create level
		level = new Level{ 1 };

		// Top view camera
		renderer.setViewMatrix(Matrix4::createLookAt(Vector3{ 0.0f, 0.0f, Consts::Camera::HEIGHT }, Vector3::negUnitY, Vector3::unitZ));

		// Setup lights
		renderer.setAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
		DirectionalLight& dir = renderer.getDirectionalLight();
		dir.direction = Vector3(0.0f, -0.707f, -0.707f);
		dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
		dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

		// Start music
		//musicEvent = audioSystem.playEvent("event:/Music");

		//v =============================================================╗
		//v Tests                                                        ║

		// Enable FPS view
		// FPSActor* testActor = new FPSActor();


		//^ Tests                                                        ║
		//^ =============================================================╝ 
		
		return;
	}

	if (state == GameState::WinGame) {
		Actor* test = new Actor{};
		test->setScale(1.0f);
		SpriteComponent* spriteComponent = new SpriteComponent{ test, Assets::getTexture("Default") };


		// Top view camera
		renderer.setViewMatrix(Matrix4::createLookAt(Vector3{ 0.0f, 0.0f, Consts::Camera::HEIGHT }, Vector3::negUnitY, Vector3::unitZ));
	
		return;
	}
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::close()
{
	inputSystem.close();
	renderer.close();
	audioSystem.close();
	window.close();
	SDL_Quit();
}

void Game::setState(GameState stateP)
{
	state = stateP;
	loadStates();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}
