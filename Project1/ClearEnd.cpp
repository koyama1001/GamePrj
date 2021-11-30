#include "ClearEnd.h"

ClearEnd::ClearEnd():
m_gEndFlag {},
m_texture{}
{
	m_gEndFlag = false;
	//テクスチャーの生成
	glGenTextures(
		1,//GLsizei n,初期化する数 
		&m_texture);//GLuint *textures

	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);

	TexFromBMP("End1.BMP", 0xff, 0x00, 0xff);
	m_flip = RECT_FLIP_NONE;
	m_size = vec2(200.f, 200.f);
	m_position = vec2(0, 0);

}


void ClearEnd::Initialize()
{
	m_gEndFlag = false;
}

void ClearEnd::Keyboard(unsigned char _Key)
{
	
}

void ClearEnd::Update()
{
	if (Keyboard::m_nowPressedKey[' '])
	{
		m_gEndFlag = true;
	}
}

void ClearEnd::Release()
{
}

void ClearEnd::Draw()
{
	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	Rect::Draw();
}

bool ClearEnd::IsEnd()
{
	return m_gEndFlag;
}

SceneType ClearEnd::NextScene()
{
	return SceneType::Title;
}
