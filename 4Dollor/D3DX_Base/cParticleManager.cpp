#include "stdafx.h"
#include "cParticleManager.h"
#include "cParticle.h"


cParticleManager::cParticleManager()
{

}


cParticleManager::~cParticleManager()
{

}

void cParticleManager::AddHitParticle(D3DXVECTOR3 pos)
{
	for each(auto p in pInfo)
	{
		if (!p.isOn)//사용중이 아닐때는 받은 좌표로 바꾸고 사용하는중으로 바꾸기
		{
			p.position = pos;
			p.isOn = true;
			return;
		}
	}
	Partice_info pi;
	pi.particle = new cParticle;
	pi.particle->SetupParticle(10, 1, D3DCOLOR_ARGB(255, 150, 60, 70));
	pi.position = pos;
	pi.isOn = true;
	pInfo.push_back(pi);
}

void cParticleManager::Setup()
{
	pInfo.resize(10);
	Partice_info pi;
	pi.particle = new cParticle;
	pi.particle->SetupParticle(10, 1, D3DCOLOR_ARGB(255, 150, 60, 70));
	for each (auto p in pInfo)
	{
		p = pi;
	}
}

void cParticleManager::Destroy()
{
	for each(auto p in pInfo)
	{
		SAFE_DELETE(p.particle);
		p.particle = NULL;
	}
	pInfo.clear();
}

void cParticleManager::Update()
{
	for each(auto p in pInfo)
	{
		if (p.isOn)
		{
			if (!p.particle->Update())
				p.isOn = false;
		}
	}
}

void cParticleManager::Render(char* TextureName)
{
	for each(auto p in pInfo)
	{
		if (p.isOn)
		{
			p.particle->RenderParticle(TextureName);
		}
	}
}
