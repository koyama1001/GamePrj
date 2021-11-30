#pragma once
#include <vector>

using namespace std;

//アニメーションの種類を定義
enum 
{
	ANIMATION_NONE =-1,
	UNITYCHAN_ANIMATION_IDLE,
	UNITYCHAN_ANIMATION_RUN,
	UNITYCHAN_ANIMATION_BRAKE,
	UNITYCHAN_ANIMATION_JUMP,
	UNITYCHAN_ANIMATION_JUMP_UP,
	UNITYCHAN_ANIMATION_JUMP_FALL,
	UNITYCHAN_ANIMATION_JUMP_LANDING,
	UNITYCAHN_ANIMATION_GUN,
	UNITYCHAN_ANIMATION_MAX
};

struct Animation
{
	vector<int>m_Keys;

	//アニメーションのスピードを定義
	int m_speed;
	//アニメーション切り替えを定義
	int m_next;

	//初期化
	static int InitAll();
};

extern Animation g_animation[UNITYCHAN_ANIMATION_MAX];