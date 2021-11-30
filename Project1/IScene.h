#pragma once
#include "SceneType.h"

// �V�[���C���^�[�t�F�[�X
struct IScene
{
	// ������(���z�֐�)
	virtual void Initialize() abstract;
	//�L�[�{�[�h
	virtual void Keyboard(unsigned char _Key) abstract;
	// ���C�����[�v(���z�֐�)
	virtual void Update() abstract;
	// ���(���z�֐�)
	virtual void Release() abstract;
	//�`��
	virtual void Draw() abstract;
	//�I��
	virtual bool IsEnd() abstract;
	// ���̃V�[����
	virtual SceneType NextScene() abstract;
};