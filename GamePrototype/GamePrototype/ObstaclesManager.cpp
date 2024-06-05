#include "pch.h"
#include "ObstaclesManager.h"

ObstaclesManager::ObstaclesManager()
{
}

ObstaclesManager::~ObstaclesManager()
{
	for (int index{}; index < m_Obstacles.size(); index++)
	{
		delete m_Obstacles[index];
	}
}

void ObstaclesManager::AddItem( Type& type)
{
	m_Obstacles.push_back(new Allergies(type));
}

void ObstaclesManager::Draw() const
{
	for (int index{}; index < m_Obstacles.size(); index++)
	{
		m_Obstacles[index]->Draw();
	}
}

void ObstaclesManager::Update(float elapsedSec) 
{
	for (int index{}; index < m_Obstacles.size(); index++)
	{
		m_Obstacles[index]->Update(elapsedSec);
	}
}

int ObstaclesManager::Size() const
{
	int size{ int(m_Obstacles.size()) };
	return size;
}


void ObstaclesManager::RemoveItem(int idx)
{
	if (idx < m_Obstacles.size())
	{
		std::swap(m_Obstacles[idx], m_Obstacles[m_Obstacles.size() - 1]);
		m_Obstacles.pop_back();

	}
}

Circlef ObstaclesManager::GetHitbox(int idx)
{
	Circlef hitcircle{ m_Obstacles[idx]->GetHitbox() };
	return hitcircle;
}
