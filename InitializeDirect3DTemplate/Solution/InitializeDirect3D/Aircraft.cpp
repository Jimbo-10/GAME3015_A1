#include "Aircraft.h"
#include "Game.h"

Boulder::Boulder(Type type, Game* game) : Entity(game)
, mType(type)
{
	switch (type)
	{
	case (Brick):
		mSprite = "bricks";
		break;
	case (Stone):
		mSprite = "stone";
		break;
	default:
		mSprite = "bricks";
		break;
	}
}

void Boulder::drawCurrent() const
{

	

}

void Boulder::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->World, XMMatrixScaling(10.0f, 1.0f, 10.0f));
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["sphere"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["sphere"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["sphere"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}
