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

//コースデータの読み込み
int Course::Load(const char * _fileName)
{
	//ファイルをオープン
	FILE* pFile = fopen(_fileName, "r");
	//読み込まれているかテスト
	if (pFile == nullptr)
	{
		//読み込まれてなかったらエラー呼び出し
		printf("%s open failed\n", _fileName);
		return 1;
	}
	printf("%s opened:\n", _fileName);

	//ファイルの読み込み
	for (int i = 0; i < COURSE_HEIGHT; i++)
	{
		for (int j = 0; j < COURSE_WIDTH; j++)
		{
			//2文字ずつ読み込む
			char buf[2];
			fread(buf, 2, 1, pFile);//2バイトずつ読み込む
			//printf("%d-%d %c%c\n", i, j, buf[0], buf[1]);
			//空白なら何も入れない
			if (buf[0] == ' ') {
				g_course[i][j] = PART_NONE;
			}
			else

				for (int k = PART_NONE + 1; k < PART_MAX; k++)

					//文字列*buf と文字列*g_parts[k].m_fileName を先頭から2文字比較します。
					//'\0'以降の比較は行いません。
					//K番目のパーツの文字とファイル名の最初の文字と一致したらコースはKである
					if (strncmp(buf, g_parts[k].m_fileName, 2) == 0)
					{
						g_course[i][j] = k;
						break;
					}

		}
		fseek(pFile, 2, SEEK_CUR); //SEEK_CUR ファイルの現在位置
	}

	fclose(pFile);

	return 0;
}
//コースの当たり判定
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
	//スクロールの列を求めた
	int ScrollColum = m_scroll / PART_SIZE;

	for (int i = 0; i < COURSE_HEIGHT; i++)
		for (int j = 0; j < COURSE_WIDTH; j++)
		{
			//画面両端のカット 余計な描画をカットする
			//if ((j < ScrollColum)||(j>ScrollColum+(SCREEN_WIDTH/PART_SIZE)))
				//continue;
			int part = g_course[i][j];
			//Noneなら何もしないそれ以外なら描画する
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
