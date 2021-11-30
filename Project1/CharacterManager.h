#pragma once
#include "Header.h"
#include "Timer.h"
#include "Explosion.h"
#include "BossEnemy.h"
#include "BulletShotEnemy.h"
#include <cstdint>
#include <list>


enum E_CharacterManager
{
	
	//敵の大きさ
	ENEMY_SIZE=24
};

class CustomTimer;
class Explosion;
class Enemy;
class Bullet;
class Player;
class BossEnemy;
class BulletShotEnemy;

class CHARACTERMANAGER
{
private:
	//爆発
	Explosion	*m_pExplosion;
	//タイマー
	CustomTimer *m_pTimer;
	CustomTimer *m_pExplosionTimer;

	


	int m_DrawCount;//描画カウント
	uint8_t m_BlinkMask;
	//無敵
	bool muteki;
	// EX on/off
	bool explosionOnOff;
	int testint;
public:
	//自機
	Player		*m_pPlayer;
	std::list<Enemy *> m_Enemys;
	std::list<BossEnemy *> m_BossEnemys;
	std::list<BulletShotEnemy *>m_BulletShotEnemys;
	std::list<Bullet *> m_PlayerBullets;
	std::list<Bullet *> m_EnemyBullets;
	std::list<Bullet *> m_BossEnemyBullet;

	std::list<Bullet *>::iterator Bullet_iter;
public:
	CHARACTERMANAGER();
	~CHARACTERMANAGER();

	void Init();
	void Update();
	void Draw();

private:
	//当たり判定
	void Collision();
	//球を生成
	void CreateBullet();
	//敵玉を生成
	void CreateEnemyBullet(vec2 _position, int dir);//位置と向きを指定
	//Bossの球を生成
	void CreateBossEnemyBullet(vec2 _position, int dir);//位置と向きを指定
	//敵キャラ設定
	void SetEnemy(const char*_fileName, vec2 _size, vec2 _position, int _hp);
	//爆発設定
	void CreateExplosion(vec2 _enemyPos);
	//ボスキャラ設定
	void SetBossEnemy(const char*_fileName, vec2 _size, vec2 _position, int _hp);
	//打つ敵キャラ設定
	void SetBulletShotEnemy(const char*_fileName, vec2 _size, vec2 _position, int _hp);

};
