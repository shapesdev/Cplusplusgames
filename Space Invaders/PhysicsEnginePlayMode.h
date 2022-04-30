#pragma once
#include "GameObjectSharer.h"
#include "PlayerUpdateComponent.h"

class PhysicsEnginePlayMode
{
public:
	void Initialise(GameObjectSharer& gos);
	void DetectCollisions(vector<GameObject>& objects, const vector<int>& bulletPositions);

private:
	shared_ptr<PlayerUpdateComponent> m_PUC;

	GameObject* m_Player;
	bool m_InvaderHitWallThisFrame = false;
	bool m_InvaderHitWallPreviousFrame = false;
	bool m_NeedToDropDownAndReverse = false;
	bool m_CompletedDropDownAndReverse = false;

	void DetectInvaderCollisions(vector<GameObject>& objects, const vector<int>& bulletPositions);
	void DetectPlayerCollisionsAndInvaderDirection(vector<GameObject>& objects, const vector<int>& bulletPositions);
	void HandleInvaderDirection();
};

