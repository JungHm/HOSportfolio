#include "stdafx.h"
#include "cTower.h"

cTower::cTower()
{
}


cTower::~cTower()
{
	XFile->KeyDestroy(m_sTower[TEAM_BLUE].nKey);
	XFile->KeyDestroy(m_sTower[TEAM_RED].nKey);
}

void cTower::Setup(IN D3DXVECTOR3 vBTowerPos, IN D3DXVECTOR3 vRTowerPos)
{
	for (int i = 0; i < 2; i++)
	{
		ZeroMemory(&m_sTower[i], sizeof(TOWER));	
		D3DXMatrixIdentity(&m_sTower[i].matWorld);
		D3DXMatrixIdentity(&m_sTower[i].matScal);
		D3DXMatrixIdentity(&m_sTower[i].matRotY);
		D3DXMatrixIdentity(&m_sTower[i].matTrans);

		m_sTower[i].eState = NONE;
		m_sTower[i].fBlendTime = 0.3f;
	}

	// ºí·çÆÀ Å¸¿ö
	m_sTower[TEAM_BLUE].sPath = L"obj/tower_1.x";
	m_sTower[TEAM_BLUE].nKey = 1;
	m_sTower[TEAM_BLUE].vPosition = vBTowerPos;
	m_sTower[TEAM_BLUE].fAngleY = -D3DX_PI / 2;
	m_sTower[TEAM_BLUE].sSphere.fRadius = 70.0f;
	m_sTower[TEAM_BLUE].vDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	XFile->SetXFile(m_sTower[TEAM_BLUE].nKey, m_sTower[TEAM_BLUE].sPath);

	// ·¹µåÆÀ Å¸¿ö
	m_sTower[TEAM_RED].sPath = L"obj/tower_0.x";
	m_sTower[TEAM_RED].nKey = 2;
	m_sTower[TEAM_RED].vPosition = vRTowerPos;
	m_sTower[TEAM_RED].fAngleY = D3DX_PI / 2;
	m_sTower[TEAM_RED].sSphere.fRadius = 70.0f;
	m_sTower[TEAM_RED].vDirection = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	XFile->SetXFile(m_sTower[TEAM_RED].nKey, m_sTower[TEAM_RED].sPath);

	g_Effect->CreatEffect("Texture/TowerFire.png", TOWER_FIRE, 200, 100, &m_sTower[TEAM_BLUE].matWorld, m_sTower[TEAM_BLUE].vPosition, -0.3f);
	g_Effect->CreatEffect("Texture/Hit.png", TARGET_HIT, 50, 100, &m_sTower[TEAM_BLUE].matWorld, D3DXVECTOR3(0, 0, 0), 0.0f);
}

void cTower::Update()
{
	LPD3DXANIMATIONSET pAS = nullptr;
	LPD3DXANIMATIONSET pASCompare = nullptr;
	D3DXTRACK_DESC desc;

	if (m_sTower[TEAM_BLUE].isFind || m_sTower[TEAM_RED].isFind)
	{
		g_Effect->Update();
	}

	XFile->GetXFile(m_sTower[TEAM_BLUE].nKey)->Update();
	if (m_sTower[TEAM_BLUE].isFind)
	{	
		XFile->GetAniCtrl(m_sTower[TEAM_BLUE].nKey)->AdvanceTime(g_pTimeManager->GetEllapsedTime(), NULL);
		double dA = XFile->GetAniCtrl(m_sTower[TEAM_BLUE].nKey)->GetTime();
	}
	else
	{
		XFile->GetAniCtrl(m_sTower[TEAM_BLUE].nKey)->SetTrackPosition(0, 0);
		XFile->GetAniCtrl(m_sTower[TEAM_BLUE].nKey)->AdvanceTime(0, NULL);
	}

	XFile->GetXFile(m_sTower[TEAM_RED].nKey)->Update();
	if (m_sTower[TEAM_RED].isFind)
	{
		XFile->GetAniCtrl(m_sTower[TEAM_RED].nKey)->AdvanceTime(g_pTimeManager->GetEllapsedTime(), NULL);
		double dB = XFile->GetAniCtrl(m_sTower[TEAM_RED].nKey)->GetTime();
	}
	else
	{
		XFile->GetAniCtrl(m_sTower[TEAM_RED].nKey)->SetTrackPosition(0, 0);
		XFile->GetAniCtrl(m_sTower[TEAM_RED].nKey)->AdvanceTime(0, NULL);
	}
}

void cTower::Render()
{
	D3DXMatrixScaling(&m_sTower[TEAM_BLUE].matScal, 2.5f, 2.5f, 2.5f);
	D3DXMatrixRotationY(&m_sTower[TEAM_BLUE].matRotY, m_sTower[TEAM_BLUE].fAngleY);
	D3DXMatrixTranslation(&m_sTower[TEAM_BLUE].matTrans, m_sTower[TEAM_BLUE].vPosition.x, m_sTower[TEAM_BLUE].vPosition.y, m_sTower[TEAM_BLUE].vPosition.z);
	m_sTower[TEAM_BLUE].matWorld = m_sTower[TEAM_BLUE].matScal * m_sTower[TEAM_BLUE].matRotY * m_sTower[TEAM_BLUE].matTrans;
	XFile->GetXFile(m_sTower[TEAM_BLUE].nKey)->Render(m_sTower[TEAM_BLUE].matWorld);

	D3DXMatrixScaling(&m_sTower[TEAM_RED].matScal, 2.5f, 2.5f, 2.5f);
	D3DXMatrixRotationY(&m_sTower[TEAM_RED].matRotY, m_sTower[TEAM_RED].fAngleY);
	D3DXMatrixTranslation(&m_sTower[TEAM_RED].matTrans, m_sTower[TEAM_RED].vPosition.x, m_sTower[TEAM_RED].vPosition.y, m_sTower[TEAM_RED].vPosition.z);
	m_sTower[TEAM_RED].matWorld = m_sTower[TEAM_RED].matScal * m_sTower[TEAM_RED].matRotY * m_sTower[TEAM_RED].matTrans;
	XFile->GetXFile(m_sTower[TEAM_RED].nKey)->Render(m_sTower[TEAM_RED].matWorld);
	
	if (m_sTower[TEAM_BLUE].isFind || m_sTower[TEAM_RED].isFind)
	{
		g_Effect->Render();
	}
}

void cTower::BlueFindEnemy(ST_SPHERE sSphere)
{
	if (getDistance(m_sTower[TEAM_BLUE].vPosition.x, m_sTower[TEAM_BLUE].vPosition.z, sSphere.vCenter.x, sSphere.vCenter.z) < m_sTower[TEAM_BLUE].sSphere.fRadius)
	{
		m_sTower[TEAM_BLUE].isFind = true;

		D3DXVECTOR3 vPos = sSphere.vCenter - m_sTower[TEAM_BLUE].vPosition;

		g_Effect->SetTowerWorld(m_sTower[TEAM_BLUE].matWorld);
		g_Effect->SetEnemyPos(vPos + m_sTower[TEAM_BLUE].vPosition);

		D3DXVec3Normalize(&vPos, &vPos);
		D3DXVec3Normalize(&m_sTower[TEAM_BLUE].vDirection, &m_sTower[TEAM_BLUE].vDirection);

		float fDot = D3DXVec3Dot(&vPos, &m_sTower[TEAM_BLUE].vDirection);
		float fRadian = (float)acos(fDot);

		D3DXVECTOR3 vR;
		D3DXVec3Cross(&vR, &vPos, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		if (D3DXVec3Dot(&vR, &m_sTower[TEAM_BLUE].vDirection) > 0)
		{
			D3DXMATRIXA16 matR;
			D3DXMatrixRotationY(&matR, fRadian);

			m_sTower[TEAM_BLUE].fAngleY = fRadian + -D3DX_PI / 2;
			m_sTower[TEAM_BLUE].vDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			D3DXMATRIXA16 matR;
			D3DXMatrixRotationY(&matR, -fRadian);

			m_sTower[TEAM_BLUE].fAngleY = -fRadian + -D3DX_PI / 2;
			m_sTower[TEAM_BLUE].vDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
	}
	else
	{
		m_sTower[TEAM_BLUE].isFind = false;
		m_sTower[TEAM_BLUE].vDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}
}

void cTower::RedFindEnemy(ST_SPHERE sSphere)
{
	if (getDistance(m_sTower[TEAM_RED].vPosition.x, m_sTower[TEAM_RED].vPosition.z, sSphere.vCenter.x, sSphere.vCenter.z) < m_sTower[TEAM_RED].sSphere.fRadius)
	{
		m_sTower[TEAM_RED].isFind = true;

		D3DXVECTOR3 vPos = sSphere.vCenter - m_sTower[TEAM_RED].vPosition;

		g_Effect->SetTowerWorld(m_sTower[TEAM_RED].matWorld);
		g_Effect->SetEnemyPos(vPos + m_sTower[TEAM_RED].vPosition);

		D3DXVec3Normalize(&vPos, &vPos);
		D3DXVec3Normalize(&m_sTower[TEAM_RED].vDirection, &m_sTower[TEAM_RED].vDirection);

		float fDot = D3DXVec3Dot(&vPos, &m_sTower[TEAM_RED].vDirection);
		float fRadian = (float)acos(fDot);

		D3DXVECTOR3 vR;
		D3DXVec3Cross(&vR, &vPos, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		if (D3DXVec3Dot(&vR, &m_sTower[TEAM_RED].vDirection) > 0)
		{
			D3DXMATRIXA16 matR;
			D3DXMatrixRotationY(&matR, fRadian);

			m_sTower[TEAM_RED].fAngleY = fRadian + -D3DX_PI / 2;
			m_sTower[TEAM_RED].vDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			D3DXMATRIXA16 matR;
			D3DXMatrixRotationY(&matR, -fRadian);

			m_sTower[TEAM_RED].fAngleY = -fRadian + -D3DX_PI / 2;
			m_sTower[TEAM_RED].vDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		}
	}
	else
	{
		m_sTower[TEAM_RED].isFind = false;
		m_sTower[TEAM_RED].vDirection = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	}
}
