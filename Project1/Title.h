#pragma once
#include "Header.h"
#include "IScene.h"
#include "Rect.h"
#include "glm/glm.hpp"
#include "glut.h"
#include "TexBMP.h"

class Title :public IScene,Rect
{
private:
	bool m_bEndFlag;
	unsigned int m_texture; //ŠG‚Ì–‡”

public:
	Title();


	// IScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Initialize() override;

	virtual void Keyboard(unsigned char _Key) override;

	virtual void Update() override;

	virtual void Release() override;

	virtual void Draw() override;

	virtual bool IsEnd() override;

	virtual SceneType NextScene() override;

};