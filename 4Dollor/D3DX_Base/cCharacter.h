#pragma once
class cCharacter
{
protected:
	SYNTHESIZE(int, m_State, State);
public:
	cCharacter();
	~cCharacter();

	virtual void AnimSetUp() = 0;
	virtual void SetUp() = 0;
	virtual void Update() = 0;
	virtual void Render(D3DXMATRIXA16& matRT) = 0;

	virtual void ChangeAni() = 0;
};

