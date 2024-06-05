#pragma once
#include <utils.h>


enum class Type
{
	Cat,Rain
};

class Allergies
{
public:
	Allergies(Type& type);

	bool CheckWorldBounds(const Rectf& bounds);
	void Update(float elapsedSec);
	void Draw();

	Circlef GetHitbox();

private:
	Type m_AllergyType;
	float m_Speed{};
	Vector2f m_Direction{};
	int m_Angle;

	Point2f m_Position{-20,-20};
	Circlef m_Hitbox{};

};

