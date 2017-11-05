#include "stdafx.h"
#include "cActionSeq.h"


cActionSeq::cActionSeq()
{
}


cActionSeq::~cActionSeq()
{
	for each (auto p in m_lstAction)
	{
		SAFE_DELETE(p);
	}
	m_lstAction.clear();
}

void cActionSeq::AddAction(cAction * pAction)
{
	m_lstAction.push_back(pAction);
}

void cActionSeq::Start()
{
	if (m_lstAction.empty())
		return;

	m_itCurrentAction = m_lstAction.begin();
	(*m_itCurrentAction)->Start();
}

void cActionSeq::Update()
{
	if (m_itCurrentAction == m_lstAction.end())
		return;

	(*m_itCurrentAction)->Update();
}

void cActionSeq::OnActionFinish(cAction * pSender)
{
	++m_itCurrentAction;
	if (m_itCurrentAction == m_lstAction.end())
	{
		if (m_pDelegate)
		{
			m_pDelegate->OnActionFinish(this);
		}
	}
	else
	{
		(*m_itCurrentAction)->Start();
	}
}
