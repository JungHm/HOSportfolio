#pragma once
#include "cCube.h"

class cHead :
	public cCube
{
public:
	cHead();
	~cHead();

	virtual void Setup() override;
};

