#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "Texture.h"
#include "TexBMP.h"
#include "Player.h"

#include "glut.h"

//プレイヤーのテクスチャーファイル
Textrure g_textures[TEXTURE_UNITYCHAN_MAX]={
{"Unitychan_Brake_1.bmp",},
{"Unitychan_Brake_2.bmp",},
{"Unitychan_Brake_3.bmp",},
{"Unitychan_Brake_4.bmp",},
{"Unitychan_Brake_5.bmp",},
{"Unitychan_Brake_6.bmp",},
{"Unitychan_Brake_7.bmp",},
{"Unitychan_Brake_8.bmp",},
{"Unitychan_Brake_9.bmp",},
{"Unitychan_Brake_10.bmp",},
{"Unitychan_Brake_11.bmp",},
{"Unitychan_Brake_12.bmp",},
{"Unitychan_Brake_13.bmp",},
{"Unitychan_Brake_14.bmp",},
{"Unitychan_Brake_15.bmp",},
{"Unitychan_Brake_16.bmp",},
{"Unitychan_Brake_17.bmp",},
{"Unitychan_Damage_1.bmp",},
{"Unitychan_Damage_2.bmp",},
{"Unitychan_Damage_3.bmp",},
{"Unitychan_Damage_4.bmp",},
{"Unitychan_Damage_5.bmp",},
{"Unitychan_Hundgun1_1.bmp",},
{"Unitychan_Hundgun1_2.bmp",},
{"Unitychan_Hundgun1_3.bmp",},
{"Unitychan_Hundgun1_4.bmp",},
{"Unitychan_Hundgun1_5.bmp",},
{"Unitychan_Hundgun1_6.bmp",},
{"Unitychan_Hundgun1_7.bmp",},
{"Unitychan_Hundgun1_8.bmp",},
{"Unitychan_Hundgun1_9.bmp",},
{"Unitychan_Hundgun1_10.bmp",},
{"Unitychan_Hundgun1_11.bmp",},
{"Unitychan_Hundgun1_12.bmp",},
{"Unitychan_Hundgun1_13.bmp",},
{"Unitychan_Hundgun1_14.bmp",},
{"Unitychan_Hundgun1_15.bmp",},
{"Unitychan_Hundgun1_16.bmp",},
{"Unitychan_Hundgun1_17.bmp",},
{"Unitychan_Hundgun1_18.bmp",},
{"Unitychan_Hundgun1_19.bmp",},
{"Unitychan_Hundgun1_20.bmp",},
{"Unitychan_Idle_1.bmp",},
{"Unitychan_Idle_2.bmp",},
{"Unitychan_Idle_3.bmp",},
{"Unitychan_Idle_4.bmp",},
{"Unitychan_Jump_1.bmp",},
{"Unitychan_Jump_2.bmp",},
{"Unitychan_Jump_3.bmp",},
{"Unitychan_Jump_Fall_1.bmp",},
{"Unitychan_Jump_Fall_2.bmp",},
{"Unitychan_Jump_Landing.bmp",},
{"Unitychan_Jump_Up_1.bmp",},
{"Unitychan_Jump_Up_2.bmp",},
{"Unitychan_Run_1.bmp",},
{"Unitychan_Run_2.bmp",},
{"Unitychan_Run_3.bmp",},
{"Unitychan_Run_4.bmp",},
{"Unitychan_Run_5.bmp",},
{"Unitychan_Run_6.bmp",},
{"Unitychan_Run_7.bmp",},
{"Unitychan_Run_8.bmp",},
{"Unitychan_Run_9.bmp",},
{"Unitychan_Run_10.bmp",},
{"Unitychan_Run_11.bmp",},
{"Unitychan_Run_12.bmp",},
{"Unitychan_Run_13.bmp",},
{"Unitychan_Run_14.bmp",},
{"Unitychan_Run_15.bmp",},
{"Unitychan_Run_16.bmp",},
{"Unitychan_Run_17.bmp",},
{"Unitychan_Run_18.bmp",},
};



int Textrure::Init()
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
	char fileName[256] = "Texture\\";

	sprintf(fileName, "%s%s", fileName, m_fileName);
	//確認
	//printf("%s\n", fileName);

	TexFromBMP(fileName, 0xff, 0xff, 0xff,&m_bound);
	m_bound.m_size.x = 32;
	m_bound.m_size.y = PLAYER_BOTTOM- m_bound.m_position.y;

	return 0;
}

int Textrure::InitAll()
{
	
	//テクスチャーの読み込み
	for (int i = 0; i < TEXTURE_UNITYCHAN_MAX; i++)
	{
		g_textures[i].Init();
	}


	return 0;
}

