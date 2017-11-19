#include "stdafx.h"
#include "cUIImageView.h"

cUIImageView::cUIImageView()
	: m_pTexture(NULL)
{
}

cUIImageView::~cUIImageView()
{
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	if (m_isHidden) return;

	pSprite->Begin(0);

	pSprite->SetTransform(&m_matWorld);
	RECT rc;
	SetRect(&rc, 0, 0, m_sSize.nWidth, m_sSize.nWidth);
	pSprite->Draw(m_pTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(255, 255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}

void cUIImageView::SetTexture(string szFullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetTexture(szFullPath, &stImageInfo);
	m_sSize.nWidth = stImageInfo.Width;
	m_sSize.nHeight = stImageInfo.Height;
}
