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

	int Init();//������
	static int InitAll();//�S���܂Ƃ߂ēǂݍ���

};
	extern Parts g_parts[PART_MAX];