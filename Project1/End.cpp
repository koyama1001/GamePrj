#include "End.h"

End::End():
m_bEndFlag{},
m_texture{}
{
	m_bEndFlag = false;
	//�e�N�X�`���[�̐���
	glGenTextures(
		1,//GLsizei n,���������鐔 
		&m_texture);//GLuint *textures

	//�e�N�X�`���[���o�C���h����
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);

	TexFromBMP("End1.BMP", 0xff, 0x00, 0xff);
	m_flip = RECT_FLIP_NONE;
	m_size = vec2(260.f, 250.f);
	m_position = vec2(0, 0);
	
}

void End::Initialize()
{
	m_bEndFlag = false;

}

void End::Keyboard(unsigned char _Key)
{
	
}

void End::Update()
{
	if (Keyboard::m_nowPressedKey[' '])
	{
		m_bEndFlag = true;
	}
}

void End::Release()
{
}

void End::Draw()
{
	//�e�N�X�`���[���o�C���h����
	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		m_texture//GLuint texture
	);
	Rect::Draw();
}

bool End::IsEnd()
{
	return m_bEndFlag;
}

SceneType End::NextScene()
{
	return SceneType::Title;
}
