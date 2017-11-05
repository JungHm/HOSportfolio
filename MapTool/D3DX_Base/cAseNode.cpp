#include "stdafx.h"
#include "cAseNode.h"


cAseNode::cAseNode()
	: m_pMtlTex(NULL)
	, m_pVB(NULL)
	, m_nNumTri(0)
{
}


cAseNode::~cAseNode()
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pVB);
}

void cAseNode::AddChild(cAseNode * pChild)
{
	m_vecChild.push_back(pChild);
}

void cAseNode::Update(int nKeyFrame, D3DXMATRIXA16 * pMatParent)
{
	// 프레임에 해당하는 matR, matT 계산
	D3DXMATRIXA16	matR, matT;
	CalcLoaclRotation(nKeyFrame, matR);
	CalcLoaclTranslation(nKeyFrame, matT);

	m_matLocalTM = matR * matT;

	m_matWorldTM = m_matLocalTM;
	// 부모가 있으면 
	if (pMatParent)
	{
		m_matWorldTM *= (*pMatParent);
	}

	// 자식 업데이트
	for each (auto child in m_vecChild)
	{
		child->Update(nKeyFrame, &m_matWorldTM);
	}
}

void cAseNode::Render()
{
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMaterial());
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEXT::FVF);

		g_pD3DDevice->SetStreamSource(0,
			m_pVB,
			0,
			sizeof(ST_PNT_VERTEXT));
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0,
			m_nNumTri);

		//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		//	m_vecVertex.size() / 3,
		//	&m_vecVertex[0],
		//	sizeof(ST_PNT_VERTEXT));
	}

	for each (auto child in m_vecChild)
	{
		child->Render();
	}
}

void cAseNode::Destroy()
{
	for each (auto child in m_vecChild)
	{
		child->Destroy();
	}
	m_vecChild.clear();

	this->Release();
}

void cAseNode::CalcOriginLocalTM(D3DXMATRIXA16 * pMatParent)
{
	m_matLocalTM = m_matWorldTM;
	if (pMatParent)
	{
		D3DXMATRIXA16	matInv;
		D3DXMatrixInverse(&matInv, 0, pMatParent);
		m_matLocalTM = m_matWorldTM * matInv;
	}

	for each (auto child in m_vecChild)
	{
		child->CalcOriginLocalTM(&m_matWorldTM);
	}
}

void cAseNode::CalcLoaclRotation(int nKeyFrame, D3DXMATRIXA16 & matR)
{
	D3DXMatrixIdentity(&matR);
	if (m_vecRotTrack.empty())
	{
		matR = m_matLocalTM;
		matR._41 = 0.0f;
		matR._42 = 0.0f;
		matR._43 = 0.0f;
		return;
	}

	if (nKeyFrame <= m_vecRotTrack.front().nFrame)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.front().q);
		return;
	}

	if (nKeyFrame >= m_vecRotTrack.back().nFrame)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.back().q);
		return;
	}

	int nIndex = 0;
	for (size_t i = 0; i < m_vecRotTrack.size(); i++)
	{
		if (nKeyFrame < m_vecRotTrack[i].nFrame)
		{
			nIndex = i;
			break;
		}
	}

	float t = (nKeyFrame - m_vecRotTrack[nIndex - 1].nFrame) /
		(float)(m_vecRotTrack[nIndex].nFrame - m_vecRotTrack[nIndex - 1].nFrame);

	D3DXQUATERNION q;
	D3DXQuaternionSlerp(&q, &m_vecRotTrack[nIndex - 1].q, &m_vecRotTrack[nIndex].q, t);
	D3DXMatrixRotationQuaternion(&matR, &q);
}

void cAseNode::CalcLoaclTranslation(int nKeyFrame, D3DXMATRIXA16 & matT)
{
	D3DXMatrixIdentity(&matT);
	if (m_vecPosTrack.empty())
	{
		matT._41 = m_matLocalTM._41;
		matT._42 = m_matLocalTM._42;
		matT._43 = m_matLocalTM._43;
		return;
	}

	if (nKeyFrame <= m_vecPosTrack.front().nFrame)
	{
		matT._41 = m_vecPosTrack.front().v.x;
		matT._42 = m_vecPosTrack.front().v.y;
		matT._43 = m_vecPosTrack.front().v.z;
		return;
	}

	if (nKeyFrame >= m_vecPosTrack.back().nFrame)
	{
		matT._41 = m_vecPosTrack.back().v.x;
		matT._42 = m_vecPosTrack.back().v.y;
		matT._43 = m_vecPosTrack.back().v.z;
		return;
	}


	int nIndex = 0;
	for (size_t i = 0; i < m_vecPosTrack.size(); i++)
	{
		if (nKeyFrame < m_vecPosTrack[i].nFrame)
		{
			nIndex = i;
			break;
		}
	}

	float t = (nKeyFrame - m_vecPosTrack[nIndex - 1].nFrame) /
		(float)(m_vecPosTrack[nIndex].nFrame - m_vecPosTrack[nIndex - 1].nFrame);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v, &m_vecPosTrack[nIndex - 1].v, &m_vecPosTrack[nIndex].v, t);
	matT._41 = v.x;
	matT._42 = v.y;
	matT._43 = v.z;
}

void cAseNode::BuildVB(std::vector<ST_PNT_VERTEXT>& vecVertex)
{
	m_nNumTri = vecVertex.size() / 3;
	g_pD3DDevice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PNT_VERTEXT),
		0,
		ST_PNT_VERTEXT::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	ST_PNT_VERTEXT* pV = NULL;
	m_pVB->Lock(0, 0,
		(void**)&pV, 0);

	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEXT));

	m_pVB->Unlock();
}

int cAseNode::GetKeyFrame()
{
	int first = m_dwFirstFrame * m_dwTicksPerFrame;
	int last = m_dwLastFrame * m_dwTicksPerFrame;
	return GetTickCount() % (last - first) + first;
}
