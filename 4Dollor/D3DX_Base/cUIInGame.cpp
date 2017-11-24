#include "stdafx.h"
#include "cUIInGame.h"


cUIInGame::cUIInGame()
	: m_GameEnd(false)
	, m_HPBarSizeX(6.0f)
	, m_HPBarSizeY(0.5f)
	, m_HPBarHeight(18)
	, m_LvUpCount(0)
	, m_SkillUnlockEfxAlphaCount(0)
	, m_IsVictory(false)
{
}

cUIInGame::~cUIInGame()
{
}

void cUIInGame::setupDeadAdd()
{
	wstring filePath = L"UI/ingame_img_deadbg.png";
	ZeroMemory(&m_Dead, sizeof(tagUISpriteEfx));

	D3DXMatrixIdentity(&m_Dead.matWorld);

	D3DXCreateSprite(g_pD3DDevice, &m_Dead.sprite);

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
		&m_Dead.imgInfo,
		NULL,
		&m_Dead.texture);

	SetRect(&m_Dead.drawRc, 0, 0, m_Dead.imgInfo.Width, m_Dead.imgInfo.Height);
	m_Dead.alpha = 0;
	m_Dead.scale = m_UIScale * 1.2f;
	m_Dead.pt = { 0, 0, 0 };
	m_Dead.enable = false;
}

void cUIInGame::SetDead(bool deadEnable)
{
	// enable = true면 죽음. false면 부활.
	m_Dead.enable = deadEnable;
}

void cUIInGame::rednerDead()
{
	if (m_Dead.enable)
	{
		m_Dead.sprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMatrixAffineTransformation2D(&m_Dead.matWorld,
			m_Dead.scale,
			NULL,
			NULL,
			&D3DXVECTOR2(0, 0));

		m_Dead.sprite->SetTransform(&m_Dead.matWorld);
		RECT rc;
		SetRect(&rc, 0, 0, m_Dead.imgInfo.Width, m_Dead.imgInfo.Height);
		m_Dead.sprite->Draw(m_Dead.texture,
			&rc,
			NULL,
			NULL,
			D3DCOLOR_ARGB(m_Dead.alpha, 255, 255, 255));

		m_Dead.sprite->End();
	}
}

void cUIInGame::setupDeadSideAdd(bool left)
{
	int l = 0;
	wstring filePath = L"UI/ingame_img_dead_right.png";
	if (left)
	{
		filePath = L"UI/ingame_img_dead_left.png";
		l = 1;
	}
	ZeroMemory(&m_DeadSide[l], sizeof(tagUISpriteEfx));

	D3DXMatrixIdentity(&m_DeadSide[l].matWorld);

	D3DXCreateSprite(g_pD3DDevice, &m_DeadSide[l].sprite);

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
		&m_DeadSide[l].imgInfo,
		NULL,
		&m_DeadSide[l].texture);

	SetRect(&m_DeadSide[l].drawRc, 0, 0, m_DeadSide[l].imgInfo.Width, m_DeadSide[l].imgInfo.Height);
	m_DeadSide[l].alpha = 255;
	m_DeadSide[l].scale = m_UIScale;
	m_DeadSide[l].enable = true;

	if (left)
	{
		m_DeadSide[l].pt = { 0, 0, 0 };
	}
	else
	{
		m_DeadSide[l].pt = { float(MAX_XPIXEL - m_DeadSide[l].imgInfo.Width), 0, 0 };
	}
	
}

void cUIInGame::renderDeadSide()
{
	if (m_Dead.enable)
	{
		for (int i = 0; i < DEADSIDE; i++)
		{
			m_DeadSide[i].sprite->Begin(D3DXSPRITE_ALPHABLEND);

			D3DXMatrixAffineTransformation2D(&m_DeadSide[i].matWorld,
				m_DeadSide[i].scale,
				NULL,
				NULL,
				&D3DXVECTOR2(0, 0));

			m_DeadSide[i].sprite->SetTransform(&m_DeadSide[i].matWorld);
			RECT rc;
			SetRect(&rc, 0, 0, m_DeadSide[i].imgInfo.Width, m_DeadSide[i].imgInfo.Height);
			m_DeadSide[i].sprite->Draw(m_DeadSide[i].texture,
				&rc,
				NULL,
				&m_DeadSide[i].pt,
				D3DCOLOR_ARGB(m_DeadSide[i].alpha, 255, 255, 255));

			m_DeadSide[i].sprite->End();
		}
	}
}

void cUIInGame::setupFadeAdd(wstring filePath)
{
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

	SetRect(&m_Fade.drawRc, 0, 0, 0, 0);
	m_Fade.alpha = 255;
	m_Fade.scale = 1;
	m_Fade.pt = { 0, 0, 0 };
	m_Fade.enable = true;
}

void cUIInGame::setupSkillLockList()
{
	m_SkillUnlock.push_back(&m_MUIButton.find("unlockskill1")->second);
	m_SkillUnlock.push_back(&m_MUIButton.find("unlockskill2")->second);
	m_SkillUnlock.push_back(&m_MUIButton.find("unlockskill3")->second);

	m_SkillUnlock[0]->pt = { m_MUIButton.find("charport")->second.pt.x, m_MUIButton.find("charport")->second.pt.y - 70 ,0 };
	m_SkillUnlock[1]->pt = { m_MUIButton.find("charport")->second.pt.x, m_MUIButton.find("charport")->second.pt.y - 115 ,0 };
	m_SkillUnlock[2]->pt = { m_MUIButton.find("charport")->second.pt.x, m_MUIButton.find("charport")->second.pt.y - 160 ,0 };
}

void cUIInGame::setupSkillUnlockEfx(wstring filePath)
{
	ZeroMemory(&m_SkillUnlockEfx, sizeof(tagUISpriteEfx));

	D3DXMatrixIdentity(&m_SkillUnlockEfx.matWorld);

	D3DXCreateSprite(g_pD3DDevice, &m_SkillUnlockEfx.sprite);

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
		&m_SkillUnlockEfx.imgInfo,
		NULL,
		&m_SkillUnlockEfx.texture);

	SetRect(&m_SkillUnlockEfx.drawRc, 0, 0, m_SkillUnlockEfx.imgInfo.Width, m_SkillUnlockEfx.imgInfo.Height);
	m_SkillUnlockEfx.alpha = 0;
	m_SkillUnlockEfx.scale = m_UIScale;
	m_SkillUnlockEfx.pt = m_MUIButton.find("abil1")->second.pt * 2;
	m_SkillUnlockEfx.matWorld = m_MUIButton.find("abil1")->second.matWorld;
	m_SkillUnlockEfx.enable = false;
}

void cUIInGame::setupVictoryAdd(wstring filePath, int index, float scale)
{
	ZeroMemory(&m_VictoryEfx[index], sizeof(tagUISpriteEfx));

	D3DXMatrixIdentity(&m_VictoryEfx[index].matWorld);

	D3DXCreateSprite(g_pD3DDevice, &m_VictoryEfx[index].sprite);

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
		&m_VictoryEfx[index].imgInfo,
		NULL,
		&m_VictoryEfx[index].texture);

	SetRect(&m_VictoryEfx[index].drawRc, 0, 0, m_VictoryEfx[index].imgInfo.Width, m_VictoryEfx[index].imgInfo.Height);
	m_VictoryEfx[index].alpha = 255;
	m_VictoryEfx[index].scale = scale;
	m_VictoryEfx[index].pt = { 0,0,0 };
	m_VictoryEfx[index].enable = true;
}

void cUIInGame::SetVictory()
{
	m_IsVictory = true;
}

void cUIInGame::renderVictory()
{
	if (m_IsVictory)
	{
		for (int i = 0; i < VICTORYRESOURCE; i++)
		{
			if (!m_VictoryEfx[i].enable) continue;
			m_VictoryEfx[i].sprite->Begin(D3DXSPRITE_ALPHABLEND);

			D3DXMatrixAffineTransformation2D(&m_VictoryEfx[i].matWorld,
				m_VictoryEfx[i].scale,
				NULL,
				m_VictoryEfx[i].rotate,
				&D3DXVECTOR2(0, 0));

			m_VictoryEfx[i].sprite->SetTransform(&m_VictoryEfx[i].matWorld);
			RECT rc;
			SetRect(&rc, 0, 0, m_VictoryEfx[i].imgInfo.Width, m_VictoryEfx[i].imgInfo.Height);

			if (i == 0)
			{
				if (m_VictoryEfx[i].alpha > 0)
				{
					m_VictoryEfx[i].alpha -= 10;
					if (m_VictoryEfx[i].alpha <= 0)
					{
						m_VictoryEfx[i].alpha = 0;
						m_VictoryEfx[i].enable = false;
					}
				}
			}
			if (i == 1)
			{
				m_VictoryEfx[i].rotate += 0.01;
				m_VictoryEfx[i].sprite->Draw(m_VictoryEfx[i].texture,
					&rc,
					&D3DXVECTOR3(m_VictoryEfx[i].imgInfo.Width / 2, m_VictoryEfx[i].imgInfo.Height / 2, 0),
					&m_VictoryEfx[i].pt,
					D3DCOLOR_ARGB(m_VictoryEfx[i].alpha, 255, 255, 255));
			}
			else
			{
				m_VictoryEfx[i].sprite->Draw(m_VictoryEfx[i].texture,
					&rc,
					NULL,
					&m_VictoryEfx[i].pt,
					D3DCOLOR_ARGB(m_VictoryEfx[i].alpha, 255, 255, 255));
			}
			//m_VictoryEfx[i].sprite->Draw(m_VictoryEfx[i].texture,
			//	&rc,
			//	NULL,
			//	&m_VictoryEfx[i].pt,
			//	D3DCOLOR_ARGB(m_VictoryEfx[i].alpha, 255, 255, 255));

			m_VictoryEfx[i].sprite->End();
		}
	}
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

	if (num == UIBUTTONCALLBACK_INGAME_PORTRAIT)
	{
		if(m_MUIButton.find("charport")->second.selected)
			m_MUIButton.find("charport")->second.selected = false;
		else m_MUIButton.find("charport")->second.selected = true;
	}

	if (num == UIBUTTONCALLBACK_INGAME_UNLOCKSKILL1)
	{
		SetSkillUnlock(1, true);
		skillUnlockPtChange(0);
		skillUnlockEfx(1);
		m_LvUpCount--;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_UNLOCKSKILL2)
	{
		SetSkillUnlock(2, true);
		skillUnlockPtChange(1);
		skillUnlockEfx(2);
		m_LvUpCount--;
	}
	else if (num == UIBUTTONCALLBACK_INGAME_UNLOCKSKILL3)
	{
		SetSkillUnlock(3, true);
		skillUnlockPtChange(2);
		skillUnlockEfx(3);
		m_LvUpCount--;
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
	else
	{
		m_MUIButton.find(skillName)->second.enable = false;
		m_MUISprite.find(skillNameImg)->second.enable = false;
		m_MUISprite.find(skillNameLock)->second.enable = true;
	}
}

void cUIInGame::skillUnlockPtChange(int index)
{
	float interval = 45;
	float basePtY = m_MUIButton.find("charport")->second.pt.y - 70;
	m_SkillUnlock[index]->used = true;

	for (int i = 0; i < 3; i++)
	{
		// 스킬이 아직 언락 안되었으면 기준점으로 출력 & 기준점 변경
		// 스킬이 개방되었다면 기준점 그대로 유지
		if (!m_SkillUnlock[i]->used)
		{
			m_SkillUnlock[i]->pt.y = basePtY;
			basePtY -= interval;
		}
		m_SkillUnlock[i]->enable = false;
	}
}

void cUIInGame::skillUnlockEfx(int index)
{
	string s = "abil" + to_string(index);
	m_SkillUnlockEfx.pt = m_MUIButton.find(s)->second.pt * 2;
	m_SkillUnlockEfx.enable = true;
	m_SkillUnlockEfx.matWorld = m_MUIButton.find(s)->second.matWorld;
}

void cUIInGame::updateSkillUnlockEfx()
{
	if (m_SkillUnlockEfx.enable)
	{
		int alphaSpeed = 30;
		if (m_SkillUnlockEfx.reverse)
		{
			m_SkillUnlockEfx.alpha -= alphaSpeed;
			if (m_SkillUnlockEfx.alpha <= 0)
			{
				m_SkillUnlockEfx.alpha = 0;
				m_SkillUnlockEfx.reverse = false;
				m_SkillUnlockEfxAlphaCount++;
			}
		}
		else
		{
			m_SkillUnlockEfx.alpha += alphaSpeed;
			if (m_SkillUnlockEfx.alpha >= 255)
			{
				m_SkillUnlockEfx.alpha = 255;
				m_SkillUnlockEfx.reverse = true;
			}
		}
		if (m_SkillUnlockEfxAlphaCount >= SKILLUNLOCKEFXREPEATCOUNT)
		{
			m_SkillUnlockEfx.enable = false;
			m_SkillUnlockEfxAlphaCount = 0;
		}
	}
}

void cUIInGame::skillChooseList()
{
	if (m_MUIButton.find("charport")->second.selected && m_LvUpCount > 0)
	{
		if(!m_SkillUnlock[0]->used) m_SkillUnlock[0]->enable = true;
		if(!m_SkillUnlock[1]->used) m_SkillUnlock[1]->enable = true;
		if(!m_SkillUnlock[2]->used) m_SkillUnlock[2]->enable = true;
	}
	else if (!m_MUIButton.find("charport")->second.selected)
	{
		m_SkillUnlock[0]->enable = false;
		m_SkillUnlock[1]->enable = false;
		m_SkillUnlock[2]->enable = false;
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

void cUIInGame::SetLevelUp()
{
	SetLvUpAddCount(1);
}

void cUIInGame::setupOther()
{
	setupHpBar(L"UI/ingame_img_bar_hp_bg.png");
	setupHpBar(L"UI/ingame_img_bar_hp.dds");
	setupFadeAdd(L"UI/black.png");
	setupSkillLockList();
	setupSkillUnlockEfx(L"UI/ingame_img_unlock_efx.png");
	setupDeadAdd();
	setupDeadSideAdd(true);
	setupDeadSideAdd(false);
	setupVictoryAdd(L"UI/ingame_img_victory_bg.png",	0,	0.6f);
	setupVictoryAdd(L"UI/ingame_img_victory_cycle.png",	1,	0.7f);
	setupVictoryAdd(L"UI/ingame_img_victory_text.png",	2,	0.7f);
}

void cUIInGame::updateOther()
{
	if (KEY->isOnceKeyDown('0')) SetLevelUp();
	if (KEY->isOnceKeyDown('8')) SetDead(true);
	if (KEY->isOnceKeyDown('9')) SetDead(false);
	if (KEY->isOnceKeyDown('7')) SetVictory();
	if (KEY->isOnceKeyDown(VK_LBUTTON) && m_IsVictory) m_GameEnd = true;
	skillChooseList();
	updateSkillUnlockEfx();
}

void cUIInGame::renderOther()
{
	renderBar();
	renderFade();
	renderAbilityAddGuide();
	renderSkillUnlockEfx();
	rednerDead();
	renderDeadSide();
	renderVictory();
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

void cUIInGame::renderFade()
{
	if (m_Fade.enable)
	{
		m_Fade.sprite->Begin(D3DXSPRITE_ALPHABLEND);

		m_Fade.alpha -= FADEINSPEED;
		if (m_Fade.alpha <= 0)
		{
			m_Fade.alpha = 0;
			m_Fade.enable = false;
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
}

void cUIInGame::renderAbilityAddGuide()
{
	// 스킬 찍을 수 있을 때만 떠야 됨
	if (!m_MUIButton.find("charport")->second.selected && m_LvUpCount > 0)
	{
		m_MUISprite.find("choosebg")->second.enable = true;
		int delay = 8;	// 화살표 표시되는 간격에 모두 사라졌다 등장하는 연출 시간 제어용. 4이하면 안됨
		int t = GetTickCount() / 300 % delay;
		if (t == delay / 2)
		{
			m_MUISprite.find("choose0")->second.enable = false;
			m_MUISprite.find("choose1")->second.enable = false;
			m_MUISprite.find("choose2")->second.enable = false;
			m_MUISprite.find("choose3")->second.enable = false;
		}
		if (t > 3) return;

		string tNum = "choose" + to_string(t);
		if (!m_MUISprite.find(tNum)->second.enable)
			m_MUISprite.find(tNum)->second.enable = true;
	}
	else
	{
		m_MUISprite.find("choosebg")->second.enable = false;
		m_MUISprite.find("choose0")->second.enable = false;
		m_MUISprite.find("choose1")->second.enable = false;
		m_MUISprite.find("choose2")->second.enable = false;
		m_MUISprite.find("choose3")->second.enable = false;
	}
}

void cUIInGame::renderSkillUnlockEfx()
{
	if (m_SkillUnlockEfx.enable)
	{
		m_SkillUnlockEfx.sprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMatrixAffineTransformation2D(&m_SkillUnlockEfx.matWorld,
			m_SkillUnlockEfx.scale,
			NULL,
			NULL,
			&D3DXVECTOR2(0, 0));

		m_SkillUnlockEfx.sprite->SetTransform(&m_SkillUnlockEfx.matWorld);

		m_SkillUnlockEfx.sprite->Draw(m_SkillUnlockEfx.texture,
			&m_SkillUnlockEfx.drawRc,
			NULL,
			&m_SkillUnlockEfx.pt,
			D3DCOLOR_ARGB(m_SkillUnlockEfx.alpha, 255, 255, 255));

		m_SkillUnlockEfx.sprite->End();
	}
}

void cUIInGame::destroyOther()
{
	for (int i = 0; i < m_VHPBar.size(); i++)
	{
		m_VHPBar[i].texture->Release();
	}
	m_Fade.sprite->Release();
	m_Fade.texture->Release();
	m_Dead.sprite->Release();
	m_Dead.texture->Release();
	m_SkillUnlockEfx.sprite->Release();
	m_SkillUnlockEfx.texture->Release();
	
	for (int i = 0; i < DEADSIDE; i++)
	{
		m_DeadSide[i].sprite->Release();
		m_DeadSide[i].texture->Release();
	}
	for (int i = 0; i < VICTORYRESOURCE; i++)
	{
		m_VictoryEfx[i].sprite->Release();
		m_VictoryEfx[i].texture->Release();
	}
}