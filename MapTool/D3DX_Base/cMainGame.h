#pragma once

class cMapTool;

class cMainGame
{
private:
	cMapTool*	 m_pMapTool;
	

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

