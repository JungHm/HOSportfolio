#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_isHidden(false)
	, m_pParent(NULL)
	, m_sSize(0, 0)
	, m_vPosition(0.0f, 0.0f, 0.0f)
	, m_vScaling(1.0f, 1.0f, 1.0f)
	, m_fRotZ(0.0f)
	, m_fAngleZ(0.0f)
	, m_nTag(0)
	, m_fMovePos(0.0f)
	, m_fRectSizeMin(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matScal);
	D3DXMatrixIdentity(&m_matRot);
}

cUIObject::~cUIObject()
{
}

void cUIObject::Update()
{	
	if (m_isHidden) return;

	m_fRotZ += m_fAngleZ;

	D3DXMatrixRotationZ(&m_matRot, m_fRotZ);
	D3DXMatrixScaling(&m_matScal, m_vScaling.x, m_vScaling.y, m_vScaling.z);
	m_matWorld = m_matScal * m_matRot;

	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_matWorld._41;
		m_matWorld._42 += m_pParent->m_matWorld._42;
		m_matWorld._43 += m_pParent->m_matWorld._43;
	}

	for each (auto child in m_vecChild)
	{
		child->Update();
	}
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	for each (auto child in m_vecChild)
	{
		child->Render(pSprite);
	}
}

void cUIObject::Destroy()
{
	for each (auto child in m_vecChild)
	{
		child->Destroy();
	}

	this->Release();
}

cUIObject * cUIObject::FindChildByTag(int nTag)
{
	if (m_nTag == nTag) return this;

	for each (auto child in m_vecChild)
	{
		cUIObject* p = child->FindChildByTag(nTag);

		if (p) return p;
	}

	return NULL;
}

void cUIObject::SetPosition(int nX, int nY, int nZ)
{
	m_vPosition.x = nX;
	m_vPosition.y = nY;
	m_vPosition.z = nZ;
}

void cUIObject::AddChild(cUIObject * pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);
}

