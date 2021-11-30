#pragma once
#include "Header.h"
#include "IScene.h"
#include "glm/glm.hpp"
#include "glut.h"
#include "Rect.h"


class ClearEnd :public IScene, Rect
{
private:
	//I‚í‚è‚Ìƒtƒ‰ƒO
	bool m_gEndFlag;
	unsigned int m_texture; //ŠG‚Ì–‡”

public:
	ClearEnd();

	// IScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual void Initialize() override;

	virtual void Keyboard(unsigned char _Key) override;

	virtual void Update() override;

	virtual void Release() override;

	virtual void Draw() override;

	virtual bool IsEnd() override;

	virtual SceneType NextScene() override;
};