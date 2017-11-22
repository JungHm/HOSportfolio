#include "stdafx.h"
#include "cUILoadingClientBegin.h"


cUILoadingClientBegin::cUILoadingClientBegin()
	: m_LoadingEnd(false)
{
}

cUILoadingClientBegin::~cUILoadingClientBegin()
{
}

void cUILoadingClientBegin::updateButtonOverCallback(int num)
{

}

void cUILoadingClientBegin::updateButtonCallback(int num)
{
	m_LoadingEnd = true;
}
