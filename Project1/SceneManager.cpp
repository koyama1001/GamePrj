#include "SceneManager.h"

SceneManager::SceneManager():
	m_mapScenes{},
	m_currentScene{}
{
	
}


bool SceneManager::Add(SceneType sceneName, IScene* scene)
{
	//�v�f�̃^�C�v���i�[
	m_mapScenes.insert(std::map<SceneType, IScene*>::value_type(sceneName,scene));
	return true;
}

void SceneManager::init()
{
	//������
	m_mapScenes.clear();
	
}

void SceneManager::Change(SceneType name)
{
	////�V�[�����Ȃ���Ύ̂Ă�
	//if (m_currentScene != nullptr)
	//{
	//	m_currentScene->Release();
	//}
	//�}�b�v�C�e���[�^�[���̖��O�擾
	std::map<SceneType, IScene*>::iterator findIter = m_mapScenes.find(name);
	m_currentScene = (*findIter).second;
	//������
	m_currentScene->Initialize();
}

void SceneManager::Update()
{
	if (m_currentScene == nullptr)
	{
		return;
	}

	m_currentScene->Update();
	if (m_currentScene->IsEnd() == true)
	{
		Change(m_currentScene->NextScene());
	}
}

void SceneManager::Draw()
{
	if (m_currentScene == nullptr)
	{
		return;
	}

	m_currentScene->Draw();
}


void SceneManager::Release()
{
	std::map<SceneType, IScene*>::iterator delIter = m_mapScenes.begin();
	while (delIter != m_mapScenes.end())
	{
		IScene* del = (*delIter).second;
		del->Release();
		del = nullptr;
		delIter++;
	}
	m_mapScenes.clear();

	delete this;
}
