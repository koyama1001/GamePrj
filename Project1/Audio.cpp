#include <stdio.h>
//#include <alc.h>
//#include <al.h>
//
//#include "Audio.h"
//
//#pragma comment(lib,"OpenAL32.lib")//�t�@�C���Ăяo��
//
////�O������̌Ăяo���~
//static ALuint sources;
//
//int AudioInit()
//{
//	ALCdevice* device = alcOpenDevice(NULL);//�J���@�@const ALCchar *devicename
//
//	//�e�X�g
//	if (device == NULL)
//	{
//		return 1;
//	}
//
//	ALCcontext * context=alcCreateContext(
//		device,//ALCdevice *device 
//		NULL//const ALCint* attrlist
//	); //�R���e�L�X�g���쐬
//
//	if (context == NULL)
//	{
//		return 1;
//	}
//
//	alcMakeContextCurrent(context);//ALCcontext *context �j������
//
//	ALuint buf;
//
//	//���̃f�[�^��\���I�u�W�F�N�g
//	alGenBuffers(
//		1,//ALsizei n
//		&buf//ALuint* buffers
//	);//�o�b�t�@�[�̐��ƃA�h���X���w��
//
//	unsigned char date[] = { 0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };//��`�g�̃f�[�^
//
//	alBufferData(
//		buf,//ALuint bid, �o�b�t�@�[�Z�b�g
//		AL_FORMAT_MONO8,//ALenum format, 8bit
//		date,//const ALvoid* data,�f�[�^��n��
//		sizeof date,//ALsizei size,�g�`�f�[�^�̃T�C�Y�@sizeof�őS�̂�����
//		sizeof(date)*440 //ALsizei freq�@���g��
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
