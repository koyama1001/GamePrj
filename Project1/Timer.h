#pragma once
#include "Header.h"

class CustomTimer
{

private:
	float currentTime;//Œ»İ‚ÌŠÔ
	float limitTime;//§ŒÀŠÔ
public:
	CustomTimer();
	~CustomTimer();
	void init();
	void SetTimer(float second);
	bool IsTime();
	float Now();
	void Update();
	void Change(float limitTime);
	float Rate();

};