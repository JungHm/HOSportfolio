#pragma once

class cCharacter;


class cPlayer
{
private://player �⺻ ����
	int experience;
	SYNTHESIZE(int, level, Level);
	int m_Hp, m_Mp, m_Shield;
	int Att;
	SYNTHESIZE(float, m_Radius, Radius);

	//���ݿ�
	SYNTHESIZE(float, distance, Distance);
	bool isAttack;

private:
	D3DXMATRIXA16 matWorld, matR, matT;
	cCharacter* m_pChar;
	bool Attack;

	//�ִϸ��̼� �� �޽� �ε��(�÷��̾ ĳ���� �Ľ��Ѱ��� �־���� ����Ϸ�����)
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Dir);
	SYNTHESIZE(D3DXVECTOR3, m_vFrom, From);
	SYNTHESIZE(D3DXVECTOR3, m_ptMouse, MousePos);

private:
	SYNTHESIZE(ST_SPHERE, m_pSphere, Sphere);

public:
	MATRIX16_FIX;
	cPlayer();
	~cPlayer();

	void SetCharacter(cCharacter* character) { m_pChar = character; }

	void Setup();
	void Update();
	void Update(POINT mouse);
	void moveTo();
	void Render();
	//void Destroy();

	void ExpUp(int value) { experience += value; }

public:
	/*float GetQCool() { return m_pChar->GetCoolQ(); }
	float GetWCool() { return m_pChar->GetCoolW(); }
	float GetECool() { return m_pChar->GetCoolE(); }*/
	float coolQ;
	float coolW;
	float coolE;
	bool isQcool;
	bool isWcool;
	bool isEcool;
};

