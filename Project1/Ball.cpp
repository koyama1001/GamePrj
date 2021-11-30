#include "Ball.h"
#include "glut.h"

void Ball::Update()
{
	m_LastPosition = m_position;
	m_position += m_speed;
}

void Ball::Draw()
{
	glPushMatrix(); {
		glTranslatef(m_position.x,m_position.y,0); //GLfloat x,y,z
		glScalef(16, 16, 0);//GLfloat x,y,z ���̑傫��
		glutSolidSphere(
			0.5,//GLdouble radius ���a 
			16,//GLint slices �X���C�X
			16);//GLint stacks�@�d�˂�
	}
	glPopMatrix();
}
