#include "stdafx.h"
#include "cCubeMan.h"
#include "cBody.h"
#include "cHead.h"
#include "cLeftArm.h"
#include "cRightArm.h"
#include "cLeftLeg.h"
#include "cRightLeg.h"
#include "cAction.h"
#include "iMap.h"


cCubeMan::cCubeMan()
	: m_pRoot(NULL)
{
}


cCubeMan::~cCubeMan()
{
	SAFE_DELETE(m_pRoot);
	SAFE_RELEASE(m_pTexture);
}


void cCubeMan::Setup()
{
	SetMaterial();

	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, L"batman.png", &m_pTexture)))
	{
		assert(false && "텍스처 파일 로드 실패");
	}


	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = pBody;

	cHead* pHead = new cHead;
	pHead->Setup();
	m_pRoot->AddChild(pHead);

	cLeftArm* pLeftArm = new cLeftArm;
	pLeftArm->Setup();
	pLeftArm->SetRotDeltaX(0.01f);
	m_pRoot->AddChild(pLeftArm);

	cRightArm* pRightArm = new cRightArm;
	pRightArm->Setup();
	pRightArm->SetRotDeltaX(-0.01f);
	m_pRoot->AddChild(pRightArm);

	cLeftLeg* pLeftLeg = new cLeftLeg;
	pLeftLeg->Setup();
	pLeftLeg->SetRotDeltaX(-0.01f);
	m_pRoot->AddChild(pLeftLeg);

	cRightLeg* pRightLeg = new cRightLeg;
	pRightLeg->Setup();
	pRightLeg->SetRotDeltaX(0.01f);
	m_pRoot->AddChild(pRightLeg);
}
void cCubeMan::Update(iMap * pMap)
{
	m_pMap = pMap;
	D3DXVECTOR3 vPosition = m_vPosition;

	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.1f;
	}

	if (GetKeyState('W') & 0x8000)
	{
		vPosition = m_vPosition + (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0x8000)
	{
		vPosition = m_vPosition - (m_vDirection * 0.1f);
	}

	if (pMap)
	{
		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
		{
			m_vPosition = vPosition;
		}
	}

	D3DXMATRIXA16	matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + 3.5f, m_vPosition.z);
	m_matWorld = matR * matT;

	/*
	D3DXMATRIXA16	matR, matT;
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &vUp, &m_vDirection);
	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Cross(&vUp, &m_vDirection, &vRight);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &m_vDirection, &vUp);
	D3DXMatrixTranspose(&matR, &matR);*/

	if (m_pRoot)
	{
		m_pRoot->Update();
	}

	if (m_pAction)
		m_pAction->Update();

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
}

void cCubeMan::Render()
{
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	if (m_pRoot)
	{
		m_pRoot->Render();
	}
}

void cCubeMan::SetMaterial()
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	//m_stMtl.Emissive = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
}

void cCubeMan::OnActionFinish(cAction* pSender)
{

}