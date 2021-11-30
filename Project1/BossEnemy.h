#pragma once

#include "Rect.h"
#include "Header.h"

using namespace glm;

class CustomTimer;

class BossEnemy :public Rect
{
private:
	//�����蔻��
	bool m_isCollision;
	//�ړ�����
	bool m_MoveTimer;

	//�ړ�����
	CustomTimer *m_BossTimerLeft;
	CustomTimer *m_BossTimerRight;

	//�U������
	CustomTimer *m_BulletTimer;



	float m_fMoveCounter;


public:
	BossEnemy();
	~BossEnemy();

	bool IsFire;
	//�{�XHP
	int m_nBossEnemyHP;
	
	int m_BEnemydirection;
	//�e�N�X�`���[�̐��̎w��@���͈��
	unsigned int m_texture;

	//������
	void Init(const char*_fileName, vec2 _size, vec2 _position, int _hp);

	//�A�b�v�f�[�g
	void Update();
	//�`��
	void Draw();
	//�G�l�~�[�̃_���[�W
	void Damage();
	//�̗�
	int GetHP();
	//�ł�
	void Fire();
};