#include "BulletShotEnemy.h"

BulletShotEnemy::BulletShotEnemy() :
	m_texture{},
	m_nEnemyHP{},
	m_isCollision{},
	m_TimerLeft{},
	m_TimerRight{},
	m_fMoveCounter{},
	m_MoveTimer{},
	m_BulletTimer{},
	m_Enemydirection{0}
	
{
	//�^�C�}�[����
	m_TimerLeft = new CustomTimer{};
	m_TimerRight = new CustomTimer{};
	m_BulletTimer = new CustomTimer{};
}

BulletShotEnemy::~BulletShotEnemy()
{
	//�^�C�}�[����
	delete m_TimerLeft;
	m_TimerLeft = nullptr;
	delete m_TimerRight;
	m_TimerRight = nullptr;
	delete m_BulletTimer;
	m_BulletTimer = nullptr;
}

void BulletShotEnemy::Init(const char * _fileName, vec2 _size, vec2 _position, int _hp)
{
	//�^�C�}�[����
	m_TimerLeft = new CustomTimer{};
	m_TimerRight = new CustomTimer{};
	m_BulletTimer = new CustomTimer{};

	m_MoveTimer = false;
	m_isCollision = false;
	IsFire = false;
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


void BulletShotEnemy::Update()
{
	m_TimerLeft->Update();
	m_TimerRight->Update();
	m_BulletTimer->Update();

	//printf(m_TimerLeft->IsTime);

	//�G�̔����ړ�
	if (m_TimerLeft->IsTime() && m_MoveTimer == false)
	{
		m_flip = RECT_FLIP_NONE;
		m_fMoveCounter = -0.02f;
		m_TimerRight->SetTimer(3);
		m_MoveTimer = true;
		if (m_BulletTimer->IsTime())
		{
			m_Enemydirection = 0;
			m_BulletTimer->SetTimer(rand()%3+1);
			Fire();
			
		}

	}
	if (m_TimerRight->IsTime() && m_MoveTimer == true)
	{
		m_flip = RECT_FLIP_HORIZONTAL;
		m_fMoveCounter = 0.02f;
		m_TimerLeft->SetTimer(3);
		m_MoveTimer = false;
		if (m_BulletTimer->IsTime())
		{
			m_Enemydirection = 1;
			m_BulletTimer->SetTimer(rand()%3+1);
			Fire();
			
		}
	}
	m_position.x += m_fMoveCounter;

	//printf("%f:LTimer\n", m_TimerLeft->Now());
	//printf("%f:Timer\n", m_TimerRight->Now());
	//printf("%f:Timer\n", m_BulletTimer->Now());
	if (m_isCollision)
	{
		m_nEnemyHP--;
		m_isCollision = false;
	}
}

void BulletShotEnemy::Draw()
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

void BulletShotEnemy::Damage()
{
	m_nEnemyHP--;
}

int BulletShotEnemy::GetHP()
{
	return m_nEnemyHP;
}

void BulletShotEnemy::Fire()
{
	IsFire = true;

}
