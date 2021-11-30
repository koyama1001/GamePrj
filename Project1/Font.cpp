#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "Font.h"
#include "glut.h"
#include "glm/glm.hpp"

#define FONT GLUT_STROKE_MONO_ROMAN

using namespace glm;

static vec2 size = { FONT_DEFAULT_WIDTH,FONT_DEFAULT_HEIGHT };//フォントのサイズを指定（高さと幅を設定）

static vec2 ScreenSize = { 256,256 };//画面解像度に合した

static vec2 position;//座標
static vec2 origin;//原点

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
	glPushMatrix();//変換行列の保存
	glPushAttrib(GL_ALL_ATTRIB_BITS);//GLbitfield mask

	//2Dの行列に変換

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
	glMatrixMode(GL_MODELVIEW); //GLenum mode　モード設定
	glLoadIdentity();//リセットしている

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void FontEnd()
{
	glPopMatrix();//変換行列の取り出し
	glPopAttrib();//取り消す
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
	//サイズの設定
	size = _size;
}

void FontSize(float _width, float _height)
{
	FontSize(vec2(_width, _height));
}


float FontGetWeightMin()
{
	GLfloat weight[2];//範囲取得用
	glGetFloatv(
		GL_LINE_WIDTH_RANGE,//GLenum pname
		weight);//GLfloat *params
	return weight[0];
}

float FontGetWeightMax()
{
	GLfloat weight[2];//範囲取得用
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
	//文字の太さを取得する
	return glutStrokeWidth(
		FONT,//void *font
		_character//int character
	)
		*size.x / FONT_DEFAULT_WIDTH;

	
}

float FontGetLength(const unsigned char * _string)
{
	//文字列の幅を取得する
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
		//ビューポート　画面設定値を取り出す
		glGetIntegerv(
			GL_VIEWPORT,//GLenum pname,
			Viewport//GLint *params
		);
		//printf("%d %d\n",Viewport[2],Viewport[3]);

		//画面の大きさが変わってもフォントの相対的な太さは変わらない
		glLineWidth(weight*Viewport[3]/ ScreenSize.y);//GLfloat width

	}

	
	
	char *p = str;
	
	
		
		
		for (; (*p != '\0') && (*p != '\n'); p++)
		{
			glPushMatrix();
			{
				glTranslated(position.x, position.y + size.y, 0); //GLfloat(x,y,z) 位置Yをsize100下げた
				 // 向きを変更
				glScalef(
					size.x / FONT_DEFAULT_WIDTH,//GLfloat x, 
					-size.y / FONT_DEFAULT_HEIGHT,//GLfloat y, 
					0);//GLfloat z
				glutStrokeCharacter(FONT, *p);//フォントを線の集合でやってる
				position.x += FontGetWidth(*p);//現在描画してる文字の太さ文ずらす

			}
			glPopMatrix();
		}
	

	if (*p == '\n')
	{
		//改行処理
		position.x = origin.x;
		position.y += FontGetSize().y;
		FontDraw(++p);
	}

	//printf("%s\n", str);
}

