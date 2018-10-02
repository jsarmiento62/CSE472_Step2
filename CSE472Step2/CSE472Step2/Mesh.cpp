#include "stdafx.h"
#include "Mesh.h"


CMesh::CMesh()
{
}


CMesh::~CMesh()
{
}

void CMesh::Draw()
{
	glBegin(GL_TRIANGLES);
	for (PTV v = m_triangles.begin(); v != m_triangles.end(); v++)
	{
		glNormal3dv(m_normals[v->n]);
		glVertex3dv(m_vertices[v->v]);
	}
	glEnd();
}

void CMesh::AddTriangleVertex(int v, int n, int t)
{
	TV tv;
	tv.v = v;
	tv.n = n;
	tv.t = t;
	m_triangles.push_back(tv);
}