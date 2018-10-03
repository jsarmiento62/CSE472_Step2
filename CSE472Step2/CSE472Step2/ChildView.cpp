
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "CSE472Step2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	CreateMesh();
	m_wood.LoadFile(L"textures/plank01.bmp");
	m_spinAngle = 0;
	m_spinTimer = 0;
	m_camera.Set(20, 10, 50, 0, 0, 0, 0, 1, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_SAVEBMPFILE32772, &CChildView::OnSaveImage)
	ON_COMMAND(ID_STEP_SPIN, &CChildView::OnStepSpin)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_STEP_MESH, &CChildView::OnStepMesh)
	ON_COMMAND(ID_STEP_FISH, &CChildView::OnStepFish)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}





void CChildView::OnGLDraw(CDC *pDC)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	// Set up the camera
	//

	int width, height;
	GetSize(width, height);
	m_camera.Apply(width, height);

	gluLookAt(20., 10., 50.,    // eye x,y,z
		0., 0., 0.,       // center x,y,z
		0., 1., 0.);      // Up direction

						  //
						  // Some standard parameters
						  //
	GLfloat lightpos[] = { 0.5,2.0,1.0,0. };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
						  // Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Cull backfacing polygons
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	

	// Draw a coordinate axis
	glColor3d(0., 1., 1.);

	glBegin(GL_LINES);
	glVertex3d(0., 0., 0.);
	glVertex3d(12., 0., 0.);
	glVertex3d(0., 0., 0.);
	glVertex3d(0., 12., 0.);
	glVertex3d(0., 0., 0.);
	glVertex3d(0., 0., 12.);
	glEnd();


	// 
	// INSERT DRAWING CODE HERE
	//
	GLfloat msugreen[] = { 1.f, 1.f, 1.f, 1.f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, msugreen);

	const double RED[] = { 0.7, 0.0, 0.0 };
	
	glPushMatrix();
	glTranslated(1.5, 1.5, 1.5);
	glRotated(m_spinAngle, 0., 0., 1.);
	glTranslated(-1.5, -1.5, -1.5);
	Box(3., 3., 3., RED);
	glPopMatrix();

	switch (m_scene) {
	case ID_STEP_MESH:
		glPushMatrix();
		glRotated(m_spinAngle / 3, 0, 1, 0);

		glPushMatrix();
		glTranslated(0, 4, 0);
		m_mesh.Draw();
		glPopMatrix();

		m_surface.Draw();

		m_fish.Draw();

		glPopMatrix();
		break;
	}


}


void CChildView::OnSaveImage()
{
	// TODO: Add your command handler code here
}

//
//        Name : Quad()
// Description : Inline function for drawing 
//               a quadralateral.
//
inline void Quad(GLdouble *v1, GLdouble *v2, GLdouble *v3, GLdouble *v4)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3dv(v1);
	glTexCoord2f(1, 0);
	glVertex3dv(v2);
	glTexCoord2f(1, 1);
	glVertex3dv(v3);
	glTexCoord2f(0, 1);
	glVertex3dv(v4);
	glEnd();
}

//
//        Name : CChildView::Box()
// Description : Draw an arbitrary size box. p_x, 
//               p_y, an p_z are the height of
//               the box. We will use this 
//               as a common primitive.
//      Origin : The back corner is at 0, 0, 0, and
//               the box is entirely in the
//               positive octant.
//
void CChildView::Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble *p_color)
{
	GLdouble a[] = { 0., 0., p_z };
	GLdouble b[] = { p_x, 0., p_z };
	GLdouble c[] = { p_x, p_y, p_z };
	GLdouble d[] = { 0., p_y, p_z };
	GLdouble e[] = { 0., 0., 0. };
	GLdouble f[] = { p_x, 0., 0. };
	GLdouble g[] = { p_x, p_y, 0. };
	GLdouble h[] = { 0., p_y, 0. };

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, m_wood.TexName());

	// I'm going to mess with the colors a bit so
	// the faces will be visible in solid shading
	glNormal3d(0, 0, 1);
	Quad(a, b, c, d); // Front

	glNormal3d(1, 0, 0);
	Quad(c, b, f, g); // Right

	glNormal3d(0, 0, -1);
	Quad(h, g, f, e); // Back

	glNormal3d(-1, 0, 0);
	Quad(d, h, e, a); // Left

	glNormal3d(0, 1, 0);
	Quad(d, c, g, h); // Top

	glNormal3d(0, -1, 0);
	Quad(e, f, b, a); // Bottom

	//diable texturing afterwards to prevent interfering with other parts of the rendering code
	glDisable(GL_TEXTURE_2D);
}


void CChildView::OnStepSpin()
{
	if (m_spinTimer == 0)
	{
		// Create the timer
		m_spinTimer = SetTimer(1, 30, NULL);
	}
	else
	{
		// Destroy the timer
		KillTimer(m_spinTimer);
		m_spinTimer = 0;
	}
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	m_spinAngle += 5;       // 5 degrees every 30ms about
	Invalidate();

	COpenGLWnd::OnTimer(nIDEvent);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y);

	COpenGLWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_camera.MouseMove(point.x, point.y, nFlags))
		Invalidate();
	COpenGLWnd::OnMouseMove(nFlags, point);
}



void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y, 2);
	COpenGLWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnStepMesh()
{
	m_scene = ID_STEP_MESH;
	Invalidate();
}
void CChildView::CreateMesh()
{
	double v[8][4] = { { 0, 0, 2, 1 },{ 2, 0, 2, 1 },{ 2, 2, 2, 1 },{ 0, 2, 2, 1 },
	{ 0, 0, 0, 1 },{ 2, 0, 0, 1 },{ 2, 2, 0, 1 },{ 0, 2, 0, 1 } };
	double n[6][4] = { { 0, 0, 1, 0 },{ 1, 0, 0, 0 },{ 0, 0, -1, 0 },
	{ -1, 0, 0, 0 },{ 0, 1, 0, 0 },{ 0, -1, 0, 0 } };

	for (int i = 0; i<8; i++)
		m_mesh.AddVertex(v[i]);

	for (int i = 0; i<6; i++)
		m_mesh.AddNormal(n[i]);

	m_mesh.AddFlatQuad(0, 1, 2, 3, 0);
	m_mesh.AddFlatQuad(1, 5, 6, 2, 1);
	m_mesh.AddFlatQuad(5, 4, 7, 6, 2);
	m_mesh.AddFlatQuad(4, 0, 3, 7, 3);
	m_mesh.AddFlatQuad(3, 2, 6, 7, 4);
	m_mesh.AddFlatQuad(0, 4, 5, 1, 5);

	//
	// Create a surface
	//

	double wid = 20;        // 20 units wide
	double dep = 20;        // 20 units deep
	int nW = 15;            // Number of quads across
	int nD = 15;            // Number of quads deep
	const double PI = 3.141592653;

	// Create the vertices and -temporary- normals
	// Note that the surface is nW+1 by nD+1 vertices
	for (int j = 0; j <= nD; j++)
	{
		for (int i = 0; i <= nW; i++)
		{
			double x = double(i) / double(nW) * wid - wid / 2;
			double z = double(j) / double(nD) * dep - dep / 2;
			double y = sin(double(i) / double(nW) * 4 * PI) +
				sin(double(j) / double(nD) * 3 * PI);

			CGrVector normal(-4 * PI / wid * cos(double(i) / double(nW) * 4 * PI),
				1., -3 * PI / dep * cos(double(j) / double(nD) * 3 * PI));
			normal.Normalize();


			m_surface.AddVertex(CGrVector(x, y, z, 1));
			m_surface.AddNormal(normal);
		}
	}

	// Create the quadrilaterals
	for (int j = 0; j<nD; j++)
	{
		for (int i = 0; i<nW; i++)
		{
			int a = j * (nW + 1) + i;
			int b = a + nW + 1;
			int c = b + 1;
			int d = a + 1;

			m_surface.AddQuad(a, b, c, d);
		}
	}

	m_fish.LoadOBJ("models\\fish4.obj");
}



void CChildView::OnStepFish()
{
	m_scene = ID_STEP_MESH;
}
