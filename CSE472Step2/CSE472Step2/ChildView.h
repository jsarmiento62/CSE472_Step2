
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "graphics/OpenGLWnd.h"
#include "graphics/GrTexture.h"
#include "graphics/GrCamera.h"
#include "Mesh.h"

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

private:
	CGrTexture m_wood;
	double  m_spinAngle;
	UINT_PTR m_spinTimer;
	CGrCamera m_camera;
	CMesh m_mesh;
	CMesh m_surface;
	CMesh m_fish;
	int m_scene;
	
public:
	afx_msg void OnStepSpin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStepMesh();
private:
	void CreateMesh();
public:
	afx_msg void OnStepFish();
};

