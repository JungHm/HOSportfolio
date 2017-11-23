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

<<<<<<< HEAD
	void AddParticle();
=======
	void AddHitParticle();
	

>>>>>>> 1a2ef2cc514bb9e961f0e1f2d796ac3fe9e47d84
};

