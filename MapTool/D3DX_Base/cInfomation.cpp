#include "stdafx.h"
#include "cInfomation.h"

cInfomation::cInfomation()
	: m_pFont(NULL)
	, m_fScale(0.0f)
	, m_fRotation(0.0f)
	, m_vPosition(0.0f, 0.0f, 0.0f)
	, m_eObjKind(0)
	, m_nObjNum(0)
{
}

cInfomation::~cInfomation()
{
	SAFE_RELEASE(m_pFont);
}

void cInfomation::Setup()
{
	m_pFont = g_pFontManager->GetFont(FT_QUEST, 12, 23);
}

void cInfomation::Render()
{
	char szWolrdTime[124];
	char szScale[124];
	char szRot[124];
	char szPosX[124];
	char szPosY[124];
	char szPosZ[124];
	char szKind[124];
	char szNum[124];

	sprintf_s(szWolrdTime, "World Time : %f", g_pTimeManager->GetWorldTime());
	sprintf_s(szScale, "Scale         : %.2f", m_fScale * 100.0f);
	sprintf_s(szRot, "Rotation	    : %d", (int)(m_fRotation * 57.3f));
	sprintf_s(szPosX, "Position.X : %.1f", m_vPosition.x);
	sprintf_s(szPosY, "Position.Y : %.1f", m_vPosition.y);
	sprintf_s(szPosZ, "Position.Z : %.1f", m_vPosition.z);
	sprintf_s(szNum, "TotalObjNum : %d", m_nObjNum);

	switch (m_eObjKind)
	{
	case 0:
		sprintf_s(szKind, "ObjKind    : GATE_01", NULL);
		break;

	case 1:
		sprintf_s(szKind, "ObjKind    : WALL_01", NULL);
		break;

	case 2:
		sprintf_s(szKind, "ObjKind    : WALL_02", NULL);
		break;

	case 3:
		sprintf_s(szKind, "ObjKind    : WALL_03", NULL);
		break;

	case 4:
		sprintf_s(szKind, "ObjKind    : WALL_04", NULL);
		break;

	case 5:
		sprintf_s(szKind, "ObjKind    : WALL_05", NULL);
		break;

	case 6:
		sprintf_s(szKind, "ObjKind    : FOUNTAIN", NULL);
		break;

	case 7:
		sprintf_s(szKind, "ObjKind    : ROCK_00", NULL);
		break;

	case 8:
		sprintf_s(szKind, "ObjKind    : ROCK_04", NULL);
		break;

	case 9:
		sprintf_s(szKind, "ObjKind    : ROCK_05", NULL);
		break;

	default:
		sprintf_s(szKind, "ObjKind    :", NULL);
		break;
	}

	RECT rc1;
	SetRect(&rc1, 0, 0, 20, 30);
	m_pFont->DrawTextA(NULL, szWolrdTime, strlen(szWolrdTime), &rc1, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(150, 150, 150));

	RECT rc2;
	SetRect(&rc2, 0, 72, 20, 30);
	m_pFont->DrawTextA(NULL, szScale, strlen(szScale), &rc2, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	RECT rc3;
	SetRect(&rc3, 0, 92, 20, 30);
	m_pFont->DrawTextA(NULL, szRot, strlen(szRot), &rc3, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	RECT rc4;
	SetRect(&rc4, 0, 112, 20, 30);
	m_pFont->DrawTextA(NULL, szPosX, strlen(szPosX), &rc4, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	RECT rc5;
	SetRect(&rc5, 0, 132, 20, 30);
	m_pFont->DrawTextA(NULL, szPosY, strlen(szPosY), &rc5, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	RECT rc6;
	SetRect(&rc6, 0, 152, 20, 30);
	m_pFont->DrawTextA(NULL, szPosZ, strlen(szPosZ), &rc6, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));

	RECT rc7;
	SetRect(&rc7, 0, 50, 20, 30);
	m_pFont->DrawTextA(NULL, szKind, strlen(szKind), &rc7, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 0));

	RECT rc8;
	SetRect(&rc8, 0, 28, 20, 30);
	m_pFont->DrawTextA(NULL, szNum, strlen(szNum), &rc8, DT_LEFT | DT_TOP | DT_NOCLIP, D3DCOLOR_XRGB(255, 0, 0));
}
