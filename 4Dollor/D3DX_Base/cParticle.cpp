#include "stdafx.h"
#include "cParticle.h"

DWORD FtoDW(float f)
{
	return *((DWORD*)&f);
}

cParticle::cParticle()
{
}


cParticle::~cParticle()
{
}

void cParticle::SetupParticle(int num, D3DXCOLOR c)
{
	m_vecParticle.resize(1000);
	for (int i = 0; i < m_vecParticle.size(); i++)
	{
		float fRadius = rand() % 100 / 10.0f;
		m_vecParticle[i].p = D3DXVECTOR3(0, 0, fRadius);

		D3DXVECTOR3 vAngle = D3DXVECTOR3(
			D3DXToRadian(rand() % 3600 / 10.0f),
			D3DXToRadian(rand() % 3600 / 10.0f),
			D3DXToRadian(rand() % 3600 / 10.0f));

		D3DXMATRIXA16 matRX, matRY, matRZ, matWorld;
		D3DXMatrixRotationX(&matRX, vAngle.x);
		D3DXMatrixRotationY(&matRY, vAngle.y);
		D3DXMatrixRotationZ(&matRZ, vAngle.z);
		matWorld = matRX * matRY * matRZ;

		D3DXVec3TransformCoord(
			&m_vecParticle[i].p,
			&m_vecParticle[i].p,
			&matWorld);

		color = c;
		m_vecParticle[i].c = c;// D3DCOLOR_ARGB(255, 150, 60, 70);
	}

	// 포인트 확대여부
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	// 포인트 사이즈 설정
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(5.0f));

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
}

void cParticle::RenderParticle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetFVF(ST_PC_VERTEXT::FVF);
	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("batman.png"));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST,
		m_vecParticle.size(),
		&m_vecParticle[0],
		sizeof(ST_PC_VERTEXT));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

void cParticle::UpdateParticle()
{
	static int nAlpha = 0;
	static int nDelta = 5;
	nAlpha += nDelta;
	if (nAlpha > 255)
	{
		nAlpha = 255;
		nDelta *= -1;
	}
	if (nAlpha < 0)
	{
		nAlpha = 0;
		nDelta *= -1;
	}
	for (int i = 0; i < m_vecParticle.size(); i++)
	{
		m_vecParticle[i].c = color;// D3DCOLOR_ARGB(nAlpha, 150, 60, 70);
	}
}
