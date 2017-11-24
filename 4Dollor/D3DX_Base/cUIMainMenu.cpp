#include "stdafx.h"
#include "cUIMainMenu.h"
#include "cUILoadingInGame.h"


cUIMainMenu::cUIMainMenu()
	: m_GameStart(false)
	, m_GameReady(false)
	, m_InGameLoadingEnable(false)
{
}


cUIMainMenu::~cUIMainMenu()
{
}

int cUIMainMenu::updateButtonCallback(int num)
{
	if (num == UIBUTTONCALLBACK_MAIN_READY)
	{
		// 준비 버튼 눌렸을 때 처리
		m_GameReady = true;
		m_MUIButton.find("ready")->second.used = true;
		m_MUIButton.find("ready")->second.buttonState = UIBUTTONSTATE_DISENABLE;
		m_GameReadyTime = GetTickCount() / 1000;
		m_GameReadyEfx.find(m_GameReadyEfxPath[2])->second.enable = true;
	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY)
	{
		if (!m_MUIButton.find("heroabil")->second.selected)
		{
			m_MUIButton.find("heroabil")->second.selected = true;
			m_MUIButton.find("heroinfo")->second.selected = false;
			m_MUIButton.find("herotalent")->second.selected = false;
			heroinfoPopup(true);
		}
		else
		{
			m_MUIButton.find("heroabil")->second.selected = false;
			heroinfoPopup(false);
		}
	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_EQUIP)
	{
		if (!m_MUIButton.find("heroinfo")->second.selected)
		{
			m_MUIButton.find("heroabil")->second.selected = false;
			m_MUIButton.find("heroinfo")->second.selected = true;
			m_MUIButton.find("herotalent")->second.selected = false;
			heroinfoPopup(false);
		}
		else
		{
			m_MUIButton.find("heroinfo")->second.selected = false;
		}
	}
	else if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_TALENT)
	{
		if (!m_MUIButton.find("herotalent")->second.selected)
		{
			m_MUIButton.find("heroabil")->second.selected = false;
			m_MUIButton.find("heroinfo")->second.selected = false;
			m_MUIButton.find("herotalent")->second.selected = true;
			heroinfoPopup(false);
		}
		else
		{
			m_MUIButton.find("herotalent")->second.selected = false;
		}
	}
	return 0;
}

int cUIMainMenu::updateButtonOverCallback(int num)
{
	string s1 = "heroabil_1_popup";
	string s2 = "heroabil_2_popup";
	string s3 = "heroabil_3_popup";
	string s4 = "heroabil_4_popup";
	string s5 = "heroabil_5_popup";
	string s6 = "heroabil_6_popup";
	if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY_1) heroinfoPopup2(s1, true); else heroinfoPopup2(s1, false);
	if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY_2) heroinfoPopup2(s2, true); else heroinfoPopup2(s2, false);
	if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY_3) heroinfoPopup2(s3, true); else heroinfoPopup2(s3, false);
	if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY_4) heroinfoPopup2(s4, true); else heroinfoPopup2(s4, false);
	if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY_5) heroinfoPopup2(s5, true); else heroinfoPopup2(s5, false);
	if (num == UIBUTTONCALLBACK_MAIN_HEROINFO_ABILITY_6) heroinfoPopup2(s6, true); else heroinfoPopup2(s6, false);
	return 0;
}

void cUIMainMenu::heroinfoPopup(bool enable)
{
	for (int i = 0; i < 7; i++)
	{
		string strAbil = "heroabil_" + to_string(i);
		m_MUIButton.find(strAbil)->second.enable = enable;
	}
}

void cUIMainMenu::heroinfoPopup2(string name, bool enable)
{
	m_MUIButton.find(name)->second.enable = enable;
}

void cUIMainMenu::setupOther()
{
	POINT rcSizeReady = { m_MUIButton.find("ready")->second.imgInfo.Width * m_UIScale, m_MUIButton.find("ready")->second.imgInfo.Height * m_UIScale };
	POINT ptReady = { m_MUIButton.find("ready")->second.pt.x, m_MUIButton.find("ready")->second.pt.y };
	POINT rcSizeHeroinfo = { m_MUIButton.find("heroinfo")->second.imgInfo.Width * m_UIScale, m_MUIButton.find("heroinfo")->second.imgInfo.Height * m_UIScale * 2 };
	POINT ptHeroinfo = { m_MUIButton.find("heroinfo")->second.pt.x, m_MUIButton.find("heroinfo")->second.pt.y };
	POINT rcSizeAbility = { m_MUIButton.find("heroabil")->second.imgInfo.Width * m_UIScale, m_MUIButton.find("heroabil")->second.imgInfo.Height * m_UIScale * 2 };
	POINT ptAbility = { m_MUIButton.find("heroabil")->second.pt.x, m_MUIButton.find("heroabil")->second.pt.y };
	POINT rcSizeTalent = { m_MUIButton.find("herotalent")->second.imgInfo.Width * m_UIScale, m_MUIButton.find("herotalent")->second.imgInfo.Height * m_UIScale * 2 };
	POINT ptTalent = { m_MUIButton.find("herotalent")->second.pt.x, m_MUIButton.find("herotalent")->second.pt.y };

	setupTextInput("장비", ptHeroinfo, rcSizeHeroinfo);
	setupTextInput("기술", ptAbility, rcSizeAbility);
	setupTextInput("특성", ptTalent, rcSizeTalent);
	setupTextInput("준비", ptReady, rcSizeReady);

	m_GameReadyEfxPath[0] = L"UI\\mainmenu_img_gamestart_1.dds";
	m_GameReadyEfxPath[1] = L"UI\\mainmenu_img_gamestart_2.dds";
	m_GameReadyEfxPath[2] = L"UI\\mainmenu_img_gamestart_3.dds";

	setupAddTexture(m_GameReadyEfxPath[0]);
	setupAddTexture(m_GameReadyEfxPath[1]);
	setupAddTexture(m_GameReadyEfxPath[2]);
	setupAddFadeImg(L"UI\\black.png");

	m_InGameLoading = new cUILoadingInGame;
	m_InGameLoading->setup("cUILoadingInGame");
}

void cUIMainMenu::setupTextInput(string strName, POINT pt, POINT rcPt)
{
	tagTextView tv;
	tv.alpha = 255;
	tv.pt = pt;
	tv.str = strName;
	SetRect(&tv.rcText, tv.pt.x, tv.pt.y, tv.pt.x + rcPt.x, tv.pt.y + rcPt.y);
	m_VText.push_back(tv);
}

void cUIMainMenu::setupAddTexture(wstring filePath)
{
	tagUISpriteEfx se;
	ZeroMemory(&se, sizeof(tagUISpriteEfx));
	m_GameReadyEfx.insert(make_pair(filePath, se));
	tagUISpriteEfx *pse = &m_GameReadyEfx.find(filePath)->second;

	D3DXMatrixIdentity(&se.matWorld);

	D3DXCreateSprite(g_pD3DDevice, &pse->sprite);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		filePath.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),
		&pse->imgInfo,
		NULL,
		&pse->texture);

	SetRect(&pse->drawRc, 0, 0, pse->imgInfo.Width, pse->imgInfo.Height);
	pse->alpha = 5;
	pse->scale = 2.0f;
	pse->pt = { 750, 250,0 };
}

void cUIMainMenu::setupAddFadeImg(wstring filePath)
{
	m_Fade;

	ZeroMemory(&m_Fade, sizeof(tagUISpriteEfx));

	D3DXMatrixIdentity(&m_Fade.matWorld);

	D3DXCreateSprite(g_pD3DDevice, &m_Fade.sprite);

	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		filePath.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255),
		&m_Fade.imgInfo,
		NULL,
		&m_Fade.texture);

	SetRect(&m_Fade.drawRc, 0, 0, m_Fade.imgInfo.Width, m_Fade.imgInfo.Height);
	m_Fade.alpha = 5;
	m_Fade.scale = 1;
	m_Fade.pt = { 0, 0,0 };
}

void cUIMainMenu::updateOther()
{
	updateGameReady();
}

void cUIMainMenu::updateGameReady()
{
	if (m_GameReady)
	{
		for (m_GameReadyEfxIt = m_GameReadyEfx.begin(); m_GameReadyEfxIt != m_GameReadyEfx.end(); m_GameReadyEfxIt++)
		{
			if (!m_GameReadyEfxIt->second.enable) continue;
			D3DXMatrixIdentity(&m_GameReadyEfxIt->second.matWorld);
			D3DXMATRIXA16 matT, matS;
			D3DXMatrixIdentity(&matT);
			D3DXMatrixIdentity(&matS);
			if (!m_GameReadyEfxIt->second.reverse)
			{
				if (m_GameReadyEfxIt->second.scale > 0.7f)
					m_GameReadyEfxIt->second.scale -= 0.07f;
				if (m_GameReadyEfxIt->second.alpha < 255)
					m_GameReadyEfxIt->second.alpha += 10;
				if (m_GameReadyEfxIt->second.alpha > 255)
					m_GameReadyEfxIt->second.alpha = 255;
				if (m_GameReadyEfxIt->second.scale <= 0.7f && m_GameReadyEfxIt->second.alpha == 255)
				{
					m_GameReadyEfxIt->second.reverse = true;
				}
			}
			else
			{
				if (m_GameReadyEfxIt->second.scale < 0)
					m_GameReadyEfxIt->second.scale = 0;
				else
					m_GameReadyEfxIt->second.scale -= 0.001f;
				if (m_GameReadyEfxIt->second.alpha != 0)
				{
					m_GameReadyEfxIt->second.alpha -= 7;
					if (m_GameReadyEfxIt->second.alpha <= 0)
					{
						m_GameReadyEfxIt->second.alpha = 0;
					}
				}
			}

			D3DXMatrixScaling(&matS, m_GameReadyEfxIt->second.scale, m_GameReadyEfxIt->second.scale, m_GameReadyEfxIt->second.scale);
			D3DXMatrixTranslation(&matT, m_GameReadyEfxIt->second.pt.x, m_GameReadyEfxIt->second.pt.y, m_GameReadyEfxIt->second.pt.z);
			m_GameReadyEfxIt->second.matWorld = matS * matT;
		}
	}

	if (m_GameReadyEfx.find(m_GameReadyEfxPath[2])->second.alpha == 0)
	{
		m_GameReadyEfx.find(m_GameReadyEfxPath[1])->second.enable = true;
	}
	if (m_GameReadyEfx.find(m_GameReadyEfxPath[1])->second.alpha == 0)
	{
		m_GameReadyEfx.find(m_GameReadyEfxPath[0])->second.enable = true;
	}
	if (m_GameReadyEfx.find(m_GameReadyEfxPath[0])->second.alpha == 0)
	{
		m_Fade.enable = true;
	}
}

void cUIMainMenu::renderOther()
{
	for each(auto p in m_VText)
	{
		// 동적할당 해제 안되었다는 오류남
		LPD3DXFONT font = g_pFontManager->GetFont(cFontManager::FT_SMALL);
		font->DrawTextA(NULL, p.str.c_str(), p.str.length(), &p.rcText, DT_CENTER | DT_VCENTER, D3DCOLOR_ARGB(p.alpha, 255, 255, 255));
	}
	renderGameReady();
	if (m_Fade.enable) renderFade();
	if (m_InGameLoadingEnable) renderIngameLoading();
}

void cUIMainMenu::renderGameReady()
{
	if (KEY->isOnceKeyDown('A'))
	{
		for (m_GameReadyEfxIt = m_GameReadyEfx.begin(); m_GameReadyEfxIt != m_GameReadyEfx.end(); m_GameReadyEfxIt++)
		{
			m_GameReadyEfxIt->second.reverse = false;
			m_GameReadyEfxIt->second.alpha = 0;
			m_GameReadyEfxIt->second.scale = 2;
		}
	}
	if (m_GameReady)
	{
		for (m_GameReadyEfxIt = m_GameReadyEfx.begin(); m_GameReadyEfxIt != m_GameReadyEfx.end(); m_GameReadyEfxIt++)
		{
			if (!m_GameReadyEfxIt->second.enable) continue;

			m_GameReadyEfxIt->second.sprite->Begin(D3DXSPRITE_ALPHABLEND);

			D3DXMatrixAffineTransformation2D(&m_GameReadyEfxIt->second.matWorld,
				m_GameReadyEfxIt->second.scale,
				NULL,
				NULL,
				&D3DXVECTOR2(m_GameReadyEfxIt->second.pt.x / 2, m_GameReadyEfxIt->second.pt.y / 2));

			m_GameReadyEfxIt->second.sprite->SetTransform(&m_GameReadyEfxIt->second.matWorld);

			m_GameReadyEfxIt->second.sprite->Draw(m_GameReadyEfxIt->second.texture,
				&m_GameReadyEfxIt->second.drawRc,
				NULL,
				NULL,
				D3DCOLOR_ARGB(m_GameReadyEfxIt->second.alpha, 255, 255, 255));

			m_GameReadyEfxIt->second.sprite->End();
		}
	}
}

void cUIMainMenu::renderFade()
{
	m_Fade.sprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_Fade.alpha += FADEINSPEED;
	if (m_Fade.alpha >= 255)
	{
		m_Fade.alpha = 255;
		m_InGameLoadingEnable = true;	// 씬 전환 체크용
	}

	D3DXMatrixAffineTransformation2D(&m_Fade.matWorld,
		m_Fade.scale,
		NULL,
		NULL,
		&D3DXVECTOR2(0, 0));

	m_Fade.sprite->SetTransform(&m_Fade.matWorld);
	RECT rc;
	SetRect(&rc, 0, 0, MAX_XPIXEL, MAX_YPIXEL);
	m_Fade.sprite->Draw(m_Fade.texture,
		&rc,
		NULL,
		NULL,
		D3DCOLOR_ARGB(m_Fade.alpha, 255, 255, 255));


	m_Fade.sprite->End();
}

void cUIMainMenu::renderIngameLoading()
{
	m_InGameLoading->renderBG();
	m_InGameLoading->render();
	m_GameStart = true;
}

void cUIMainMenu::destroyOther()
{
	for (m_GameReadyEfxIt = m_GameReadyEfx.begin(); m_GameReadyEfxIt != m_GameReadyEfx.end(); m_GameReadyEfxIt++)
	{
		m_GameReadyEfxIt->second.texture->Release();
		m_GameReadyEfxIt->second.sprite->Release();
	}
	m_InGameLoading->destroy();
	SAFE_DELETE(m_InGameLoading);
	m_Fade.sprite->Release();
	m_Fade.texture->Release();
	g_pFontManager->Destroy();	// 안해주면 할당해제 안되었다고 오류남
}
