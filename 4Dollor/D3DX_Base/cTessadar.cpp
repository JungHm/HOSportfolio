#include "stdafx.h"
#include "cTessadar.h"


cTessadar::cTessadar()
	: m_ft(0.1f)
	, vPos(0, 0, 0)
	, vDir(0, 0, 1)
{
	m_dTimeCurrent = 0;
	m_sPath = L"Tassadar/Tassadar.X";
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	dwCurr = 0;

	m_State = STAND;
	xKey = 0;
}


cTessadar::~cTessadar()
{
}

void cTessadar::AnimSetUp()
{

	LPD3DXANIMATIONSET pAS;

	for (DWORD i = 0; i < XFile->GetAniCtrl(xKey)->GetNumAnimationSets(); ++i)
	{
		XFile->GetAniCtrl(xKey)->GetAnimationSet(i, &pAS);

		if (!strncmp(pAS->GetName(), "Attack ", strlen(pAS->GetName())))
		{
			dwAttack = i;
		}
		else if (!strncmp(pAS->GetName(), "Spell ", strlen(pAS->GetName())))
		{
			dwSpell = i;
		}
		else if (!strncmp(pAS->GetName(), "Stand ", strlen(pAS->GetName())))
		{
			dwStand = i;
		}
		else if (!strncmp(pAS->GetName(), "Walk ", strlen(pAS->GetName())))
		{
			dwWalk = i;
		}
	}

	XFile->GetAniCtrl(xKey)->GetAnimationSet(dwAttack, &pAS);
	XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pAS);
	XFile->GetAniCtrl(xKey)->ResetTime();
}

void cTessadar::SetUp()
{
	XFile->SetXFile(xKey, m_sPath);
	this->AnimSetUp();
}

void cTessadar::Update()
{
	XFile->GetAniCtrl(xKey)->AdvanceTime(m_dTimeCurrent, NULL);



	//m_ft += 0.01f;
	//if (m_State != ATTACK)
	XFile->GetAniCtrl(xKey)->AdvanceTime(0.018f, NULL);
	double a = XFile->GetAniCtrl(xKey)->GetTime();
	LPD3DXANIMATIONSET pAS;
	if (GetAsyncKeyState('1') & 0x8000)
	{
		m_State = dwAttack;
	}
	if (GetAsyncKeyState('2') & 0x8000)
	{
		m_State = dwSpell;
	}
	if (GetAsyncKeyState('3') & 0x8000)
	{
		m_State = dwStand;
	}
	if (GetAsyncKeyState('4') & 0x8000)
	{
		m_State = dwWalk;
	}
	ChangeAni();
	XFile->GetXFile(xKey)->Update();

	
}

void cTessadar::Render()
{
	XFile->GetXFile(xKey)->Render();
	D3DXMATRIXA16 matR; D3DXMatrixIdentity(&matR);

}

void cTessadar::ChangeAni()
{
	LPD3DXANIMATIONSET pAS;
	LPD3DXANIMATIONSET pASCompare;
	D3DXTRACK_DESC desc;
	switch (m_State)
	{
	case ATTACK:
		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwAttack, &pAS);
		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pASCompare);
		if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		{
			XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &desc);
			if (desc.Position + 0.2 >= pAS->GetPeriod())
			{
				m_State = STAND;
			}
		}
		else
		{
			XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pAS);
			XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0);
		}
		break;
	case SPELL:
		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwSpell, &pAS);
		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pASCompare);
		if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		{
			XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &desc);
			if (desc.Position + 0.2 >= pAS->GetPeriod())
			{
				m_State = STAND;
			}
		}
		else
		{
			XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pAS);
			XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0);
		}
		break;

	case STAND:
		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwStand, &pAS);
		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pASCompare);
		if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		{
			break;
		}
		else
		{
			XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pAS);
			XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0);
		}
		break;

	case WALK:
		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwWalk, &pAS);
		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pASCompare);
		if (!strcmp(pAS->GetName(), pASCompare->GetName())) //이미 Idle인 경우.
		{
			break;
		}
		else
		{
			XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pAS);
			XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0);
		}
		break;
	}
}
