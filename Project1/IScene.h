#pragma once
#include "SceneType.h"

// シーンインターフェース
struct IScene
{
	// 初期化(仮想関数)
	virtual void Initialize() abstract;
	//キーボード
	virtual void Keyboard(unsigned char _Key) abstract;
	// メインループ(仮想関数)
	virtual void Update() abstract;
	// 解放(仮想関数)
	virtual void Release() abstract;
	//描画
	virtual void Draw() abstract;
	//終了
	virtual bool IsEnd() abstract;
	// 次のシーンに
	virtual SceneType NextScene() abstract;
};