#pragma once
#include "cAction.h"

class cActionLinear : public cAction
{
protected:
	float	m_dwStartTime;
	float	m_fPassedTime;

	D3DXVECTOR3		m_vPrevPos;

	SYNTHESIZE(D3DXVECTOR3, m_vFrom, From);
	SYNTHESIZE(D3DXVECTOR3, m_vTo, To);
	SYNTHESIZE(float, m_fActionTime, ActionTime);

public:
	cActionLinear();
	virtual ~cActionLinear();

	virtual void Start() override;
	virtual void Update() override;
};

