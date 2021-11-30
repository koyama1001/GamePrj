#pragma once

#include "glm/glm.hpp"
#include "Rect.h"
#include "glut.h"
#include "TexBMP.h"

//#define BULLET_DAMAGE 10;//���̃_���[�W
using namespace std;
using namespace glm;

enum BULLET {
	BULLET_DAMAGE =10 //���̃_���[�W
};

class Bullet:public Rect
{
private:

	unsigned int m_texture; //�G�̖���

	int m_dir;//���l�̕ۑ�

public:
	

	int m_countLife;//�������l
	//float m_velocity;//�ړ���
	float m_speed;//�X�s�[�h
	bool m_isCollision;

public:

	Bullet();
	~Bullet();

	void Init();//������
	void Update();//�A�b�v�f�[�g
	void Draw();//�`��

	void setPosition(vec2 _Player_Position);//�v���C���[�̈ʒu���擾
	vec2 getPosition();//�ʒu���擾
	void setDir(int dir);//�v���C���[�̐��l�擾
	//void setVelocity(float velocity);
	
};

