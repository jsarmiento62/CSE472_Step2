#include "stdafx.h"
#include "Mesh.h"
#include <fstream>      // For input streams from files
#include <string>       // For the string type
#include <sstream>      // For streams from strings


using namespace std;

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

//
// Name :         CMesh::AddFlatQuad()
// Description :  Add a quadrangle to the triangle mesh.
//
void CMesh::AddFlatQuad(int a, int b, int c, int d, int n)
{
	// First triangle
	AddTriangleVertex(a, n, -1);
	AddTriangleVertex(b, n, -1);
	AddTriangleVertex(c, n, -1);

	// Second triangle
	AddTriangleVertex(a, n, -1);
	AddTriangleVertex(c, n, -1);
	AddTriangleVertex(d, n, -1);
}

//
// Name :         CMesh::AddQuad()
// Description :  Add a quadrangle to the triangle mesh with no 
//                assumption of flatness.
//
void CMesh::AddQuad(int a, int b, int c, int d)
{
	// First triangle
	AddTriangleVertex(a, a, -1);
	AddTriangleVertex(b, b, -1);
	AddTriangleVertex(c, c, -1);

	// Second triangle
	AddTriangleVertex(a, a, -1);
	AddTriangleVertex(c, c, -1);
	AddTriangleVertex(d, d, -1);
}

//
// Name :         CMesh::LoadOBJ()
// Description :  Load a file in OBJ format.
//
void CMesh::LoadOBJ(const char *filename)
{
	ifstream str(filename);
	if (!str)
	{
		AfxMessageBox(L"File not found");
		return;
	}

	string line;
	while (getline(str, line))
	{
		istringstream lstr(line);

		string code;
		lstr >> code;
		if (code == "v")
		{
			double x, y, z;
			lstr >> x >> y >> z;
			AddVertex(CGrVector(x, y, z, 1));
		}
		else if (code == "vn")
		{
			double x, y, z;
			lstr >> x >> y >> z;
			AddNormal(CGrVector(x, y, z));
		}
		else if (code == "vt")
		{
			double x, y;
			lstr >> x >> y;
			AddTexCoord(CGrVector(x, y));
		}
		else if (code == "f")
		{
			for (int i = 0; i<3; i++)
			{
				char slash;
				int v, t, n;
				lstr >> v >> slash >> t >> slash >> n;
				AddTriangleVertex(v - 1, n - 1, t - 1);
			}
		}

	}

}