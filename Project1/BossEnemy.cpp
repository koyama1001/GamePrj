#include "BossEnemy.h"

BossEnemy::BossEnemy():
	m_texture{},
	m_nBossEnemyHP{},
	m_isCollision{},
	m_BossTimerLeft{},
	m_BossTimerRight{},
	m_fMoveCounter{},
	m_MoveTimer{},
	m_BEnemydirection{ 0 },
	m_BulletTimer{}
{
	/*m_BossTimerLeft = new CustomTimer{};
	m_BossTimerRight = new CustomTimer{};
	m_BulletTimer = new CustomTimer{};*/
}

BossEnemy::~BossEnemy()
{
	//タイマー消去
	delete m_BossTimerLeft;
	m_BossTimerLeft = nullptr;
	
	delete m_BossTimerRight;
	m_BossTimerRight = nullptr;

	delete m_BulletTimer;
	m_BulletTimer = nullptr;

	
}

void BossEnemy::Init(const char * _fileName, vec2 _size, vec2 _position, int _hp)
{
	m_BossTimerLeft = new CustomTimer{};
	m_BossTimerRight = new CustomTimer{};
	m_BulletTimer = new CustomTimer{};

	m_MoveTimer = false;
	m_isCollision = false;
	IsFire = false;
	m_texture = 1;
	m_BossTimerLeft->SetTimer(2);
	//テクスチャーの生成
	glGenTextures(
		1,//GLsizei n,初期化する数 
		&m_texture);//GLuint *textures

	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);

	TexFromBMP(_fileName, 0x00, 0xff, 0x00);
	//サイズの取得
	m_size = _size;
	//位置の取得
	m_position = _position;
	//体力の取得
	m_nBossEnemyHP = _hp;
}

void BossEnemy::Update()
{
	m_BossTimerLeft->Update();
	m_BossTimerRight->Update();
	m_BulletTimer->Update();

	//敵の移動
	if (m_BossTimerLeft->IsTime() && m_MoveTimer == false)
	{
		m_flip = RECT_FLIP_NONE;
		m_fMoveCounter = -0.06f;
		m_BossTimerRight->SetTimer(6);
		m_MoveTimer = true;
		if (m_BulletTimer->IsTime())
		{
			m_BEnemydirection = 1;
			m_BulletTimer->SetTimer(5.0f);
			Fire();
			

		}
	}
	if (m_BossTimerRight->IsTime() && m_MoveTimer == true)
	{
		m_flip = RECT_FLIP_HORIZONTAL;
		m_fMoveCounter = 0.06f;
		m_BossTimerLeft->SetTimer(6);
		m_MoveTimer = false;
		if (m_BulletTimer->IsTime())
		{
			m_BEnemydirection = 0;
			m_BulletTimer->SetTimer(4.0f);
			Fire();
			
		}
	}
	m_position.x += m_fMoveCounter;

	//当たり判定
	if (m_isCollision)
	{
		m_nBossEnemyHP--;
		m_isCollision = false;
	}
}

void BossEnemy::Draw()
{
	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	Rect::Draw();
	//Rect::DrawWire();
	//printf("HP.%d\n",m_nEnemyHP);
}

void BossEnemy::Damage()
{
	m_nBossEnemyHP--;
}

int BossEnemy::GetHP()
{
	return m_nBossEnemyHP;
}
void BossEnemy::Fire()
{
	IsFire = true;

}