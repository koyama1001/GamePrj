#pragma once
// title->stage->end->title
#include <Windows.h>
#include <map>
#include "SceneType.h"
#include "IScene.h"

class SceneManager
{
private:
	//Map格納
	std::map<SceneType, IScene*> m_mapScenes;
	//シーン作成
	IScene* m_currentScene;

public:
	SceneManager();
	//シーンの名前を入れる
	bool Add(SceneType sceneName, IScene* scene);

	void init();
	//切り替え
	void Change(SceneType name);
	void Update();
	void Draw();
	void Release();

};