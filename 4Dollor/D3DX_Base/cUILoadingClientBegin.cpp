#include "stdafx.h"
#include "cUILoadingClientBegin.h"


cUILoadingClientBegin::cUILoadingClientBegin()
	: m_LoadingEnd(false)
{
}

cUILoadingClientBegin::~cUILoadingClientBegin()
{
}

int cUILoadingClientBegin::updateButtonOverCallback(int num)
{
	return 0;
}

int cUILoadingClientBegin::updateButtonCallback(int num)
{
	m_LoadingEnd = true;
	return 0;
}

void cUILoadingClientBegin::setupOther()
{
}

void cUILoadingClientBegin::updateOther()
{
}

void cUILoadingClientBegin::renderOther()
{

}

void cUILoadingClientBegin::destroyOther()
{
}
