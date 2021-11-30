#pragma once

#include "Rect.h"

int TexFromBMP(const char* _fileName,unsigned char *_colorKey=nullptr, Rect* _pBound = nullptr);//BMPファイルからテクスチャーを読み込んで設定する
int TexFromBMP(const char* _fileName, 
	unsigned char _colorKeyR,//赤
	unsigned char _colorKeyG,//緑
	unsigned char _colorKeyB,//青
	Rect* _pBound=nullptr
);
//この関数の中だけでカラーを設定できるようにする