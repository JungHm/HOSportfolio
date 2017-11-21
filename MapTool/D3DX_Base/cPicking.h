#pragma once

/*
피 킹

1. 스크린 포인트 s를 통해 투영창에 대응되는 포인트 p를 얻는다.
2. 원점에서 출발하여 p를 통과하여 발사되는 픽킹 광선을 계산한다.
3. 픽킹 광선과 모델을 동일한 공간으로 변환한다.
4. 픽킹 광선과 교차하는 물체를 알아낸다. 교차된 물체는 선택된 스크린 물체와 대응된다.
*/

class cPicking
{
private:
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;

public:
	cPicking();
	~cPicking();

	static cPicking CalcVeiwSpace(IN int nMouseX, IN int nMouseY);	
	static cPicking CalcWorldSpace(IN int nMouseX, IN int nMouseY);    

	bool IntersectTri(IN D3DXVECTOR3 v0, IN D3DXVECTOR3 v1, IN D3DXVECTOR3 v2, OUT D3DXVECTOR3& vPickingPos);
	bool IntersectSphere(ST_SPHERE* pSphere);
};

