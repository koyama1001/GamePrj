#include "Rect.h"
#include "glut.h"
#include <stdio.h>

Rect::Rect()
{
}

Rect::Rect(vec2 const & _size):
	m_position(vec2()),
	m_size(_size)
{
}

Rect::Rect(float _width, float _height) :
	m_size(_width, _height),//����
	m_position(vec2()),//��
	m_flip(RECT_FLIP_NONE)//�N���A����
{}

Rect::Rect( vec2 const & _size,vec2 const & _position)://���ƍ���
   m_size(_size),//����
   m_position(_position),//��
   m_flip(RECT_FLIP_NONE)//�N���A����
{

}

void Rect::Draw()
{
	////�l�p�`�`��
	//glRectf(
	//m_position.x,           //GLfloat x1, 
 //   m_position.y,           //GLfloat y1, 
	//m_position.x+m_size.x,	//GLfloat x2,
	//m_position.y+m_size.y); //GLfloat y2,

	glBegin(GL_QUADS);//���C���[�t���[���ł��ł���
	{
		//���]�t���O�������Ă�����
		glTexCoord2f((m_flip&RECT_FLIP_HORIZONTAL)?1:0//���]�t���O�������Ă�����1�����ĂȂ�������O
			,( m_flip&RECT_FLIP_VERTICAL) ? 1 : 0);//GLfloat s, GLfloat t
		glVertex2fv((GLfloat*)&m_position);//const GLfloat *v

		glTexCoord2f((m_flip&RECT_FLIP_HORIZONTAL) ? 1 : 0, 
			(m_flip&RECT_FLIP_VERTICAL) ? 0 : 1);//GLfloat s, GLfloat t
		glVertex2fv((GLfloat*)&(m_position+vec2(0,m_size.y)));//const GLfloat *v

		glTexCoord2f((m_flip&RECT_FLIP_HORIZONTAL) ? 0 : 1, 
			(m_flip&RECT_FLIP_VERTICAL) ? 0 : 1);//GLfloat s, GLfloat t
		glVertex2fv((GLfloat*)&(m_position + m_size));//const GLfloat *v

		glTexCoord2f((m_flip&RECT_FLIP_HORIZONTAL) ? 0 : 1, 
			(m_flip&RECT_FLIP_VERTICAL) ? 1 : 0);//GLfloat s, GLfloat t
		glVertex2fv((GLfloat*)&(m_position + vec2( m_size.x,0)));//const GLfloat *v
	}
	glEnd();
}

void Rect::DrawWire() {
	glPushAttrib(GL_ALL_ATTRIB_BITS);// GLbitfield mask
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(
		GL_FRONT_AND_BACK,//GLenum face,
		GL_LINE);//���ŕ`��@//GLenum mode);
	glRectfv(
		(GLfloat*)&m_position,//const GLfloat *v1,
		(GLfloat*)&(m_position+m_size)//const GLfloat *v2
	);

	glPopAttrib();//�I��
}

bool Rect::Intersect(vec2 const & _point)
{
	//�����蔻��
	return (_point.x >= m_position.x&&
		_point.x < m_position.x + m_size.x
		&&_point.y >= m_position.y
		&&_point.y < m_position.y + m_size.y);
	
}

bool Rect::Intersect(Rect const & _rect)
{
	return (m_position.x + m_size.x >= _rect.m_position.x&&
		m_position.x < _rect.m_position.x + _rect.m_size.x&&
		m_position.y + m_size.y >= _rect.m_position.y&&
		m_position.y <_rect.m_position.y + _rect.m_size.y);
		
	
}
