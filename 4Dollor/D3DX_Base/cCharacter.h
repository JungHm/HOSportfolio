#pragma once
class cCharacter
{
protected:
	SYNTHESIZE(int, Skill, skill);
	SYNTHESIZE(int, m_State, State);
	SYNTHESIZE(D3DXVECTOR3, mouse, mousePos);
public:
	cCharacter();
	virtual ~cCharacter();

	virtual void AnimSetUp() = 0;
	virtual void SetUp() = 0;
	virtual void Update() = 0;
	virtual void Render(D3DXMATRIXA16& matR, D3DXMATRIXA16& matT) = 0;

	virtual void ChangeAni() = 0;
	virtual void BlendAni(int State) = 0;
};

