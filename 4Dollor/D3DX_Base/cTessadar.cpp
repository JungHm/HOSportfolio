#include "stdafx.h"
#include "cTessadar.h"


cTessadar::cTessadar()
	: m_ft(0.1f)
	, vPos(0, 0, 0)
	, vDir(0, 0, 1)
	, m_fBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
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
	m_fPassedBlendTime += g_pTimeManager->GetEllapsedTime();

	if (m_fPassedBlendTime > m_fBlendTime)
	{
		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, 1.0f);
		XFile->GetAniCtrl(xKey)->SetTrackEnable(1, false);
	}
	else
	{
		float fWeight = m_fPassedBlendTime / m_fBlendTime;
		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, fWeight);
		XFile->GetAniCtrl(xKey)->SetTrackWeight(1, 1.0f - fWeight);
	}




	XFile->GetAniCtrl(xKey)->AdvanceTime(g_pTimeManager->GetEllapsedTime(), NULL);



	//m_ft += 0.01f;
	//if (m_State != ATTACK)
	//XFile->GetAniCtrl(xKey)->AdvanceTime(0.018f, NULL);
	double a = XFile->GetAniCtrl(xKey)->GetTime();
	//LPD3DXANIMATIONSET pAS;

	ChangeAni();

	XFile->GetXFile(xKey)->Update();



}

void cTessadar::Render(D3DXMATRIXA16& matRT)
{
	XFile->GetXFile(xKey)->Render(matRT);
	D3DXMATRIXA16 matR; D3DXMatrixIdentity(&matR);

}

void cTessadar::ChangeAni()
{
	LPD3DXANIMATIONSET pAS = nullptr;
	LPD3DXANIMATIONSET pASCompare = nullptr;
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
	case SPELL_Q:
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
	case SPELL_W:
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
	case SPELL_E:
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
	case SPELL_R:
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

	SAFE_RELEASE(pAS);
	SAFE_RELEASE(pASCompare);
}

void cTessadar::BlendAni(int State)
{
	if (State == m_State) return;
	m_State = State;
	m_fPassedBlendTime = 0.0f;

	LPD3DXANIMATIONSET		pCurrAnimSet = NULL;
	LPD3DXANIMATIONSET		pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;
	switch (m_State)
	{
	case ATTACK:
		XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(1, pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackDesc(1, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwAttack, &pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0.0f);

		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, 0.0f);
		XFile->GetAniCtrl(xKey)->SetTrackWeight(1, 1.0f);
		break;
	case SPELL_Q:
		XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(1, pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackDesc(1, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwSpell, &pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0.0f);

		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, 0.0f);
		XFile->GetAniCtrl(xKey)->SetTrackWeight(1, 1.0f);
		break;
	case SPELL_W:
		XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(1, pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackDesc(1, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwSpell, &pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0.0f);

		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, 0.0f);
		XFile->GetAniCtrl(xKey)->SetTrackWeight(1, 1.0f);
		break;
	case SPELL_E:
		XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(1, pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackDesc(1, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwSpell, &pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0.0f);

		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, 0.0f);
		XFile->GetAniCtrl(xKey)->SetTrackWeight(1, 1.0f);
		break;
	case SPELL_R:
		XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(1, pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackDesc(1, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwSpell, &pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0.0f);

		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, 0.0f);
		XFile->GetAniCtrl(xKey)->SetTrackWeight(1, 1.0f);
		break;
	case STAND:
		XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(1, pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackDesc(1, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwStand, &pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0.0f);

		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, 0.0f);
		XFile->GetAniCtrl(xKey)->SetTrackWeight(1, 1.0f);
		break;
	case WALK:
		XFile->GetAniCtrl(xKey)->GetTrackDesc(0, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetTrackAnimationSet(0, &pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(1, pCurrAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackDesc(1, &stTrackDesc);

		XFile->GetAniCtrl(xKey)->GetAnimationSet(dwWalk, &pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackAnimationSet(0, pNextAnimSet);
		XFile->GetAniCtrl(xKey)->SetTrackPosition(0, 0.0f);

		XFile->GetAniCtrl(xKey)->SetTrackWeight(0, 0.0f);
		XFile->GetAniCtrl(xKey)->SetTrackWeight(1, 1.0f);
		break;
	}
}

