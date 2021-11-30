#include "Animation.h"
#include "Texture.h"

Animation g_animation[UNITYCHAN_ANIMATION_MAX];

int Animation::InitAll()
{
	//走るアニメーション
	for (int i = TEXTURE_UNITYCHAN_RUN_1; i <= TEXTURE_UNITYCHAN_RUN_18; i++)
		g_animation[UNITYCHAN_ANIMATION_RUN].m_Keys.push_back(i);
	g_animation[UNITYCHAN_ANIMATION_RUN].m_speed = 80;
	g_animation[UNITYCHAN_ANIMATION_RUN].m_next = UNITYCHAN_ANIMATION_RUN;


	//待機アニメーション
	for (int i = TEXTURE_UNITYCHAN_IDLE_1; i <= TEXTURE_UNITYCHAN_IDLE_4; i++)
		g_animation[UNITYCHAN_ANIMATION_IDLE].m_Keys.push_back(i);
	g_animation[UNITYCHAN_ANIMATION_IDLE].m_speed = 210;

	g_animation[UNITYCHAN_ANIMATION_IDLE].m_next = UNITYCHAN_ANIMATION_IDLE;

	//ブレーキアニメーション
	for (int i = TEXTURE_UNITYCHAN_BRAKE_1; i <= TEXTURE_UNITYCHAN_BRAKE_17; i++)
		g_animation[UNITYCHAN_ANIMATION_BRAKE].m_Keys.push_back(i);

	g_animation[UNITYCHAN_ANIMATION_BRAKE].m_speed = 60;

	g_animation[UNITYCHAN_ANIMATION_BRAKE].m_next = ANIMATION_NONE;

	

	//ジャンプ(飛ぶ瞬間)のアニメーション
	for (int i = TEXTURE_UNITYCHAN_JUMP_UP_1; i <= TEXTURE_UNITYCHAN_JUMP_UP_2; i++)
		g_animation[UNITYCHAN_ANIMATION_JUMP_UP].m_Keys.push_back(i);

	g_animation[UNITYCHAN_ANIMATION_JUMP_UP].m_speed = 80;

	g_animation[UNITYCHAN_ANIMATION_JUMP_UP].m_next = UNITYCHAN_ANIMATION_JUMP_UP;

	//ジャンプ（耐空アニメーション）
	for (int i = TEXTURE_UNITYCHAN_JUMP_1; i <= TEXTURE_UNITYCHAN_JUMP_3; i++)
		g_animation[UNITYCHAN_ANIMATION_JUMP].m_Keys.push_back(i);

	g_animation[UNITYCHAN_ANIMATION_JUMP].m_speed = 80;

	g_animation[UNITYCHAN_ANIMATION_JUMP].m_next = UNITYCHAN_ANIMATION_JUMP;

	
	//ジャンプ（RANDINGアニメーション）
	g_animation[UNITYCHAN_ANIMATION_JUMP_LANDING].m_Keys.push_back(TEXTURE_UNITYCHAN_JUMP_LANDING);

	g_animation[UNITYCHAN_ANIMATION_JUMP_LANDING].m_speed = 80;

	g_animation[UNITYCHAN_ANIMATION_JUMP_LANDING].m_next = ANIMATION_NONE;

	//ジャンプ（落下アニメーション）
	for (int i = TEXTURE_UNITYCHAN_JUMP_FALL_1; i <= TEXTURE_UNITYCHAN_JUMP_FALL_2; i++)
		g_animation[UNITYCHAN_ANIMATION_JUMP_FALL].m_Keys.push_back(i);

	g_animation[UNITYCHAN_ANIMATION_JUMP_FALL].m_speed = 80;

	g_animation[UNITYCHAN_ANIMATION_JUMP_FALL].m_next = UNITYCHAN_ANIMATION_JUMP_FALL;

	//打つアニメーション
	for (int i = TEXTURE_UNITYCHAN_HUNDGUN1_1; i <= TEXTURE_UNITYCHAN_HUNDGUN1_10; i++)
		g_animation[UNITYCAHN_ANIMATION_GUN].m_Keys.push_back(i);

	g_animation[UNITYCAHN_ANIMATION_GUN].m_speed = 80;

	g_animation[UNITYCAHN_ANIMATION_GUN].m_next = UNITYCHAN_ANIMATION_IDLE;

	return 0;


}
