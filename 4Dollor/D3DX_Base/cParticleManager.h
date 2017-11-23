#pragma once
class cParticle;

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
	cParticleManager();
	~cParticleManager();

	void AddHitParticle(D3DXVECTOR3 pos);
	void Destroy();
	void Update();
	void Render(char* TextureName);
};

