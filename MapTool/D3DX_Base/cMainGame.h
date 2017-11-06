#pragma once

class cCamera;
class cGrid;
class cInfomation;

class cMainGame
{
private:
	cCamera*	 m_pCamera;
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

