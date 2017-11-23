#include "stdafx.h"
#include "cUIObject.h"

/*
���� ���� �Լ��� ���°� �ƴ϶� �̰� �״�� ���ΰ��ӿ� ���� ��. �׽�Ʈ��


*/

cUIObject::cUIObject()
	: m_UIScale(0.5f)
	, m_CollisionRectReduce(0.7f)
{
}

cUIObject::~cUIObject()
{
}

void cUIObject::AddSprite(tagUISpriteLoadData &spriteData)
{
	// �ؽ��� ����� �ؽ��� �Ŵ����� �ؾߵ�. ���� �ؽ��� �Ŵ����� Ȯ������ �ʾ����Ƿ� ���⿡�� ���
	spriteData.indexName = spriteData.indexName;

	// D3DXCreateTextureFromFileEx �갡 �ε��ð� �� ���� �ɸ�. �̹����� Ŭ���� ���� �ɸ�.
	// ���� ��� �̹��� ���µ� 1.500ms ����

	if (spriteData.button)	// ��ư�̸� �� 4���� �̹��� ��� �ʿ� (�⺻.����.Ŭ��.��Ȱ��)
	{
		if (m_MUIButton.find(spriteData.indexName) == m_MUIButton.end())	// mapIndexName�� �ߺ����� �ʴ´ٸ�
		{
			tagUISpriteButton uis;
			ZeroMemory(&uis, sizeof(tagUISprite));
			m_MUIButton.insert(make_pair(spriteData.indexName, uis));	// ������ �ʱ�ȭ �� �߰�
			tagUISpriteButton *uisAdd = &m_MUIButton.find(spriteData.indexName)->second;	// �߰��� �����Ϳ� �� ä���
			D3DXMatrixIdentity(&uisAdd->matWorld);
			D3DXCreateSprite(g_pD3DDevice, &uisAdd->sprite);

			for (int i = 0; i < 4; i++)	// 0 �Ϲ�, 1 ����, 2 Ŭ��&���� ��, 3 ��Ȱ�� :: ���̺��� ���� ������ �����ؾ� ��
			{
				wstring fileName(spriteData.file[i].begin(), spriteData.file[i].end());

				D3DXCreateTextureFromFileEx(
					g_pD3DDevice,
					fileName.c_str(),
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,
					D3DX_FILTER_NONE,
					D3DX_DEFAULT,
					D3DCOLOR_XRGB(255, 255, 255),
					&uisAdd->imgInfo,
					NULL,
					&uisAdd->texture[i]);
			}

			D3DXMatrixIdentity(&uisAdd->matWorld);
			uisAdd->pt = spriteData.pt;
			uisAdd->enable = spriteData.enable;
			uisAdd->rotSpd = spriteData.rotSpd;
			SetRect(&uisAdd->drawRc, 0, 0, uisAdd->imgInfo.Width, uisAdd->imgInfo.Height);	// ���ϻ󿡼� �̹����� ������ ����(ũ��)
			uisAdd->buttonFunc = spriteData.buttonFunc;
		}
	}
	else if (spriteData.BG)	// ���� �̹������ BG�� ����
	{
		if (m_MUISpriteBG.find(spriteData.indexName) == m_MUISpriteBG.end())	// mapIndexName�� �ߺ����� �ʴ´ٸ�
		{
			tagUISprite uis;
			ZeroMemory(&uis, sizeof(tagUISprite));
			m_MUISpriteBG.insert(make_pair(spriteData.indexName, uis));	// ������ �ʱ�ȭ �� �߰�
			tagUISprite *uisAdd = &m_MUISpriteBG.find(spriteData.indexName)->second;	// �߰��� �����Ϳ� �� ä���

			D3DXCreateSprite(g_pD3DDevice, &uisAdd->sprite);

			wstring fileName(spriteData.file[0].begin(), spriteData.file[0].end());

			D3DXCreateTextureFromFileEx(
				g_pD3DDevice,
				fileName.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				0,
				D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_DEFAULT,
				D3DCOLOR_XRGB(255, 255, 255),
				&uisAdd->imgInfo,
				NULL,
				&uisAdd->texture);

			D3DXMatrixIdentity(&uisAdd->matWorld);
			uisAdd->pt = spriteData.pt;
			uisAdd->enable = spriteData.enable;
			uisAdd->rotSpd = spriteData.rotSpd;
			SetRect(&uisAdd->drawRc, 0, 0, uisAdd->imgInfo.Width, uisAdd->imgInfo.Height);
		}
	}
	else
	{
		if (m_MUISprite.find(spriteData.indexName) == m_MUISprite.end())	// mapIndexName�� �ߺ����� �ʴ´ٸ�
		{
			tagUISprite uis;
			ZeroMemory(&uis, sizeof(tagUISprite));
			m_MUISprite.insert(make_pair(spriteData.indexName, uis));	// ������ �ʱ�ȭ �� �߰�
			tagUISprite *uisAdd = &m_MUISprite.find(spriteData.indexName)->second;	// �߰��� �����Ϳ� �� ä���

			D3DXCreateSprite(g_pD3DDevice, &uisAdd->sprite);

			wstring fileName(spriteData.file[0].begin(), spriteData.file[0].end());

			D3DXCreateTextureFromFileEx(
				g_pD3DDevice,
				fileName.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				0,
				D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_DEFAULT,
				D3DCOLOR_XRGB(255, 255, 255),
				&uisAdd->imgInfo,
				NULL,
				&uisAdd->texture);

			D3DXMatrixIdentity(&uisAdd->matWorld);
			uisAdd->pt = spriteData.pt;
			uisAdd->enable = spriteData.enable;
			uisAdd->rotSpd = spriteData.rotSpd;
			SetRect(&uisAdd->drawRc, 0, 0, uisAdd->imgInfo.Width, uisAdd->imgInfo.Height);
		}
	}
}

void cUIObject::setup(string className)
{
	vector<tagUISpriteLoadData> vUIData;
	int dataCount = 0;
	tagUISpriteLoadData ld;
	ZeroMemory(&ld, sizeof(tagUISpriteLoadData));
	// csv���� ���� ������ ���� �� AddSprite

	// ---------------------------------- ������ �б�(�Ľ�) ����
	// ������ �Ľ��� ���� �ڵ�� �� �ʿ� ����.
	// �Ľ��ؾߵ� �������� ��ġ�� ���ڴ� �׻� �����ϱ� ����.
	// �Ʒ� ���� �Ľ��� ������ ����.
	FILE *file;
	string thereis = "UI\\UIDatas.csv";
	fopen_s(&file, thereis.c_str(), "r");

	while (true)
	{
		char str1[128];
		char *str2 = str1;
		fgets(str1, sizeof(str1), file);
		strtok_s(str1, ",", &str2);
		if (str1 == className)
			break;	// �ش� ������ �ҷ����� ���� ��
	}

	{
		char str1[128];
		char *str2 = str1;
		fgets(str1, sizeof(str1), file);
		strtok_s(str1, ",", &str2);
		dataCount = atoi(str1);
	}

	for (int i = 0; i < dataCount; i++)
	{
		char str1[512];
		char *str2 = str1;
		fgets(str1, sizeof(str1), file);
		ld.pt.x = atoi(strtok_s(str2, ",", &str2));
		ld.pt.y = atoi(strtok_s(str2, ",", &str2));
		ld.enable = atoi(strtok_s(str2, ",", &str2));
		strtok_s(str2, ",", &str2);	// ��ư ��� ���δ� ó���� ��� false. ��ų ��� �� true
		ld.BG = atoi(strtok_s(str2, ",", &str2));
		ld.indexName = strtok_s(str2, ",", &str2);
		ld.rotate = atof(strtok_s(str2, ",", &str2));
		ld.rotSpd = atof(strtok_s(str2, ",", &str2));
		ld.button = atoi(strtok_s(str2, ",", &str2));
		ld.buttonFunc = atoi(strtok_s(str2, ",", &str2));
		if (ld.button)	// ��ư�̸� 4�� �̹��� �߰�
		{
			string st1 = strtok_s(str2, ",", &str2);
			string st2 = strtok_s(str2, ",", &str2);
			string st3 = strtok_s(str2, ",", &str2);
			string st4 = strtok_s(str2, "\n", &str2);

			ld.file[0] = "UI\\" + st1;
			ld.file[1] = "UI\\" + st2;
			ld.file[2] = "UI\\" + st3;
			ld.file[3] = "UI\\" + st4;
		}
		else	// ��ư�� �ƴϸ� 1�� �̹��� �߰�
		{
			string st1 = strtok_s(str2, ",", &str2);
			ld.file[0] = "UI\\" + st1;
		}
		vUIData.push_back(ld);
	}

	// ---------------------------------- ������ �б�(�Ľ�) �Ϸ�

	for (int i = 0; i < vUIData.size(); i++)	// �Ľ��� �����͸� sprite�� ����(�߰�)
	{
		AddSprite(vUIData[i]);
	}

	setupOther();
}

void cUIObject::update()
{
	updateButton();
	updateOther();
}

void cUIObject::updateButton()
{
	for (m_MUIButtonIt = m_MUIButton.begin(); m_MUIButtonIt != m_MUIButton.end(); m_MUIButtonIt++)
	{
		if (!m_MUIButtonIt->second.enable) continue;
		updateMatWorld(m_MUIButtonIt->second.matWorld, m_MUIButtonIt->second.pt);
		// �� �Ʒ����� pt ���� matWorld�� _41, _42 ���� ��� �Ѵ�. Scale, Trans�� ����� World�� �������� �ؾߵ�
		if (m_MUIButtonIt->second.used) continue;	// ��� ���̸� ��ư ������Ʈ�� ���� (��ư ��� ��Ȱ��)
		updateButtonState(m_MUIButtonIt->second.imgInfo, D3DXVECTOR3(m_MUIButtonIt->second.matWorld._41, m_MUIButtonIt->second.matWorld._42, 0), m_MUIButtonIt->second.buttonState, m_MUIButtonIt->second.buttonFunc);
		if (m_MUIButtonIt->second.selected)
		{
			m_MUIButtonIt->second.buttonState = UIBUTTONSTATE_SELECT;
		}
	}
}

void cUIObject::updateMatWorld(D3DXMATRIXA16 &matWorld, D3DXVECTOR3 pt)
{
	D3DXMATRIXA16 matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	
	D3DXMatrixScaling(&matS, m_UIScale, m_UIScale, m_UIScale);
	D3DXMatrixTranslation(&matT, pt.x, pt.y, 0.0f);
	matWorld = matS * matT;
}

void cUIObject::updateCollisionRect(RECT &rc, D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt)
{
	int width = imgInfo.Width * m_UIScale;	// scaling �� ��ǥ�� �������� �߽����� ã�ƾ� ��
	int height = imgInfo.Height * m_UIScale;
	POINT rcCenterPt = { pt.x + width / 2, pt.y + height / 2 };
	SetRect(&rc,
		rcCenterPt.x - width	 * m_CollisionRectReduce / 2,
		rcCenterPt.y - height	 * m_CollisionRectReduce / 2,
		rcCenterPt.x + width	 * m_CollisionRectReduce / 2,
		rcCenterPt.y + height	 * m_CollisionRectReduce / 2);
	// m_CollisionRectReduce�� 0.5�� 100%. �߽��� ������� �� ���� ����� �����ϱ� ����.

	// ������ UI�� Sprite ������ �Ⱦ��� ��� 3D(��ŷ) ó���� �� �� ����
}

void cUIObject::updateButtonState(D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt, int &buttonState, int buttonFunc)
{
	// ��ư �浹 ó��
	RECT rc;
	updateCollisionRect(rc, imgInfo, pt);

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (PtInRect(&rc, ptMouse))
	{
		if (KEY->isStayKeyDown(VK_LBUTTON))
		{
			buttonState = UIBUTTONSTATE_SELECT;
		}
		else
		{
			buttonState = UIBUTTONSTATE_OVER;
			updateButtonOverCallback(buttonFunc);
		}
		if (KEY->isOnceKeyUp(VK_LBUTTON) && buttonState == UIBUTTONSTATE_OVER)
		{
			updateButtonCallback(buttonFunc);
		}
	}
	else
	{
		buttonState = UIBUTTONSTATE_NORMAL;
	}
	
	//if (PtInRect(&rc, ptMouse))
	//{
	//	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	//	{
	//		if (buttonState == UIBUTTONSTATE_OVER)	// ���� ������ �� Ŭ�� ��
	//		{
	//			buttonState = UIBUTTONSTATE_SELECT;
	//			updateButtonCallback(buttonFunc);
	//		}
	//		else if (buttonState == UIBUTTONSTATE_SELECT)
	//		{
	//			buttonState = UIBUTTONSTATE_OVER;
	//			updateButtonCallback(buttonFunc);
	//		}
	//	}
	//	else
	//	{
	//		if (buttonState == UIBUTTONSTATE_SELECT)
	//		{
	//			// ���콺 Ŭ�� �� ��� ����
	//			//updateButtonCallback(buttonFunc);
	//		}
	//		else if (buttonState == UIBUTTONSTATE_OVER)
	//		{
	//			// ���콺 ���� �� ��� ����
	//			updateButtonOverCallback(buttonFunc);
	//		}
	//		buttonState = UIBUTTONSTATE_OVER;	// ���� �� ���� ����
	//	}
	//}
	//else
	//{
	//	buttonState = UIBUTTONSTATE_NORMAL;
	//}
}

void cUIObject::render()
{
	renderNormal();
	renderButton();
	renderOther();
}

void cUIObject::renderBG()
{
	for (m_MUISpriteBGIt = m_MUISpriteBG.begin(); m_MUISpriteBGIt != m_MUISpriteBG.end(); m_MUISpriteBGIt++)
	{
		if (!m_MUISpriteBGIt->second.enable) continue;
		m_MUISpriteBGIt->second.sprite->Begin(D3DXSPRITE_ALPHABLEND);

		updateMatWorld(m_MUISpriteBGIt->second.matWorld, m_MUISpriteBGIt->second.pt);

		m_MUISpriteBGIt->second.sprite->SetTransform(&m_MUISpriteBGIt->second.matWorld);

		m_MUISpriteBGIt->second.sprite->Draw(m_MUISpriteBGIt->second.texture,
			&m_MUISpriteBGIt->second.drawRc,
			NULL,	// �߽���. ȸ����ų���� imgInfo���� Width / 2, Height / 2 ������ �ɵ�
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		m_MUISpriteBGIt->second.sprite->End();
	}
}

void cUIObject::renderButton()
{
	for (m_MUIButtonIt = m_MUIButton.begin(); m_MUIButtonIt != m_MUIButton.end(); m_MUIButtonIt++)
	{
		if (!m_MUIButtonIt->second.enable) continue;
		m_MUIButtonIt->second.sprite->Begin(D3DXSPRITE_ALPHABLEND);

		updateMatWorld(m_MUIButtonIt->second.matWorld, m_MUIButtonIt->second.pt);
		m_MUIButtonIt->second.sprite->SetTransform(&m_MUIButtonIt->second.matWorld);

		m_MUIButtonIt->second.sprite->Draw(m_MUIButtonIt->second.texture[m_MUIButtonIt->second.buttonState],
			&m_MUIButtonIt->second.drawRc,
			NULL,	// �߽���. ȸ����ų���� imgInfo���� Width / 2, Height / 2 ������ �ɵ�
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255));

		m_MUIButtonIt->second.sprite->End();
	}
}

void cUIObject::renderNormal()
{
	for (m_MUISpriteIt = m_MUISprite.begin(); m_MUISpriteIt != m_MUISprite.end(); m_MUISpriteIt++)
	{
		if (!m_MUISpriteIt->second.enable) continue;
		m_MUISpriteIt->second.sprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMatrixAffineTransformation2D(&m_MUISpriteIt->second.matWorld,
			m_UIScale,
			NULL,	// ȸ�� �߽����� �־ ������ �ȵ�
			m_MUISpriteIt->second.rotate,
			&D3DXVECTOR2(m_MUISpriteIt->second.pt.x, m_MUISpriteIt->second.pt.y));
		//updateMatWorld(m_MUISpriteIt->second.matWorld, m_MUISpriteIt->second.pt);
		m_MUISpriteIt->second.sprite->SetTransform(&m_MUISpriteIt->second.matWorld);

		if (m_MUISpriteIt->second.rotSpd != 0)
		{
			m_MUISpriteIt->second.rotate += m_MUISpriteIt->second.rotSpd;
			m_MUISpriteIt->second.sprite->Draw(m_MUISpriteIt->second.texture,
				&m_MUISpriteIt->second.drawRc,
				&D3DXVECTOR3(m_MUISpriteIt->second.imgInfo.Width / 2, m_MUISpriteIt->second.imgInfo.Height / 2, 0),	// �߽���. ȸ����ų���� imgInfo���� Width / 2, Height / 2 ������ �ɵ�
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			m_MUISpriteIt->second.sprite->Draw(m_MUISpriteIt->second.texture,
				&m_MUISpriteIt->second.drawRc,
				NULL,	// �߽���. ȸ����ų���� imgInfo���� Width / 2, Height / 2 ������ �ɵ�
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}

		m_MUISpriteIt->second.sprite->End();
	}
}

void cUIObject::destroy()
{
	for (m_MUISpriteIt = m_MUISprite.begin(); m_MUISpriteIt != m_MUISprite.end(); m_MUISpriteIt++)
	{
		m_MUISpriteIt->second.sprite->Release();
		m_MUISpriteIt->second.texture->Release();
	}

	for (m_MUIButtonIt = m_MUIButton.begin(); m_MUIButtonIt != m_MUIButton.end(); m_MUIButtonIt++)
	{
		m_MUIButtonIt->second.sprite->Release();
		m_MUIButtonIt->second.texture[0]->Release();
		m_MUIButtonIt->second.texture[1]->Release();
		m_MUIButtonIt->second.texture[2]->Release();
		m_MUIButtonIt->second.texture[3]->Release();
	}

	for (m_MUISpriteBGIt = m_MUISpriteBG.begin(); m_MUISpriteBGIt != m_MUISpriteBG.end(); m_MUISpriteBGIt++)
	{
		m_MUISpriteBGIt->second.sprite->Release();
		m_MUISpriteBGIt->second.texture->Release();
	}
	destroyOther();
}
