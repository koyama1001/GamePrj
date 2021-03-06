#pragma once
#include "Header.h"
#include "IScene.h"
#include "glm/glm.hpp"
#include "glut.h"
#include "Rect.h"


class End :public IScene,Rect
{
private:
	//終わりのフラグ
	bool m_bEndFlag;
	unsigned int m_texture; //絵の枚数

public:
	End();

	// IScene を介して継承されました
	virtual void Initialize() override;

	virtual void Keyboard(unsigned char _Key) override;

	virtual void Update() override;

	virtual void Release() override;

	virtual void Draw() override;

	virtual bool IsEnd() override;

	virtual SceneType NextScene() override;
};