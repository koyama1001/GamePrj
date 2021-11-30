#pragma once


class Game
{
public:
	//ゲーム内のカウントを指定
	unsigned int m_count;

	void Update();
};

extern Game g_game;