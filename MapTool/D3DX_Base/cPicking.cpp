#include "stdafx.h"
#include "cPicking.h"

cPicking::cPicking()
	: m_vDirection(0.0f, 0.0f, 0.0f)
	, m_vPosition(0.0f, 0.0f, 0.0f)
{
}

cPicking::~cPicking()
{
}

cPicking cPicking::CalcVeiwSpace(IN int nMouseX, IN int nMouseY)
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	
	cPicking ray;
	ray.m_vDirection.x = ((2.0f * nMouseX) / vp.Width - 1.0f) / matProj._11;
	ray.m_vDirection.y = ((-2.0f * nMouseY) / vp.Height + 1.0f) / matProj._22;
	ray.m_vDirection.z = 1.0f;

	return ray;
}

cPicking cPicking::CalcWorldSpace(IN int nMouseX, IN int nMouseY)
{
	cPicking ray = cPicking::CalcVeiwSpace(nMouseX, nMouseY);

	D3DXMATRIXA16 matView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matInView;
	D3DXMatrixInverse(&matInView, 0, &matView);

	// 광선의 원점을 변환한다 w = 1
	D3DXVec3TransformCoord(&ray.m_vPosition, &ray.m_vPosition, &matInView);
	// 광선의 방향을 변환한다 w = 0
	D3DXVec3TransformNormal(&ray.m_vDirection, &ray.m_vDirection, &matInView);
	// 방향을 정규화 한다
	D3DXVec3Normalize(&ray.m_vDirection, &ray.m_vDirection);

	return ray;
}

bool cPicking::IntersectTri(IN D3DXVECTOR3 v0, IN D3DXVECTOR3 v1, IN D3DXVECTOR3 v2, OUT D3DXVECTOR3 & vPickingPos)
{
	float u, v, f;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vPosition, &m_vDirection, &u, &v, &f);
	D3DXVECTOR3 vOut;

	vOut = m_vPosition + (m_vDirection * f);

	vPickingPos.x = vOut.x;
	vPickingPos.y = vOut.y;
	vPickingPos.z = vOut.z;

	return b;
}


