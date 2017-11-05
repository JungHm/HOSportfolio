#pragma once
#include "cCube.h"
class cRightArm :
	public cCube
{
public:
	cRightArm();
	~cRightArm();

	virtual void Setup() override;
};

