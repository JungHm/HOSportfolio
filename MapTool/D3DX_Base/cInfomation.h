#pragma once

class cInfomation
{
private:
	LPD3DXFONT			m_pFont;

public:
	cInfomation();
	~cInfomation();

	void Setup();
	void Render();
};

