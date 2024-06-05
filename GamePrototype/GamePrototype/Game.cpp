#include "pch.h"
#include "Game.h"
#include <iostream>

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_PlayerPtr = new Player(GetViewPort());

	m_ObstaclesPtr = new ObstaclesManager();
	
	std::cout << "Press 'I' to learn about the functionality and goal of the game." << std::endl << std::endl << std::endl;

// for (int index{}; index < 20; ++index)
// {
// 
// 	m_ObstaclesPtr->AddItem(catType);
// }
// 
}

void Game::Cleanup( )
{
	delete m_PlayerPtr;
	delete m_ObstaclesPtr;

}

void Game::Update(float elapsedSec)
{
	Type catType{ Type::Cat };
	Type rainType{ Type::Rain };

	if (m_PlayerPtr->ReturnGameState()&&m_GameState==gameState::Playing)
	{
		m_GameTime += elapsedSec;
		m_AccumulatedTime += elapsedSec;

		if (m_AccumulatedTime >= interval)
		{
			if (rand() % 2 == 1)
			{
				for (int index{}; index < 20; ++index)
				{
					m_ObstaclesPtr->AddItem(catType);
				}
			}
			else m_ObstaclesPtr->AddItem(rainType);

			m_AccumulatedTime -= 10.f;

			interval -= m_GameTime / 40.f;
		}

		m_PlayerPtr->Update(elapsedSec, m_MousePosition);
		m_ObstaclesPtr->Update(elapsedSec);


		for (int index{}; index < m_ObstaclesPtr->Size(); ++index)
		{
			m_PlayerPtr->Hitbox(m_ObstaclesPtr->GetHitbox(index));
		}
	}

	

}

void Game::Draw( ) const
{
	ClearBackground();

	utils::SetColor(Color4f(0.f, 0.2f, 0.f, 1.f));
	utils::FillRect(Rectf(0,0,GetViewPort().width,GetViewPort().height));

	if (m_PlayerPtr->ReturnGameState())
	{
		m_PlayerPtr->Draw();
		m_ObstaclesPtr->Draw();
	}

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch (e.keysym.sym)
	{
	case SDLK_i:
		if (m_GameState == gameState::Begin)
		{
			std::cout << "Press 'S' to start the game."<< std::endl
			<< "Press 'P' to pause the game." << std::endl
			<< "Press 'R' to reset the game."<< std::endl<<std::endl
			<< "Use the mouse to move and the '1' and '2' keys to equip and unequip the umbrella." << std::endl << std::endl
			<< "Try to dodge the cats and weather storms. Use the umbrella as a shield but be careful to not hold it for too long!" << std::endl << std::endl << std::endl
				;
		}
		break;
	case SDLK_r:
		if (m_GameState != gameState::Begin) m_GameState = gameState::Reset;
		break;
	case SDLK_p:
		if (m_GameState == gameState::Playing) m_GameState = gameState::Pause;
		else if (m_GameState == gameState::Pause) m_GameState = gameState::Playing;
		break;
	case SDLK_s:
		if (m_GameState == gameState::Begin or m_GameState == gameState::Reset) m_GameState = gameState::Playing;
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_MousePosition.x = e.x;
	m_MousePosition.y = e.y;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
