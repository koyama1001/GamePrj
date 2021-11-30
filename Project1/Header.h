#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Font.h"
#include "glm/glm.hpp"

#include "Rect.h"

#include "Ball.h"
#include "TexBMP.h"
#include "Keyboard.h"
#include "Audio.h"
#include "Texture.h"
#include "Animation.h"
#include "AnimationController.h"
#include "Player.h"


#include "Parts.h"
#include "Course.h"
#include "Game.h"
#include "Enemy.h"

#include "CharacterManager.h"
#include "Bullet.h"

#include "glut.h"


enum EScreen
{
//“à•”‰ð‘œ“x
	SCREEN_WIDTH=256,
	SCREEN_HEIGHT=256
};

using namespace glm;

