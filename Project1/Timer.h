#pragma once
#include "Header.h"

class CustomTimer
{

private:
	float currentTime;//���݂̎���
	float limitTime;//��������
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