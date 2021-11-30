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
	m_ExplosionCountLife = 300;//��������
	//�e�N�X�`���[�̐���
	glGenTextures(
		1,//GLsizei n,���������鐔 
		&m_texture);//GLuint *textures

	//�e�N�X�`���[���o�C���h����
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	//�`��@���߂���F�̎w��
	TexFromBMP("Object\\Fire.bmp", 0xff, 0xff, 0xff);
	m_size = vec2(26, 26);
	
}

void Explosion::Update()
{
	//m_ExplosionCountLife--;
	
	
}

void Explosion::Draw()
{
	//�e�N�X�`���[���o�C���h����
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
	return m_position;//�ʒu��Ԃ�
}
