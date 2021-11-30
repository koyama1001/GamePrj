#include <stdio.h>
//#include <alc.h>
//#include <al.h>
//
//#include "Audio.h"
//
//#pragma comment(lib,"OpenAL32.lib")//ファイル呼び出し
//
////外部からの呼び出し×
//static ALuint sources;
//
//int AudioInit()
//{
//	ALCdevice* device = alcOpenDevice(NULL);//開く　　const ALCchar *devicename
//
//	//テスト
//	if (device == NULL)
//	{
//		return 1;
//	}
//
//	ALCcontext * context=alcCreateContext(
//		device,//ALCdevice *device 
//		NULL//const ALCint* attrlist
//	); //コンテキストを作成
//
//	if (context == NULL)
//	{
//		return 1;
//	}
//
//	alcMakeContextCurrent(context);//ALCcontext *context 破棄する
//
//	ALuint buf;
//
//	//音のデータを表すオブジェクト
//	alGenBuffers(
//		1,//ALsizei n
//		&buf//ALuint* buffers
//	);//バッファーの数とアドレスを指定
//
//	unsigned char date[] = { 0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };//矩形波のデータ
//
//	alBufferData(
//		buf,//ALuint bid, バッファーセット
//		AL_FORMAT_MONO8,//ALenum format, 8bit
//		date,//const ALvoid* data,データを渡す
//		sizeof date,//ALsizei size,波形データのサイズ　sizeofで全体を見る
//		sizeof(date)*440 //ALsizei freq　周波数
//	
//	);
//
//	
//
//	alGenSources(
//		1,//ALsizei n,
//		&sources// ALuint* sources
//	);
//	alSourcei(
//		sources,//ALuint sid, 
//		AL_BUFFER,//ALenum param,
//		buf//ALint value
//
//	);
//	alSourcei(
//		sources,//ALuint sid, 
//		AL_LOOPING,//ALenum param,
//		AL_TRUE//ALint value
//	);
//	
//	alSourcef(
//		sources,
//		AL_GAIN,
//		.1f);
//
//	return 0;
//}
//
//void AudioPlay()
//{
//	alSourcePlay(sources);
//}
//
//void AudioStop()
//{
//	alSourceStop(sources);
//}
