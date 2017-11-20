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
	Attack = false;
	level = experience = 0;
	Att = 100;
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
	if ((GetAsyncKeyState(VK_F2) & 0x8001))//치트키 레벨업
	{
		experience += 2;
		if (experience / 100 >= 1)
		{
			level += experience / 100;
			experience = 0;
		}
	}

	m_pChar->Update();
	m_pChar->SetmousePos(m_ptMouse);
	if (GetAsyncKeyState('Q') & 0x8001)
	{
		//if(coolQ==0)//쿨다운이 0일때 스킬 사용할수 있게
		m_pChar->Setskill(SPELL_Q);
	}
	if ((GetAsyncKeyState('W') & 0x8001) && level == 2)
	{
		//if(coolW==0)//쿨다운이 0일때 스킬 사용할수 있게
		m_pChar->Setskill(SPELL_W);
	}
	if ((GetAsyncKeyState('E') & 0x8001) && level == 3)
	{
		//if(coolE==0)//쿨다운이 0일때 스킬 사용할수 있게
		m_pChar->Setskill(SPELL_E);
	}
	if ((GetAsyncKeyState('R') & 0x8001) && level == 4)// 궁극기는 사용할지 안할지 모름
	{
		m_pChar->Setskill(SPELL_R);
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		if (m_pChar->Getskill() != NULL)// 스킬에 예약된 무언가가 있다면 
		{
			m_pChar->BlendAni(m_pChar->Getskill());
			m_pChar->Setskill(NULL);//스킬 사용후 NULL로
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8001)
	{
		m_pChar->Setskill(NULL);
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

void cPlayer::Update(POINT mouse)
{
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
	//matR *= matT;
	m_pChar->Render(matR, matT);
}

void cPlayer::Destroy()
{
	SAFE_DELETE(m_pChar);
}
