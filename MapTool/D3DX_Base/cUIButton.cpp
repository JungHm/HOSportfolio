#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
	: m_eButtonState(BTN_NORMAL)
	, m_pDelegate(NULL)
{
}

cUIButton::~cUIButton()
{
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(0);
	
	pSprite->SetTransform(&m_matWorld);
	RECT rc;
	SetRect(&rc, 0, 0, m_sSize.nWidth, m_sSize.nHeight);
	pSprite->Draw(m_pArrTexture[m_eButtonState],
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}

void cUIButton::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	RECT rc;
	SetRect(&rc,
		(int)m_matWorld._41,
		(int)m_matWorld._42,
		(int)m_matWorld._41 + (int)m_sSize.nWidth - m_fRectSizeMin,
		(int)m_matWorld._42 + (int)m_sSize.nHeight - m_fRectSizeMin);

	if (PtInRect(&rc, pt))
	{
		if (KEY->isOnceKeyDown(VK_RBUTTON))
		{
			if (m_eButtonState == BTN_MOUSE_OVER)
			{
				m_eButtonState = BTN_SELECTED;
			}
		}
		else
		{
			if (m_eButtonState == BTN_SELECTED)
			{
				// 딜리게이트 호출(기능 호출)
				if (m_pDelegate) m_pDelegate->OnClick(this);
			}

			m_eButtonState = BTN_MOUSE_OVER;
		}
	}
	else
	{
		m_eButtonState = BTN_NORMAL;
	}

	cUIObject::Update();
}

void cUIButton::SetTexture(char * szNormal, char * szOver, char * szSelected)
{
	D3DXIMAGE_INFO	stImageInfo;

	m_pArrTexture[BTN_NORMAL] = g_pTextureManager->GetTexture(szNormal, &stImageInfo);
	m_sSize.nWidth = stImageInfo.Width;
	m_sSize.nHeight = stImageInfo.Height;

	m_pArrTexture[BTN_MOUSE_OVER] = g_pTextureManager->GetTexture(szOver, &stImageInfo);
	assert(m_sSize.nWidth == stImageInfo.Width && m_sSize.nHeight == stImageInfo.Height);

	m_pArrTexture[BTN_SELECTED] = g_pTextureManager->GetTexture(szSelected, &stImageInfo);
	assert(m_sSize.nWidth == stImageInfo.Width && m_sSize.nHeight == stImageInfo.Height);
}
