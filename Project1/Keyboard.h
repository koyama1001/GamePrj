#pragma once


enum EKeyboard {
	//キーの数
	KEYBOARD_KEY=256
};

struct Keyboard
{
	static bool m_pressedKey[KEYBOARD_KEY];//キーボード取得

	static bool m_LastpressedKey[KEYBOARD_KEY];//1フレーム前のキーを取得

	static bool m_ChangeKey[KEYBOARD_KEY];//変化があったキーを取得

	static bool m_nowPressedKey[KEYBOARD_KEY];//今押されたキーを取得

	static bool m_ReleasedKey[KEYBOARD_KEY];//離されたキーを取得

	static bool m_nowReleasedKey[KEYBOARD_KEY];//今離されたキーを取得

	static int Init();//初期化
	static void Begin();//開始
	static void End();//終了
};