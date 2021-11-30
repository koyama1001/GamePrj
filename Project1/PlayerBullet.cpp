#include "PlayerBullet.h"
#include "Header.h"

PlayerBullet g_playerBullet;



PlayerBullet::PlayerBullet():
	m_texture{},
	m_enable{}
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Init()
{
	//球のサイズ
	m_size = vec2(PLAYER_BULLET_WIDTH, PLAYER_BULLET_HEIGHT);
	//テクスチャーの生成
	glGenTextures(
		1,//GLsizei n,初期化する数 
		&m_texture);//GLuint *textures

	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);

	TexFromBMP("Texture\\White.bmp", 0x00, 0xff, 0x00);
	
}

void PlayerBullet::setDir(int dir)
{
	this->dir = dir;
}

void PlayerBullet::Update()
{
	//球の発射
	if (dir == 0)
		m_position.x += PLAYER_BULLET_SPEED;
	else
		m_position.x -= PLAYER_BULLET_SPEED;

	/*if (g_WalkEnemy.WalkEnemyIntersect(g_playerBullet))
	{
		
	}*/
}



void PlayerBullet::Draw()
{
	
	if (!m_enable) {
		return;
	}
		
		//テクスチャーをバインドする
		glBindTexture(
			GL_TEXTURE_2D,//GLenum target,
			m_texture//GLuint texture
		);

		Rect::Draw();
	
}

bool PlayerBullet::Intersect(PlayerBullet const & _rect)
{

	return Rect::Intersect(_rect);
	
}
