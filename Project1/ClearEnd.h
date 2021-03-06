#pragma once
#include "Header.h"
#include "IScene.h"
#include "glm/glm.hpp"
#include "glut.h"
#include "Rect.h"


class ClearEnd :public IScene, Rect
{
private:
	//終わりのフラグ
	bool m_gEndFlag;
	unsigned int m_texture; //絵の枚数

public:
	ClearEnd();

	// IScene を介して継承されました
	virtual void Initialize() override;

	virtual void Keyboard(unsigned char _Key) override;

	virtual void Update() override;

	virtual void Release() override;

	virtual void Draw() override;

	virtual bool IsEnd() override;

	virtual SceneType NextScene() override;
};