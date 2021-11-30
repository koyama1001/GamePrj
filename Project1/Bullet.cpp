#include "Bullet.h"
#include <iostream>

Bullet::Bullet() :
	m_isCollision{},
	m_texture{},
	m_dir{},
	m_countLife{},
	m_speed{}
{}

Bullet::~Bullet()
{
}



void Bullet::Init()
{
	m_isCollision = false;	// private
	m_texture = 1;			// private

	m_dir = 0;				// public

	m_speed = 0.4f;		// public

	m_countLife = 600; //生存時間

	//テクスチャーの生成
	glGenTextures(
		1,//GLsizei n,初期化する数 
		&m_texture);//GLuint *textures

	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);

	TexFromBMP("Object\\Bullet.BMP", 0xff, 0xff, 0xff);
	m_size = vec2(7.f, 7.f);
	/*m_position.x = 0.f;
	m_position.y = 0.f;*/

}

void Bullet::setPosition(vec2 _Player_Position)
{
	m_position = _Player_Position;
}

vec2 Bullet::getPosition()
{
	return m_position;//位置を返す
}

void Bullet::setDir(int dir)
{
	m_dir = dir;
}


void Bullet::Update()
{
	//球の発射
	if (m_dir == 0)
		m_position.x += m_speed;
	else
		m_position.x -= m_speed;

	m_countLife--;

	//printf("bullet X %f Y %f\n", m_position.x, m_position.y);
}

void Bullet::Draw()
{
	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	Rect::Draw();
	//Rect::DrawWire();
}

