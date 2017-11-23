#include "stdafx.h"
#include "cUIInGame.h"


cUIInGame::cUIInGame()
	: m_GameEnd(false)
	, m_HPBarSizeX(6.0f)
	, m_HPBarSizeY(0.5f)
	, m_HPBarHeight(18)
{
}


cUIInGame::~cUIInGame()
{
}

int cUIInGame::updateButtonOverCallback(int num)
{
	return 0;
}

int cUIInGame::updateButtonCallback(int num)
{
	if (num == UIBUTTONCALLBACK_INGAME_HOME)
	{
		m_GameEnd = true;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL1)
	{
		SetSkillUse(1, true);	// 스킬이 비활성화, 사용 중이라면 여길 못오니 바로 사용
		return 1;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL2)
	{
		SetSkillUse(2, true);
		return 2;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL3)
	{
		SetSkillUse(3, true);
		return 3;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL4)
	{
		SetSkillUse(4, true);
		return 4;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_SKILL5)
	{
		SetSkillUse(5, true);
		return 5;
	}

	return 0;
}

void cUIInGame::SetSkillUnlock(int SkillIndex, bool unlock)
{
	string skillName = "abil" + to_string(SkillIndex);
	string skillNameImg = "abil" + to_string(SkillIndex) + "img";
	string skillNameLock = "skill" + to_string(SkillIndex) + "lock";

	if (unlock)	// 스킬 언락 시 락 이미지 enable = false & 스킬 enable = true
	{
		m_MUIButton.find(skillName)->second.enable = true;
		m_MUISprite.find(skillNameImg)->second.enable = true;
		m_MUISprite.find(skillNameLock)->second.enable = false;
	}
	else	// 스킬 재사용 가능 시 위에 기능 반대로 작동
	{
		m_MUIButton.find(skillName)->second.enable = false;
		m_MUISprite.find(skillNameImg)->second.enable = false;
		m_MUISprite.find(skillNameLock)->second.enable = true;
	}
}

void cUIInGame::SetSkillUse(int SkillIndex, bool used)
{
	string skillName = "abil" + to_string(SkillIndex);
	string skillNameImg = "abil" + to_string(SkillIndex) + "img";

	if (used)
	{
		m_MUIButton.find(skillName)->second.used = true;
		m_MUIButton.find(skillName)->second.buttonState = UIBUTTONSTATE_DISENABLE;
		//m_MUISprite.find(skillNameImg)->second.enable = false;
	}
	else
	{
		m_MUIButton.find(skillName)->second.used = false;
		m_MUIButton.find(skillName)->second.buttonState = UIBUTTONSTATE_NORMAL;
		//m_MUISprite.find(skillNameImg)->second.enable = true;
		
		for (int i = 0; i < SKILLCOUNTNUM; i++)
		{
			string countName = "skill" + to_string(SkillIndex) + "cool" + to_string(i);
			m_MUIButton.find(countName)->second.enable = false;
		}
	}
}

void cUIInGame::SetSkillUseCooldown(int SkillIndex, float count)
{
	// 이미지 저장하는 구조부터 바꿔야 할듯. 아래 구조는 불안정하고 확장성이 부족함
	int countInt = (int)count;
	countInt++;	// 0.9가 0으로 치환되므로 표현을 +1로 해준다.
	if (countInt > 9)
		countInt = 9;	// 10초 이상은 구조 자체를 바꿔야 할듯. 지금은 한자리 수만 됨...
	string skillName = "abil" + to_string(SkillIndex);
	string countName = "skill" + to_string(SkillIndex) + "cool" + to_string(countInt);
	string countName2 = "skill" + to_string(SkillIndex) + "cool" + to_string(countInt + 1);

	if (m_MUIButton.find(skillName)->second.used)	// 스킬이 사용 중이라면 카운트 표시. 아니면 안함
	{
		m_MUIButton.find(countName)->second.enable = true;
		if (countInt > 8) return;	// 이게 없으면 countInt + 1 = 10이 될 경우 터짐.
		m_MUIButton.find(countName2)->second.enable = false;
	}
}

void cUIInGame::setupOther()
{
	setupHpBar(L"UI/ingame_img_bar_hp_bg.png");
	setupHpBar(L"UI/ingame_img_bar_hp.dds");
}

void cUIInGame::updateOther()
{

}

void cUIInGame::renderOther()
{
	renderBar();
}

void cUIInGame::setupHpBar(wstring filePath)
{
	tagHPBar hb;
	ZeroMemory(&hb, sizeof(tagHPBar));
	m_VHPBar.push_back(hb);
	tagHPBar *phb = &m_VHPBar[m_VHPBar.size() - 1];

	phb->max = HPMAX;
	phb->current = HPMAX;

	D3DXMatrixIdentity(&phb->matWorld);
	D3DXMATRIXA16 matT, matR;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);

	D3DXMatrixRotationX(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, -m_HPBarSizeX, m_HPBarHeight, 0.0f);
	phb->matWorld = matR * matT;
	
	
	phb->filePath = filePath;
	D3DXVECTOR2 v2(0, 0);
	g_pTextureManager->AddTexture(phb->filePath.c_str(), phb->texture, &v2);
	
	ST_PT_VERTEXT p;
	p.p = D3DXVECTOR3(0, 0, -m_HPBarSizeY);	// 사이즈
	p.t = D3DXVECTOR2(0, 1);		// 텍스쳐
	phb->vertex.push_back(p);
	p.p = D3DXVECTOR3(0, 0, m_HPBarSizeY);
	p.t = D3DXVECTOR2(0, 0);
	phb->vertex.push_back(p);
	p.p = D3DXVECTOR3(m_HPBarSizeX * 2, 0, m_HPBarSizeY);
	p.t = D3DXVECTOR2(1, 0);
	phb->vertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, -m_HPBarSizeY);
	p.t = D3DXVECTOR2(0, 1);
	phb->vertex.push_back(p);
	p.p = D3DXVECTOR3(m_HPBarSizeX * 2, 0, m_HPBarSizeY);
	p.t = D3DXVECTOR2(1, 0);
	phb->vertex.push_back(p);
	p.p = D3DXVECTOR3(m_HPBarSizeX * 2, 0, -m_HPBarSizeY);
	p.t = D3DXVECTOR2(1, 1);
	phb->vertex.push_back(p);
}

void cUIInGame::updateBar(bool pc, D3DXVECTOR3 pt, int currHp)
{
	// 체력의 비율을 계산해서 scale.x 값을 조정.
	if (currHp < 0) currHp = 0;
	else if (currHp > m_VHPBar[1].max) currHp = HPMAX;

	m_VHPBar[1].current = currHp;
	float scale = m_VHPBar[1].current / m_VHPBar[1].max;
	if (scale < 0) scale = 0;
	else if (scale > 1) scale = 1;

	D3DXMatrixIdentity(&m_VHPBar[1].matWorld);
	D3DXMATRIXA16 matT, matR, matS;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matS);

	D3DXMatrixScaling(&matS, (m_VHPBar[1].current / m_VHPBar[1].max), 1, 1);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, -m_HPBarSizeX + pt.x, m_HPBarHeight + pt.y, pt.z);

	for (int i = 0; i < m_VHPBar.size(); i++)
	{
		m_VHPBar[i].matWorld = matR * matT;
	}

	if (pc)
	{
		m_VHPBar[1].matWorld = matS * matR * matT;
	}
	else if (!pc)
	{
		m_VHPBar[3].matWorld = matS * matR * matT;
	}
}

void cUIInGame::renderBar()
{
	
	for (int i = 0; i < m_VHPBar.size(); i++)
	{
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

		g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));

		g_pD3DDevice->SetFVF(ST_PT_VERTEXT::FVF);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_VHPBar[i].matWorld);
		g_pD3DDevice->SetTexture(0, m_VHPBar[i].texture);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_VHPBar[i].vertex.size() / 3, &m_VHPBar[i].vertex[0], sizeof(ST_PT_VERTEXT));
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
}
