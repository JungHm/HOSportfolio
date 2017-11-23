#include "stdafx.h"
#include "cUIObject.h"

/*
현재 가상 함수로 쓰는게 아니라 이거 그대로 메인게임에 쓰는 중. 테스트용


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
	// 텍스쳐 등록은 텍스쳐 매니저로 해야됨. 현재 텍스쳐 매니저를 확장하지 않았으므로 여기에서 등록
	spriteData.indexName = spriteData.indexName;

	// D3DXCreateTextureFromFileEx 얘가 로딩시간 꽤 오래 걸림. 이미지가 클수록 오래 걸림.
	// 현재 배경 이미지 띄우는데 1.500ms 정도

	if (spriteData.button)	// 버튼이면 총 4개의 이미지 등록 필요 (기본.오버.클릭.비활성)
	{
		if (m_MUIButton.find(spriteData.indexName) == m_MUIButton.end())	// mapIndexName이 중복되지 않는다면
		{
			tagUISpriteButton uis;
			ZeroMemory(&uis, sizeof(tagUISprite));
			m_MUIButton.insert(make_pair(spriteData.indexName, uis));	// 데이터 초기화 후 추가
			tagUISpriteButton *uisAdd = &m_MUIButton.find(spriteData.indexName)->second;	// 추가된 데이터에 값 채우기
			D3DXMatrixIdentity(&uisAdd->matWorld);
			D3DXCreateSprite(g_pD3DDevice, &uisAdd->sprite);

			for (int i = 0; i < 4; i++)	// 0 일반, 1 오버, 2 클릭&선택 중, 3 비활성 :: 테이블의 파일 순서도 동일해야 됨
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
			SetRect(&uisAdd->drawRc, 0, 0, uisAdd->imgInfo.Width, uisAdd->imgInfo.Height);	// 파일상에서 이미지를 가져올 범위(크기)
			uisAdd->buttonFunc = spriteData.buttonFunc;
		}
	}
	else if (spriteData.BG)	// 배경용 이미지라면 BG에 저장
	{
		if (m_MUISpriteBG.find(spriteData.indexName) == m_MUISpriteBG.end())	// mapIndexName이 중복되지 않는다면
		{
			tagUISprite uis;
			ZeroMemory(&uis, sizeof(tagUISprite));
			m_MUISpriteBG.insert(make_pair(spriteData.indexName, uis));	// 데이터 초기화 후 추가
			tagUISprite *uisAdd = &m_MUISpriteBG.find(spriteData.indexName)->second;	// 추가된 데이터에 값 채우기

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
		if (m_MUISprite.find(spriteData.indexName) == m_MUISprite.end())	// mapIndexName이 중복되지 않는다면
		{
			tagUISprite uis;
			ZeroMemory(&uis, sizeof(tagUISprite));
			m_MUISprite.insert(make_pair(spriteData.indexName, uis));	// 데이터 초기화 후 추가
			tagUISprite *uisAdd = &m_MUISprite.find(spriteData.indexName)->second;	// 추가된 데이터에 값 채우기

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
	// csv에서 파일 데이터 읽은 후 AddSprite

	// ---------------------------------- 데이터 읽기(파싱) 시작
	// 데이터 파싱을 수업 코드로 할 필요 없다.
	// 파싱해야될 데이터의 위치와 인자는 항상 동일하기 때문.
	// 아래 같은 파싱이 오히려 빠름.
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
			break;	// 해당 데이터 불러오기 위한 비교
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
		strtok_s(str2, ",", &str2);	// 버튼 사용 여부는 처음에 모두 false. 스킬 사용 시 true
		ld.BG = atoi(strtok_s(str2, ",", &str2));
		ld.indexName = strtok_s(str2, ",", &str2);
		ld.rotate = atof(strtok_s(str2, ",", &str2));
		ld.rotSpd = atof(strtok_s(str2, ",", &str2));
		ld.button = atoi(strtok_s(str2, ",", &str2));
		ld.buttonFunc = atoi(strtok_s(str2, ",", &str2));
		if (ld.button)	// 버튼이면 4개 이미지 추가
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
		else	// 버튼이 아니면 1개 이미지 추가
		{
			string st1 = strtok_s(str2, ",", &str2);
			ld.file[0] = "UI\\" + st1;
		}
		vUIData.push_back(ld);
	}

	// ---------------------------------- 데이터 읽기(파싱) 완료

	for (int i = 0; i < vUIData.size(); i++)	// 파싱한 데이터를 sprite로 생성(추가)
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
		// 이 아래부터 pt 값은 matWorld의 _41, _42 값을 줘야 한다. Scale, Trans가 적용된 World를 기준으로 해야됨
		if (m_MUIButtonIt->second.used) continue;	// 사용 중이면 버튼 업데이트를 안함 (버튼 기능 비활성)
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
	int width = imgInfo.Width * m_UIScale;	// scaling 된 좌표를 기준으로 중심점을 찾아야 함
	int height = imgInfo.Height * m_UIScale;
	POINT rcCenterPt = { pt.x + width / 2, pt.y + height / 2 };
	SetRect(&rc,
		rcCenterPt.x - width	 * m_CollisionRectReduce / 2,
		rcCenterPt.y - height	 * m_CollisionRectReduce / 2,
		rcCenterPt.x + width	 * m_CollisionRectReduce / 2,
		rcCenterPt.y + height	 * m_CollisionRectReduce / 2);
	// m_CollisionRectReduce는 0.5가 100%. 중심을 기반으로 양 옆의 사이즈를 조정하기 때문.

	// 히오스 UI는 Sprite 같은걸 안쓰고 모두 3D(픽킹) 처리를 한 것 같음
}

void cUIObject::updateButtonState(D3DXIMAGE_INFO imgInfo, D3DXVECTOR3 pt, int &buttonState, int buttonFunc)
{
	// 버튼 충돌 처리
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
	//		if (buttonState == UIBUTTONSTATE_OVER)	// 오버 상태일 때 클릭 시
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
	//			// 마우스 클릭 시 기능 실행
	//			//updateButtonCallback(buttonFunc);
	//		}
	//		else if (buttonState == UIBUTTONSTATE_OVER)
	//		{
	//			// 마우스 오버 시 기능 실행
	//			updateButtonOverCallback(buttonFunc);
	//		}
	//		buttonState = UIBUTTONSTATE_OVER;	// 오버 시 상태 변경
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
			NULL,	// 중심점. 회전시킬꺼면 imgInfo에서 Width / 2, Height / 2 넣으면 될듯
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
			NULL,	// 중심점. 회전시킬꺼면 imgInfo에서 Width / 2, Height / 2 넣으면 될듯
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
			NULL,	// 회전 중심점을 넣어도 적용이 안됨
			m_MUISpriteIt->second.rotate,
			&D3DXVECTOR2(m_MUISpriteIt->second.pt.x, m_MUISpriteIt->second.pt.y));
		//updateMatWorld(m_MUISpriteIt->second.matWorld, m_MUISpriteIt->second.pt);
		m_MUISpriteIt->second.sprite->SetTransform(&m_MUISpriteIt->second.matWorld);

		if (m_MUISpriteIt->second.rotSpd != 0)
		{
			m_MUISpriteIt->second.rotate += m_MUISpriteIt->second.rotSpd;
			m_MUISpriteIt->second.sprite->Draw(m_MUISpriteIt->second.texture,
				&m_MUISpriteIt->second.drawRc,
				&D3DXVECTOR3(m_MUISpriteIt->second.imgInfo.Width / 2, m_MUISpriteIt->second.imgInfo.Height / 2, 0),	// 중심점. 회전시킬꺼면 imgInfo에서 Width / 2, Height / 2 넣으면 될듯
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255));
		}
		else
		{
			m_MUISpriteIt->second.sprite->Draw(m_MUISpriteIt->second.texture,
				&m_MUISpriteIt->second.drawRc,
				NULL,	// 중심점. 회전시킬꺼면 imgInfo에서 Width / 2, Height / 2 넣으면 될듯
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
