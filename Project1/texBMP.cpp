#include <stdio.h>
#include <Windows.h>
#include "glut.h"
#include "TexBMP.h"


int TexFromBMP(const char * _fileName,unsigned char *_colorKey, Rect* _pBound)
{
	FILE *pFile;
	fopen_s(&pFile, _fileName, "rb");//ファイルの読み込み

	if (pFile == nullptr)
	{
		//printf("%s open failed\n", _fileName);
		return 1;
	}
	//printf("%s open\n", _fileName);

	BITMAPFILEHEADER bf;//ヘッダーのデータを格納する

	fread(&bf, sizeof BITMAPFILEHEADER, 1, pFile);
	//printf("bf size:%d\n", bf.bfSize);//ファイルサイズ

	BITMAPINFOHEADER bi;
	fread(&bi, sizeof BITMAPINFOHEADER, 1, pFile);

	//printf("biWidth:%d biHHeight:%d\n", bi.biWidth, bi.biHeight);
	//printf("biBitCount:%d\n",bi.biBitCount);

	int Padding = (4-bi.biWidth*(bi.biBitCount / 8)%4)%4;

	//typedef struct {
	//	unsigned char r, g, b;//24Bitなので
	//}RGB;
	//RGB *bits = (RGB*)malloc(sizeof RGB * bi.biWidth * bi.biHeight);//ピクセルデータを確保する
	//fread(bits, sizeof RGB, bi.biWidth * bi.biHeight, pFile);//ピクセルデータを読み込んだ


	
	typedef struct {
		//unsigned char型　保存できる値は　0-255
		unsigned char r, g, b, a;//32Bit Aチャンネル追加
	}RGBA;
	RGBA *pixels = (RGBA*)malloc(sizeof RGBA * bi.biWidth * bi.biHeight);//ピクセルデータを確保する
	
	for (int y = 0; y < bi.biHeight; y++) {
		for (int x = 0; x < bi.biWidth; x++) {

			//memcpy(&pixels[y * bi.biWidth + x],//画像データRGBをコピー
			//	&bits[y * bi.biWidth + x],//コピー元のデータ
			//	sizeof RGB);//コピーサイズ


			RGBA *pPixsel = &pixels[y * bi.biWidth + x];//ポインターで指定
			fread(&pixels[y*bi.biWidth + x], 3, 1, pFile);

			pPixsel->a = ((_colorKey != nullptr)
				&& (pPixsel->r == _colorKey[0])
				&& (pPixsel->g == _colorKey[1])
				&& (pPixsel->b == _colorKey[2]))
				? 0x00
				: 0xff;
		}
		fseek(pFile, Padding, SEEK_CUR);//ファイル行リセット
	}
	//RGBのRとBを入れ替えた
	for (int y = 0; y < bi.biHeight; y++)
		for (int x = 0; x < bi.biWidth; x++)
		{
			RGBA *pPixel = &pixels[y * bi.biWidth + x];
			unsigned char temp = pPixel->r;
			pPixel->r = pPixel->b;
			pPixel->b = temp;




		}
	//ピクセル反転
	for (int y = 0; y < bi.biHeight / 2; y++)
		for (int x = 0; x < bi.biWidth; x++)
		{
			RGBA *pPixel0 = &pixels[y*bi.biWidth + x];
			RGBA *pPixel1 = &pixels[(bi.biHeight - 1 - y)*bi.biWidth + x];
			RGBA temp = *pPixel0;
			*pPixel0 = *pPixel1;
			*pPixel1 = temp;
		}
	
	//バウンドの位置と大きさを取得する
	if (_pBound)
	{
		ivec2 v1(bi.biWidth, bi.biHeight), v2(0, 0);
		for (int y = 0; y < bi.biHeight; y++)
			for (int x = 0; x < bi.biWidth; x++) 
			{

				RGBA *pPixel = &pixels[y*bi.biWidth + x];
				if (pPixel->a <= 0)
				
					//スキップする
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

	//2次元テクスチャを描画
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

	//フィルタリング
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
	//フィルタリング
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
//この関数でカラーキーを設定してる
int TexFromBMP(const char * _fileName,
	unsigned char  _colorKeyR,
	unsigned char  _colorKeyG,
	unsigned char  _colorKeyB,
	Rect* _pBound )
{
	unsigned char colorKey[] = {_colorKeyR,_colorKeyG,_colorKeyB };//RGBカラー設定

	return TexFromBMP(_fileName,colorKey,_pBound );//元の関数を呼ぶ
}
