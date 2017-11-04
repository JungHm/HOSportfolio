#include "stdafx.h"
#include "cAseNode.h"


void cAseNode::CalcLoaclRotation(int nKeyFrame, OUT D3DXMATRIXA16 & matR)
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
	if (nKeyFrame <= m_vecRotTrack.front().frame)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.front().rot);
		return;
	}
	else if (nKeyFrame >= m_vecRotTrack.back().frame)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.back().rot);
		return;
	}

	int nNextIndex = 0;
	for (UINT i = 0; i < m_vecRotTrack.size(); i++)
	{
		if (nKeyFrame < m_vecRotTrack[i].frame)
		{
			nNextIndex = i;
			break;
		}
	}

	int nPrevIndex = nNextIndex - 1;

	float t = (nKeyFrame - m_vecRotTrack[nPrevIndex].frame) /
		(float)(m_vecRotTrack[nNextIndex].frame -
			m_vecRotTrack[nPrevIndex].frame);

	D3DXQUATERNION q;
	D3DXQuaternionSlerp(&q, 
		&m_vecRotTrack[nPrevIndex].rot,
		&m_vecRotTrack[nNextIndex].rot, 
		t);
	D3DXMatrixRotationQuaternion(&matR, &q);
}

void cAseNode::CalcLoaclTranslation(int nKeyFrame, OUT D3DXMATRIXA16 & matT)
{
	D3DXMatrixIdentity(&matT);
	if (m_vecPosTrack.empty())
	{
		matT._41 = m_matLocalTM._41;
		matT._42 = m_matLocalTM._42;
		matT._43 = m_matLocalTM._43;
		return;
	}
	if (nKeyFrame <= m_vecPosTrack.front().frame)
	{
		matT._41 = m_vecPosTrack.front().pos.x;
		matT._42 = m_vecPosTrack.front().pos.y;
		matT._43 = m_vecPosTrack.front().pos.z;
		return;
	}
	if (nKeyFrame >= m_vecPosTrack.back().frame)
	{
		matT._41 = m_vecPosTrack.front().pos.x;
		matT._42 = m_vecPosTrack.front().pos.y;
		matT._43 = m_vecPosTrack.front().pos.z;
		return;
	}

	int nNextIndex = 0;
	for (UINT i = 0; i < m_vecPosTrack.size(); i++)
	{
		if (nKeyFrame < m_vecPosTrack[i].frame)
		{
			nNextIndex = i;
			break;
		}
	}

	int nPrevIndex = nNextIndex - 1;

	float t = (nKeyFrame - m_vecPosTrack[nPrevIndex].frame) /
		(float)(m_vecPosTrack[nNextIndex].frame - m_vecPosTrack[nPrevIndex].frame);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v, &m_vecPosTrack[nPrevIndex].pos, &m_vecPosTrack[nNextIndex].pos, t);

	matT._41 = v.x;
	matT._42 = v.y;
	matT._43 = v.z;
}

cAseNode::cAseNode()
	: m_pMtlTex(NULL)
{
}


cAseNode::~cAseNode()
{
	SAFE_RELEASE(m_pMtlTex);
}

void cAseNode::AddChild(cAseNode * pChild)
{
	m_vecChild.push_back(pChild);

}

void cAseNode::Update(int nKeyFrame, D3DXMATRIXA16 * pMatParent)
{
	D3DXMATRIXA16 matR, matT;
	// 프레임에 해당하는 matR, matT 계산
	CalcLoaclRotation(nKeyFrame, matR);
	CalcLoaclTranslation(nKeyFrame, matT);

	m_matLocalTM = matR * matT;
	// 부모가 있으면 
	m_matWorldTM = m_matLocalTM;
	if (pMatParent)
	{
		m_matWorldTM *= (*pMatParent);
	}
	// 자식 업데이트
	for each(auto child in m_vecChild)
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
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEXT::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_PNT_VERTEXT));
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
	//nodeTM = localTM*pMatParent;
	D3DXMATRIXA16 inverseTM;
	D3DXMatrixInverse(&inverseTM, 0, pMatParent);

	m_matLocalTM = m_matWorldTM * inverseTM;
}

int cAseNode::GetKeyFrame()
{
	int first = m_dwFirstFrame * m_dwTicksPerFrame;
	int last = m_dwLastFrame * m_dwTicksPerFrame;
	return GetTickCount() % (last - first) + first;
}
