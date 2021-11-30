#pragma once

struct  AnimationController
{
	int m_animation;
	int m_count;
	int m_time;

	void Update();
	//アニメーションを設定
	void SetAnimation(int _animation);
	
};