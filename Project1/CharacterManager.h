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
	
	//�G�̑傫��
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
	//����
	Explosion	*m_pExplosion;
	//�^�C�}�[
	CustomTimer *m_pTimer;
	CustomTimer *m_pExplosionTimer;

	


	int m_DrawCount;//�`��J�E���g
	uint8_t m_BlinkMask;
	//���G
	bool muteki;
	// EX on/off
	bool explosionOnOff;
	int testint;
public:
	//���@
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
	//�����蔻��
	void Collision();
	//���𐶐�
	void CreateBullet();
	//�G�ʂ𐶐�
	void CreateEnemyBullet(vec2 _position, int dir);//�ʒu�ƌ������w��
	//Boss�̋��𐶐�
	void CreateBossEnemyBullet(vec2 _position, int dir);//�ʒu�ƌ������w��
	//�G�L�����ݒ�
	void SetEnemy(const char*_fileName, vec2 _size, vec2 _position, int _hp);
	//�����ݒ�
	void CreateExplosion(vec2 _enemyPos);
	//�{�X�L�����ݒ�
	void SetBossEnemy(const char*_fileName, vec2 _size, vec2 _position, int _hp);
	//�łG�L�����ݒ�
	void SetBulletShotEnemy(const char*_fileName, vec2 _size, vec2 _position, int _hp);

};
