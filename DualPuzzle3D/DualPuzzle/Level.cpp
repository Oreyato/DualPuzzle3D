#include "Level.h"

#include "Consts.h"
#include "Game.h"


Level::Level(int levelIndexP) :
	currentLevelIndex{ levelIndexP },
	game{ Game::instance() }
{
	tileWidth = Consts::Tile::WIDTH;
	tileLength = Consts::Tile::LENGTH;

	fillLayouts();
	generateLevel();
}

Level::~Level()
{
}

void Level::generateLevel()
{
	Layout currentLayout = levelLayouts[currentLevelIndex];

	int rows = currentLayout.rowNb;
	int columns = currentLayout.colNb;

	float xOffset = tileWidth * columns / 2.0f;
	float yOffset = tileLength * rows / 2.0f;

	Vector2 offset{ xOffset, yOffset };

	int index{ 0 };

	Quaternion gameCubeRot{ Vector3::unitY, Maths::pi };
	gameCubeRot = Quaternion::concatenate(gameCubeRot, Quaternion{ Vector3::unitZ, Maths::pi });

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++) {
			int desc = currentLayout.description[index];

			// -- Create Tile --
			Tile* tile = new Tile(tileWidth, tileLength, desc);
			Vector3 pos{ col * tileLength - offset.x, row * tileWidth - offset.y, .0f };

			tile->setPosition(pos);
			tile->setType(TileType::A_START);

			level.push_back(tile);

			index++;

			// -- Create GameCubes --
			if (desc != TileType::LIMIT) {
				// Create ground cubes
				GameCube* ground = new GameCube{ tileWidth, tileLength, desc };

				ground->setPosition(Vector3{ pos });
				ground->setScale(100.0f);
				ground->setRotation(gameCubeRot);

				actors.push_back(ground);

				// Create special GameCubes
				if (desc != TileType::BACKGROUND) {
					// PLAYER CUBES
					if (desc == TileType::A_START || desc == TileType::B_START) {
						MovableGameCube* movableCube = new MovableGameCube{ tileWidth, tileLength, desc };
						pos += Vector3{ 0.0f, 0.0f, 100.0f };

						movableCube->setPosition(Vector3{ pos });
						movableCube->setScale(100.0f);
						movableCube->setRotation(gameCubeRot);
						movableCube->getTileGridInputComponent()->setLevelLayout(currentLayout);

						playerCharacters.push_back(movableCube);
						actors.push_back(movableCube);
					}
					// OBSTACLES
					else if (desc == TileType::OBSTACLE) {
						GameCube* obstacleCube = new GameCube{ tileWidth, tileLength, desc };
						pos += Vector3{ 0.0f, 0.0f, 100.0f };

						obstacleCube->setPosition(Vector3{ pos });
						obstacleCube->setScale(100.0f);

						actors.push_back(obstacleCube);
					}
				}
			}
		}
	}

	std::cout << "Level size: " << level.size() << std::endl;
}

void Level::update(float dt)
{
	if (playerCharacters.size() != 0)
	{
		for (MovableGameCube* character : playerCharacters) {
			if (character->getState() == Actor::ActorState::Out) {
				clean();

				generateLevel();
			}
		}
	}
}

void Level::setLevel(int levelIndex)
{
	currentLevelIndex = levelIndex;

	generateLevel();
}

void Level::clean()
{
	for (Actor* actor : actors) {
		actor->setState(Actor::ActorState::Dead);
	}
	actors.clear();
	playerCharacters.clear();
}

void Level::fillLayouts()
{
	levelLayouts.emplace_back(Layout{
		0,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
		});
	levelLayouts.emplace_back(Layout{
		1,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	6,	6,	6,	6,	1,	1,	1,	1,	6,	4,	1,	1,	7,
			7,	2,	1,	1,	6,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	6,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	6,	1,	1,	5,	6,	6,	6,	6,	7,
			7,	6,	6,	1,	1,	6,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	3,	1,	1,	1,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
	levelLayouts.emplace_back(Layout{
		2,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	4,	1,	1,	6,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	6,	6,	1,	1,	1,	7,
			7,	1,	1,	1,	6,	6,	1,	1,	6,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	6,	1,	5,	1,	1,	7,
			7,	1,	6,	6,	1,	1,	1,	1,	6,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	6,	3,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
	levelLayouts.emplace_back(Layout{
		3,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	6,	6,	3,	6,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	6,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	6,	1,	1,	1,	1,	1,	1,	6,	6,	1,	7,
			7,	1,	6,	1,	1,	1,	1,	1,	1,	1,	4,	1,	1,	7,
			7,	1,	6,	1,	5,	1,	6,	6,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
	levelLayouts.emplace_back(Layout{
		4,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	1,	1,	1,	1,	6,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	6,	1,	5,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	6,	1,	1,	1,	1,	6,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	3,	1,	6,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	4,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	6,	1,	1,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
	levelLayouts.emplace_back(Layout{
		4,
		{
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	3,	1,	2,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	6,	6,	1,	1,	6,	1,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	6,	6,	1,	1,	1,	1,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	6,	1,	1,	6,	6,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	4,	1,	5,	1,	7,
			7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
			7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
		},
		9,
		14
	});
}