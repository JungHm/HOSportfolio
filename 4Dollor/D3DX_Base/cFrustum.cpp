#include "stdafx.h"
#include "cFrustum.h"


cFrustum::cFrustum()
{
}


cFrustum::~cFrustum()
{
}

void cFrustum::Setup()
{
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 0));

	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, 1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, 1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(1, -1, 1));

	m_vecWorldVertex.resize(8);
	m_vecPlane.resize(6);
}

void cFrustum::Update()
{
	D3DXMATRIXA16 matView, matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	for (int i = 0; i < m_vecProjVertex.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i],
			&m_vecProjVertex[i],
			NULL,
			&matProj,
			&matView,
			NULL);
	}
	//¹Ú½º¾ÈÂÊÀ¸·Î °è»ê
	D3DXPlaneFromPoints(&m_vecPlane[0],//µÞ¸é
		&m_vecWorldVertex[0],
		&m_vecWorldVertex[1],
		&m_vecWorldVertex[2]);

	D3DXPlaneFromPoints(&m_vecPlane[1],//¾Õ¸é
		&m_vecWorldVertex[6],
		&m_vecWorldVertex[5],
		&m_vecWorldVertex[4]);

	D3DXPlaneFromPoints(&m_vecPlane[2],//À­¸é
		&m_vecWorldVertex[5],
		&m_vecWorldVertex[6],
		&m_vecWorldVertex[2]);


	D3DXPlaneFromPoints(&m_vecPlane[3],//¹Ø¸é
		&m_vecWorldVertex[7],
		&m_vecWorldVertex[4],
		&m_vecWorldVertex[0]);

	D3DXPlaneFromPoints(&m_vecPlane[4],//ÁÂÃø¸é
		&m_vecWorldVertex[5],
		&m_vecWorldVertex[1],
		&m_vecWorldVertex[0]);

	D3DXPlaneFromPoints(&m_vecPlane[5],//¿ìÃø¸é
		&m_vecWorldVertex[7],
		&m_vecWorldVertex[3],
		&m_vecWorldVertex[2]);
}

bool cFrustum::IsInside(ST_SPHERE * pSphere)
{
	for each (D3DXPLANE p in m_vecPlane)
	{
		if (D3DXPlaneDotCoord(&p, &pSphere->vCenter) > pSphere->fRadius)
			return false;
	}
	return true;
}
