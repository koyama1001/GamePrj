#pragma once
#include <vector>

using namespace std;

//�A�j���[�V�����̎�ނ��`
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

	//�A�j���[�V�����̃X�s�[�h���`
	int m_speed;
	//�A�j���[�V�����؂�ւ����`
	int m_next;

	//������
	static int InitAll();
};

extern Animation g_animation[UNITYCHAN_ANIMATION_MAX];