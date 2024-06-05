#include "pch.h"
#include "Player.h"
#include <utils.h>
#include <iostream>

Player::Player(Rectf viewPort)
	:m_Window{0,0,viewPort.width,viewPort.height}
{
	m_Position = Point2f(viewPort.width / 2, viewPort.width / 2 );
	m_BasePlayer = Rectf(m_Position.x+m_BasePlayerSize/2, m_Position.y+m_BasePlayerSize/2, m_BasePlayerSize, m_BasePlayerSize);
	m_UmbrellaPlayer = Ellipsef(m_Position.x, m_Position.y, m_UmbrellaPlayerRadius, m_UmbrellaPlayerRadius);
	std::cout << m_CurrentHp << " / " << m_MAX_HP << std::endl;
}

void Player::Draw()
{
	utils::SetColor(Color4f(1.f, 1.f, 1.f, 1.f));
	utils::FillRect(m_BasePlayer);

	if (m_UmbrellaActive)
	{
		utils::SetColor(Color4f(1.f, 0.7f, 0.7f, 0.8f));

		utils::FillEllipse(m_UmbrellaPlayer);
	}


	for (int index{}; index<m_UmbrellaSec; ++index)
	{
		if (index < m_MaxUmbrellaSec) utils::SetColor(Color4f(1.f, 1.f, 1.f, 0.5f));
		else
		{
			utils::SetColor(Color4f(1.f, 0.f, 0.f, 0.5f));
			m_CanTakeUmbrDmg = true;
		}

		utils::FillRect(20+20*index+100*index, m_Window.height - 20 -50, 100, 50);
	}

	for (int index{}; index<m_MaxUmbrellaSec; ++index)
	{
		utils::SetColor(Color4f(1.f, 1.7f, 1.f,1.f));
		utils::DrawRect(20 + 20 * index + 100 * index, m_Window.height - 20 -50 , 100, 50);
	}


	//std::cout << m_CurrentHp << " / " << m_MAX_HP << std::endl;
}

void Player::Update(float elapsedSec, Point2f mousePos)
{
	
	if (m_Position.x==mousePos.x and m_Position.y==mousePos.y)
	{
		m_Speed = 0;
	}
	else
	{
		m_Speed = 200.f;
	}
	

    m_SpeedVector = Vector2f{ mousePos.x - m_Position.x , mousePos.y - m_Position.y };
	m_SpeedVector /= m_SpeedVector.Norm();

	m_Position.x += m_Speed *m_SpeedVector.x*elapsedSec;
	m_Position.y += m_Speed *m_SpeedVector.y*elapsedSec;

	m_BasePlayer = Rectf(m_Position.x - m_BasePlayerSize / 2, m_Position.y - m_BasePlayerSize / 2, m_BasePlayerSize, m_BasePlayerSize);
	m_UmbrellaPlayer = Ellipsef(m_Position.x, m_Position.y, m_UmbrellaPlayerRadius, m_UmbrellaPlayerRadius);


		accumulatedTime += elapsedSec;
		accumulatedTime2 += elapsedSec;
		const float frameDelay{ 1.f };
		if (m_UmbrellaActive)
		{
			if (frameDelay <= accumulatedTime)
			{
				accumulatedTime -= frameDelay;

				++m_UmbrellaSec;

			}
		}
		else
		{
			accumulatedTime = 0;
			m_UmbrellaSec = 0;
		}

		if (m_CurrentHp<=0)
		{
			m_CurrentHp = 0;
			m_GameInProgress = 0;
		}

		if (frameDelay <= accumulatedTime2)
		{
			accumulatedTime2 -= frameDelay;

			if (m_CanTakeUmbrDmg)
			{
				m_CurrentHp -= 10.f;
				std::cout << m_CurrentHp << " / " << m_MAX_HP << std::endl;
			}
			if (m_CanTakeHitDmg)
			{
				m_CurrentHp -= 10.f;
				m_CanTakeHitDmg = 0;
				std::cout << m_CurrentHp << " / " << m_MAX_HP << std::endl;
			}


			
		}


		// Keyboard input

	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	
		if (pStates[SDL_SCANCODE_1])
		{
			
			m_UmbrellaActive = 0;
			m_CanTakeUmbrDmg = false;
			
		}
		else if (pStates[SDL_SCANCODE_2])
		{
			m_UmbrellaActive = 1;
		}
	
		
		

}


bool Player::UmbrellaActive()
{
	return m_UmbrellaActive;
}

void Player::Hitbox(Circlef circle)
{
	if (utils::IsOverlapping(m_BasePlayer, circle))
	{
		if (!m_UmbrellaActive)
		{
			m_CanTakeHitDmg = 1;
		}
	}
}

bool Player::ReturnGameState()
{
	return m_GameInProgress;
}
