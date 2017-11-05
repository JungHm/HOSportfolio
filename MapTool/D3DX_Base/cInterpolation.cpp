#include "stdafx.h"
#include "cInterpolation.h"
#include "cCubeMan.h"
#include "cActionLinear.h"
#include "cActionBezier.h"
#include "cActionSeq.h"
#include "cActionRepeat.h"


cInterpolation::cInterpolation()
{
}


cInterpolation::~cInterpolation()
{
	for (int i = 0; i < 2; i++)
	{
		SAFE_DELETE(m_arrCubeMan[i]);
	}
}

void cInterpolation::Setup()
{
	for (int i = 0; i < 2; i++)
	{
		m_arrCubeMan[i] = new cCubeMan;
		m_arrCubeMan[i]->Setup();
	}

	for (int i = 0; i < 6; i++)
	{
		D3DXVECTOR3 vPos = D3DXVECTOR3(
			cosf(i * D3DX_PI / 3.0f) * 10.0f,
			0.0f,
			sinf(i * D3DX_PI / 3.0f) * 10.0f);

		ST_PC_VERTEXT v;
		v.p = vPos;
		v.c = D3DXCOLOR((rand() % 256) / 256.0f,
			(rand() % 256) / 256.0f,
			(rand() % 256) / 256.0f,
			1.0f);
		m_vecLineVertex.push_back(v);
	}
	m_vecLineVertex.push_back(m_vecLineVertex.front());

	cActionSeq* pActionSeq = new cActionSeq;

	for (int i = 0; i < m_vecLineVertex.size() - 1; i++)
	{
		cActionLinear* pActionLinear = new cActionLinear;
		pActionLinear->SetFrom(m_vecLineVertex[i].p);
		pActionLinear->SetTo(m_vecLineVertex[i + 1].p);
		pActionLinear->SetActionTime(5.0f);
		pActionLinear->SetOwner(m_arrCubeMan[0]);
		pActionLinear->SetDelegate(pActionSeq);

		pActionSeq->AddAction(pActionLinear);
	}

	m_arrCubeMan[0]->SetAction(pActionSeq);
	pActionSeq->Start();


	cActionRepeat* pActionRepeat = new cActionRepeat;
	cActionSeq* pActionBezierSeq = new cActionSeq;
	pActionBezierSeq->SetDelegate(pActionRepeat);

	for (int i = 0; i < m_vecLineVertex.size() - 2; i += 2)
	{
		cActionBezier* pActionBezier = new cActionBezier;
		pActionBezier->SetFrom(m_vecLineVertex[i].p);
		pActionBezier->SetVia(m_vecLineVertex[i + 1].p);
		pActionBezier->SetTo(m_vecLineVertex[i + 2].p);
		pActionBezier->SetActionTime(5.0f);
		pActionBezier->SetOwner(m_arrCubeMan[1]);
		pActionBezier->SetDelegate(pActionBezierSeq);

		pActionBezierSeq->AddAction(pActionBezier);
	}
	pActionRepeat->SetAction(pActionBezierSeq);

	m_arrCubeMan[1]->SetAction(pActionRepeat);
	pActionRepeat->Start();
}

void cInterpolation::Update()
{
	//for (int i = 0; i < 2; i++)
	//{
	//	m_arrCubeMan[i]->Update();
	//}
}

void cInterpolation::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEXT::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP,
		m_vecLineVertex.size() - 1,
		&m_vecLineVertex[0],
		sizeof(ST_PC_VERTEXT));


	for (int i = 0; i < 2; i++)
	{
		m_arrCubeMan[i]->Render();
	}
}

void cInterpolation::OnActionFinish(cAction * pSender)
{
}
