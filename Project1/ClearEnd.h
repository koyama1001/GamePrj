#pragma once
#include "Header.h"
#include "IScene.h"
#include "glm/glm.hpp"
#include "glut.h"
#include "Rect.h"


class ClearEnd :public IScene, Rect
{
private:
	//�I���̃t���O
	bool m_gEndFlag;
	unsigned int m_texture; //�G�̖���

public:
	ClearEnd();

	// IScene ����Čp������܂���
	virtual void Initialize() override;

	virtual void Keyboard(unsigned char _Key) override;

	virtual void Update() override;

	virtual void Release() override;

	virtual void Draw() override;

	virtual bool IsEnd() override;

	virtual SceneType NextScene() override;
};