#include "AnimationController.h"

#include "Animation.h"

void AnimationController::Update()
{
	m_count++;
	Animation &a = g_animation[m_animation];
	//アニメーションループ
	m_time = m_count / a.m_speed;
	//アニメーションを切り替える
	if (m_time >=(int) a.m_Keys.size())
	{
		//もし次のアニメーションがなかったら
		if (a.m_next == ANIMATION_NONE)
		{
			m_count--;
			//最後のフレームで止めておく
			m_time = a.m_Keys.size() - 1;
		}
		else

		SetAnimation(a.m_next);
	}

	
}

void AnimationController::SetAnimation(int _animation)
{
	m_animation = _animation;
	m_count = m_time = 0;
}
