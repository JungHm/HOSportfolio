#pragma once
#include "iScene.h"
class cUILoadingInGame;
class cUIInGame;

class cInGame :
	public iScene
{
private:
	cUILoadingInGame*	m_UILoading;
	cUIInGame*			m_UI;

public:
	cInGame();
	~cInGame();

	virtual void SetUp() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
};

