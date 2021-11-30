#include "Stage.h"
#include "Course.h"

Stage::Stage():
	m_characterManager{},
	m_bEndFlag{},
	m_gEndFlag{}
{
}

void Stage::Initialize()
{
	m_bEndFlag = false;
	m_gEndFlag = false;
	g_course.Load("Course.txt");
	//パーツの初期化
	Parts::InitAll();
	m_characterManager.Init();
}


void Stage::Keyboard(unsigned char _Key)
{
}

void Stage::Update()
{
	m_characterManager.Update();
	//もしプレイヤーのHPが０になるかエリア外に出たら終了にする
	if (m_characterManager.m_pPlayer->m_PlayerHP == 0 || m_characterManager.m_pPlayer->m_position.y >= 350)
	{
		g_course.m_scroll = (0, 0);
		m_characterManager.m_pPlayer->m_position = vec2(0, 0);
		m_bEndFlag = true;
	}
	std::list<BossEnemy *>::iterator iter = m_characterManager.m_BossEnemys.begin();
	while (iter != m_characterManager.m_BossEnemys.end())
	{
		if ((*iter)->GetHP() == 0)
		{
			//death
			g_course.m_scroll = (0, 0);
			m_characterManager.m_pPlayer->m_position = vec2(0, 0);
			
			m_gEndFlag = true;
		}
		++iter;
	}
	
}

void Stage::Release()
{
	m_characterManager.~CHARACTERMANAGER();
}

void Stage::Draw()
{
	g_course.Draw();
	m_characterManager.Draw();
}

bool Stage::IsEnd()
{
	bool isEnd = false;
	if(m_bEndFlag)
		return m_bEndFlag;

	if (m_gEndFlag)
		return m_gEndFlag;
}

SceneType Stage::NextScene()
{
	if(m_bEndFlag)
		return SceneType::Ending;

	if (m_gEndFlag)
		return SceneType::Clear;
}
