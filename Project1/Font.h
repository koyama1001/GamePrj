#pragma once
#include "glm/glm.hpp"


using namespace glm;

enum FONT_DEFALUT {
//フォントの幅
FONT_DEFAULT_WIDTH =104,
//フォントの高さ
FONT_DEFAULT_HEIGHT=119 
};
//フォントの幅
//#define FONT_DEFAULT_WIDTH  104.0f
//フォントの高さ
//#define FONT_DEFAULT_HEIGHT 119.05f 




//文字列描画するためのヘッダーファイルを作る

    void FontInit(float _width, float _height);//初期化

	void FontScreenSize(float _width,float _height);//サイズ設定

	void FontBegin();//開始

	void FontEnd();//終わり

	void FontPosition(float _x, float _y);//位置

	void FontPosition(vec2 const _position);//位置

	void FontSize(vec2 const& _size);//大きさ

	void FontSize(float _width,float _height);//大きさ

	void FontWeight(float _weight);//基準に太さを設定する

	float FontGetWidth(int _character);//幅の太さ取得

	float FontGetLength(const unsigned char* _string);//文字列の幅を取得する

	float FontGetLength(const  char * _string);//文字列の幅を取得する

	vec2 FontGetSize();//大きさを取得

	float FontGetWeightMin();//設定可能な一番細い

	float FontGetWeightMax();//設定可能な一番太い太さ

	float FontGetWeight();

	void FontDraw(const char *_format, ...);//printFみたいに描画




