#pragma once
#include"glm/glm.hpp"

using namespace glm;


struct Ball
{
	vec2 m_LastPosition;//1�t���[���O�̃|�W�V����
	vec2 m_position;//�{�[���̈ʒu
	vec2 m_speed;//�{�[���̃X�s�[�h

	
	void Update();//�X�V
	
	void Draw();//�`��
};