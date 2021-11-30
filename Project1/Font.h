#pragma once
#include "glm/glm.hpp"


using namespace glm;

enum FONT_DEFALUT {
//�t�H���g�̕�
FONT_DEFAULT_WIDTH =104,
//�t�H���g�̍���
FONT_DEFAULT_HEIGHT=119 
};
//�t�H���g�̕�
//#define FONT_DEFAULT_WIDTH  104.0f
//�t�H���g�̍���
//#define FONT_DEFAULT_HEIGHT 119.05f 




//������`�悷�邽�߂̃w�b�_�[�t�@�C�������

    void FontInit(float _width, float _height);//������

	void FontScreenSize(float _width,float _height);//�T�C�Y�ݒ�

	void FontBegin();//�J�n

	void FontEnd();//�I���

	void FontPosition(float _x, float _y);//�ʒu

	void FontPosition(vec2 const _position);//�ʒu

	void FontSize(vec2 const& _size);//�傫��

	void FontSize(float _width,float _height);//�傫��

	void FontWeight(float _weight);//��ɑ�����ݒ肷��

	float FontGetWidth(int _character);//���̑����擾

	float FontGetLength(const unsigned char* _string);//������̕����擾����

	float FontGetLength(const  char * _string);//������̕����擾����

	vec2 FontGetSize();//�傫�����擾

	float FontGetWeightMin();//�ݒ�\�Ȉ�ԍׂ�

	float FontGetWeightMax();//�ݒ�\�Ȉ�ԑ�������

	float FontGetWeight();

	void FontDraw(const char *_format, ...);//printF�݂����ɕ`��




