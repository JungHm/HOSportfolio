#pragma once
class cGrid
{
private:
	std::vector<ST_PC_VERTEXT>	m_vecVertex;

public:
	cGrid();
	~cGrid();

	void Setup(int nNumHalfTile = 15, float fInterval = 1.0f);
	void Render();
};

