#pragma once
#include"glm/glm.hpp"
#include <vector>

using namespace glm;
using namespace std;

struct Spark
{
public:
	vec2 m_position;//位置の保存

	vec2 m_speed;//スピードの保存

	int m_countLeft;//生存数値

	void Update();//更新

	//すべてを更新
	static void UpdateAll();
	//すべてを描画
	static void DrawAll();
	//爆発
	static void Explosion(vec2 const& _position);
};
extern vector<Spark>m_Sparks;