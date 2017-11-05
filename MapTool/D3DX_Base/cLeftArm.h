#pragma once
#include "cCube.h"
class cLeftArm :
	public cCube
{
public:
	cLeftArm();
	~cLeftArm();

	virtual void Setup() override;
};

