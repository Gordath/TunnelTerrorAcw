#include "PipeItem.h"
#include <GL/GLM/GTC/matrix_transform.inl>
#include "RenderComponent.h"
#include "CollisionMatrix.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "Texture_DX.h"

PipeItem::PipeItem(Mesh* m) : GameObject("pipeItem")
{
	RenderComponent* rc{ new RenderComponent(this) };
	rc->SetMesh(m);
	Material mat;
	mat.diffuse = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
	mat.specular = glm::vec4{ 1.0f, 1.0f, 1.0f, 60.0f };
	mat.textures[TEX_DIFFUSE] = Game::_resourceManager.Get<Texture_DX>(L"obstacleDiff.png");
	mat.textures[TEX_SPECULAR] = Game::_resourceManager.Get<Texture_DX>(L"obstacleSpec.png");
	mat.textures[TEX_NORMAL] = Game::_resourceManager.Get<Texture_DX>(L"obstacleNorm.png");
	rc->SetMaterial(mat);

	CollisionComponent* cc{ new CollisionComponent{ this } };
	cc->SetCollisionRadius(m->CalculateMaxSize());
	cc->SetCollisionID(OBSTACLE_ID);
	cc->SetCollisionMatrixFlag(PLAYER_ID);
}

void PipeItem::Start()
{
}

void PipeItem::Update(double deltaTime)
{
}

void PipeItem::OnMessage(Message* msg)
{
	GameObject::OnMessage(msg);
}

void PipeItem::End()
{
}

void PipeItem::Reset()
{
}
