#pragma once

#include "Rect.h"

int TexFromBMP(const char* _fileName,unsigned char *_colorKey=nullptr, Rect* _pBound = nullptr);//BMP�t�@�C������e�N�X�`���[��ǂݍ���Őݒ肷��
int TexFromBMP(const char* _fileName, 
	unsigned char _colorKeyR,//��
	unsigned char _colorKeyG,//��
	unsigned char _colorKeyB,//��
	Rect* _pBound=nullptr
);
//���̊֐��̒������ŃJ���[��ݒ�ł���悤�ɂ���