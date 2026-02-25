#pragma once
#include "Entity.h"

class SpriteNode :
	public Entity
{
public:
	SpriteNode(Game* game);

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
};

