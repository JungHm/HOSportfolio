#include "stdafx.h"
#include "cFireEffect.h"

DWORD FtoDW(float f)
{
	return *((DWORD*)&f);
}

cFireEffect::cFireEffect()
{
}


cFireEffect::~cFireEffect()
{
}

void cFireEffect::CreatEffect(IN char* pFullPath, IN EKIND eKind, IN int nSize, IN int nRndNum, IN D3DXMATRIXA16 * matTowerWorld, IN D3DXVECTOR3 vPos, IN float fAngleY)
{
	tagEffect e;
	ZeroMemory(&e, sizeof(tagEffect));

	D3DXMatrixIdentity(&e.matWorld);
	D3DXMatrixIdentity(&e.matRotY);
	D3DXMatrixIdentity(&e.matTrans);
	D3DXMatrixIdentity(&e.matTowerWorld);

	e.pFullPath = pFullPath;
	e.eKind = eKind;
	e.matTowerWorld = *matTowerWorld;
	e.vPosition = vPos;
	e.fAngleY = fAngleY;
	e.nRndNUm = nRndNum;
	e.vecParticle.resize(nSize);
		
	m_vecEffect.push_back(e);
}

void cFireEffect::Update()
{
	m_vecEffect[0].matTowerWorld = m_vTowerWorld;
	m_vecEffect[1].vPosition = m_vEnemyPos;

	static float fMove = 0.0f;
	fMove -= 0.005f;

	for (int j = 0; j < m_vecEffect.size(); j++)
	{
		m_vecEffect[j].vPosition.z += fMove;

		if (fMove <= -0.06f)
		{
			m_vecEffect[j].vPosition = D3DXVECTOR3(2000, 2000, 2000);
		}

		if (fMove <= -0.13f)
		{
			m_vecEffect[j].vPosition = D3DXVECTOR3(0, 16, -11);
			fMove = 0.0f;
		}

		static int nAlpha = 0;
		static int nDelta = 14;

		nAlpha += nDelta;

		if (nAlpha > 255)
		{
			nAlpha = 255;
			nDelta *= -1;

			for (int i = 0; i < m_vecEffect[j].vecParticle.size(); i++)
			{
				float fRadius = rand() % 100 / 10.0f;
				m_vecEffect[j].vecParticle[i].p = D3DXVECTOR3(0, 0, fRadius);
				
				D3DXVECTOR3 vAngle;

				if (m_vecEffect[j].eKind == TOWER_FIRE)
				{
					vAngle = D3DXVECTOR3(
						D3DXToRadian(rand() % 350 / 10.0f),
						D3DXToRadian(rand() % 350 / 10.0f),
						D3DXToRadian(rand() % 350 / 10.0f));
				}
				else if (m_vecEffect[j].eKind == TARGET_HIT)
				{
					vAngle = D3DXVECTOR3(
						D3DXToRadian(rand() % 3600 / 10.0f),
						D3DXToRadian(rand() % 3600 / 10.0f),
						D3DXToRadian(rand() % 3600 / 10.0f));
				}

				D3DXMATRIXA16 matRX, matRY, matRZ, matWorld;
				D3DXMatrixRotationX(&matRX, vAngle.x);
				D3DXMatrixRotationY(&matRY, vAngle.y);
				D3DXMatrixRotationZ(&matRZ, vAngle.z);
				matWorld = matRX * matRY * matRZ;

				D3DXVec3TransformCoord(&m_vecEffect[j].vecParticle[i].p, &m_vecEffect[j].vecParticle[i].p, &matWorld);
			}
		}

		if (nAlpha < 0)
		{
			nAlpha = 0;
			nDelta *= -1;

			for (int i = 0; i < m_vecEffect[j].vecParticle.size(); i++)
			{
				float fRadius = rand() % 100 / 10.0f;
				m_vecEffect[j].vecParticle[i].p = D3DXVECTOR3(0, 0, fRadius);
				
				D3DXVECTOR3 vAngle;

				if (m_vecEffect[j].eKind == TOWER_FIRE)
				{
					vAngle = D3DXVECTOR3(
						D3DXToRadian(rand() % 300 / 10.0f),
						D3DXToRadian(rand() % 300 / 10.0f),
						D3DXToRadian(rand() % 300 / 10.0f));
				}
				else if (m_vecEffect[j].eKind == TARGET_HIT)
				{
					vAngle = D3DXVECTOR3(
						D3DXToRadian(rand() % 3600 / 10.0f),
						D3DXToRadian(rand() % 3600 / 10.0f),
						D3DXToRadian(rand() % 3600 / 10.0f));
				}

				D3DXMATRIXA16 matRX, matRY, matRZ, matWorld;
				D3DXMatrixRotationX(&matRX, vAngle.x);
				D3DXMatrixRotationY(&matRY, vAngle.y);
				D3DXMatrixRotationZ(&matRZ, vAngle.z);
				matWorld = matRX * matRY * matRZ;

				D3DXVec3TransformCoord(&m_vecEffect[j].vecParticle[i].p, &m_vecEffect[j].vecParticle[i].p, &matWorld);
			}
		}

		if (m_vecEffect[j].eKind == TOWER_FIRE)
		{
			for (int i = 0; i < m_vecEffect[j].vecParticle.size() - 20; i++)
			{
				m_vecEffect[j].vecParticle[i].c = D3DCOLOR_ARGB(nAlpha, 255, 0, 0);
			}

			for (int i = 180; i < m_vecEffect[j].vecParticle.size(); i++)
			{
				m_vecEffect[j].vecParticle[i].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 0);
			}
		}

		if (m_vecEffect[j].eKind == TARGET_HIT)
		{
			for (int i = 0; i < m_vecEffect[j].vecParticle.size() / 2; i++)
			{
				m_vecEffect[j].vecParticle[i].c = D3DCOLOR_ARGB(nAlpha, 0, 100, 234);
			}

			for (int i = 25; i < m_vecEffect[j].vecParticle.size(); i++)
			{
				m_vecEffect[j].vecParticle[i].c = D3DCOLOR_ARGB(nAlpha, 127, 40, 0);
			}
		}
	}
}

void cFireEffect::Render()
{
	// 포인트 확대여부
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);

	// 기본도형의 사이즈를 거리에 따라서 감소 제어
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(1.0f));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDW(100.0f));

	// 텍스처 알파 옵션 설정
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	// 알파블랜딩 방식 결정
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	for (int i = 0; i < m_vecEffect.size(); i++)
	{
		if (m_vecEffect[i].eKind == TOWER_FIRE)
		{
			// 포인트 사이즈 설정
			g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(10.0f));
		
			D3DXMatrixRotationY(&m_vecEffect[i].matRotY, m_vecEffect[i].fAngleY);
			D3DXMatrixTranslation(&m_vecEffect[i].matTrans, m_vecEffect[i].vPosition.x, m_vecEffect[i].vPosition.y, m_vecEffect[i].vPosition.z);
			m_vecEffect[i].matWorld = m_vecEffect[i].matRotY * m_vecEffect[i].matTrans * m_vecEffect[i].matTowerWorld;
		}
		else if (m_vecEffect[i].eKind == TARGET_HIT)
		{
			// 포인트 사이즈 설정
			g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(25.0f));

			D3DXMatrixTranslation(&m_vecEffect[i].matTrans, m_vecEffect[i].vPosition.x, m_vecEffect[i].vPosition.y, m_vecEffect[i].vPosition.z);
			m_vecEffect[i].matWorld = m_vecEffect[i].matTrans;
		}

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecEffect[i].matWorld);
		g_pD3DDevice->SetFVF(ST_PC_VERTEXT::FVF);
		g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture(m_vecEffect[i].pFullPath));
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, m_vecEffect[i].vecParticle.size(), &m_vecEffect[i].vecParticle[0], sizeof(ST_PC_VERTEXT));
	}

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
