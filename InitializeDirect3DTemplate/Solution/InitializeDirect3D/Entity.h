#pragma once
#include "SceneNode.h"
class Entity :
    public SceneNode
{
public:
	Entity(Game* game);
	void				setVelocity(XMFLOAT3 velocity);
	void				setVelocity(float vx, float vy);
	XMFLOAT3			getVelocity() const;
	void				accelerate(const XMFLOAT3& v);
	void				accelerate(float vx, float vy);

	virtual	void		updateCurrent(const GameTimer& gt);

public:
	XMFLOAT3		mVelocity;
	XMFLOAT3		mPosition;
};

