#pragma once

#include "glm/glm.hpp"


//#define COURSE_WIDTH 212
//#define COURSE_HEIGHT 16

using namespace glm;

enum ECourse {

COURSE_WIDTH=201,//�R�[�X�̉��̒���
COURSE_HEIGHT=16 //�R�[�X�̏c�̒���

};

struct Course
{

	int g_course[COURSE_HEIGHT][COURSE_WIDTH];

	float m_scroll;

	int Load(const char* _fileName);

	bool Intersect(vec2 const& _point);

	//�R�[�X��`��
	void Draw();
};


extern Course g_course;