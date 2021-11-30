#include "Enemy.h"


Enemy::Enemy():
	m_texture{},
	m_nEnemyHP{},
	m_isCollision{},
	m_TimerLeft{},
	m_TimerRight{},
	m_fMoveCounter{},
	m_MoveTimer{}
{
	//�^�C�}�[����
	m_TimerLeft = new CustomTimer{};
	m_TimerRight = new CustomTimer{};
}

Enemy::~Enemy()
{
	//�^�C�}�[����
	delete m_TimerLeft;
	m_TimerLeft = nullptr;
	delete m_TimerRight;
	m_TimerRight = nullptr;
}

void Enemy::Init(const char * _fileName, vec2 _size, vec2 _position, int _hp)
{
	//�^�C�}�[����
	m_TimerLeft = new CustomTimer{};
	m_TimerRight = new CustomTimer{};

	m_MoveTimer = false;
	m_isCollision = false;
	m_texture = 1;
	m_TimerLeft->SetTimer(1);
	//�e�N�X�`���[�̐���
	glGenTextures(
		1,//GLsizei n,���������鐔 
		&m_texture);//GLuint *textures

	//�e�N�X�`���[���o�C���h����
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);

	TexFromBMP(_fileName, 0x00, 0xff, 0x00);
	//�T�C�Y�̎擾
	m_size = _size;
	//�ʒu�̎擾
	m_position = _position;
	//�̗͂̎擾
	m_nEnemyHP = _hp;



}


void Enemy::Update()
{
	m_TimerLeft->Update();
	m_TimerRight->Update();

	
	//printf(m_TimerLeft->IsTime);
	
	//�G�̔����ړ�
	if (m_TimerLeft->IsTime() && m_MoveTimer==false)
	{
		m_flip = RECT_FLIP_NONE;
		m_fMoveCounter = -0.02f;
		m_TimerRight->SetTimer(3);
		m_MoveTimer = true;

	}
	if (m_TimerRight->IsTime()&& m_MoveTimer==true)
	{
		m_flip = RECT_FLIP_HORIZONTAL;
		m_fMoveCounter = 0.02f;
		m_TimerLeft->SetTimer(3);
		m_MoveTimer = false;

	}
	m_position.x += m_fMoveCounter;

	//printf("%f:LTimer\n", m_TimerLeft->Now());
	//printf("%f:Timer\n", m_TimerRight->Now());
	if (m_isCollision)
	{
		m_nEnemyHP--;
		m_isCollision = false;
	}
}

void Enemy::Draw()
{
	//�e�N�X�`���[���o�C���h����
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	Rect::Draw();
	//Rect::DrawWire();
	//printf("HP.%d\n",m_nEnemyHP);

}

void Enemy::Damage()
{
	m_nEnemyHP--;
}

int Enemy::GetHP()
{
	return m_nEnemyHP;
}
