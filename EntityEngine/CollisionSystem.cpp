#include "CollisionSystem.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "CollisionMessage.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

CollisionSystem::CollisionSystem()
{
}

/******************************************************************************************************************/

CollisionSystem::~CollisionSystem()
{
}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

void CollisionSystem::Process(std::vector<GameObject*>& list, double deltaTime)
{
	for (size_t i = 0; i < list.size(); i++) {
		GameObject* collidee = list[i];

		if (!collidee->IsAlive()) continue; // Skip dead things

		// Does this object even have a Collision component?
		if (CollisionComponent* cc1 = static_cast<CollisionComponent*>(collidee->GetComponent("collision"))) {
			if (cc1->GetCollisionID() == 0) continue; // Skip things with no collision ID

			// Collide against all objects we're meant to collide with
			for (size_t j = 0; j < list.size(); j++) {
				GameObject* collider = list[j];

				if (collidee == collider) continue; // Skip colliding against yourself
				if (!collider->IsAlive()) continue; // Skip dead things

				if (CollisionComponent* cc2 = static_cast<CollisionComponent*>(collider->GetComponent("collision"))) {
					if (cc2->GetCollisionID() == 0) continue; // Skip things with no collision ID


					// Check collision matrix
					if (cc1->CheckCollisionMatrixFlag(cc2->GetCollisionID())) {
						// Collide with it...
						if (CollideWith(cc1, cc2)) {
							// Send a collision message to both objects
							CollisionMessage msg(collidee, collider);
							collidee->OnMessage(&msg);
							collider->OnMessage(&msg);

							goto NextCollision;
						}
					}
				}
			}
		}
	NextCollision:
		;
	}
}

/******************************************************************************************************************/

bool CollisionSystem::CollideWith(const CollisionComponent* collidee, const CollisionComponent* collider)
{
	glm::vec4 sph_center{ 0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec4 sph_center2{ 0.0f, 0.0f, 0.0f, 1.0f };

	sph_center = collider->GetGameObject()->GetXform() * sph_center;
	sph_center2 = collidee->GetGameObject()->GetXform() * sph_center2;

	glm::vec3 diff = sph_center - sph_center2;
	float len = glm::length(diff);
	float radsum = collidee->GetCollisionRadius() * 0.9f + collider->GetCollisionRadius();

	bool res = len < radsum;

	return res;
}

/******************************************************************************************************************/
