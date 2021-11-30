#include <time.h>
#include "Header.h"
#include "SceneManager.h"
#include "Title.h"
#include "Stage.h"
#include "End.h"
#include "ClearEnd.h"

using namespace glm;

void display();
void Idle();
void Timer(int value);
void Reshape(int width, int height);
void init();
void Render();
void Update();
void Destroy();

ivec2 WindowSize;

SceneManager* g_Scenemanager = new SceneManager();

int main(int argc, char * argv[])
{
	srand(time(NULL));

	//垂直同期がとれないためTimerでやる
	glutTimerFunc(
		0,//unsigned int millis 〇秒後に開始
		Timer,//void (GLUTCALLBACK *func)(int value) 関数起動
		0); //int value 渡す数値　必要ないので０

	glutInit(
		&argc, //int *argcp,
		argv); //char **argv);
	glutInitDisplayMode(GL_DOUBLE);//unsigned int mode　ダブルバッファを使うようにする
	glutInitWindowPosition(0, 0);//Windowポジション
	{
		WindowSize.y = 480;
		WindowSize.x = WindowSize.y * 4 / 3;
		glutInitWindowSize(WindowSize.x, WindowSize.y);//Windowサイズを定義
	}
	glutCreateWindow("Unity Girl");//const char *title

	//初期化
	init();

	//TexFromBMP(".bmp",0xff,0xff,0xff);

	//game loop
	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)
	glutIdleFunc(Idle);//void (GLUTCALLBACK *func)(void) Idle状態のときに呼ばれる

	//windowのサイズが変わったときのコールバック関数定義
	glutReshapeFunc(Reshape);//void (GLUTCALLBACK *func)(int width, int height) 

	//keyrepeatを無効にする
	glutIgnoreKeyRepeat(GL_TRUE);//int ignore

	glutMainLoop();//MainLoop

	//MainLoopが終わったら。。。
	Destroy();

	return 0;
}


void display()
{
	//glClearColor(80 / 255.f, 128 / 255.f, 255 / 255.f,1);//GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha
	glClearColor(0.f, 0.f, 0.f, 1);//GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha
	glClear(GL_COLOR_BUFFER_BIT); //GLbitfield mask 画面の情報をリセット

	//2D
	glMatrixMode(GL_PROJECTION);//GLenum mode

	glLoadIdentity();
	gluOrtho2D(
		g_course.m_scroll,//GLdouble left,
		g_course.m_scroll + SCREEN_WIDTH,//GLdouble right,
		SCREEN_HEIGHT,//GLdouble bottom,
		0//GLdouble top
	);
	glMatrixMode(GL_MODELVIEW); //GLenum mode　モード設定
	glLoadIdentity();//リセットしている

	glEnable(GL_TEXTURE_2D);//2次元テクスチャを有効


	glEnable(GL_BLEND);//混合処理
	glBlendFunc(
		GL_SRC_ALPHA,//Lenum sfactor
		GL_ONE_MINUS_SRC_ALPHA	// GLenum dfactor
	);

	//描画
	Render();

	{
		float f = (float)WindowSize.x / SCREEN_WIDTH;
		glPointSize(f);
		glLineWidth(f);
	}


	FontEnd();//フォント描画終了

	glutSwapBuffers();//命令

}

void Idle()
{
	Keyboard::Begin();

	Update();

	glutPostRedisplay();

	Keyboard::End();

}


//再描画命令
void Timer(int value)
{
	glutTimerFunc(
		1000 / 60,//unsigned int millis 〇秒後に開始 60FPSにしてる
		Timer,//void (GLUTCALLBACK *func)(int value) 関数起動
		0); //int value 渡す数値　必要ないので０

	glutPostRedisplay();//再度描画命令
}

void Reshape(int width, int height)
{
	WindowSize = ivec2(width, height);
	printf("reshape: width:%d height:%d\n", WindowSize.x, WindowSize.y);//確認のため
	//更新するのでwindowサイズが変わっても大丈夫
	glViewport(
		0, 0,//(GLint x,y, 座標
		WindowSize.x, WindowSize.y//GLsizei width,height)　幅高さ
	);
}

// 初期化
void init()
{
	Keyboard::Init();
	Textrure::InitAll();
	Animation::InitAll();

	//フォントの初期化
	FontInit(SCREEN_WIDTH, SCREEN_HEIGHT);

	//シーン初期化
	g_Scenemanager->init();
	//シーン呼び出し
	g_Scenemanager->Add(SceneType::Title, new Title{});
	g_Scenemanager->Add(SceneType::Stage, new Stage{});
	g_Scenemanager->Add(SceneType::Ending, new End{});
	g_Scenemanager->Add(SceneType::Clear, new ClearEnd{});

	//最初のシーン
	g_Scenemanager->Change(SceneType::Title);
	//g_Scenemanager->Change(SceneType::Ending);
	//g_Scenemanager->Change(SceneType::Clear);
}

//描画
void Render()
{
	g_Scenemanager->Draw();

}

//更新
void Update()
{
	g_game.Update();
	g_Scenemanager->Update();


}

// メモリ解除
void Destroy()//ここにReleaseを入れる
{
	if (g_Scenemanager)
	{
		g_Scenemanager->Release();
		g_Scenemanager = nullptr;
	}
}


