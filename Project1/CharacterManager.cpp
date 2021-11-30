#include "CharacterManager.h"


CHARACTERMANAGER::CHARACTERMANAGER() :
	m_pPlayer{},
	m_Enemys{},
	m_BossEnemys{},
	m_DrawCount(0),
	m_BlinkMask(1),
	m_PlayerBullets{},
	m_pTimer{},
	muteki{},
	explosionOnOff{},
	m_pExplosion{},
	m_BulletShotEnemys{},
	m_EnemyBullets{}
	
	
{
	
}

CHARACTERMANAGER::~CHARACTERMANAGER()
{
	//データ消去
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pTimer;
	m_pTimer = nullptr;
	delete m_pExplosionTimer;
	m_pExplosionTimer = nullptr;

	//敵のリストの中身を消す
	std::list<Enemy *>::iterator delIter = m_Enemys.begin();
	while (delIter != m_Enemys.end())
	{

		Enemy *del;
		del = *delIter;
		delete del;
		del = nullptr;
		delIter++;
	}
	m_Enemys.clear();
	//敵のリストの中身を消す
	std::list<BulletShotEnemy *>::iterator BulletShotEnemyDelIter = m_BulletShotEnemys.begin();
	while (BulletShotEnemyDelIter != m_BulletShotEnemys.end())
	{

		BulletShotEnemy *del;
		del = *BulletShotEnemyDelIter;
		delete del;
		del = nullptr;
		BulletShotEnemyDelIter++;
	}
	m_BulletShotEnemys.clear();

	//Bossのリストの中身を消す
	std::list<BossEnemy *>::iterator DelIter = m_BossEnemys.begin();
	while (DelIter != m_BossEnemys.end())
	{
		BossEnemy *Del;
		Del = *DelIter;
		delete Del;
		Del = nullptr;
		DelIter++;
	}
	m_BossEnemys.clear();
}

void CHARACTERMANAGER::Init()
{
	m_pPlayer = new Player{};
	m_pTimer = new CustomTimer{};
	m_pExplosionTimer = new CustomTimer{};

	m_pPlayer->Init();//プレイヤーを初期化
	m_pTimer->init();//プレイヤータイマーを初期化
	m_pExplosionTimer->init();//爆発タイマーを初期化

	//Bullets
	m_PlayerBullets.clear();//初期化
	m_EnemyBullets.clear();//初期化

	//Enemy
	m_Enemys.clear();//初期化
	m_BossEnemys.clear();//初期化
	m_BulletShotEnemys.clear();//初期化

	muteki = false;
	explosionOnOff = false;

	//敵の画像、大きさ、座標、体力を指定
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(120.f, 135.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(500.f, 135.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(600.f, 135.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(800.f, 105.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(1080.f, 152.f),4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(1320.f, 72.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(2110.f, 40.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(2400.f, 104.f),4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(2710.f, 152.f),4);
	//打つ敵の画像、大きさ、座標、体力を指定
	SetBulletShotEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(260.f, 75.f) ,4);
	SetBulletShotEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(800.f, 105.f),4);
	//ボスキャラの画像、大きさ、座標、体力を指定												 
	SetBossEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(3180.f, 215.f), 50);
}
//球の速度
float RandomFloat(float a, float b)
{
	//0～1のランダム生成
	float random = ((float)rand()) / (float)RAND_MAX;

	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void CHARACTERMANAGER::Update()
{
	////プレイヤーの体力が0になったら消す
	//if (m_pPlayer->m_PlayerHP == 0)
	//	delete m_pPlayer;



	m_pPlayer->Update();//更新
	m_pTimer->Update();//更新
	m_pExplosionTimer->Update();//更新

	//printf("%f:Timer\n", m_Timer->Now());

	// enemys Update
	std::list<Enemy *>::iterator EnemyUpdate_iter = m_Enemys.begin();
	while (EnemyUpdate_iter != m_Enemys.end())
	{
		Enemy *del;
		//エネミーイテレーターアップデート
		(*EnemyUpdate_iter)->Update();

		//敵の体力が0なら
		if ((*EnemyUpdate_iter)->GetHP() == 0)
		{
			//爆発　敵の位置取得
			CreateExplosion((*EnemyUpdate_iter)->m_position);
			//爆発　フラグ　ON
			explosionOnOff = true;
			//時間設定
			m_pExplosionTimer->SetTimer(1);

			//イテレーターを消す
			del = *EnemyUpdate_iter;
			EnemyUpdate_iter = m_Enemys.erase(EnemyUpdate_iter);
			//敵を消す
			delete del;
			del = nullptr;
		}
		else EnemyUpdate_iter++;
	}
	// BSenemys Update
	std::list<BulletShotEnemy *>::iterator BSE_Update_iter = m_BulletShotEnemys.begin();
	while (BSE_Update_iter != m_BulletShotEnemys.end())
	{
		BulletShotEnemy *del;
		//エネミーイテレーターアップデート
		(*BSE_Update_iter)->Update();

		//敵の体力が0なら
		if ((*BSE_Update_iter)->GetHP() == 0)
		{
			//爆発　敵の位置取得
			CreateExplosion((*BSE_Update_iter)->m_position);
			//爆発　フラグ　ON
			explosionOnOff = true;
			//時間設定
			m_pExplosionTimer->SetTimer(1);

			//イテレーターを消す
			del = *BSE_Update_iter;
			BSE_Update_iter = m_BulletShotEnemys.erase(BSE_Update_iter);
			//敵を消す
			delete del;
			del = nullptr;
		}
		else BSE_Update_iter++;
	}
	// boss Enemy Update
	std::list<BossEnemy *>::iterator BossUpdater = m_BossEnemys.begin();
	while (BossUpdater != m_BossEnemys.end())
	{
		BossEnemy *Del;
		//エネミーイテレーターアップデート
		(*BossUpdater)->Update();

		//敵の体力が0なら
		if ((*BossUpdater)->GetHP() == 0)
		{
			//爆発　敵の位置取得
			CreateExplosion((*BossUpdater)->m_position);
			//爆発　フラグ　ON
			explosionOnOff = true;
			//時間設定
			m_pExplosionTimer->SetTimer(1);

			//イテレーターを消す
			Del = *BossUpdater;
			BossUpdater = m_BossEnemys.erase(BossUpdater);
			//敵を消す
			delete Del;
			Del = nullptr;
		}
		else BossUpdater++;
	}
	//当たり判定
	Collision();

	//もしタイマーが切れてれば無敵をOFF
	if (m_pTimer->IsTime())
		muteki = false;
	//もしタイマーが切れてれば爆発をOFF
	if (m_pExplosionTimer->IsTime())
	{
		//爆発をOFF
		explosionOnOff = false;
		delete m_pExplosion;
		m_pExplosion = nullptr;
	}
	//プレイヤー球発射
	if (m_pPlayer->isFire)
	{
		//バレットを生成
		CreateBullet();
		m_pPlayer->isFire = false;
	}
	
	//shotEnemys球発射
	std::list<BulletShotEnemy*>::iterator BSE_iter = m_BulletShotEnemys.begin();
	while (BSE_iter != m_BulletShotEnemys.end())
	{
		if ((*BSE_iter)->IsFire)
		{
			testint++;
			
			//printf("TEST %d", testint);
			//球の生成
			CreateEnemyBullet(vec2((*BSE_iter)->m_position.x, (*BSE_iter)->m_position.y), (*BSE_iter)->m_Enemydirection);
			(*BSE_iter)->IsFire = false;
		}
		else
			BSE_iter++;
	}
	//shotEnemys球発射
	std::list<BossEnemy*>::iterator BSBE_iter = m_BossEnemys.begin();
	while (BSBE_iter != m_BossEnemys.end())
	{
		//球を発射
		if ((*BSBE_iter)->IsFire)
		{
			testint++;

			//printf("TEST %d", testint);
			//球を8発生成
			for (int i = 0; i < 8; i++)
			{
				CreateBossEnemyBullet(vec2((*BSBE_iter)->m_position.x+RandomFloat(3.f,80.f), (*BSBE_iter)->m_position.y - RandomFloat(1.f, 192.f)), (*BSBE_iter)->m_BEnemydirection);
			}
			(*BSBE_iter)->IsFire = false;
		}
		else
			BSBE_iter++;
	}

	//敵の球のイテレーターを作る
	std::list<Bullet *>::iterator EBUpdate_iter = m_EnemyBullets.begin();
	while (EBUpdate_iter != m_EnemyBullets.end())
	{
		(*EBUpdate_iter)->Update();
		//球の無いまたは当たったら
		if ((*EBUpdate_iter)->m_countLife <= 0 || (*EBUpdate_iter)->m_isCollision)
		{
			Bullet *Del;
			Del = *EBUpdate_iter;
			(*EBUpdate_iter)->m_isCollision = false;
			EBUpdate_iter = m_EnemyBullets.erase(EBUpdate_iter);//この*iteraの球を消去する
			//バレットを消去する
			delete Del;
			Del = nullptr;
		}
		else
			EBUpdate_iter++;
	}
	//BOSS敵の球のイテレーターを作る
	std::list<Bullet *>::iterator EBBUpdate_iter = m_BossEnemyBullet.begin();
	while (EBBUpdate_iter != m_BossEnemyBullet.end())
	{
		//球のアップデート
		(*EBBUpdate_iter)->Update();
		//球の生存がしてて当たった場合
		if ((*EBBUpdate_iter)->m_countLife <= 0 || (*EBBUpdate_iter)->m_isCollision)
		{
			
			Bullet *Del;
			Del = *EBBUpdate_iter;

			(*EBBUpdate_iter)->m_isCollision = false;
			EBBUpdate_iter = m_BossEnemyBullet.erase(EBBUpdate_iter);//この*iteraの球を消去する
			//バレットを消去する
			delete Del;
			Del = nullptr;
		}
		else
			EBBUpdate_iter++;
	}
	//バレットのイテレーターを作る
	std::list<Bullet *>::iterator itera = m_PlayerBullets.begin();

	//iteraがバレットendじゃない時まで回す
	while (itera != m_PlayerBullets.end())
	{
		(*itera)->Update();
		//printf("bullet X %f,Y %f \n", (*itera)->getPosition().x, (*itera)->getPosition().y);
		//printf("b_bullet X %f, Y %f \n", newBullet.getPosition().x, newBullet.getPosition().y);
		//printf("testini : %d\n", testint++);

		//もしカウントレフトが0以下だったら
		if ((*itera)->m_countLife <= 0 || (*itera)->m_isCollision)
		{
			Bullet *Del;
			Del = *itera;
			(*itera)->m_isCollision = false;
			itera = m_PlayerBullets.erase(itera);//この*iteraの球を消去する
			//バレットを消去する
			delete Del;
			Del = nullptr;
		}
		else
			itera++;
	}
}

void CHARACTERMANAGER::Draw()
{
	m_pPlayer->Draw();
	//m_pPlayer->DrawWire();
	if (explosionOnOff == true)
	{
		m_pExplosion->Draw();
	}
	
	// Enemy Draw
	std::list<Enemy *>::iterator iterDrawEnemy = m_Enemys.begin();
	while (iterDrawEnemy != m_Enemys.end())
	{
		//描画
		(*iterDrawEnemy)->Draw();
		iterDrawEnemy++;
	}
	// BulletShotEnemy Draw
	std::list<BulletShotEnemy *>::iterator BulletShotEnemyDraw = m_BulletShotEnemys.begin();
	while (BulletShotEnemyDraw != m_BulletShotEnemys.end())
	{
		//描画
		(*BulletShotEnemyDraw)->Draw();
		BulletShotEnemyDraw++;
	}
	//Bossバレットのイテレーター
	std::list<BossEnemy *>::iterator IterDrawBossEnemy = m_BossEnemys.begin();
	while (IterDrawBossEnemy != m_BossEnemys.end())
	{
		//描画
		(*IterDrawBossEnemy)->Draw();
		IterDrawBossEnemy++;
	}
	//プレイヤーバレットのイテレーター
	Bullet_iter = m_PlayerBullets.begin();
	while (Bullet_iter != m_PlayerBullets.end())
	{
		//描画
		(*Bullet_iter)->Draw();
		Bullet_iter++;
	}
	//敵バレットのイテレーター
	Bullet_iter = m_EnemyBullets.begin();
	while (Bullet_iter != m_EnemyBullets.end())
	{
		//描画
		(*Bullet_iter)->Draw();
		Bullet_iter++;
	}
	//Boss敵バレットのイテレーター
	Bullet_iter = m_BossEnemyBullet.begin();
	while (Bullet_iter !=m_BossEnemyBullet.end())
	{
		//描画
		(*Bullet_iter)->Draw();
		Bullet_iter++;
	}
	//文字の描画
	
	FontBegin();
	FontSize (32,32);
	FontPosition(0, 0);
	FontDraw("HP :%d\n", m_pPlayer->m_PlayerHP);
	//FontDraw("TIMER :  %f\n", m_pTimer->Now());
	//FontDraw("TIMER2 :  %f\n", m_pExplosionTimer->Now());
	//FontDraw("X : %f\n Y : %f \n", m_pPlayer->m_position.x, m_pPlayer->m_position.y);

	std::list<BossEnemy *>::iterator IterDrawBoss = m_BossEnemys.begin();
	while (IterDrawBoss != m_BossEnemys.end())
	{
		//描画
		FontPosition(310,0);
		FontDraw("BOSS HP:%d\n", (*IterDrawBoss)->GetHP());
		IterDrawBoss++;
	}
	
}

void CHARACTERMANAGER::Collision()
{
	//敵のイテレーター
	std::list<Enemy *>::iterator C_EnemyIter = m_Enemys.begin();
	while (C_EnemyIter != m_Enemys.end())
	{
		//敵と自機の当たり判定
		if ((*C_EnemyIter)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//デバック
			//printf("Atatta");

			//プレイヤーのHPを１0減らす
			m_pPlayer->damege();
			//プレイヤーの位置をずらす
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//当たったら点滅
			//一致するビットが一つでもあれば描画
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//無敵開始
			muteki = true;
			//時間は約3秒
			m_pTimer->SetTimer(1);
		}
		C_EnemyIter++;
	}
	//BulletShotEnemyのイテレーター
	std::list<BulletShotEnemy *>::iterator C_BulletShot = m_BulletShotEnemys.begin();
	while (C_BulletShot != m_BulletShotEnemys.end())
	{
		//敵と自機の当たり判定
		if ((*C_BulletShot)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//デバック
			//printf("Atatta");

			//プレイヤーのHPを１0減らす
			m_pPlayer->damege();
			//プレイヤーの位置をずらす
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//当たったら点滅
			//一致するビットが一つでもあれば描画
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//無敵開始
			muteki = true;
			//時間は約3秒
			m_pTimer->SetTimer(1);
		}
		C_BulletShot++;
	}
	//BOSSのイテレーター
	std::list<BossEnemy *>::iterator C_BossEnemyIter = m_BossEnemys.begin();
	while (C_BossEnemyIter != m_BossEnemys.end())
	{
		//敵と自機の当たり判定
		if ((*C_BossEnemyIter)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//デバック
			//printf("Atatta");

			//プレイヤーのHPを１0減らす
			m_pPlayer->damege();
			//プレイヤーの位置をずらす
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//当たったら点滅
			//一致するビットが一つでもあれば描画
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//無敵開始
			muteki = true;
			//時間は約3秒
			m_pTimer->SetTimer(1);
		}
		C_BossEnemyIter++;
	}
	//敵球のイテレーター
	std::list<Bullet *>::iterator EBCollision_iter = m_EnemyBullets.begin();
	while (EBCollision_iter != m_EnemyBullets.end())
	{
		//球と敵の当たり判定
		if ((*EBCollision_iter)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//デバック
			//printf("Atatta");
			//球の当たり判定
			(*EBCollision_iter)->m_isCollision = true;
			//プレイヤーのHPを１0減らす
			m_pPlayer->damege();
			//プレイヤーの位置をずらす
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//当たったら点滅
			//一致するビットが一つでもあれば描画
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//無敵開始
			muteki = true;
			//時間は約3秒
			m_pTimer->SetTimer(1);
		}
		EBCollision_iter++;
	}
	//敵球のイテレーター
	std::list<Bullet *>::iterator EBBCollision_iter = m_BossEnemyBullet.begin();
	while (EBBCollision_iter != m_BossEnemyBullet.end())
	{
		//球と敵の当たり判定
		if ((*EBBCollision_iter)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//デバック
			//printf("Atatta");
			//球の当たり判定
			(*EBBCollision_iter)->m_isCollision = true;
			//プレイヤーのHPを１0減らす
			m_pPlayer->damege();
			//プレイヤーの位置をずらす
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//当たったら点滅
			//一致するビットが一つでもあれば描画
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//無敵開始
			muteki = true;
			//時間は約3秒
			m_pTimer->SetTimer(1);
		}
		EBBCollision_iter++;
	}

	//自機球のイテレーター
	for (std::list<Bullet *>::iterator bulletIter = m_PlayerBullets.begin(); bulletIter != m_PlayerBullets.end(); bulletIter++)
	{
		for (std::list<Enemy *>::iterator enemyIter = m_Enemys.begin(); enemyIter != m_Enemys.end(); enemyIter++)
		{
			//球と敵の当たり判定
			if ((*bulletIter)->Intersect(*(*enemyIter)) == true || (*enemyIter)->Intersect(*(*bulletIter)) == true)
			{
				(*bulletIter)->m_isCollision = true;
				(*enemyIter)->Damage();
			}
		}
		for (std::list<BulletShotEnemy *>::iterator BulletEnemyIter = m_BulletShotEnemys.begin(); BulletEnemyIter != m_BulletShotEnemys.end(); BulletEnemyIter++)
		{
			//球と敵の当たり判定
			if ((*bulletIter)->Intersect(*(*BulletEnemyIter)) == true || (*BulletEnemyIter)->Intersect(*(*bulletIter)) == true)
			{
				(*bulletIter)->m_isCollision = true;
				(*BulletEnemyIter)->Damage();
			}
		}
		for (std::list<BossEnemy *>::iterator BossEnemyIter = m_BossEnemys.begin(); BossEnemyIter != m_BossEnemys.end(); BossEnemyIter++)
		{
			//球と敵の当たり判定
			if ((*bulletIter)->Intersect(*(*BossEnemyIter)) == true || (*BossEnemyIter)->Intersect(*(*bulletIter)) == true)
			{
				(*bulletIter)->m_isCollision = true;
				(*BossEnemyIter)->Damage();
			}
		}

	}
}

void CHARACTERMANAGER::CreateBullet()
{
	//バレット生成
	Bullet *cNewBullet = new Bullet{};
	//バレット初期化
	cNewBullet->Init();

	//バレットの位置は自機の位置
	if (m_pPlayer->m_direction == 0)
	{
		cNewBullet->setPosition(vec2(m_pPlayer->m_position.x + 8, m_pPlayer->m_position.y + 12));
		cNewBullet->setDir(0);//右向き
	}
	else if (m_pPlayer->m_direction == 1)
	{
		cNewBullet->setPosition(vec2(m_pPlayer->m_position.x - 8, m_pPlayer->m_position.y + 12));
		cNewBullet->setDir(1);//左向き
	}
	//末尾にデータを入れる
	m_PlayerBullets.push_back(cNewBullet);
}


void CHARACTERMANAGER::CreateEnemyBullet(vec2 _position, int dir)
{

	//バレット生成
	Bullet *pNewEBullet = new Bullet{};
	//バレット初期化
	pNewEBullet->Init();
	//球のスピード
	pNewEBullet->m_speed = RandomFloat(0.2f, 0.5f);

	//球の向き
	if (dir == 0)
	{
		pNewEBullet->setPosition(vec2(_position.x + 1.f, _position.y + 12.f));
		pNewEBullet->setDir(0);//右向き
	}
	else if (dir == 1)
	{
		pNewEBullet->setPosition(vec2(_position.x-1.f, _position.y+12.f));
		pNewEBullet->setDir(1);//左向き
	}

	//末尾にデータを入れる
	m_EnemyBullets.push_back(pNewEBullet);
}

void CHARACTERMANAGER::CreateBossEnemyBullet(vec2 _position, int dir)
{
	//バレット生成
	Bullet *pNewBEBullet = new Bullet{};

	//バレット初期化
	pNewBEBullet->Init();

	//球のスピード
	pNewBEBullet->m_speed =0.12f;

	pNewBEBullet->m_countLife = 2000;

	//球の向き
	if (dir == 0)
	{
		pNewBEBullet->setPosition(vec2(_position.x + 1.0f, _position.y + 12.f));
		pNewBEBullet->setDir(0);//右向き
	}
	else if(dir==1)
	{
		pNewBEBullet->setPosition(vec2(_position.x - 1.0f, _position.y + 12.0f));
		pNewBEBullet->setDir(1);
	}
	//末尾にデータを入れる
		m_BossEnemyBullet.push_back(pNewBEBullet);
	
}

void CHARACTERMANAGER::SetEnemy(const char*_fileName, vec2 _size, vec2 _position, int _hp)
{
	//エネミーを生成
	Enemy *NewEnemy = new Enemy();

	//ファイルの名前、敵の大きさ、位置、体力を設定
	NewEnemy->Init(_fileName, _size, _position, _hp);
	//エネミーリストの末尾に入れる
	m_Enemys.push_back(NewEnemy);
}

void CHARACTERMANAGER::SetBossEnemy(const char * _fileName, vec2 _size, vec2 _position, int _hp)
{
	//Bossキャラを生成
	BossEnemy *NewBossEnemy = new BossEnemy();
	//Bossキャラ初期化
	NewBossEnemy->Init(_fileName, _size, _position, _hp);
	//Bossキャラを末尾に置く
	m_BossEnemys.push_back(NewBossEnemy);
}
void CHARACTERMANAGER::SetBulletShotEnemy(const char * _fileName, vec2 _size, vec2 _position, int _hp)
{
	//打つ敵キャラを生成
	BulletShotEnemy *NewBulletShotEnemy = new BulletShotEnemy();
	//打つ敵キャラを初期化
	NewBulletShotEnemy->Init(_fileName, _size, _position, _hp);
	//打つ敵キャラを末尾おく
	m_BulletShotEnemys.push_back(NewBulletShotEnemy);
}
void CHARACTERMANAGER::CreateExplosion(vec2 _enemyPos)
{
	////爆発を生成
	m_pExplosion = new Explosion();
	////爆発の初期化
	m_pExplosion->Init();
	//m_pExplosion->Update();
	////爆発の位置を指定
	m_pExplosion->SetPosition(_enemyPos);
}




