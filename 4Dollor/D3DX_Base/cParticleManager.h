#pragma once
class cParticle;

struct Partice_info
{
	cParticle* particle;
	D3DXVECTOR3 position;
	bool isOn;
};

class cParticleManager
{
private:
	vector<Partice_info> pInfo;
public:
	cParticleManager();
	~cParticleManager();


	void AddHitParticle();
	

};

