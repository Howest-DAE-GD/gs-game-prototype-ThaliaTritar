#pragma once
#include <Vector2f.h>
#include <utils.h>
class Player
{

public:
	Player(Rectf viewPort);

	void Draw();
	
	void Update(float elapsedSec, Point2f mousePos);

	bool UmbrellaActive();

	void Hitbox(Circlef circle);

	bool ReturnGameState();
	

private:
	bool m_UmbrellaActive{ 0 };

	const int m_BasePlayerSize{ 40 };
	const int m_UmbrellaPlayerRadius{ 25 };

	Point2f m_Position;
	Ellipsef m_UmbrellaPlayer;
	Rectf m_BasePlayer;

	Vector2f m_SpeedVector{ };
	float m_Speed{};

	float accumulatedTime{};
	float accumulatedTime2{};
	int m_UmbrellaSec{};
	const int m_MaxUmbrellaSec{2};
	bool m_CanTakeUmbrDmg{ 0 };
	bool m_CanTakeHitDmg{ 0 };

	Rectf m_Window;


	float m_MAX_HP{ 100 };
	int m_CurrentHp{ 100 };



	bool m_GameInProgress{1};

};

