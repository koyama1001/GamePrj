#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "glut.h"
#include "Keyboard.h"

bool Keyboard::m_pressedKey[KEYBOARD_KEY];
bool Keyboard::m_LastpressedKey[KEYBOARD_KEY];
bool Keyboard::m_ChangeKey[KEYBOARD_KEY];
bool Keyboard::m_nowPressedKey[KEYBOARD_KEY];
bool Keyboard::m_ReleasedKey[KEYBOARD_KEY];
bool Keyboard::m_nowReleasedKey[KEYBOARD_KEY];

void keyboard(unsigned char key, int x, int y)//int�̓}�E�X���W
{
	if (key == 0x1b)
	{
		exit(0);
	}
	printf("Keyboard:\'%c\'(%#x)\n", key, key);
	Keyboard::m_pressedKey[key] = true;
}
void keyboardUp(unsigned char key, int x, int y)
{
	printf("KeyboardUp:\'%c\'(%#x)\n", key, key);
	Keyboard::m_pressedKey[key] = false;
}


int Keyboard::Init()
{
	//Keyboard���擾
	glutKeyboardFunc(keyboard);//void (GLUTCALLBACK *func)(unsigned char key, int x, int y)

	//keyboard�������ꂽ�Ƃ��̏���
	glutKeyboardUpFunc(keyboardUp);//void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	return 0;
}

void Keyboard::Begin()
{
	for (int i = 0; i < KEYBOARD_KEY; i++)
	{
		m_ChangeKey[i] = (m_pressedKey[i] != m_LastpressedKey[i]);

		m_nowPressedKey[i] = (m_ChangeKey[i] && m_pressedKey[i]);

		m_ReleasedKey[i] = !m_pressedKey[i];

		m_nowReleasedKey[i] = (m_ChangeKey[i] && m_ReleasedKey[i]);
	}
}

void Keyboard::End()
{
	memcpy(m_LastpressedKey, m_pressedKey, sizeof m_pressedKey);//memcpy�֐��͎w��o�C�g�����̃��������R�s�[
}
