#pragma once
#include "Entity.h"
#include <string>

class Boulder :
	public Entity
{
public:
	enum Type
	{
		Brick,
		Stone,
	};


public:
	Boulder(Type type, Game* game);


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();


private:
	Type				mType;
	std::string			mSprite;
};
