#pragma once
#include"glm/glm.hpp"

using namespace glm;


#define RECT_FLIP_NONE 0   //������
#define RECT_FLIP_HORIZONTAL (1<<0)//�����]�t���O
#define RECT_FLIP_VERTICAL (1<<1)//�c���]�t���O

struct Rect
{
	vec2 m_position;//�ʒu��ێ�
	vec2 m_size;//�傫����ێ�
	int m_flip;//���]���w��

	//�R���X�g���N�^
	Rect();
	Rect(vec2 const& _size);
	Rect(float _width, float _height);
	Rect( vec2 const&_size,vec2 const & _position );

	//�`��
	void Draw();
	
	void DrawWire();//���C���[��`��
	//�����蔻��
	bool Intersect(vec2 const& _point);
	bool Intersect(Rect const& _rect);
};