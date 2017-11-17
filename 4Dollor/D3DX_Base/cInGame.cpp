#include "stdafx.h"
#include "cInGame.h"
#include "cUILoadingInGame.h"
#include "cUIInGame.h"


cInGame::cInGame()
{
}


cInGame::~cInGame()
{


	
	if (m_UI)
	{
		m_UI->destroy();
		SAFE_DELETE(m_UI);
	}

	if (m_UILoading)
	{
		m_UILoading->destroy();
		SAFE_DELETE(m_UILoading);
	}
}

void cInGame::SetUp()
{
	m_UILoading = new cUILoadingInGame;
	m_UILoading->setup("cUILoadingInGame");

	m_UI = new cUIInGame;
	m_UI->setup("cInGame");
}

void cInGame::Destroy()
{
}

void cInGame::Update()
{
	//if (GetAsyncKeyState(VK_LBUTTON)&0001)
	//{
	//	g_Scene->ChangeScene("menu");
	//}


	if (m_UI && !m_UILoading) m_UI->update();	// 버튼이 있으므로 update
	else if (m_UILoading)
	{
		m_UILoading->update();
		if (m_UILoading->getLoadingEnd())
		{
			m_UILoading->destroy();
			SAFE_DELETE(m_UILoading);
		}
	}
}

void cInGame::Render()
{
	if (m_UI && !m_UILoading) m_UI->renderBG();	// 배경 먼저 띄워야 함
	else if (m_UILoading) m_UILoading->renderBG();





	if (m_UI && !m_UILoading) m_UI->render();	// 배경 외 UI 관련된 내용
	else if (m_UILoading) m_UILoading->render();
}
