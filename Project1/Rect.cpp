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
	m_size(_width, _height),//高さ
	m_position(vec2()),//幅
	m_flip(RECT_FLIP_NONE)//クリアする
{}

Rect::Rect( vec2 const & _size,vec2 const & _position)://幅と高さ
   m_size(_size),//高さ
   m_position(_position),//幅
   m_flip(RECT_FLIP_NONE)//クリアする
{

}

void Rect::Draw()
{
	////四角形描画
	//glRectf(
	//m_position.x,           //GLfloat x1, 
 //   m_position.y,           //GLfloat y1, 
	//m_position.x+m_size.x,	//GLfloat x2,
	//m_position.y+m_size.y); //GLfloat y2,

	glBegin(GL_QUADS);//ワイヤーフレームでもできる
	{
		//反転フラグが建っていたら
		glTexCoord2f((m_flip&RECT_FLIP_HORIZONTAL)?1:0//反転フラグが建っていたら1建ってなかったら０
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
		GL_LINE);//線で描画　//GLenum mode);
	glRectfv(
		(GLfloat*)&m_position,//const GLfloat *v1,
		(GLfloat*)&(m_position+m_size)//const GLfloat *v2
	);

	glPopAttrib();//終了
}

bool Rect::Intersect(vec2 const & _point)
{
	//当たり判定
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
