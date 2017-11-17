#pragma once

class cCharacter;

class cPlayer
{
private://player �⺻ ����
	int m_Hp, m_Mp;


private:
	D3DXMATRIXA16 matWorld, matR, matT;
	cCharacter* m_pChar;
	bool Attack;
	int Skill;
	//�ִϸ��̼� �� �޽� �ε��(�÷��̾ ĳ���� �Ľ��Ѱ��� �־���� ����Ϸ�����)
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Dir);
	SYNTHESIZE(D3DXVECTOR3, m_vFrom, From);
public:
	MATRIX16_FIX;
	cPlayer();
	~cPlayer();

	void SetCharacter(cCharacter* character) { m_pChar = character; }

	void Setup();
	void Update();
	void moveTo();
	void Render();
	void Destroy();
};

