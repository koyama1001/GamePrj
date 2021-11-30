#pragma once
#include "glm/glm.hpp"
#include "Rect.h"
#include "glut.h"
#include "TexBMP.h"
#include "Timer.h"

using namespace std;
using namespace glm;

class Explosion:public Rect
{
public:
	int m_ExplosionCountLife;//生存数値

	Explosion();
	~Explosion();
	
	void Init();//初期化
	void Update();//アップデート
	void Draw();//描画

	void SetPosition(vec2 _Enemy_Position);//敵の位置を取得
	vec2 GetPosition();//位置を取得
	

private:
	unsigned int m_texture; //絵の枚数
};


