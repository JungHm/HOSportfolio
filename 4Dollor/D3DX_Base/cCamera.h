#pragma once

#define g_Cam	cCamera::GetInstance()

class cCamera
{
	SINGLETONE(cCamera);
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	POINT			m_ptPrevMouse;
	bool			m_isLButtonDown;
	float			m_fCameraDistance;
	SYNTHESIZE(D3DXVECTOR2, m_fCamMove, CamPos);
	D3DXVECTOR3		m_vCamRotAngle;

	SYNTHESIZE(bool, ingame, InGame);

	GETTER(D3DXMATRIXA16, matView, View);
	GETTER(D3DXMATRIXA16, matProj, Proj);
public:


	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

