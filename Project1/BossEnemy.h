#pragma once

#include "Rect.h"
#include "Header.h"

using namespace glm;

class CustomTimer;

class BossEnemy :public Rect
{
private:
	//当たり判定
	bool m_isCollision;
	//移動時間
	bool m_MoveTimer;

	//移動時間
	CustomTimer *m_BossTimerLeft;
	CustomTimer *m_BossTimerRight;

	//攻撃時間
	CustomTimer *m_BulletTimer;



	float m_fMoveCounter;


public:
	BossEnemy();
	~BossEnemy();

	bool IsFire;
	//ボスHP
	int m_nBossEnemyHP;
	
	int m_BEnemydirection;
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
	//打つ
	void Fire();
};