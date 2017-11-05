#pragma once
#include "cCube.h"
class cLeftLeg :
	public cCube
{
public:
	cLeftLeg();
	~cLeftLeg();

	virtual void Setup() override;
};

