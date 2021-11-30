#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "Font.h"
#include "glut.h"
#include "glm/glm.hpp"

#define FONT GLUT_STROKE_MONO_ROMAN

using namespace glm;

static vec2 size = { FONT_DEFAULT_WIDTH,FONT_DEFAULT_HEIGHT };//�t�H���g�̃T�C�Y���w��i�����ƕ���ݒ�j

static vec2 ScreenSize = { 256,256 };//��ʉ𑜓x�ɍ�����

static vec2 position;//���W
static vec2 origin;//���_

static float weight = 1;


void FontInit(float _width, float _height)
{
	FontScreenSize(_width, _height);
}

void FontScreenSize(float _width, float _height)
{
	ScreenSize = vec2(_width, _height);
}

void FontBegin()
{
	glPushMatrix();//�ϊ��s��̕ۑ�
	glPushAttrib(GL_ALL_ATTRIB_BITS);//GLbitfield mask

	//2D�̍s��ɕϊ�

	glMatrixMode(GL_PROJECTION);//GLenum mode

	glLoadIdentity();

	GLint Viewport[4];

	glGetIntegerv(GL_VIEWPORT,Viewport);//GLenum pname, GLint *params
	gluOrtho2D(
		0,//GLdouble left,
		Viewport[2],//GLdouble right,
		Viewport[3],//GLdouble bottom,
		0//GLdouble top

	);
	glMatrixMode(GL_MODELVIEW); //GLenum mode�@���[�h�ݒ�
	glLoadIdentity();//���Z�b�g���Ă���

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void FontEnd()
{
	glPopMatrix();//�ϊ��s��̎��o��
	glPopAttrib();//������
}



void FontPosition(float _x, float _y)
{
	FontPosition(vec2(_x , _y));
}

void FontPosition(vec2 const _position)
{
	origin = position = _position;
}


void FontSize(vec2 const& _size)
{
	//�T�C�Y�̐ݒ�
	size = _size;
}

void FontSize(float _width, float _height)
{
	FontSize(vec2(_width, _height));
}


float FontGetWeightMin()
{
	GLfloat weight[2];//�͈͎擾�p
	glGetFloatv(
		GL_LINE_WIDTH_RANGE,//GLenum pname
		weight);//GLfloat *params
	return weight[0];
}

float FontGetWeightMax()
{
	GLfloat weight[2];//�͈͎擾�p
	glGetFloatv(
		GL_LINE_WIDTH_RANGE,//GLenum pname
		weight);//GLfloat *params
	return weight[1];
}

void FontWeight(float _weight)
{
	weight = _weight;
}

float FontGetWidth(int _character)
{
	//�����̑������擾����
	return glutStrokeWidth(
		FONT,//void *font
		_character//int character
	)
		*size.x / FONT_DEFAULT_WIDTH;

	
}

float FontGetLength(const unsigned char * _string)
{
	//������̕����擾����
	return glutStrokeLength(
		FONT,//void *font, 
		_string//const unsigned char *string
	)*size.x / FONT_DEFAULT_WIDTH;
		
}
float FontGetLength(const  char * _string)
{
	return FontGetLength((unsigned  char *)(_string));

}

vec2 FontGetSize()
{
	return size;
}

float FontGetWeight()
{
	return weight;
}



void FontDraw(const char *_format, ...)
{
	va_list argList;
	va_start(argList, _format);
	char str[256];
	vsprintf_s(str, _format, argList);
	va_end(argList);

	{
		GLint Viewport[4];//x, y, w, h
		//�r���[�|�[�g�@��ʐݒ�l�����o��
		glGetIntegerv(
			GL_VIEWPORT,//GLenum pname,
			Viewport//GLint *params
		);
		//printf("%d %d\n",Viewport[2],Viewport[3]);

		//��ʂ̑傫�����ς���Ă��t�H���g�̑��ΓI�ȑ����͕ς��Ȃ�
		glLineWidth(weight*Viewport[3]/ ScreenSize.y);//GLfloat width

	}

	
	
	char *p = str;
	
	
		
		
		for (; (*p != '\0') && (*p != '\n'); p++)
		{
			glPushMatrix();
			{
				glTranslated(position.x, position.y + size.y, 0); //GLfloat(x,y,z) �ʒuY��size100������
				 // ������ύX
				glScalef(
					size.x / FONT_DEFAULT_WIDTH,//GLfloat x, 
					-size.y / FONT_DEFAULT_HEIGHT,//GLfloat y, 
					0);//GLfloat z
				glutStrokeCharacter(FONT, *p);//�t�H���g����̏W���ł���Ă�
				position.x += FontGetWidth(*p);//���ݕ`�悵�Ă镶���̑��������炷

			}
			glPopMatrix();
		}
	

	if (*p == '\n')
	{
		//���s����
		position.x = origin.x;
		position.y += FontGetSize().y;
		FontDraw(++p);
	}

	//printf("%s\n", str);
}

