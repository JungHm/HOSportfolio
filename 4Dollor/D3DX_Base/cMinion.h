#pragma once

#include <iostream>

#define	MINIONMANAGER		cMinion::GetInstance()

#define MINION_POOL			15

#define BLUE_ANGLE			-D3DX_PI / 2
#define RED_ANGLE			D3DX_PI / 2

#define MINI_LONG_DIS		55
#define MINI_SHORT_DIS		25

#define BLUE_START_X			(float)-250
#define RED_START_X				(float)250

#define CHAR_MINI_RANGE			(float)35
#define CHAR_MINI_ATTACK		(float)15
#define CHAR_MINI_LONG_ATTACK	(float)40

#define MINI_TO_MINI_RANGE		(float)10

enum MINION_DISTANCE
{
	LONG_DIS,
	SHORT_DIS
};

enum DIRECTION
{
	MINI_STAY,			// ���� ��
	MINI_WALK,			// ���� ���� �� �� ���� ���� �ɾ
	MINI_AGGRO,
	MINI_ATTACK,		// (�̴Ͼ� - �̴Ͼ�)���� ������ ����
	MINI_DEATH
};

enum RND_DIRECTION
{
	RND_LEFT,
	RND_RIGHT
};

struct tagMinion
{
	D3DXVECTOR3 pos;	// ������
	D3DXVECTOR3 dir;	// ���� ����

	float angleY;

	int hp;			// �����
	int attack;	// ���ݷ�
	int attack_count; // ���� ��Ÿ��?

	D3DXMATRIXA16 matWorld, matTrans, matScale, matRot;

	float speed;
	float radius;
	int attackSpeed;	// ���� ���ǵ�

	RND_DIRECTION rnd;

	bool coll; // �Ʊ� �̴Ͼ𳢸� �浹���� ��

	TEAM team;					// �Ʊ�, ���� ����
	MINION_DISTANCE dis;
	DIRECTION direction;	// minion�� ���� ����

	int count;

	float coll_angleY;
	bool char_attack;		// �̴Ͼ��� ĳ���� �����ϴ� bool��

							//xFile
	wstring sPath;
	DWORD dAttack;
	DWORD dNone;
	float fBlendTime;
	float fPassedBlendTime;

	int nKey;
	SYNTHESIZE_PASS_BY_REF(ST_SPHERE, sSphere, Sphere);

	DWORD	ani_walk;
	DWORD	ani_attack;


	tagMinion()
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matTrans);
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixIdentity(&matRot);

		pos = D3DXVECTOR3(0, 0, 0);
		dir = D3DXVECTOR3(0, 0, 0.1f);
		hp = 10;
		attack = 1;
		attack_count = 0;
		direction = MINI_STAY;
		count = 0;
		speed = 0.1f;
		radius = 1.0f;
		coll = false;
	}
};

class cMinion
{
	SINGLETONE(cMinion);

private:
	//SYNTHESIZE(vector<tagMinion>, minion, Minion);

	SYNTHESIZE(vector<tagMinion>, blue_minion, BlueMinion);
	SYNTHESIZE(vector<tagMinion>, red_minion, RedMinion);


public:
	void BlueXfileSetup();
	void RedXfileSetup();
	void XfileAnimSetup(DWORD key, char * ani1, char * ani2, OUT DWORD& walk, OUT DWORD& attack);

	void BlueSetup();
	void RedSetup();
	void BlueUpdate(D3DXVECTOR3 chPos, int & chHp);
	void RedUpdate(D3DXVECTOR3 chPos, int & chHp);
	void BlueXfileUpdate(int index);
	void RedXfileUpdate(int index);
	void BlueRender();
	void RedRender();
	void BlueXfileRender(int index);
	void RedXfileRender(int index);



	void BlueDirection(int index, D3DXVECTOR3 chPos, int & chHp);
	void RedDirection(int index, D3DXVECTOR3 chPos, int & chHp);

	// �� ���� ���� �Ÿ� ���ϴ� �Լ�
	float GetDistance(D3DXVECTOR3 a, D3DXVECTOR3 b);

	bool TeamCollision(vector<tagMinion>&a, int index);	// ���� ���� �̴Ͼ𳢸� �浹
	bool OtherCollision(vector<tagMinion>& a, int index); // ���� �ٸ� ���� �̴Ͼ𳢸� �浹

	bool GetAggro(tagMinion& a, D3DXVECTOR3 chPos);

	// �� ���� ������ ���� ���ϴ� �Լ�
	float Vector_To_Vector(D3DXVECTOR3 ch, D3DXVECTOR3 min);

	void BlueMinionCollision();
	void BlueMinionUnColl();

	void RedMinionCollision();
	void RedMinionUnColl();

	void Char_Red_Attack_Q(D3DXVECTOR3 centerPos);
	void Char_Red_Attack_B(D3DXVECTOR3 chPos, bool attack);
};