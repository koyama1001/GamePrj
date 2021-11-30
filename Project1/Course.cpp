#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>

#include "glm\\glm.hpp"

#include "Course.h"
#include "Parts.h"
#include "Rect.h"
#include "Header.h"

#include "glut.h"

using namespace glm;

Course g_course;

//�R�[�X�f�[�^�̓ǂݍ���
int Course::Load(const char * _fileName)
{
	//�t�@�C�����I�[�v��
	FILE* pFile = fopen(_fileName, "r");
	//�ǂݍ��܂�Ă��邩�e�X�g
	if (pFile == nullptr)
	{
		//�ǂݍ��܂�ĂȂ�������G���[�Ăяo��
		printf("%s open failed\n", _fileName);
		return 1;
	}
	printf("%s opened:\n", _fileName);

	//�t�@�C���̓ǂݍ���
	for (int i = 0; i < COURSE_HEIGHT; i++)
	{
		for (int j = 0; j < COURSE_WIDTH; j++)
		{
			//2�������ǂݍ���
			char buf[2];
			fread(buf, 2, 1, pFile);//2�o�C�g���ǂݍ���
			//printf("%d-%d %c%c\n", i, j, buf[0], buf[1]);
			//�󔒂Ȃ牽������Ȃ�
			if (buf[0] == ' ') {
				g_course[i][j] = PART_NONE;
			}
			else

				for (int k = PART_NONE + 1; k < PART_MAX; k++)

					//������*buf �ƕ�����*g_parts[k].m_fileName ��擪����2������r���܂��B
					//'\0'�ȍ~�̔�r�͍s���܂���B
					//K�Ԗڂ̃p�[�c�̕����ƃt�@�C�����̍ŏ��̕����ƈ�v������R�[�X��K�ł���
					if (strncmp(buf, g_parts[k].m_fileName, 2) == 0)
					{
						g_course[i][j] = k;
						break;
					}

		}
		fseek(pFile, 2, SEEK_CUR); //SEEK_CUR �t�@�C���̌��݈ʒu
	}

	fclose(pFile);

	return 0;
}
//�R�[�X�̓����蔻��
bool Course::Intersect(vec2 const & _point)
{
	ivec2 cellPoint =(ivec2)_point / PART_SIZE;
	
	if ((cellPoint.x < 0) || (cellPoint.x >= COURSE_WIDTH) || (cellPoint.y < 0) || (cellPoint.y >= COURSE_HEIGHT))

		return false;
	switch (g_course[cellPoint.y][cellPoint.x])
	{
	case PART_GROUND:
	case PART_GROUND2:
	
		return true;
	
	}
	
	return false;
}

void Course::Draw()
{
	//�X�N���[���̗�����߂�
	int ScrollColum = m_scroll / PART_SIZE;

	for (int i = 0; i < COURSE_HEIGHT; i++)
		for (int j = 0; j < COURSE_WIDTH; j++)
		{
			//��ʗ��[�̃J�b�g �]�v�ȕ`����J�b�g����
			//if ((j < ScrollColum)||(j>ScrollColum+(SCREEN_WIDTH/PART_SIZE)))
				//continue;
			int part = g_course[i][j];
			//None�Ȃ牽�����Ȃ�����ȊO�Ȃ�`�悷��
			switch (part)
			{
			case PART_NONE:
				break;
				
			default:
			{
				GLuint texture = g_parts[part].m_texture;
				glBindTexture(
					GL_TEXTURE_2D,//GLenum target,
					texture);//GLuint texture
				Rect(vec2(PART_SIZE, PART_SIZE), vec2(j, i)*(float)PART_SIZE ).Draw();

			}
			break;
			}
		}
}
