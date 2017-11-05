#pragma once
#include "cCube.h"
class cBody :
	public cCube
{
public:
	cBody();
	~cBody();

	virtual void Setup() override;
};

