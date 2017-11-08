#pragma once

#define g_cCamera cCamera::GetInstance()

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
	D3DXVECTOR3		m_vCamRotAngle;
	D3DXMATRIXA16 matR, matRX, matRY;

private:
	CAMMODE			m_eCamMode;
	D3DXVECTOR3		m_vMove;
	D3DXMATRIXA16	m_matTrans;

public:
	void Setup();
	void Update();
	void CameraModeChange();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

