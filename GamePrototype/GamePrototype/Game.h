#pragma once
#include "BaseGame.h"
#include "Player.h"
#include "ObstaclesManager.h"

class Game : public BaseGame
{
	enum gameState
	{
		Begin, Playing,Reset , End,Pause
	};
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	Player* m_PlayerPtr;
	ObstaclesManager* m_ObstaclesPtr;

	Point2f m_MousePosition{};

	float m_AccumulatedTime{};
	float m_GameTime{};
	float interval{ 10 };

	gameState m_GameState{ Begin };
};