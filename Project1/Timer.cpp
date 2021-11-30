#include "Timer.h"


CustomTimer::CustomTimer():
	currentTime{},
	limitTime{}
{
	limitTime = 60;//1•b, 60fps
}

CustomTimer::~CustomTimer()
{
}

void CustomTimer::init()
{
	currentTime = limitTime;
}

void CustomTimer::SetTimer(float second)
{
	limitTime = 600 * second;
	init();
}

bool CustomTimer::IsTime()
{
	return currentTime == 0.0f;
}

float CustomTimer::Now()
{
	return currentTime;
}

void CustomTimer::Update()
{
	currentTime -= 1.0f;
	currentTime = max(currentTime, 0.0f);
}

void CustomTimer::Change(float limitTime)
{
	CustomTimer::limitTime = limitTime;
	init();
}

float CustomTimer::Rate()
{
	return currentTime / limitTime;
}
