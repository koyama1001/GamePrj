#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "Parts.h"
#include "Texture.h"
#include "TexBMP.h"
#include "glut.h"

Parts g_parts[PART_MAX] = {
	{nullptr,},//PART_NONE
	{"b1.bmp",},//PART_GROUND
	{"b2.bmp",},//PART_GROUND2
	

 
};

int Parts::Init()
{
	//�����t�@�C������Nullptr�Ȃ�ǂݍ���
	if (m_fileName != nullptr) {
		//�e�N�X�`���[�̐���
		glGenTextures(
			1,//GLsizei n,���������鐔 
			&m_texture);//GLuint *textures

		//�e�N�X�`���[���o�C���h����
		glBindTexture(
			GL_TEXTURE_2D,//GLenum target,
			m_texture//GLuint texture
		);
		char fileName[256] = "Parts\\";

		sprintf(fileName, "%s%s", fileName, m_fileName);
		//�m�F
		//printf("%s\n", fileName);

		TexFromBMP(fileName, 0xff, 0x00, 0xff);
	}
	return 0;
}

int Parts::InitAll()
{
	for (int i = 0; i < PART_MAX; i++)
		g_parts[i].Init();
	return 0;
}
