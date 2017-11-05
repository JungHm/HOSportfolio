#pragma once
#include "cAction.h"

class cGameObject : public cObject, public iActionDelegate
{
protected:
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Direction);

public:
	cGameObject();
	virtual ~cGameObject();

	virtual void OnActionFinish(cAction* pSender) override;
};

