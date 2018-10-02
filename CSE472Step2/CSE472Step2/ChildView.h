
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "graphics/OpenGLWnd.h"

// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnGLDraw(CDC *pDC);
	afx_msg void OnSaveImage();
	void Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble * p_color);
};

