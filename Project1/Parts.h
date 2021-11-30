#pragma once

#define PART_SIZE 16

enum 
{
	
	PART_NONE,
	PART_GROUND,
	PART_GROUND2,
	PART_MAX
};


struct Parts
{
	const char *m_fileName;
	unsigned int m_texture;

	int Init();//初期化
	static int InitAll();//全部まとめて読み込む

};
	extern Parts g_parts[PART_MAX];