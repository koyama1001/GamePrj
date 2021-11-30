#include <stdio.h>
#include <Windows.h>
#include "glut.h"
#include "TexBMP.h"


int TexFromBMP(const char * _fileName,unsigned char *_colorKey, Rect* _pBound)
{
	FILE *pFile;
	fopen_s(&pFile, _fileName, "rb");//�t�@�C���̓ǂݍ���

	if (pFile == nullptr)
	{
		//printf("%s open failed\n", _fileName);
		return 1;
	}
	//printf("%s open\n", _fileName);

	BITMAPFILEHEADER bf;//�w�b�_�[�̃f�[�^���i�[����

	fread(&bf, sizeof BITMAPFILEHEADER, 1, pFile);
	//printf("bf size:%d\n", bf.bfSize);//�t�@�C���T�C�Y

	BITMAPINFOHEADER bi;
	fread(&bi, sizeof BITMAPINFOHEADER, 1, pFile);

	//printf("biWidth:%d biHHeight:%d\n", bi.biWidth, bi.biHeight);
	//printf("biBitCount:%d\n",bi.biBitCount);

	int Padding = (4-bi.biWidth*(bi.biBitCount / 8)%4)%4;

	//typedef struct {
	//	unsigned char r, g, b;//24Bit�Ȃ̂�
	//}RGB;
	//RGB *bits = (RGB*)malloc(sizeof RGB * bi.biWidth * bi.biHeight);//�s�N�Z���f�[�^���m�ۂ���
	//fread(bits, sizeof RGB, bi.biWidth * bi.biHeight, pFile);//�s�N�Z���f�[�^��ǂݍ���


	
	typedef struct {
		//unsigned char�^�@�ۑ��ł���l�́@0-255
		unsigned char r, g, b, a;//32Bit A�`�����l���ǉ�
	}RGBA;
	RGBA *pixels = (RGBA*)malloc(sizeof RGBA * bi.biWidth * bi.biHeight);//�s�N�Z���f�[�^���m�ۂ���
	
	for (int y = 0; y < bi.biHeight; y++) {
		for (int x = 0; x < bi.biWidth; x++) {

			//memcpy(&pixels[y * bi.biWidth + x],//�摜�f�[�^RGB���R�s�[
			//	&bits[y * bi.biWidth + x],//�R�s�[���̃f�[�^
			//	sizeof RGB);//�R�s�[�T�C�Y


			RGBA *pPixsel = &pixels[y * bi.biWidth + x];//�|�C���^�[�Ŏw��
			fread(&pixels[y*bi.biWidth + x], 3, 1, pFile);

			pPixsel->a = ((_colorKey != nullptr)
				&& (pPixsel->r == _colorKey[0])
				&& (pPixsel->g == _colorKey[1])
				&& (pPixsel->b == _colorKey[2]))
				? 0x00
				: 0xff;
		}
		fseek(pFile, Padding, SEEK_CUR);//�t�@�C���s���Z�b�g
	}
	//RGB��R��B�����ւ���
	for (int y = 0; y < bi.biHeight; y++)
		for (int x = 0; x < bi.biWidth; x++)
		{
			RGBA *pPixel = &pixels[y * bi.biWidth + x];
			unsigned char temp = pPixel->r;
			pPixel->r = pPixel->b;
			pPixel->b = temp;




		}
	//�s�N�Z�����]
	for (int y = 0; y < bi.biHeight / 2; y++)
		for (int x = 0; x < bi.biWidth; x++)
		{
			RGBA *pPixel0 = &pixels[y*bi.biWidth + x];
			RGBA *pPixel1 = &pixels[(bi.biHeight - 1 - y)*bi.biWidth + x];
			RGBA temp = *pPixel0;
			*pPixel0 = *pPixel1;
			*pPixel1 = temp;
		}
	
	//�o�E���h�̈ʒu�Ƒ傫�����擾����
	if (_pBound)
	{
		ivec2 v1(bi.biWidth, bi.biHeight), v2(0, 0);
		for (int y = 0; y < bi.biHeight; y++)
			for (int x = 0; x < bi.biWidth; x++) 
			{

				RGBA *pPixel = &pixels[y*bi.biWidth + x];
				if (pPixel->a <= 0)
				
					//�X�L�b�v����
					continue;

					v1.x = min(v1.x, x);
					v1.y = min(v1.y, y);
					v2.x = max(v2.x, x);
					v2.y = max(v2.y, y);
			}
				//printf("%d,%d-%d,%d\n", v1.x, v1.y, v2.x, v2.y);
		_pBound->m_position = (vec2)v1;
		_pBound->m_size = v2 - v1;

		
	}

	//2�����e�N�X�`����`��
	glTexImage2D(
		GL_TEXTURE_2D,	//GLenum target,
		0,//GLint level,
		GL_RGBA,	//GLint internalformat,
		bi.biWidth,		//GLsizei width,
		bi.biHeight,	//GLsizei height, 
		0,//GLint border,
		GL_RGBA,//GLenum format,
		GL_UNSIGNED_BYTE,//GLenum type, 
		pixels);//const GLvoid *pixels

	//�t�B���^�����O
	glTexParameteri(
		GL_TEXTURE_2D,//GLenum target,
		GL_TEXTURE_MAG_FILTER,//GLenum pname,
		GL_NEAREST//GLint param
	);
	glTexParameteri(
		GL_TEXTURE_2D,//GLenum target,
		GL_TEXTURE_MIN_FILTER,//GLenum pname,
		GL_NEAREST//GLint param
	);
	//�t�B���^�����O
	glTexParameteri(
		GL_TEXTURE_2D,//GLenum target,
		GL_TEXTURE_WRAP_S,//GLenum pname,
		GL_NEAREST//GLint param
	);
	glTexParameteri(
		GL_TEXTURE_2D,//GLenum target,
		GL_TEXTURE_WRAP_T,//GLenum pname,
		GL_NEAREST//GLint param
	);
	//free(bits);
	free(pixels);
	fclose(pFile);

	return 0;
}
//���̊֐��ŃJ���[�L�[��ݒ肵�Ă�
int TexFromBMP(const char * _fileName,
	unsigned char  _colorKeyR,
	unsigned char  _colorKeyG,
	unsigned char  _colorKeyB,
	Rect* _pBound )
{
	unsigned char colorKey[] = {_colorKeyR,_colorKeyG,_colorKeyB };//RGB�J���[�ݒ�

	return TexFromBMP(_fileName,colorKey,_pBound );//���̊֐����Ă�
}
