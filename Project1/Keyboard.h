#pragma once


enum EKeyboard {
	//�L�[�̐�
	KEYBOARD_KEY=256
};

struct Keyboard
{
	static bool m_pressedKey[KEYBOARD_KEY];//�L�[�{�[�h�擾

	static bool m_LastpressedKey[KEYBOARD_KEY];//1�t���[���O�̃L�[���擾

	static bool m_ChangeKey[KEYBOARD_KEY];//�ω����������L�[���擾

	static bool m_nowPressedKey[KEYBOARD_KEY];//�������ꂽ�L�[���擾

	static bool m_ReleasedKey[KEYBOARD_KEY];//�����ꂽ�L�[���擾

	static bool m_nowReleasedKey[KEYBOARD_KEY];//�������ꂽ�L�[���擾

	static int Init();//������
	static void Begin();//�J�n
	static void End();//�I��
};