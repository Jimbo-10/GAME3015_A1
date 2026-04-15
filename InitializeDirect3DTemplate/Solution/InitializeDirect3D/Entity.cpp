#include "Entity.h"
#include <iostream>
Entity::Entity(Game* game) : SceneNode(game), mVelocity(0, 0, 0)
{
}

void Entity::setVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

XMFLOAT3 Entity::getVelocity() const
{
	return mVelocity;
	std::cout << mVelocity.x << "\n";
}

void Entity::updateCurrent(const GameTimer& gt)
{
	float dt = gt.DeltaTime();
	move(mVelocity.x * dt, mVelocity.y * dt, mVelocity.z * dt);

	// reset the velocity
	mVelocity = { 0.0f, 0.0f, 0.0f };

	XMFLOAT4X4 world = getWorldTransform();
	XMStoreFloat4x4(&renderer->World, XMLoadFloat4x4(&world));

	renderer->NumFramesDirty = 3;

	OutputDebugStringA("UPDATE\n");
}

void Entity::accelerate(const XMFLOAT3& v)
{
	mVelocity.x += v.x;
	mVelocity.y += v.y;
	mVelocity.z += v.z;

	OutputDebugStringA("ACCELERATE\n");
}

void Entity::accelerate(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}