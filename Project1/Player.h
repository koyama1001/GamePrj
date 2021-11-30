#pragma once

#include <vector>
#include "Rect.h"
#include "AnimationController.h"
#include "Enemy.h"
#include "Bullet.h"
#include <list>


#define PLAYER_KEY_LEFT  'a'
#define PLAYER_KEY_RIGHT  'd'
#define PLAYER_KEY_JUMP   ' '
#define PLAYER_KEY_BULLET 'k'


using namespace std;

enum
{
PLAYER_SIZE=16,
PLAYER_BOTTOM=64,
PLAYER_JUMP_COUNT_MAX=600
};

//�Ǝ��̃f�[�^���`
class Player:public Rect
{
private:
	AnimationController m_animationController;


	Rect m_bound;
	Rect m_combindBound;
	
	int m_textureIndex;

	vec2 m_speed;

	//�ǂƂ̓����蔻��Ɏg���|�C���g
	vector<vec2>m_rightPoint;
	vector<vec2>m_leftPoint;
	vector<vec2>m_bottomPoint;
	vector<vec2>m_topPoint;
	
public:

	Player();
	~Player();
	void Init();
	void Update();
	void Draw();
	void Fire();
	void damege();
	
	int m_PlayerHP;
	

	bool m_touch;
	//���̃��X�g�����
	//std::list<Bullet *> m_bullets{};

	bool isFire;
	//����
	int m_direction;

private:

	bool m_jumping;
	bool m_falling;
	//�W�����v�L�ѐ�
	int m_JumpCount;


};

