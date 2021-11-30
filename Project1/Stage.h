#pragma once
#include "Header.h"
#include "IScene.h"
#include "SceneType.h"

class Stage : public IScene
{
private:
	CHARACTERMANAGER m_characterManager;
	bool m_bEndFlag;
	bool m_gEndFlag;


public:
	Stage();

	// IScene ����Čp������܂���
	virtual void Initialize() override;

	virtual void Keyboard(unsigned char _Key) override;

	virtual void Update() override;

	virtual void Release() override;

	virtual void Draw() override;

	virtual bool IsEnd() override;

	virtual SceneType NextScene() override;

};