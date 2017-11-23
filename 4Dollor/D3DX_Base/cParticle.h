#pragma once
class cParticle
{
private:
	std::vector<ST_PC_VERTEXT>	m_vecParticle;
	D3DXCOLOR color;
public:
	cParticle();
	~cParticle();
	void SetupParticle(int size,int rad, D3DXCOLOR c);
	void RenderParticle(char* TextureName);
	void UpdateParticle();
	bool Update();
};

