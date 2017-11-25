#pragma once

#include <iostream>

#define	MINIONMANAGER		cMinion::GetInstance()

#define MINION_POOL			15

#define BLUE_ANGLE			-D3DX_PI / 2
#define RED_ANGLE			D3DX_PI / 2

#define MINI_LONG_DIS		50
#define MINI_SHORT_DIS		15

#define BLUE_START_X		(float)-250
#define RED_START_X			(float)250

#define CHAR_MINI_RANGE		(float)35
#define CHAR_MINI_ATTACK	(float)10
#define MINI_TO_MINI_RANGE	(float)10

enum MINION_DISTANCE
{
	LONG_DIS,
	SHORT_DIS
};

enum DIRECTION
{
	MINI_STAY,			// 생성 전
	MINI_WALK,			// 적이 없을 때 적 기지 까지 걸어감
	MINI_AGGRO,
	MINI_ATTACK,		// (미니언 - 미니언)적을 만나면 공격
	MINI_DEATH
};

enum RND_DIRECTION
{
	RND_LEFT,
	RND_RIGHT
};

struct tagMinion
{
	D3DXVECTOR3 pos;	// 포지션
	D3DXVECTOR3 dir;	// 전방 벡터

	float angleY;

	int hp;			// 생명력
	int attack;	// 공격력
	int attack_count; // 공격 쿨타임?

	D3DXMATRIXA16 matWorld, matTrans, matScale, matRot;

	float speed;
	float radius;
	int attackSpeed;	// 공격 스피드

	RND_DIRECTION rnd;

	bool coll; // 아군 미니언끼리 충돌했을 때

	TEAM team;					// 아군, 적군 구분
	MINION_DISTANCE dis;
	DIRECTION direction;	// minion의 상태 구분


	LPD3DXMESH cube;	// 리소스 불러오기 전까지 작업할 큐브
	D3DMATERIAL9 mtrl;

	LPD3DXMESH cylinder;	// 바운딩 박스
	D3DMATERIAL9 c_mtrl;
	D3DXMATRIXA16 c_World;
	D3DXMATRIXA16 c_Rot;

	int count;

	float coll_angleY;

	//xFile
	wstring sPath;
	DWORD dAttack;
	DWORD dNone;
	float fBlendTime;
	float fPassedBlendTime;

	int nKey;
	ST_SPHERE sSphere;
	DWORD	ani_walk;
	DWORD	ani_attack;


	tagMinion()
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matTrans);
		D3DXMatrixIdentity(&matScale);
		D3DXMatrixIdentity(&matRot);
		D3DXMatrixIdentity(&c_World);
		D3DXMatrixIdentity(&c_Rot);

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
	void BlueUpdate(D3DXVECTOR3 chPos);
	void RedUpdate(D3DXVECTOR3 chPos);
	void BlueXfileUpdate(int index);
	void RedXfileUpdate(int index);
	void BlueRender();
	void RedRender();
	void BlueXfileRender(int index);
	void RedXfileRender(int index);

	void BlueDirection(int index, D3DXVECTOR3 chPos);
	void RedDirection(int index, D3DXVECTOR3 chPos);

	// 두 벡터 사이 거리 구하는 함수
	float GetDistance(D3DXVECTOR3 a, D3DXVECTOR3 b);

	bool TeamCollision(vector<tagMinion>&a, int index);	// 같은 팀의 미니언끼리 충돌
	bool OtherCollision(vector<tagMinion>& a, int index); // 서로 다른 팀의 미니언끼리 충돌

	bool GetAggro(tagMinion& a, D3DXVECTOR3 chPos);

	// 두 벡터 사이의 각도 구하는 함수
	float Vector_To_Vector(D3DXVECTOR3 ch, D3DXVECTOR3 min);

	void BlueMinionCollision();
	void BlueMinionUnColl();

	void RedMinionCollision();
	void RedMinionUnColl();
};