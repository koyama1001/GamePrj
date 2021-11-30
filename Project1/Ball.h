#pragma once
#include"glm/glm.hpp"

using namespace glm;


struct Ball
{
	vec2 m_LastPosition;//1フレーム前のポジション
	vec2 m_position;//ボールの位置
	vec2 m_speed;//ボールのスピード

	
	void Update();//更新
	
	void Draw();//描画
};