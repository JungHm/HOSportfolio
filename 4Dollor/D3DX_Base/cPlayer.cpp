#include "stdafx.h"
#include "cPlayer.h"
#include "cCharacter.h"

cPlayer::cPlayer()
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, -1)
{
	m_vFrom = m_vPosition;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matT); D3DXMatrixIdentity(&matR);
}


cPlayer::~cPlayer()
{
}

void cPlayer::Setup()
{
	m_pChar->SetUp();
}

void cPlayer::Update()
{

	m_pChar->Update();
	if (GetAsyncKeyState('Q') & 0x8001)
	{
		m_pChar->BlendAni(SPELL_Q);
		Skill = SPELL_Q;
	}
	if (GetAsyncKeyState('W') & 0x8001)
	{
		Skill = SPELL_W;
	}
	if (GetAsyncKeyState('E') & 0x8001)
	{
		Skill = SPELL_E;
	}
	if (GetAsyncKeyState('R') & 0x8001)
	{
		Skill = SPELL_R;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		if (Skill != NULL)// 스킬에 예약된 무언가가 있다면 
		{

			m_pChar->BlendAni(Skill);
			Skill = NULL;//스킬 사용후 NULL로
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8001)
	{
		Skill = NULL;
	}
	if (Attack == true)
	{
		m_pChar->BlendAni(ATTACK);
	}

	D3DXVec3Normalize(&m_vDirection, &m_vDirection);
	D3DXVECTOR3 vUp(0, 1, 0);
	D3DXVECTOR3 vRight;
	D3DXVec3Cross(&vRight, &vUp, &m_vDirection);
	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Cross(&vUp, &m_vDirection, &vRight);
	D3DXMatrixLookAtLH(&matR, &D3DXVECTOR3(0, 0, 0), &-m_vDirection, &vUp);
	D3DXMatrixTranspose(&matR, &matR);


	if (m_pChar->GetState() == STAND || m_pChar->GetState() == WALK)
		moveTo();
}

void cPlayer::moveTo()
{
	if ((int)m_vPosition.x == (int)m_vFrom.x || (int)m_vPosition.z == (int)m_vFrom.z)
	{
		m_pChar->BlendAni(STAND);
		return;
	}

	m_vPosition += (m_vDirection / 10) * 5;
	m_pChar->BlendAni(WALK);
}


void cPlayer::Render()
{
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matR *= matT;
	m_pChar->Render(matR);
}

void cPlayer::Destroy()
{
	SAFE_DELETE(m_pChar);
}
