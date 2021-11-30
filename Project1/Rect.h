#pragma once
#include"glm/glm.hpp"

using namespace glm;


#define RECT_FLIP_NONE 0   //初期化
#define RECT_FLIP_HORIZONTAL (1<<0)//横反転フラグ
#define RECT_FLIP_VERTICAL (1<<1)//縦反転フラグ

struct Rect
{
	vec2 m_position;//位置を保持
	vec2 m_size;//大きさを保持
	int m_flip;//反転を指示

	//コンストラクタ
	Rect();
	Rect(vec2 const& _size);
	Rect(float _width, float _height);
	Rect( vec2 const&_size,vec2 const & _position );

	//描画
	void Draw();
	
	void DrawWire();//ワイヤーを描画
	//当たり判定
	bool Intersect(vec2 const& _point);
	bool Intersect(Rect const& _rect);
};