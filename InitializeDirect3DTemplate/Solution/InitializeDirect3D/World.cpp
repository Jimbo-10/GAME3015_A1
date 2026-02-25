#include "World.h"

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f) //Left, Right, Down, Up
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.0f)
{
}

void World::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	std::unique_ptr<Boulder> player(new Boulder(Boulder::Brick, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 2, 0.0);
	mPlayerAircraft->setScale(1.5, 1.5, 1.5);
	mPlayerAircraft->setWorldRotation(0, XM_PI *2, 0);
	//mPlayerAircraft->setVelocity(mScrollSpeed, 0.0, 0.0);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Boulder> boulder(new Boulder(Boulder::Stone, mGame));
	auto globe = boulder.get();
	globe->setPosition(2, 0, 1);
	globe->setScale(1.0, 1.0, 1.0);
	globe->setWorldRotation(0, 0, 0);
	mPlayerAircraft->attachChild(std::move(boulder));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 0.0);
	//mBackground->setScale(10.0, 1.0, 200.0);
	mBackground->setScale(1.0, 1.0, 1.0);
	//mBackground->setVelocity(0, 0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));
	

	mSceneGraph->build();
}