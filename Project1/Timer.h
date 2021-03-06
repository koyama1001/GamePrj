#pragma once
#include "Header.h"

class CustomTimer
{

private:
	float currentTime;//現在の時間
	float limitTime;//制限時間
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