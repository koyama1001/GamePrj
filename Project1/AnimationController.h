#pragma once

struct  AnimationController
{
	int m_animation;
	int m_count;
	int m_time;

	void Update();
	//�A�j���[�V������ݒ�
	void SetAnimation(int _animation);
	
};