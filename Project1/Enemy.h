#pragma once
#include "Rect.h"
#include "Header.h"

using namespace glm;

class CustomTimer;

class Enemy:public Rect
{
private:
	int m_nEnemyHP;
	bool m_isCollision;
	bool m_MoveTimer;

	CustomTimer *m_TimerLeft;
	CustomTimer *m_TimerRight;
	float m_fMoveCounter;
	

public:
	Enemy();
	~Enemy();

	//テクスチャーの数の指定　今は一つ
	unsigned int m_texture;

	//初期化
	void Init(const char*_fileName, vec2 _size, vec2 _position, int _hp);

	//アップデート
	void Update();
	//描画
	void Draw();
	//エネミーのダメージ
	void Damage();
	//体力
	int GetHP();
	
};