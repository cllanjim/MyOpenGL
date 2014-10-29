#include "ScrolRect.h"
#include "InputManager.h"
#include "glRenderer.h"
#include "TextureMgr.h"
#include "OpenGLEngine.h"
ScrolRect::ScrolRect()
{
	m_hit = CMyRectTracker::TrackerHit::hitNothing;
	m_hit1 = CMyRectTracker::TrackerHit::hitNothing;

}

ScrolRect::ScrolRect(Rectangle _rect)
{
	m_Rectangle = _rect;

}

ScrolRect::~ScrolRect()
{

}

void ScrolRect::MouseEven(MouseType nType, MousePos pos)
{
	P3_POS _pos;
	_pos.x = pos.X;
	_pos.y = pos.Y;
	switch (nType)
	{
	case MouseDown:
	{

					  m_hit = (CMyRectTracker::TrackerHit)showRect.HitTest(_pos);
					  m_hit1 = (CMyRectTracker::TrackerHit)horizontalRect.HitTest(_pos);

	}break;
	case MouseUp:
	{
					m_hit = CMyRectTracker::TrackerHit::hitNothing;
					m_hit1 = CMyRectTracker::TrackerHit::hitNothing;
	}
		break;
	case MouseDClick:
	{

	}
		break;
	case MouseMove:
	{
					  if (m_hit >= 0)
					  {
						  m_hit = CMyRectTracker::TrackerHit::hitMiddle;
						  if (showRect.top+ pos.Y <= 0)
						  {
							  pos.Y = 0 - showRect.top;
						  }
						  if (showRect.bottom + pos.Y >= pageRect.bottom)
						  {
							  pos.Y = pageRect.bottom - showRect.bottom;
						  }
						  showRect.OffsetRect(0, pos.Y);
					  }

					  if (m_hit1 >= 0)
					  {
						  m_hit1 = CMyRectTracker::TrackerHit::hitMiddle;
						  if (horizontalRect.left + pos.X <= 0)
						  {
							  pos.X = 0 - horizontalRect.left;
						  }
						  if (horizontalRect.right + pos.X >= pageRect.right)
						  {
							  pos.X = pageRect.right - horizontalRect.right;
						  }
						  horizontalRect.OffsetRect(pos.X, 0);
					  }

	}
		break;
	case MouseWheel:
	{

	}
		break;
	}
}



void ScrolRect::SetPageRect(Rectangle _rect)
{
	pageRect = _rect;
	float nHeight = (float)pageRect.Height() / (float)m_Rectangle.Height();
	if (nHeight > 1.0f) nHeight = 1.0f;
	nHeight *= pageRect.Height();
	//showRect.SetRect(pageRect.Width() - 20*5, pageRect.left, pageRect.Width(), (int)nHeight);
	int nOffsetX = 20 * (float)g_objBase.m_nWidth / 1024.0f;

	//showRect.SetRect(pageRect.Width() - 20, pageRect.left, pageRect.Width() - 5, (int)nHeight);
	showRect.SetRect(pageRect.Width() - nOffsetX, pageRect.left, pageRect.Width(), (int)nHeight);

	float nWidth = (float)pageRect.Width() / (float)m_Rectangle.Width();
	if (nWidth > 1.0f) nWidth = 1.0f;
	nWidth *= pageRect.Width();
	int nOffsetY = 20 * (float)g_objBase.m_nHeight /600.0f;

	horizontalRect.SetRect(0, pageRect.Height() - nOffsetY, (int)nWidth, (int)pageRect.Height());
}

void ScrolRect::SetRect(Rectangle _rect)
{
	m_Rectangle = _rect;
	float nHeight = (float)pageRect.Height() / (float)m_Rectangle.Height();
	if (nHeight > 1.0f) nHeight = 1.0f;
	nHeight *= pageRect.Height();
	int nOffsetX = 20 * (float)g_objBase.m_nWidth / 1024.0f;
	
	//showRect.SetRect(pageRect.Width() - 20, pageRect.left, pageRect.Width() - 5, (int)nHeight);
	showRect.SetRect(pageRect.Width() - nOffsetX, pageRect.left, pageRect.Width(), (int)nHeight);

	float nWidth = (float)pageRect.Width() / (float)m_Rectangle.Width();
	if (nWidth > 1.0f) nWidth = 1.0f;
	nWidth *= pageRect.Width();
	int nOffsetY = 20 * (float)g_objBase.m_nHeight / 600.0f;

	horizontalRect.SetRect(0, pageRect.Height() - nOffsetY, (int)nWidth, (int)pageRect.Height());


}

void ScrolRect::Process()
{
	float r = 0XA9 / 255.0f;
	float g = 0XA9 / 255.0f;
	float b = 0XA9 / 255.0f;
	Rectangle showRectTmp;
	showRectTmp.left = m_Rectangle.left - 5;
	float nHeight = (float)pageRect.Height() / (float)m_Rectangle.Height();
	if (nHeight > 1.0f) nHeight = 1.0f;
	nHeight = showRect.top / nHeight;
	showRectTmp.top = m_Rectangle.top - (int)nHeight;

	float nWidth = (float)pageRect.Width() / (float)m_Rectangle.Width();
	if (nWidth > 1.0f) nWidth = 1.0f;
	nWidth = horizontalRect.left / nWidth;
	showRectTmp.left = m_Rectangle.left - (int)nWidth;

	showRectTmp.right = showRectTmp.left + m_Rectangle.Width();
	showRectTmp.bottom = showRectTmp.top + m_Rectangle.Height();

	CTexture* pTexture = g_objTextureMgr.GetTexture("4.jpg");
	RECT pSrc;
	pSrc.left = 0;
	pSrc.top = 0;
	pSrc.right = pTexture->m_nWidth;
	pSrc.bottom = pTexture->m_nHeight;
	g_objBase.BeginClipRect(pageRect);
	g_objRender.ShowTextureEx( showRectTmp.left, showRectTmp.top, 
		&pSrc, showRectTmp.Width(), showRectTmp.Height(), pTexture,0.0f);
	g_objBase.EndClipRect();
	DX_SCREEN_COLOR _color(r, g, b);
	int nOffsetY = 20 * (float)g_objBase.m_nHeight / 600.0f;
	int nOffsetX = 20 * (float)g_objBase.m_nWidth / 1024.0f;
	Rectangle m_Rect(pageRect.Width() - nOffsetX, 0, pageRect.Width(), pageRect.Height());
	g_objRender.ShowRectEx(m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom, DX_SCREEN_COLOR(0, 0, 0));

	g_objRender.ShowRectEx(showRect.left, showRect.top, showRect.right, showRect.bottom, _color);

	Rectangle m_Rect1(0, pageRect.Height() - nOffsetY, pageRect.Width() - nOffsetX, pageRect.Height());
	g_objRender.ShowRectEx(m_Rect1.left, m_Rect1.top, m_Rect1.right, m_Rect1.bottom, DX_SCREEN_COLOR(0, 0, 0));
	g_objRender.ShowRectEx(horizontalRect.left, horizontalRect.top, horizontalRect.right, horizontalRect.bottom, _color);


}
