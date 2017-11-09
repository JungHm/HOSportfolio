#pragma once
class cUnit
{
protected:
	//x file로드에 사용
	char* fileName;
	LPD3DXFRAME* m_pFrameRoot;
	LPD3DXANIMATIONCONTROLLER*	m_pAnimControl;
	LPD3DXMESH* m_pMesh;
	//position & direction
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Direction);
	//Animation Blending.
	DWORD						m_AnimationIndex;
	DWORD						m_PrevAnimationIndex;
	float						m_TrackWeight_0;
	float						m_TrackWeight_1;
public:
	cUnit();
	~cUnit();
};

