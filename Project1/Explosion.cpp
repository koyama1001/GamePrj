#include "Explosion.h"
#include <iostream>

Explosion::Explosion():
	m_texture{},
	m_ExplosionCountLife{}
{
	
}

Explosion::~Explosion()
{
	
}

void Explosion::Init()
{
	m_texture = 1;//private
	m_ExplosionCountLife = 300;//生存時間
	//テクスチャーの生成
	glGenTextures(
		1,//GLsizei n,初期化する数 
		&m_texture);//GLuint *textures

	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	//描画　透過する色の指定
	TexFromBMP("Object\\Fire.bmp", 0xff, 0xff, 0xff);
	m_size = vec2(26, 26);
	
}

void Explosion::Update()
{
	//m_ExplosionCountLife--;
	
	
}

void Explosion::Draw()
{
	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	Rect::Draw();
}

void Explosion::SetPosition(vec2 _Enemy_Position)
{
	m_position = _Enemy_Position;
}

vec2 Explosion::GetPosition()
{
	return m_position;//位置を返す
}
