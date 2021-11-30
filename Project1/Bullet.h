#pragma once

#include "glm/glm.hpp"
#include "Rect.h"
#include "glut.h"
#include "TexBMP.h"

//#define BULLET_DAMAGE 10;//球のダメージ
using namespace std;
using namespace glm;

enum BULLET {
	BULLET_DAMAGE =10 //球のダメージ
};

class Bullet:public Rect
{
private:

	unsigned int m_texture; //絵の枚数

	int m_dir;//数値の保存

public:
	

	int m_countLife;//生存数値
	//float m_velocity;//移動量
	float m_speed;//スピード
	bool m_isCollision;

public:

	Bullet();
	~Bullet();

	void Init();//初期化
	void Update();//アップデート
	void Draw();//描画

	void setPosition(vec2 _Player_Position);//プレイヤーの位置を取得
	vec2 getPosition();//位置を取得
	void setDir(int dir);//プレイヤーの数値取得
	//void setVelocity(float velocity);
	
};

