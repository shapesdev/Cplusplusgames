#include "GameObjectFactoryPlayMode.h"
#include <iostream>
#include "TransformComponent.h"
#include "StandardGraphicsComponent.h"
#include "PlayerUpdateComponent.h"
#include "RectColliderComponent.h"
#include "InvaderUpdateComponent.h"
#include "BulletUpdateComponent.h"

void GameObjectFactoryPlayMode::BuildGameObject(GameObjectBlueprint& bp, std::vector<GameObject>& gameObjects) {
	GameObject gameObject;
	gameObject.SetTag(bp.GetName());

	auto it = bp.GetComponentList().begin();
	auto end = bp.GetComponentList().end();

	for (it; it != end; ++it) {
		if (*it == "Transform") {
			gameObject.AddComponent(make_shared<TransformComponent>(bp.GetWidth(), bp.GetHeight(), Vector2f(bp.GetLocationX(), bp.GetLocationY())));
		}
		else if (*it == "Player Update") {
			gameObject.AddComponent(make_shared<PlayerUpdateComponent>());
		}
		else if (*it == "Invader Update") {
			gameObject.AddComponent(make_shared<InvaderUpdateComponent>());
		}
		else if (*it == "Bullet Update") {
			gameObject.AddComponent(make_shared<BulletUpdateComponent>());
		}
		else if (*it == "Standard Graphics") {
			shared_ptr<StandardGraphicsComponent> sgp = make_shared<StandardGraphicsComponent>();
			gameObject.AddComponent(sgp);
			sgp->InitialiseGraphics(bp.GetBitmapName(), Vector2f(bp.GetWidth(), bp.GetHeight()));
		}
	}

	if (bp.GetEncompassingRectCollider()) {
		shared_ptr<RectColliderComponent> rcc = make_shared<RectColliderComponent>(bp.GetEncompassingRectColliderLabel());
		gameObject.AddComponent(rcc);
		rcc->SetOrMoveCollider(bp.GetLocationX(), bp.GetLocationY(), bp.GetWidth(), bp.GetHeight());
	}

	gameObjects.push_back(gameObject);
}