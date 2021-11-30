#pragma once

#include "glm/glm.hpp"


//#define COURSE_WIDTH 212
//#define COURSE_HEIGHT 16

using namespace glm;

enum ECourse {

COURSE_WIDTH=201,//コースの横の長さ
COURSE_HEIGHT=16 //コースの縦の長さ

};

struct Course
{

	int g_course[COURSE_HEIGHT][COURSE_WIDTH];

	float m_scroll;

	int Load(const char* _fileName);

	bool Intersect(vec2 const& _point);

	//コースを描画
	void Draw();
};


extern Course g_course;