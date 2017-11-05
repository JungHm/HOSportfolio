#include "stdafx.h"
#include "cInfomation.h"

cInfomation::cInfomation()
	: m_pFont(NULL)
{
}

cInfomation::~cInfomation()
{
	SAFE_RELEASE(m_pFont);
}

void cInfomation::PrintInfo()
{

}
