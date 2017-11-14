#pragma once

class cCharacter;

class cPlayer
{
private:
	D3DXMATRIXA16 matWorld, matR, matT;
	cCharacter* m_pChar;
	int Skill;
	//애니메이션 및 메쉬 로드용(플레이어에 캐릭터 파싱한것을 넣어놓고 사용하려구염)
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Dir);
	SYNTHESIZE(D3DXVECTOR3, m_vFrom, From);
public:
	cPlayer();
	~cPlayer();

	void SetCharacter(cCharacter* character) { m_pChar = character; }

	void Setup();
	void Update();
	void moveTo();
	void Render();
	void Destroy();
};

