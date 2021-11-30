#include "Player.h"
#include "Header.h"

Player::Player() :
	m_animationController{},
	m_textureIndex{},
	m_bound{},
	m_combindBound{},
	m_speed{},
	m_rightPoint{},
	m_leftPoint{},
	m_bottomPoint{},
	m_topPoint{},
	m_PlayerHP{ 100 },
	m_jumping{},
	m_falling{},
	m_JumpCount{},
	m_direction{ 0 },
	//m_bullets{},
	m_touch{},
	isFire{}
{}

Player::~Player()
{
	
}

void Player::Init()
{
	//�v���C���[�T�C�Y
	m_size = vec2(PLAYER_SIZE, 32);
	m_touch;
	m_direction;
	m_PlayerHP;
	isFire = false;
	//m_bullets.clear();

}

void Player::Update()
{
	//�A�j���[�V�����R���g���[���[���擾���ăA�b�v�f�[�g
	AnimationController &ac = m_animationController;

	ac.Update();

	

	////�o���b�g�̃C�e���[�^�[�����
	//std::list<Bullet *>::iterator itera = m_bullets.begin();

	////itera���o���b�gend����Ȃ����܂ŉ�
	//while (itera != m_bullets.end())
	//{
	//	(*itera)->Update();
	//	//printf("bullet X %f,Y %f \n", (*itera)->getPosition().x, (*itera)->getPosition().y);
	//	//printf("b_bullet X %f, Y %f \n", newBullet.getPosition().x, newBullet.getPosition().y);
	//	//printf("testini : %d\n", testint++);
	//	
	//	//�����J�E���g���t�g��0�ȉ���������
	//	if ((*itera)->m_countLife <= 0 || (*itera)->m_isCollision)
	//	{
	//		Bullet *Del;
	//		Del = *itera;
	//		itera = m_bullets.erase(itera);//����*itera�̋�����������
	//		//�o���b�g����������
	//		delete Del;
	//	}
	//	else
	//		itera++;
	//}



	//�v���C���[�̑��x
	float acceleration = 0.018f;
	//�v���C���[�̈ړ�
	if (Keyboard::m_pressedKey[PLAYER_KEY_LEFT])
	{
		m_direction = 1;
		m_speed.x -= acceleration;
	}
	if (Keyboard::m_pressedKey[PLAYER_KEY_RIGHT])
	{
		m_direction = 0;
		m_speed.x += acceleration;
	}
	//�X�y�[�X��������Ă��󒆂ɂ��Ȃ���΃W�����v����
	if (Keyboard::m_nowPressedKey[PLAYER_KEY_JUMP] && (!m_falling))
	{
		m_jumping = m_falling = true;
		m_JumpCount = 0;
		ac.SetAnimation(UNITYCHAN_ANIMATION_JUMP_UP);
	}

	//�����łL�[���������Ȃ�łA�j���[�V����������
	if (Keyboard::m_pressedKey[PLAYER_KEY_BULLET])
	{
		m_flip = m_direction;
		ac.SetAnimation(UNITYCAHN_ANIMATION_GUN);
		//�����������ꂽ�L�[�ł���Ȃ甭�˂���
		if (Keyboard::m_nowPressedKey[PLAYER_KEY_BULLET]) {
			Fire();
		}
	}



	//������True�Ȃ火
	if (m_falling) {
		//�����W�����v��true�Ȃ炙���ɔ��
		if (m_jumping)
		{
			m_speed.y = -.3;
			//�����W�����v�J�E���g��500�ȏ�ɂȂ�����܂��̓X�y�[�X�L�[�������ꂽ��W�����v����߂�
			if ((++m_JumpCount >= PLAYER_JUMP_COUNT_MAX) || (!Keyboard::m_pressedKey[PLAYER_KEY_JUMP]))
			{
				m_jumping = false;
				ac.SetAnimation(UNITYCHAN_ANIMATION_JUMP);
			}
		}
		m_speed.y += 0.02f;
	}//ifEND


	//����
	//m_speed *= .9f;
	{
		//���挩�đł��Ă݂�
		//�Œ菬���_�Ō���
		int one = 0x100;
		ivec2 fixed = m_speed * (float)one;
		fixed = fixed * 0xe8 / one;
		//�Œ菬���_���畂�������_�ɖ߂�
		m_speed = (vec2)fixed / (float)one;
	}


	m_position += m_speed;
	{

		//��ʂ̍��[�Ŏ~�߂� ���ƂŏC��
		float left = g_course.m_scroll - PLAYER_SIZE * 3 / 8;
		if ((m_position.x < left)&& (m_position.x < g_course.m_scroll + SCREEN_WIDTH / 2 - PLAYER_SIZE / 2))
		{
			m_position.x = left;
			g_course.m_scroll += m_speed.x;
			//m_speed.x = 0;
		}
	}
	{

		//�Ƃ肠������ʂ̉E�[�Ŏ~�߂�@�����͏C������
		float right = COURSE_WIDTH * PART_SIZE - PLAYER_SIZE * 5 / 8;
		if (m_position.x > right)
		{
			m_position.x = right;
			m_speed.x = 0;
		}
	}
	//��ʃX�N���[������
	if ((m_speed.x > 0) && (m_position.x > g_course.m_scroll + SCREEN_WIDTH / 2 - PLAYER_SIZE / 2))
	{
		g_course.m_scroll += m_speed.x;

		g_course.m_scroll = min(g_course.m_scroll, (float)(COURSE_WIDTH*PART_SIZE - SCREEN_WIDTH));

	}

	//�A�j���[�V�����؂�ւ�
	switch (ac.m_animation)
	{
	case UNITYCHAN_ANIMATION_IDLE:

		//�X�s�[�h���̐�Βl���O����Ȃ瑖��
		if (fabs(m_speed.x) > 0)
		{
			ac.SetAnimation(UNITYCHAN_ANIMATION_RUN);
			//�X�s�[�h���O���������]����@0����Ȃ牽�����Ȃ�
			m_flip = (m_speed.x < 0) ? RECT_FLIP_HORIZONTAL : RECT_FLIP_NONE;
		}

		if (Keyboard::m_nowPressedKey[PLAYER_KEY_LEFT])
		{

			m_flip = RECT_FLIP_HORIZONTAL;
		}
		if (Keyboard::m_nowPressedKey[PLAYER_KEY_RIGHT])
		{
			m_flip = RECT_FLIP_NONE;
		}


		break;

		//����A�j���[�V�������Ɏ~�߂����
	case UNITYCHAN_ANIMATION_RUN:

		//�X�s�[�h��0���������]����
		if (m_speed.x < 0)
			m_flip = RECT_FLIP_HORIZONTAL;

		//�X�s�[�h��0����Ȃ牽���Ȃ�
		if (m_speed.x > 0)
			m_flip = RECT_FLIP_NONE;

		//�L�[�{�[�h��������ĂȂ����ăX�s�[�h���O�ȉ��Ȃ�u���[�L���[�V����
		if (
			((!Keyboard::m_pressedKey[PLAYER_KEY_LEFT]) && (m_speed.x < 0)) ||
			((!Keyboard::m_pressedKey[PLAYER_KEY_RIGHT]) && (m_speed.x > 0))
			)
			ac.SetAnimation(UNITYCHAN_ANIMATION_BRAKE);

		if (length(m_speed) <= 0)
			ac.SetAnimation(UNITYCHAN_ANIMATION_IDLE);

		break;

	case UNITYCHAN_ANIMATION_BRAKE:

		//�L�[�{�[�h��������ĂȂ����ăX�s�[�h���O�Ȃ�u���[�L���[�V����
		if (
			((!Keyboard::m_pressedKey[PLAYER_KEY_LEFT]) && (m_speed.x < 0.0005)) ||
			((!Keyboard::m_pressedKey[PLAYER_KEY_RIGHT]) && (m_speed.x > 0.0005))
			)
		{
			ac.SetAnimation(UNITYCHAN_ANIMATION_RUN);
			//�����C��������
			//m_flip = Keyboard::m_pressedKey[PLAYER_KEY_LEFT] ? RECT_FLIP_HORIZONTAL : RECT_FLIP_NONE;
		}

		//�L�[�𗣂�����ԂŎ~�܂�����
		else if (length(m_speed) <= 0)
		{
			m_flip ^= 1;//0�Ȃ�P�A�P�Ȃ�O
			ac.SetAnimation(UNITYCHAN_ANIMATION_IDLE);
		}
		break;

	case UNITYCHAN_ANIMATION_JUMP:
		//�X�s�[�h���O�ȏ�ɂȂ����痎�����
		if (m_speed.y > 0)

			ac.SetAnimation(UNITYCHAN_ANIMATION_JUMP_FALL);
		break;

	case UNITYCHAN_ANIMATION_JUMP_LANDING:
		//�������E���������瑖��
		if (Keyboard::m_pressedKey[PLAYER_KEY_LEFT] || Keyboard::m_pressedKey[PLAYER_KEY_RIGHT])
			ac.SetAnimation(UNITYCHAN_ANIMATION_RUN);

		if ((length(m_speed) <= 0) && (ac.m_count >= g_animation[UNITYCHAN_ANIMATION_JUMP_LANDING].m_speed - 1))

			ac.SetAnimation(UNITYCHAN_ANIMATION_IDLE);
		break;

	case UNITYCAHN_ANIMATION_GUN:
		break;
	}

	//�����o�[�ϐ��Ƃ��Ďg��
	m_textureIndex = g_animation[ac.m_animation].m_Keys[ac.m_time];

	Textrure &texture = g_textures[m_textureIndex];

	m_bound = texture.m_bound;
	//�����蔻�苫�E�{�b�N�X�w��
	if (m_flip&RECT_FLIP_HORIZONTAL)
		m_bound.m_position.x = 32.f - (m_bound.m_position.x + m_bound.m_size.x);
	float s = 0.5f;
	m_bound.m_position *= s;
	m_bound.m_size *= s;


	////�v���C���[�̈ʒu ���łȂ���Βn�ʂɐݒu
	//float Ground_PlayerY = SCREEN_HEIGHT - PART_SIZE * 6 - PLAYER_SIZE + (PLAYER_SIZE - m_bound.m_position.y - m_bound.m_size.y);
	////���n�ݒ�
	//if (m_falling)
	//{
	//	if (m_position.y >= Ground_PlayerY)
	//	{
	//		m_position.y = Ground_PlayerY;
	//		m_speed.y = 0;
	//		m_falling = false;
	//		ac.SetAnimation(UNITYCHAN_ANIMATION_JUMP_LANDING);
	//	}
	//}

	////�v���C���[�̈ʒu ���łȂ���Βn�ʂɐݒu
	//else if (!m_falling)
	//	m_position.y = Ground_PlayerY;

	//�v���C���[�ɂ��Ă��鋫�E�{�b�N�X���w��
	m_combindBound = m_bound;
	m_combindBound.m_position += m_position;


	m_leftPoint.clear();
	m_rightPoint.clear();
	m_bottomPoint.clear();
	m_topPoint.clear();

	//�����蔻��|�C���g�o�^
	m_leftPoint.push_back(m_combindBound.m_position + vec2(0, m_bound.m_size.y - PART_SIZE + 5));
	m_leftPoint.push_back(m_combindBound.m_position);

	m_rightPoint.push_back(m_combindBound.m_position + m_bound.m_size + vec2(0, -PART_SIZE + 5));
	m_rightPoint.push_back(m_combindBound.m_position + vec2(m_bound.m_size.x, 0));

	m_bottomPoint.push_back(m_combindBound.m_position + vec2(1, m_bound.m_size.y));
	m_bottomPoint.push_back(m_combindBound.m_position + m_bound.m_size - vec2(1, 0));
	m_bottomPoint.push_back(m_combindBound.m_position + m_bound.m_size - vec2(8, 0));

	m_topPoint.push_back(m_combindBound.m_position + vec2(m_bound.m_size.x / 1.5, 0));

	m_topPoint.push_back(m_combindBound.m_position + vec2(m_bound.m_size.x / 4, 0));


	for (vector<vec2>::iterator iter = m_leftPoint.begin();
		iter != m_leftPoint.end();
		iter++)
	{
		//�����|�C���^�[�����ǂƓ�����̂ł���Ή����߂�
		if (g_course.Intersect(*iter))
		{
			vec2 left = ((ivec2)*iter / PART_SIZE + ivec2(1, 0)) * PART_SIZE;

			m_position.x = left.x - m_bound.m_position.x;
			m_speed.x = 0;
			break;
		}
	
	}

	//
	for (vector<vec2>::iterator iter = m_rightPoint.begin();
		iter != m_rightPoint.end();
		iter++)
	{
		//�����|�C���^�[���ǂƓ�����̂ł���Ή����߂�
		if (g_course.Intersect(*iter))
		{
			vec2 right = (ivec2)*iter / PART_SIZE * PART_SIZE;

			m_position.x = right.x - (m_bound.m_position.x + m_bound.m_size.x);
			m_speed.x = 0;
			break;
		}
		
	}
	{
		bool lastFalling = m_falling;
		m_falling = true;

		if (m_speed.y >= 0)
			for (vector<vec2>::iterator iter = m_bottomPoint.begin();
				iter != m_bottomPoint.end();
				iter++)
		{
			//�����|�C���^�[�����Ɠ�����̂ł���Ή����߂�
			if (g_course.Intersect(*iter))
			{
				vec2 bottom = ((ivec2)*iter / PART_SIZE) * PART_SIZE;

				m_position.y = bottom.y - (m_bound.m_position.y + m_bound.m_size.y);


				m_speed.y = 0;

				m_falling = false;

				if (lastFalling)
					ac.SetAnimation(UNITYCHAN_ANIMATION_JUMP_LANDING);

				break;
			}
			
		}
	}
	for (vector<vec2>::iterator iter = m_topPoint.begin();
		iter != m_topPoint.end();
		iter++)
	{
		//�����|�C���^�[���ǂƓ�����̂ł���Ή����߂�
		if (g_course.Intersect(*iter))
		{
			vec2 top = ((ivec2)*iter / PART_SIZE + ivec2(0, 1))* PART_SIZE;

			m_position.y = top.y - m_bound.m_position.y;
			m_speed.y = 0;
			break;
		}
	}
}



void Player::Draw()
{
	Textrure &texture = g_textures[m_textureIndex];

	glBindTexture(
		GL_TEXTURE_2D,//GLenum target,
		texture.m_texture//GLuint texture
	);

	Rect::Draw();
	//DrawWire();

	//m_bound.DrawWire();

	//m_combindBound.DrawWire();

	//�f�o�b�N�p
	//{
	//	//���I�z��ɂ���
	//	glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);//GLbitfield mask
	//	glPushAttrib(GL_ALL_ATTRIB_BITS);//GLbitfield mask
	//	glDisable(GL_TEXTURE_2D);
	//	glColor3ub(0xff, 0x00, 0x00);
	//	//���_�z���L���ɂ���
	//	glEnableClientState(GL_VERTEX_ARRAY);//GLenum array glVertexPointer()���Q��
	//	glVertexPointer(
	//		2,//GLint size,
	//		GL_FLOAT, //GLenum type, 
	//		0,// GLsizei stride,
	//		m_rightPoint.data()); //const GLvoid *pointer

	//	glDrawArrays(GL_POINTS, 0, m_rightPoint.size());

	//	glVertexPointer(
	//		2,//GLint size,
	//		GL_FLOAT, //GLenum type, 
	//		0,// GLsizei stride,
	//		m_leftPoint.data()); //const GLvoid *pointer

	//	glDrawArrays(GL_POINTS, 0, m_leftPoint.size());

	//	glColor3ub(0x00, 0x80, 0x00);
	//	glVertexPointer(
	//		2,//GLint size,
	//		GL_FLOAT, //GLenum type, 
	//		0,// GLsizei stride,
	//		m_bottomPoint.data()); //const GLvoid *pointer

	//	glDrawArrays(GL_POINTS, 0, m_bottomPoint.size());

	//	glColor3ub(0x00, 0x00, 0xff);
	//	glVertexPointer(
	//		2,//GLint size,
	//		GL_FLOAT, //GLenum type, 
	//		0,// GLsizei stride,
	//		m_topPoint.data()); //const GLvoid *pointer

	//	glDrawArrays(GL_POINTS, 0, m_topPoint.size());

	//	glPopAttrib();
	//	glPopClientAttrib();
	//}


}

void Player::Fire()
{
	isFire = true;
}

void Player::damege()
{
	m_PlayerHP -= 10;
}


