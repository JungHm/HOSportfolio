#pragma once

/*
�� ŷ

1. ��ũ�� ����Ʈ s�� ���� ����â�� �����Ǵ� ����Ʈ p�� ��´�.
2. �������� ����Ͽ� p�� ����Ͽ� �߻�Ǵ� ��ŷ ������ ����Ѵ�.
3. ��ŷ ������ ���� ������ �������� ��ȯ�Ѵ�.
4. ��ŷ ������ �����ϴ� ��ü�� �˾Ƴ���. ������ ��ü�� ���õ� ��ũ�� ��ü�� �����ȴ�.
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

