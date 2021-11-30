#pragma once
#pragma once
#include "Rect.h"
#include "Header.h"

using namespace glm;

class CustomTimer;

class BulletShotEnemy :public Rect
{
private:
	int m_nEnemyHP;
	bool m_isCollision;
	bool m_MoveTimer;


	CustomTimer *m_TimerLeft;
	CustomTimer *m_TimerRight;
	CustomTimer *m_BulletTimer;
	float m_fMoveCounter;


public:
	BulletShotEnemy();
	~BulletShotEnemy();

	//�e�N�X�`���[�̐��̎w��@���͈��
	unsigned int m_texture;
	bool IsFire;
	int m_Enemydirection;

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
	//����
	void Fire();
};