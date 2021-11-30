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
	
};