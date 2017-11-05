#pragma once
#include "cAction.h"
class cCubeMan;

class cInterpolation : public iActionDelegate
{
protected:
	std::vector<ST_PC_VERTEXT>		m_vecLineVertex;
	cCubeMan*						m_arrCubeMan[2];

public:
	cInterpolation();
	virtual ~cInterpolation();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	virtual void OnActionFinish(cAction* pSender) override;
};

