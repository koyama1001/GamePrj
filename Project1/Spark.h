#pragma once
#include"glm/glm.hpp"
#include <vector>

using namespace glm;
using namespace std;

struct Spark
{
public:
	vec2 m_position;//�ʒu�̕ۑ�

	vec2 m_speed;//�X�s�[�h�̕ۑ�

	int m_countLeft;//�������l

	void Update();//�X�V

	//���ׂĂ��X�V
	static void UpdateAll();
	//���ׂĂ�`��
	static void DrawAll();
	//����
	static void Explosion(vec2 const& _position);
};
extern vector<Spark>m_Sparks;