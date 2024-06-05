#pragma once
#include "Allergies.h"
#include <vector>

class ObstaclesManager
{
public:
	ObstaclesManager();
	~ObstaclesManager();

	void AddItem(Type& type);
	void Draw() const;
	void Update(float elapsedSec);
	int Size() const;
	void RemoveItem(int idx);
	Circlef GetHitbox(int idx);

private:

	std::vector<Allergies*> m_Obstacles;


};

