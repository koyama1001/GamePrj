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

	//�����������Ƃ�Ȃ�����Timer�ł��
	glutTimerFunc(
		0,//unsigned int millis �Z�b��ɊJ�n
		Timer,//void (GLUTCALLBACK *func)(int value) �֐��N��
		0); //int value �n�����l�@�K�v�Ȃ��̂łO

	glutInit(
		&argc, //int *argcp,
		argv); //char **argv);
	glutInitDisplayMode(GL_DOUBLE);//unsigned int mode�@�_�u���o�b�t�@���g���悤�ɂ���
	glutInitWindowPosition(0, 0);//Window�|�W�V����
	{
		WindowSize.y = 480;
		WindowSize.x = WindowSize.y * 4 / 3;
		glutInitWindowSize(WindowSize.x, WindowSize.y);//Window�T�C�Y���`
	}
	glutCreateWindow("Unity Girl");//const char *title

	//������
	init();

	//TexFromBMP(".bmp",0xff,0xff,0xff);

	//game loop
	glutDisplayFunc(display);//void (GLUTCALLBACK *func)(void)
	glutIdleFunc(Idle);//void (GLUTCALLBACK *func)(void) Idle��Ԃ̂Ƃ��ɌĂ΂��

	//window�̃T�C�Y���ς�����Ƃ��̃R�[���o�b�N�֐���`
	glutReshapeFunc(Reshape);//void (GLUTCALLBACK *func)(int width, int height) 

	//keyrepeat�𖳌��ɂ���
	glutIgnoreKeyRepeat(GL_TRUE);//int ignore

	glutMainLoop();//MainLoop

	//MainLoop���I�������B�B�B
	Destroy();

	return 0;
}


void display()
{
	//glClearColor(80 / 255.f, 128 / 255.f, 255 / 255.f,1);//GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha
	glClearColor(0.f, 0.f, 0.f, 1);//GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha
	glClear(GL_COLOR_BUFFER_BIT); //GLbitfield mask ��ʂ̏������Z�b�g

	//2D
	glMatrixMode(GL_PROJECTION);//GLenum mode

	glLoadIdentity();
	gluOrtho2D(
		g_course.m_scroll,//GLdouble left,
		g_course.m_scroll + SCREEN_WIDTH,//GLdouble right,
		SCREEN_HEIGHT,//GLdouble bottom,
		0//GLdouble top
	);
	glMatrixMode(GL_MODELVIEW); //GLenum mode�@���[�h�ݒ�
	glLoadIdentity();//���Z�b�g���Ă���

	glEnable(GL_TEXTURE_2D);//2�����e�N�X�`����L��


	glEnable(GL_BLEND);//��������
	glBlendFunc(
		GL_SRC_ALPHA,//Lenum sfactor
		GL_ONE_MINUS_SRC_ALPHA	// GLenum dfactor
	);

	//�`��
	Render();

	{
		float f = (float)WindowSize.x / SCREEN_WIDTH;
		glPointSize(f);
		glLineWidth(f);
	}


	FontEnd();//�t�H���g�`��I��

	glutSwapBuffers();//����

}

void Idle()
{
	Keyboard::Begin();

	Update();

	glutPostRedisplay();

	Keyboard::End();

}


//�ĕ`�施��
void Timer(int value)
{
	glutTimerFunc(
		1000 / 60,//unsigned int millis �Z�b��ɊJ�n 60FPS�ɂ��Ă�
		Timer,//void (GLUTCALLBACK *func)(int value) �֐��N��
		0); //int value �n�����l�@�K�v�Ȃ��̂łO

	glutPostRedisplay();//�ēx�`�施��
}

void Reshape(int width, int height)
{
	WindowSize = ivec2(width, height);
	printf("reshape: width:%d height:%d\n", WindowSize.x, WindowSize.y);//�m�F�̂���
	//�X�V����̂�window�T�C�Y���ς���Ă����v
	glViewport(
		0, 0,//(GLint x,y, ���W
		WindowSize.x, WindowSize.y//GLsizei width,height)�@������
	);
}

// ������
void init()
{
	Keyboard::Init();
	Textrure::InitAll();
	Animation::InitAll();

	//�t�H���g�̏�����
	FontInit(SCREEN_WIDTH, SCREEN_HEIGHT);

	//�V�[��������
	g_Scenemanager->init();
	//�V�[���Ăяo��
	g_Scenemanager->Add(SceneType::Title, new Title{});
	g_Scenemanager->Add(SceneType::Stage, new Stage{});
	g_Scenemanager->Add(SceneType::Ending, new End{});
	g_Scenemanager->Add(SceneType::Clear, new ClearEnd{});

	//�ŏ��̃V�[��
	g_Scenemanager->Change(SceneType::Title);
	//g_Scenemanager->Change(SceneType::Ending);
	//g_Scenemanager->Change(SceneType::Clear);
}

//�`��
void Render()
{
	g_Scenemanager->Draw();

}

//�X�V
void Update()
{
	g_game.Update();
	g_Scenemanager->Update();


}

// ����������
void Destroy()//������Release������
{
	if (g_Scenemanager)
	{
		g_Scenemanager->Release();
		g_Scenemanager = nullptr;
	}
}


