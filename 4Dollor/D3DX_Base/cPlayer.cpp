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

	level = 1; experience = 2;
	m_Hp = m_Mp = Att = 100;
	m_Shield = 10;
	distance = 0.0f;
	isQcool = isWcool = isEcool = isAttack = false;
	coolQ = 0.0f;
	coolW = 0.0f;
	coolE = 0.0f;
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pChar);
}

void cPlayer::Setup()
{
	m_pChar->SetUp();
}

void cPlayer::Update()
{
	m_pSphere.fRadius = m_Radius;
	m_pSphere.vCenter = m_vPosition;

	m_pChar->Update();
	m_pChar->SetmousePos(m_ptMouse);
	if ((GetAsyncKeyState(VK_F2) & 0x8001) && level <= 20)//치트키 레벨업
	{
		experience += 2;
		if (experience / 100 >= 1)
		{
			level += experience / 100;
			experience = 0;
		}
	}

	//====================쿨타임 업데이트=============================
	//쿨넘겨주기위해
	coolQ = m_pChar->GetCoolQ();
	coolW = m_pChar->GetCoolW();
	coolE = m_pChar->GetCoolE();
	if (coolQ > 0.0f)// 쿨타임 max 보다 작다면 쿨을 돌려준다
	{

		m_pChar->SetCoolQ(coolQ - g_pTimeManager->GetEllapsedTime());
		isQcool = true;
	}
	else isQcool = false;
	if (coolW > 0.0f)// 쿨타임 max 보다 작다면 쿨을 돌려준다
	{
		m_pChar->SetCoolW(coolW - g_pTimeManager->GetEllapsedTime());
		isWcool = true;
	}
	else isWcool = false;

	if (coolE > 0.0f)// 쿨타임 max 보다 작다면 쿨을 돌려준다
	{
		m_pChar->SetCoolE(coolE - g_pTimeManager->GetEllapsedTime());
		isEcool = true;
	}
	else isEcool = false;
	
	//===============================================================
	//====================스킬 시전=============================
	if (GetAsyncKeyState('Q') & 0x8001)
	{
		if (m_pChar->GetCoolQ() <= 0.0f)
		{
			m_pChar->Setskill(SPELL_Q);
			
		}
	}
	if ((GetAsyncKeyState('W') & 0x8001) && level >= 2)
	{
		if (m_pChar->GetCoolW() <= 0.0f)
		{
			m_pChar->Setskill(SPELL_W);
			m_pChar->BlendAni(m_pChar->Getskill());
			m_pChar->SetCoolW(10.0f);
		}
	}
	if ((GetAsyncKeyState('E') & 0x8001) && level >= 3)
	{
		if (m_pChar->GetCoolE() <= 0.0f)
		{
			m_pChar->Setskill(SPELL_E);
			m_pChar->BlendAni(m_pChar->Getskill());
			m_pChar->SetCoolE(10.0f);
		}
	}

	//==========================================================

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		if (m_pChar->Getskill() != NULL)// 스킬에 예약된 무언가가 있다면 
		{
			m_pChar->BlendAni(m_pChar->Getskill());
			m_pChar->Setskill(NULL);//스킬 사용후 NULL로
			m_pChar->SetCoolQ(10.0f);
		}
	}
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8001)
	{
		isAttack = true;//적을 피킹했을때만 true 나머지는 false
		m_pChar->Setskill(NULL);
	}

	if (distance >= 5.0f && isAttack)
	{
		m_pChar->BlendAni(ATTACK);
		isAttack = false;
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
