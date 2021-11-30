#pragma once
// title->stage->end->title
#include <Windows.h>
#include <map>
#include "SceneType.h"
#include "IScene.h"

class SceneManager
{
private:
	//Map�i�[
	std::map<SceneType, IScene*> m_mapScenes;
	//�V�[���쐬
	IScene* m_currentScene;

public:
	SceneManager();
	//�V�[���̖��O������
	bool Add(SceneType sceneName, IScene* scene);

	void init();
	//�؂�ւ�
	void Change(SceneType name);
	void Update();
	void Draw();
	void Release();

};