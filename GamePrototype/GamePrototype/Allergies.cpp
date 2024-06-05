#include "pch.h"
#include "Allergies.h"
#include <iostream>

Allergies::Allergies(Type& type)
	:m_AllergyType{ type }
{
	m_Angle = rand() % 360;

	// std::cout << m_Angle << std::endl;

	if (0 <= m_Angle && m_Angle < 90) m_Position = Point2f{ -50,-50 };
	else if (90 <= m_Angle && m_Angle < 180) m_Position = Point2f{ 900,-50 };
	else if (180 <= m_Angle && m_Angle < 270) m_Position = Point2f{ 900,550 };
	else m_Position = Point2f{ -50,550 };

	m_Hitbox.center = m_Position;
}


bool Allergies::CheckWorldBounds(const Rectf& bounds)
{
	if ((m_Position.x + m_Hitbox.radius <= bounds.left) or (m_Position.x + m_Hitbox.radius >= bounds.left + bounds.width))
	{
		return true;
	}
	else if ((m_Position.y + m_Hitbox.radius <= bounds.bottom) or (m_Position.y + m_Hitbox.radius >= bounds.bottom + bounds.height))
	{
		return true;
	}

	return false;

}

void Allergies::Update(float elapsedSec)
{
	// Variable Set
	if (m_AllergyType == Type::Rain)
	{
		m_Speed = 20;

		m_Hitbox.radius = 150;
	}
	else
	{
		m_Speed = 90;

		m_Hitbox.radius= 15;
	}

	// Direction etc
	m_Direction.x = cos((float(m_Angle) / 360.f)*2*M_PI);
	m_Direction.y = sin((float(m_Angle) / 360.f )* 2 * M_PI);

	m_Position += m_Speed * elapsedSec * m_Direction.Normalized();
}

void Allergies::Draw()
{
	m_Hitbox.center = m_Position;

	if (m_AllergyType == Type::Rain) utils::SetColor(Color4f(0.f, 0.f, 0.8f, 0.5f));
	else if (m_AllergyType == Type::Cat)utils::SetColor(Color4f(181.f/265.f, 98.f / 265.f, 32.f / 265.f, 1.f));
	utils::FillEllipse(Ellipsef(m_Hitbox.center, m_Hitbox.radius, m_Hitbox.radius));
}

Circlef Allergies::GetHitbox()
{
	return m_Hitbox;
}
