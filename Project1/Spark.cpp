#define _USE_MATH_DEFINES
#include <math.h>

#include "Spark.h"
#include "glut.h"

vector<Spark> m_Sparks;
void Spark::Update()
{
	if (m_countLeft > 0)
	{
		m_countLeft--;
	}
}

void Spark::UpdateAll()
{
	//�X�p�[�N�̃T�C�Y���O�ȉ���������A�b�v�f�[�g���Ȃ�
	if (m_Sparks.size() <= 0)
		return;

	for (vector<Spark>::iterator iter_Spark = m_Sparks.begin();
		iter_Spark != m_Sparks.end();)
	{
		(*iter_Spark).Update();
		//�����X�p�[�N�̃J�E���g��0�ȉ���������
		if ((*iter_Spark).m_countLeft <= 0)
		{
			iter_Spark = m_Sparks.erase(iter_Spark);//���̔����q������
		}
		else
		{
			iter_Spark++;
		}
	}
}

void Spark::DrawAll()
{
	glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);//GLbitfield mask
	glPushAttrib(GL_ALL_ATTRIB_BITS);//GLbitfield mask
	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);//GLenum array glVertexPointer()���Q��
	//���̕`��
	glColor3ub(0x00, 0x80, 0x00);
	glPointSize(8);//���̃T�C�Y�ύX
	//���̕`����e
	glVertexPointer(
		2,//GLint size,
		GL_FLOAT, //GLenum type, 
		sizeof(Spark),// GLsizei stride,
		&m_Sparks.data()->m_position); //const GLvoid *pointer

	glDrawArrays(GL_POINTS, 0, m_Sparks.size());
}

void Spark::Explosion(vec2 const & _position)
{
	//���̃p�[�e�B�N����100��
	for (int i = 0; i < 100; i++)
	{
		Spark spark{};
		spark.m_position = _position;
		{
			float r =M_PI *2*rand()/RAND_MAX;
			float power = (float)rand() / RAND_MAX;
			spark.m_speed = vec2(0.2, 0.2);
		}
		spark.m_countLeft = 60*2*rand()/RAND_MAX;
		m_Sparks.push_back(spark);
	}
}


