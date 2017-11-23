#pragma once
class cParticle;

#define g_Particle cParticleManager::GetInstance()

struct Partice_info
{
	cParticle* particle;
	D3DXVECTOR3 position;
	bool isOn;

	Partice_info() :
		isOn(false),
		position(0, 0, 0),
		particle(NULL)
	{

	}
};

class cParticleManager
{
private:
	vector<Partice_info> pInfo;
public:
	SINGLETONE(cParticleManager);
	//cParticleManager();
	//~cParticleManager();

	void AddHitParticle(D3DXVECTOR3 pos);
	void Setup();
	void Destroy();
	void Update();
	void Render(char* TextureName);
};

