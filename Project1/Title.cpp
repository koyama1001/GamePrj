#include "Title.h"

Title::Title():
	m_bEndFlag{},
	m_texture{}
{
	m_bEndFlag = false;
}

void Title::Initialize()
{
	//テクスチャーの生成
	glGenTextures(
		1,//GLsizei n,初期化する数 
		&m_texture);//GLuint *textures

	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);

	TexFromBMP("Title.BMP", 0xff, 0x00, 0xff);
	m_flip= RECT_FLIP_NONE;
	m_size = vec2(250.f, 250.f);
	m_position = vec2(0, 0);
	m_bEndFlag = false;
}

void Title::Keyboard(unsigned char _Key)
{
}

void Title::Update()
{
	if (Keyboard::m_nowPressedKey[' '])
	{
		m_bEndFlag = true;
	}
}

void Title::Release()
{

}

void Title::Draw()
{
	//テクスチャーをバインドする
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	Rect::Draw();
}

bool Title::IsEnd()
{
	return m_bEndFlag;
}

SceneType Title::NextScene()
{
	return SceneType::Stage;
}
