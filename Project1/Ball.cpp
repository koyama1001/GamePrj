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
		glScalef(16, 16, 0);//GLfloat x,y,z 球の大きさ
		glutSolidSphere(
			0.5,//GLdouble radius 半径 
			16,//GLint slices スライス
			16);//GLint stacks　重ねる
	}
	glPopMatrix();
}
