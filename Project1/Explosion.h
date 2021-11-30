#pragma once
#include "glm/glm.hpp"
#include "Rect.h"
#include "glut.h"
#include "TexBMP.h"
#include "Timer.h"

using namespace std;
using namespace glm;

class Explosion:public Rect
{
public:
	int m_ExplosionCountLife;//�������l

	Explosion();
	~Explosion();
	
	void Init();//������
	void Update();//�A�b�v�f�[�g
	void Draw();//�`��

	void SetPosition(vec2 _Enemy_Position);//�G�̈ʒu���擾
	vec2 GetPosition();//�ʒu���擾
	

private:
	unsigned int m_texture; //�G�̖���
};


