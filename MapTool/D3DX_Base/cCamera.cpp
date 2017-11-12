#include "stdafx.h"
#include "cCamera.h"

cCamera::cCamera()
	: m_vEye(0, 0, 0)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_fCameraDistance(100.0f)
	, m_isLButtonDown(false)
	, m_vCamRotAngle(0, 0, 0)
	, m_eCamMode(WORLD)
	, m_vMove(0, 0, 0)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
	D3DXMatrixIdentity(&m_matTrans);
}

cCamera::~cCamera()
{
}

void cCamera::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update()
{
	if (KEY->isOnceKeyDown(VK_F1))
	{
		m_vLookAt = D3DXVECTOR3(0, 0, 0);
		m_fCameraDistance = 100.0f;
		m_eCamMode = BASE;
	}

	if (KEY->isOnceKeyDown(VK_F2))
	{
		m_vMove = D3DXVECTOR3(0, 0, -15.0f);
		m_fCameraDistance = 50.0f;
		m_eCamMode = WORLD;
	}

	CameraModeChange();

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::CameraModeChange()
{
	switch (m_eCamMode)
	{
	case BASE:	 // 축 중심 카메라
		D3DXMatrixRotationX(&matRX, m_vCamRotAngle.x);
		D3DXMatrixRotationY(&matRY, m_vCamRotAngle.y);
		matR = matRX * matRY;

		m_vEye = D3DXVECTOR3(0, m_fCameraDistance, -m_fCameraDistance);
		D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);
		break;

	case WORLD: // 월드 카메라
		if (KEY->isStayKeyDown('W')) m_vMove.z++;
		if (KEY->isStayKeyDown('S')) m_vMove.z--;
		if (KEY->isStayKeyDown('A')) m_vMove.x--;
		if (KEY->isStayKeyDown('D')) m_vMove.x++;

		D3DXMatrixTranslation(&m_matTrans, m_vMove.x, m_vMove.y, m_vMove.z);

		m_vLookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vEye = D3DXVECTOR3(0.0f, m_fCameraDistance, -m_fCameraDistance);
		D3DXVec3TransformCoord(&m_vLookAt, &m_vLookAt, &m_matTrans);
		D3DXVec3TransformCoord(&m_vEye, &m_vEye, &m_matTrans);
		break;
	}
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		break;

	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;

	case WM_MOUSEMOVE:
		if (m_isLButtonDown)
		{
			POINT ptCurrMouse;
			ptCurrMouse.x = LOWORD(lParam);
			ptCurrMouse.y = HIWORD(lParam);

			float fDeltaX = (float)ptCurrMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)ptCurrMouse.y - m_ptPrevMouse.y;

			m_vCamRotAngle.y += (fDeltaX / 100.f);
			m_vCamRotAngle.x += (fDeltaY / 100.f);

			if (m_vCamRotAngle.x < -D3DX_PI / 2.0f + 0.0001f) m_vCamRotAngle.x = -D3DX_PI / 2.0f + 0.0001f;
			if (m_vCamRotAngle.x > D3DX_PI / 2.0f - 0.0001f) m_vCamRotAngle.x = D3DX_PI / 2.0f - 0.0001f;

			m_ptPrevMouse = ptCurrMouse;
		}
		break;

	case WM_MOUSEWHEEL:
		if (!KEY->isStayKeyDown('R'))
		{
			m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 30.f);
			if (m_fCameraDistance < 0.0001f)
				m_fCameraDistance = 0.0001f;
		}
		break;
	}
}


