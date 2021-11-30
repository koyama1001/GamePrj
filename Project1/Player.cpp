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
	//プレイヤーサイズ
	m_size = vec2(PLAYER_SIZE, 32);
	m_touch;
	m_direction;
	m_PlayerHP;
	isFire = false;
	//m_bullets.clear();

}

void Player::Update()
{
	//アニメーションコントローラーを取得してアップデート
	AnimationController &ac = m_animationController;

	ac.Update();

	

	////バレットのイテレーターを作る
	//std::list<Bullet *>::iterator itera = m_bullets.begin();

	////iteraがバレットendじゃない時まで回す
	//while (itera != m_bullets.end())
	//{
	//	(*itera)->Update();
	//	//printf("bullet X %f,Y %f \n", (*itera)->getPosition().x, (*itera)->getPosition().y);
	//	//printf("b_bullet X %f, Y %f \n", newBullet.getPosition().x, newBullet.getPosition().y);
	//	//printf("testini : %d\n", testint++);
	//	
	//	//もしカウントレフトが0以下だったら
	//	if ((*itera)->m_countLife <= 0 || (*itera)->m_isCollision)
	//	{
	//		Bullet *Del;
	//		Del = *itera;
	//		itera = m_bullets.erase(itera);//この*iteraの球を消去する
	//		//バレットを消去する
	//		delete Del;
	//	}
	//	else
	//		itera++;
	//}



	//プレイヤーの速度
	float acceleration = 0.018f;
	//プレイヤーの移動
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
	//スペースが押されてかつ空中にいなければジャンプする
	if (Keyboard::m_nowPressedKey[PLAYER_KEY_JUMP] && (!m_falling))
	{
		m_jumping = m_falling = true;
		m_JumpCount = 0;
		ac.SetAnimation(UNITYCHAN_ANIMATION_JUMP_UP);
	}

	//もし打つキーを押したなら打つアニメーションをする
	if (Keyboard::m_pressedKey[PLAYER_KEY_BULLET])
	{
		m_flip = m_direction;
		ac.SetAnimation(UNITYCAHN_ANIMATION_GUN);
		//もし今押されたキーであるなら発射する
		if (Keyboard::m_nowPressedKey[PLAYER_KEY_BULLET]) {
			Fire();
		}
	}



	//落下がTrueなら↓
	if (m_falling) {
		//もしジャンプがtrueならｙ軸に飛ぶ
		if (m_jumping)
		{
			m_speed.y = -.3;
			//もしジャンプカウントが500以上になったらまたはスペースキーが離されたらジャンプをやめる
			if ((++m_JumpCount >= PLAYER_JUMP_COUNT_MAX) || (!Keyboard::m_pressedKey[PLAYER_KEY_JUMP]))
			{
				m_jumping = false;
				ac.SetAnimation(UNITYCHAN_ANIMATION_JUMP);
			}
		}
		m_speed.y += 0.02f;
	}//ifEND


	//減速
	//m_speed *= .9f;
	{
		//動画見て打ってみた
		//固定小数点で原則
		int one = 0x100;
		ivec2 fixed = m_speed * (float)one;
		fixed = fixed * 0xe8 / one;
		//固定小数点から浮動小数点に戻す
		m_speed = (vec2)fixed / (float)one;
	}


	m_position += m_speed;
	{

		//画面の左端で止める あとで修正
		float left = g_course.m_scroll - PLAYER_SIZE * 3 / 8;
		if ((m_position.x < left)&& (m_position.x < g_course.m_scroll + SCREEN_WIDTH / 2 - PLAYER_SIZE / 2))
		{
			m_position.x = left;
			g_course.m_scroll += m_speed.x;
			//m_speed.x = 0;
		}
	}
	{

		//とりあえず画面の右端で止める　ここは修正する
		float right = COURSE_WIDTH * PART_SIZE - PLAYER_SIZE * 5 / 8;
		if (m_position.x > right)
		{
			m_position.x = right;
			m_speed.x = 0;
		}
	}
	//画面スクロール処理
	if ((m_speed.x > 0) && (m_position.x > g_course.m_scroll + SCREEN_WIDTH / 2 - PLAYER_SIZE / 2))
	{
		g_course.m_scroll += m_speed.x;

		g_course.m_scroll = min(g_course.m_scroll, (float)(COURSE_WIDTH*PART_SIZE - SCREEN_WIDTH));

	}

	//アニメーション切り替え
	switch (ac.m_animation)
	{
	case UNITYCHAN_ANIMATION_IDLE:

		//スピードｘの絶対値が０より上なら走る
		if (fabs(m_speed.x) > 0)
		{
			ac.SetAnimation(UNITYCHAN_ANIMATION_RUN);
			//スピードが０だったら回転する　0より上なら何もしない
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

		//走りアニメーション中に止める条件
	case UNITYCHAN_ANIMATION_RUN:

		//スピードが0だったら回転する
		if (m_speed.x < 0)
			m_flip = RECT_FLIP_HORIZONTAL;

		//スピードが0より上なら何もなし
		if (m_speed.x > 0)
			m_flip = RECT_FLIP_NONE;

		//キーボードが押されてなくってスピードが０以下ならブレーキモーション
		if (
			((!Keyboard::m_pressedKey[PLAYER_KEY_LEFT]) && (m_speed.x < 0)) ||
			((!Keyboard::m_pressedKey[PLAYER_KEY_RIGHT]) && (m_speed.x > 0))
			)
			ac.SetAnimation(UNITYCHAN_ANIMATION_BRAKE);

		if (length(m_speed) <= 0)
			ac.SetAnimation(UNITYCHAN_ANIMATION_IDLE);

		break;

	case UNITYCHAN_ANIMATION_BRAKE:

		//キーボードが押されてなくってスピードが０ならブレーキモーション
		if (
			((!Keyboard::m_pressedKey[PLAYER_KEY_LEFT]) && (m_speed.x < 0.0005)) ||
			((!Keyboard::m_pressedKey[PLAYER_KEY_RIGHT]) && (m_speed.x > 0.0005))
			)
		{
			ac.SetAnimation(UNITYCHAN_ANIMATION_RUN);
			//ここ修正加える
			//m_flip = Keyboard::m_pressedKey[PLAYER_KEY_LEFT] ? RECT_FLIP_HORIZONTAL : RECT_FLIP_NONE;
		}

		//キーを離した状態で止まった時
		else if (length(m_speed) <= 0)
		{
			m_flip ^= 1;//0なら１、１なら０
			ac.SetAnimation(UNITYCHAN_ANIMATION_IDLE);
		}
		break;

	case UNITYCHAN_ANIMATION_JUMP:
		//スピードが０以上になったら落下状態
		if (m_speed.y > 0)

			ac.SetAnimation(UNITYCHAN_ANIMATION_JUMP_FALL);
		break;

	case UNITYCHAN_ANIMATION_JUMP_LANDING:
		//もし左右を押したら走る
		if (Keyboard::m_pressedKey[PLAYER_KEY_LEFT] || Keyboard::m_pressedKey[PLAYER_KEY_RIGHT])
			ac.SetAnimation(UNITYCHAN_ANIMATION_RUN);

		if ((length(m_speed) <= 0) && (ac.m_count >= g_animation[UNITYCHAN_ANIMATION_JUMP_LANDING].m_speed - 1))

			ac.SetAnimation(UNITYCHAN_ANIMATION_IDLE);
		break;

	case UNITYCAHN_ANIMATION_GUN:
		break;
	}

	//メンバー変数として使う
	m_textureIndex = g_animation[ac.m_animation].m_Keys[ac.m_time];

	Textrure &texture = g_textures[m_textureIndex];

	m_bound = texture.m_bound;
	//当たり判定境界ボックス指定
	if (m_flip&RECT_FLIP_HORIZONTAL)
		m_bound.m_position.x = 32.f - (m_bound.m_position.x + m_bound.m_size.x);
	float s = 0.5f;
	m_bound.m_position *= s;
	m_bound.m_size *= s;


	////プレイヤーの位置 飛んでなければ地面に設置
	//float Ground_PlayerY = SCREEN_HEIGHT - PART_SIZE * 6 - PLAYER_SIZE + (PLAYER_SIZE - m_bound.m_position.y - m_bound.m_size.y);
	////着地設定
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

	////プレイヤーの位置 飛んでなければ地面に設置
	//else if (!m_falling)
	//	m_position.y = Ground_PlayerY;

	//プレイヤーについてくる境界ボックスを指定
	m_combindBound = m_bound;
	m_combindBound.m_position += m_position;


	m_leftPoint.clear();
	m_rightPoint.clear();
	m_bottomPoint.clear();
	m_topPoint.clear();

	//当たり判定ポイント登録
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
		//もしポインターが左壁と当たるのであれば押し戻す
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
		//もしポインターが壁と当たるのであれば押し戻す
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
			//もしポインターが下と当たるのであれば押し戻す
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
		//もしポインターが壁と当たるのであれば押し戻す
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

	//デバック用
	//{
	//	//動的配列にする
	//	glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);//GLbitfield mask
	//	glPushAttrib(GL_ALL_ATTRIB_BITS);//GLbitfield mask
	//	glDisable(GL_TEXTURE_2D);
	//	glColor3ub(0xff, 0x00, 0x00);
	//	//頂点配列を有効にする
	//	glEnableClientState(GL_VERTEX_ARRAY);//GLenum array glVertexPointer()を参照
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


