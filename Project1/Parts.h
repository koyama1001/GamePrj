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

	int Init();//‰Šú‰»
	static int InitAll();//‘S•”‚Ü‚Æ‚ß‚Ä“Ç‚İ‚Ş

};
	extern Parts g_parts[PART_MAX];