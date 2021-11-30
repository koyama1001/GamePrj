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
	//�f�[�^����
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pTimer;
	m_pTimer = nullptr;
	delete m_pExplosionTimer;
	m_pExplosionTimer = nullptr;

	//�G�̃��X�g�̒��g������
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
	//�G�̃��X�g�̒��g������
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

	//Boss�̃��X�g�̒��g������
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

	m_pPlayer->Init();//�v���C���[��������
	m_pTimer->init();//�v���C���[�^�C�}�[��������
	m_pExplosionTimer->init();//�����^�C�}�[��������

	//Bullets
	m_PlayerBullets.clear();//������
	m_EnemyBullets.clear();//������

	//Enemy
	m_Enemys.clear();//������
	m_BossEnemys.clear();//������
	m_BulletShotEnemys.clear();//������

	muteki = false;
	explosionOnOff = false;

	//�G�̉摜�A�傫���A���W�A�̗͂��w��
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(120.f, 135.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(500.f, 135.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(600.f, 135.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(800.f, 105.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(1080.f, 152.f),4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(1320.f, 72.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(2110.f, 40.f), 4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(2400.f, 104.f),4);
	SetEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(2710.f, 152.f),4);
	//�łG�̉摜�A�傫���A���W�A�̗͂��w��
	SetBulletShotEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(260.f, 75.f) ,4);
	SetBulletShotEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(800.f, 105.f),4);
	//�{�X�L�����̉摜�A�傫���A���W�A�̗͂��w��												 
	SetBossEnemy("Enemy\\WalkEnemy.bmp", vec2(ENEMY_SIZE, ENEMY_SIZE), vec2(3180.f, 215.f), 50);
}
//���̑��x
float RandomFloat(float a, float b)
{
	//0�`1�̃����_������
	float random = ((float)rand()) / (float)RAND_MAX;

	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void CHARACTERMANAGER::Update()
{
	////�v���C���[�̗̑͂�0�ɂȂ��������
	//if (m_pPlayer->m_PlayerHP == 0)
	//	delete m_pPlayer;



	m_pPlayer->Update();//�X�V
	m_pTimer->Update();//�X�V
	m_pExplosionTimer->Update();//�X�V

	//printf("%f:Timer\n", m_Timer->Now());

	// enemys Update
	std::list<Enemy *>::iterator EnemyUpdate_iter = m_Enemys.begin();
	while (EnemyUpdate_iter != m_Enemys.end())
	{
		Enemy *del;
		//�G�l�~�[�C�e���[�^�[�A�b�v�f�[�g
		(*EnemyUpdate_iter)->Update();

		//�G�̗̑͂�0�Ȃ�
		if ((*EnemyUpdate_iter)->GetHP() == 0)
		{
			//�����@�G�̈ʒu�擾
			CreateExplosion((*EnemyUpdate_iter)->m_position);
			//�����@�t���O�@ON
			explosionOnOff = true;
			//���Ԑݒ�
			m_pExplosionTimer->SetTimer(1);

			//�C�e���[�^�[������
			del = *EnemyUpdate_iter;
			EnemyUpdate_iter = m_Enemys.erase(EnemyUpdate_iter);
			//�G������
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
		//�G�l�~�[�C�e���[�^�[�A�b�v�f�[�g
		(*BSE_Update_iter)->Update();

		//�G�̗̑͂�0�Ȃ�
		if ((*BSE_Update_iter)->GetHP() == 0)
		{
			//�����@�G�̈ʒu�擾
			CreateExplosion((*BSE_Update_iter)->m_position);
			//�����@�t���O�@ON
			explosionOnOff = true;
			//���Ԑݒ�
			m_pExplosionTimer->SetTimer(1);

			//�C�e���[�^�[������
			del = *BSE_Update_iter;
			BSE_Update_iter = m_BulletShotEnemys.erase(BSE_Update_iter);
			//�G������
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
		//�G�l�~�[�C�e���[�^�[�A�b�v�f�[�g
		(*BossUpdater)->Update();

		//�G�̗̑͂�0�Ȃ�
		if ((*BossUpdater)->GetHP() == 0)
		{
			//�����@�G�̈ʒu�擾
			CreateExplosion((*BossUpdater)->m_position);
			//�����@�t���O�@ON
			explosionOnOff = true;
			//���Ԑݒ�
			m_pExplosionTimer->SetTimer(1);

			//�C�e���[�^�[������
			Del = *BossUpdater;
			BossUpdater = m_BossEnemys.erase(BossUpdater);
			//�G������
			delete Del;
			Del = nullptr;
		}
		else BossUpdater++;
	}
	//�����蔻��
	Collision();

	//�����^�C�}�[���؂�Ă�Ζ��G��OFF
	if (m_pTimer->IsTime())
		muteki = false;
	//�����^�C�}�[���؂�Ă�Δ�����OFF
	if (m_pExplosionTimer->IsTime())
	{
		//������OFF
		explosionOnOff = false;
		delete m_pExplosion;
		m_pExplosion = nullptr;
	}
	//�v���C���[������
	if (m_pPlayer->isFire)
	{
		//�o���b�g�𐶐�
		CreateBullet();
		m_pPlayer->isFire = false;
	}
	
	//shotEnemys������
	std::list<BulletShotEnemy*>::iterator BSE_iter = m_BulletShotEnemys.begin();
	while (BSE_iter != m_BulletShotEnemys.end())
	{
		if ((*BSE_iter)->IsFire)
		{
			testint++;
			
			//printf("TEST %d", testint);
			//���̐���
			CreateEnemyBullet(vec2((*BSE_iter)->m_position.x, (*BSE_iter)->m_position.y), (*BSE_iter)->m_Enemydirection);
			(*BSE_iter)->IsFire = false;
		}
		else
			BSE_iter++;
	}
	//shotEnemys������
	std::list<BossEnemy*>::iterator BSBE_iter = m_BossEnemys.begin();
	while (BSBE_iter != m_BossEnemys.end())
	{
		//���𔭎�
		if ((*BSBE_iter)->IsFire)
		{
			testint++;

			//printf("TEST %d", testint);
			//����8������
			for (int i = 0; i < 8; i++)
			{
				CreateBossEnemyBullet(vec2((*BSBE_iter)->m_position.x+RandomFloat(3.f,80.f), (*BSBE_iter)->m_position.y - RandomFloat(1.f, 192.f)), (*BSBE_iter)->m_BEnemydirection);
			}
			(*BSBE_iter)->IsFire = false;
		}
		else
			BSBE_iter++;
	}

	//�G�̋��̃C�e���[�^�[�����
	std::list<Bullet *>::iterator EBUpdate_iter = m_EnemyBullets.begin();
	while (EBUpdate_iter != m_EnemyBullets.end())
	{
		(*EBUpdate_iter)->Update();
		//���̖����܂��͓���������
		if ((*EBUpdate_iter)->m_countLife <= 0 || (*EBUpdate_iter)->m_isCollision)
		{
			Bullet *Del;
			Del = *EBUpdate_iter;
			(*EBUpdate_iter)->m_isCollision = false;
			EBUpdate_iter = m_EnemyBullets.erase(EBUpdate_iter);//����*itera�̋�����������
			//�o���b�g����������
			delete Del;
			Del = nullptr;
		}
		else
			EBUpdate_iter++;
	}
	//BOSS�G�̋��̃C�e���[�^�[�����
	std::list<Bullet *>::iterator EBBUpdate_iter = m_BossEnemyBullet.begin();
	while (EBBUpdate_iter != m_BossEnemyBullet.end())
	{
		//���̃A�b�v�f�[�g
		(*EBBUpdate_iter)->Update();
		//���̐��������Ăē��������ꍇ
		if ((*EBBUpdate_iter)->m_countLife <= 0 || (*EBBUpdate_iter)->m_isCollision)
		{
			
			Bullet *Del;
			Del = *EBBUpdate_iter;

			(*EBBUpdate_iter)->m_isCollision = false;
			EBBUpdate_iter = m_BossEnemyBullet.erase(EBBUpdate_iter);//����*itera�̋�����������
			//�o���b�g����������
			delete Del;
			Del = nullptr;
		}
		else
			EBBUpdate_iter++;
	}
	//�o���b�g�̃C�e���[�^�[�����
	std::list<Bullet *>::iterator itera = m_PlayerBullets.begin();

	//itera���o���b�gend����Ȃ����܂ŉ�
	while (itera != m_PlayerBullets.end())
	{
		(*itera)->Update();
		//printf("bullet X %f,Y %f \n", (*itera)->getPosition().x, (*itera)->getPosition().y);
		//printf("b_bullet X %f, Y %f \n", newBullet.getPosition().x, newBullet.getPosition().y);
		//printf("testini : %d\n", testint++);

		//�����J�E���g���t�g��0�ȉ���������
		if ((*itera)->m_countLife <= 0 || (*itera)->m_isCollision)
		{
			Bullet *Del;
			Del = *itera;
			(*itera)->m_isCollision = false;
			itera = m_PlayerBullets.erase(itera);//����*itera�̋�����������
			//�o���b�g����������
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
		//�`��
		(*iterDrawEnemy)->Draw();
		iterDrawEnemy++;
	}
	// BulletShotEnemy Draw
	std::list<BulletShotEnemy *>::iterator BulletShotEnemyDraw = m_BulletShotEnemys.begin();
	while (BulletShotEnemyDraw != m_BulletShotEnemys.end())
	{
		//�`��
		(*BulletShotEnemyDraw)->Draw();
		BulletShotEnemyDraw++;
	}
	//Boss�o���b�g�̃C�e���[�^�[
	std::list<BossEnemy *>::iterator IterDrawBossEnemy = m_BossEnemys.begin();
	while (IterDrawBossEnemy != m_BossEnemys.end())
	{
		//�`��
		(*IterDrawBossEnemy)->Draw();
		IterDrawBossEnemy++;
	}
	//�v���C���[�o���b�g�̃C�e���[�^�[
	Bullet_iter = m_PlayerBullets.begin();
	while (Bullet_iter != m_PlayerBullets.end())
	{
		//�`��
		(*Bullet_iter)->Draw();
		Bullet_iter++;
	}
	//�G�o���b�g�̃C�e���[�^�[
	Bullet_iter = m_EnemyBullets.begin();
	while (Bullet_iter != m_EnemyBullets.end())
	{
		//�`��
		(*Bullet_iter)->Draw();
		Bullet_iter++;
	}
	//Boss�G�o���b�g�̃C�e���[�^�[
	Bullet_iter = m_BossEnemyBullet.begin();
	while (Bullet_iter !=m_BossEnemyBullet.end())
	{
		//�`��
		(*Bullet_iter)->Draw();
		Bullet_iter++;
	}
	//�����̕`��
	
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
		//�`��
		FontPosition(310,0);
		FontDraw("BOSS HP:%d\n", (*IterDrawBoss)->GetHP());
		IterDrawBoss++;
	}
	
}

void CHARACTERMANAGER::Collision()
{
	//�G�̃C�e���[�^�[
	std::list<Enemy *>::iterator C_EnemyIter = m_Enemys.begin();
	while (C_EnemyIter != m_Enemys.end())
	{
		//�G�Ǝ��@�̓����蔻��
		if ((*C_EnemyIter)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//�f�o�b�N
			//printf("Atatta");

			//�v���C���[��HP���P0���炷
			m_pPlayer->damege();
			//�v���C���[�̈ʒu�����炷
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//����������_��
			//��v����r�b�g����ł�����Ε`��
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//���G�J�n
			muteki = true;
			//���Ԃ͖�3�b
			m_pTimer->SetTimer(1);
		}
		C_EnemyIter++;
	}
	//BulletShotEnemy�̃C�e���[�^�[
	std::list<BulletShotEnemy *>::iterator C_BulletShot = m_BulletShotEnemys.begin();
	while (C_BulletShot != m_BulletShotEnemys.end())
	{
		//�G�Ǝ��@�̓����蔻��
		if ((*C_BulletShot)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//�f�o�b�N
			//printf("Atatta");

			//�v���C���[��HP���P0���炷
			m_pPlayer->damege();
			//�v���C���[�̈ʒu�����炷
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//����������_��
			//��v����r�b�g����ł�����Ε`��
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//���G�J�n
			muteki = true;
			//���Ԃ͖�3�b
			m_pTimer->SetTimer(1);
		}
		C_BulletShot++;
	}
	//BOSS�̃C�e���[�^�[
	std::list<BossEnemy *>::iterator C_BossEnemyIter = m_BossEnemys.begin();
	while (C_BossEnemyIter != m_BossEnemys.end())
	{
		//�G�Ǝ��@�̓����蔻��
		if ((*C_BossEnemyIter)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//�f�o�b�N
			//printf("Atatta");

			//�v���C���[��HP���P0���炷
			m_pPlayer->damege();
			//�v���C���[�̈ʒu�����炷
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//����������_��
			//��v����r�b�g����ł�����Ε`��
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//���G�J�n
			muteki = true;
			//���Ԃ͖�3�b
			m_pTimer->SetTimer(1);
		}
		C_BossEnemyIter++;
	}
	//�G���̃C�e���[�^�[
	std::list<Bullet *>::iterator EBCollision_iter = m_EnemyBullets.begin();
	while (EBCollision_iter != m_EnemyBullets.end())
	{
		//���ƓG�̓����蔻��
		if ((*EBCollision_iter)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//�f�o�b�N
			//printf("Atatta");
			//���̓����蔻��
			(*EBCollision_iter)->m_isCollision = true;
			//�v���C���[��HP���P0���炷
			m_pPlayer->damege();
			//�v���C���[�̈ʒu�����炷
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//����������_��
			//��v����r�b�g����ł�����Ε`��
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//���G�J�n
			muteki = true;
			//���Ԃ͖�3�b
			m_pTimer->SetTimer(1);
		}
		EBCollision_iter++;
	}
	//�G���̃C�e���[�^�[
	std::list<Bullet *>::iterator EBBCollision_iter = m_BossEnemyBullet.begin();
	while (EBBCollision_iter != m_BossEnemyBullet.end())
	{
		//���ƓG�̓����蔻��
		if ((*EBBCollision_iter)->Intersect(*m_pPlayer) == true && muteki == false)
		{
			//�f�o�b�N
			//printf("Atatta");
			//���̓����蔻��
			(*EBBCollision_iter)->m_isCollision = true;
			//�v���C���[��HP���P0���炷
			m_pPlayer->damege();
			//�v���C���[�̈ʒu�����炷
			if (m_pPlayer->m_direction == 0)
				m_pPlayer->m_position += vec2(-20, -30);
			if (m_pPlayer->m_direction = 1)
				m_pPlayer->m_position += vec2(+20, -30);

			//����������_��
			//��v����r�b�g����ł�����Ε`��
			//if (m_DrawCount & m_BlinkMask)
			//{
			//	m_pPlayer->Draw();
			//}
			//++m_DrawCount;

			//���G�J�n
			muteki = true;
			//���Ԃ͖�3�b
			m_pTimer->SetTimer(1);
		}
		EBBCollision_iter++;
	}

	//���@���̃C�e���[�^�[
	for (std::list<Bullet *>::iterator bulletIter = m_PlayerBullets.begin(); bulletIter != m_PlayerBullets.end(); bulletIter++)
	{
		for (std::list<Enemy *>::iterator enemyIter = m_Enemys.begin(); enemyIter != m_Enemys.end(); enemyIter++)
		{
			//���ƓG�̓����蔻��
			if ((*bulletIter)->Intersect(*(*enemyIter)) == true || (*enemyIter)->Intersect(*(*bulletIter)) == true)
			{
				(*bulletIter)->m_isCollision = true;
				(*enemyIter)->Damage();
			}
		}
		for (std::list<BulletShotEnemy *>::iterator BulletEnemyIter = m_BulletShotEnemys.begin(); BulletEnemyIter != m_BulletShotEnemys.end(); BulletEnemyIter++)
		{
			//���ƓG�̓����蔻��
			if ((*bulletIter)->Intersect(*(*BulletEnemyIter)) == true || (*BulletEnemyIter)->Intersect(*(*bulletIter)) == true)
			{
				(*bulletIter)->m_isCollision = true;
				(*BulletEnemyIter)->Damage();
			}
		}
		for (std::list<BossEnemy *>::iterator BossEnemyIter = m_BossEnemys.begin(); BossEnemyIter != m_BossEnemys.end(); BossEnemyIter++)
		{
			//���ƓG�̓����蔻��
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
	//�o���b�g����
	Bullet *cNewBullet = new Bullet{};
	//�o���b�g������
	cNewBullet->Init();

	//�o���b�g�̈ʒu�͎��@�̈ʒu
	if (m_pPlayer->m_direction == 0)
	{
		cNewBullet->setPosition(vec2(m_pPlayer->m_position.x + 8, m_pPlayer->m_position.y + 12));
		cNewBullet->setDir(0);//�E����
	}
	else if (m_pPlayer->m_direction == 1)
	{
		cNewBullet->setPosition(vec2(m_pPlayer->m_position.x - 8, m_pPlayer->m_position.y + 12));
		cNewBullet->setDir(1);//������
	}
	//�����Ƀf�[�^������
	m_PlayerBullets.push_back(cNewBullet);
}


void CHARACTERMANAGER::CreateEnemyBullet(vec2 _position, int dir)
{

	//�o���b�g����
	Bullet *pNewEBullet = new Bullet{};
	//�o���b�g������
	pNewEBullet->Init();
	//���̃X�s�[�h
	pNewEBullet->m_speed = RandomFloat(0.2f, 0.5f);

	//���̌���
	if (dir == 0)
	{
		pNewEBullet->setPosition(vec2(_position.x + 1.f, _position.y + 12.f));
		pNewEBullet->setDir(0);//�E����
	}
	else if (dir == 1)
	{
		pNewEBullet->setPosition(vec2(_position.x-1.f, _position.y+12.f));
		pNewEBullet->setDir(1);//������
	}

	//�����Ƀf�[�^������
	m_EnemyBullets.push_back(pNewEBullet);
}

void CHARACTERMANAGER::CreateBossEnemyBullet(vec2 _position, int dir)
{
	//�o���b�g����
	Bullet *pNewBEBullet = new Bullet{};

	//�o���b�g������
	pNewBEBullet->Init();

	//���̃X�s�[�h
	pNewBEBullet->m_speed =0.12f;

	pNewBEBullet->m_countLife = 2000;

	//���̌���
	if (dir == 0)
	{
		pNewBEBullet->setPosition(vec2(_position.x + 1.0f, _position.y + 12.f));
		pNewBEBullet->setDir(0);//�E����
	}
	else if(dir==1)
	{
		pNewBEBullet->setPosition(vec2(_position.x - 1.0f, _position.y + 12.0f));
		pNewBEBullet->setDir(1);
	}
	//�����Ƀf�[�^������
		m_BossEnemyBullet.push_back(pNewBEBullet);
	
}

void CHARACTERMANAGER::SetEnemy(const char*_fileName, vec2 _size, vec2 _position, int _hp)
{
	//�G�l�~�[�𐶐�
	Enemy *NewEnemy = new Enemy();

	//�t�@�C���̖��O�A�G�̑傫���A�ʒu�A�̗͂�ݒ�
	NewEnemy->Init(_fileName, _size, _position, _hp);
	//�G�l�~�[���X�g�̖����ɓ����
	m_Enemys.push_back(NewEnemy);
}

void CHARACTERMANAGER::SetBossEnemy(const char * _fileName, vec2 _size, vec2 _position, int _hp)
{
	//Boss�L�����𐶐�
	BossEnemy *NewBossEnemy = new BossEnemy();
	//Boss�L����������
	NewBossEnemy->Init(_fileName, _size, _position, _hp);
	//Boss�L�����𖖔��ɒu��
	m_BossEnemys.push_back(NewBossEnemy);
}
void CHARACTERMANAGER::SetBulletShotEnemy(const char * _fileName, vec2 _size, vec2 _position, int _hp)
{
	//�łG�L�����𐶐�
	BulletShotEnemy *NewBulletShotEnemy = new BulletShotEnemy();
	//�łG�L������������
	NewBulletShotEnemy->Init(_fileName, _size, _position, _hp);
	//�łG�L�����𖖔�����
	m_BulletShotEnemys.push_back(NewBulletShotEnemy);
}
void CHARACTERMANAGER::CreateExplosion(vec2 _enemyPos)
{
	////�����𐶐�
	m_pExplosion = new Explosion();
	////�����̏�����
	m_pExplosion->Init();
	//m_pExplosion->Update();
	////�����̈ʒu���w��
	m_pExplosion->SetPosition(_enemyPos);
}




