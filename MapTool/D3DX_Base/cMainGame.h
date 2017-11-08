#pragma once

class cGrid;
class cInfomation;

class cMainGame
{
private:
	cGrid*		 m_pGrid;
	cInfomation* m_pInfo;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

