#include "stdafx.h"
#include "cMinion.h"


cMinion::cMinion()
{
}


cMinion::~cMinion()
{
}

void cMinion::BlueXfileSetup()
{
	for (int j = 0; j < 5; j++)
	{
		tagMinion m;

		if (j < 2) // 0, 1
		{
			m.fBlendTime = 0.3f;
			m.sPath = L"minion/minionRange2.x";
			m.nKey = j + 3;
			m.dis = LONG_DIS;
			XFile->SetXFile(m.nKey, m.sPath);
			XfileAnimSetup(m.nKey, "Anim-1 ", "Anim-2 ", m.ani_walk, m.ani_attack);
		}

		else // 2, 3, 4
		{
			m.fBlendTime = 0.3f;
			m.sPath = L"minion/minion2.x";
			m.nKey = j + 3;
			m.dis = SHORT_DIS;
			XFile->SetXFile(m.nKey, m.sPath);
			XfileAnimSetup(m.nKey, "Anim-2 ", "Anim-3 ", m.ani_walk, m.ani_attack);
		}

		int rnd = rand() % 2;

		if (rnd == 0) m.rnd = RND_LEFT;
		else m.rnd = RND_RIGHT;

		int pos_rnd = (rand() % 5) - 2;

		m.coll_angleY = 0.0f;
		m.angleY = BLUE_ANGLE;

		m.team = TEAM_BLUE;
		m.pos = D3DXVECTOR3(BLUE_START_X, 1.0f, pos_rnd);
		m.dir = D3DXVECTOR3(0.2f, 0.0f, 0.0f);

		m.hp = 10;
		m.attack = 1;
		m.direction = MINI_DEATH;
		blue_minion.push_back(m);
	}
}

void cMinion::RedXfileSetup()
{
	for (int j = 0; j < 5; j++)
	{
		tagMinion m;

		if (j < 2) // 0, 1
		{
			m.fBlendTime = 0.3f;
			m.sPath = L"minion/minionRange1.x";
			m.nKey = j + 8;
			m.dis = LONG_DIS;
			XFile->SetXFile(m.nKey, m.sPath);
			XfileAnimSetup(m.nKey, "Anim-1 ", "Anim-2 ", m.ani_walk, m.ani_attack);
		}

		else // 2, 3, 4
		{
			m.fBlendTime = 0.3f;
			m.sPath = L"minion/minion1.x";
			m.nKey = j + 8;
			m.dis = SHORT_DIS;
			XFile->SetXFile(m.nKey, m.sPath);
			XfileAnimSetup(m.nKey, "Anim-3 ", "Anim-4 ", m.ani_walk, m.ani_attack);
		}

		int rnd = rand() % 2;

		if (rnd == 0) m.rnd = RND_LEFT;
		else m.rnd = RND_RIGHT;

		int pos_rnd = (rand() % 5) - 2;

		m.coll_angleY = 0.0f;
		m.angleY = RED_ANGLE;

		m.team = TEAM_RED;
		m.pos = D3DXVECTOR3(RED_START_X, 1.0f, pos_rnd);
		m.dir = D3DXVECTOR3(-0.2f, 0.0f, 0.0f);

		m.hp = 10;
		m.attack = 1;
		m.direction = MINI_DEATH;
		red_minion.push_back(m);
	}
}

void cMinion::XfileAnimSetup(DWORD key, char * ani1, char * ani2, OUT DWORD& walk, OUT DWORD& attack)
{
	LPD3DXANIMATIONSET pAS;

	for (DWORD i = 0; i < XFile->GetAniCtrl(key)->GetNumAnimationSets(); ++i)
	{
		XFile->GetAniCtrl(key)->GetAnimationSet(i, &pAS);

		if (!strncmp(pAS->GetName(), ani1, strlen(pAS->GetName())))
		{
			walk = i;
		}

		else if (!strncmp(pAS->GetName(), ani2, strlen(pAS->GetName())))
		{
			attack = i;
		}
	}
	XFile->GetAniCtrl(key)->GetAnimationSet(walk, &pAS);
	XFile->GetAniCtrl(key)->SetTrackAnimationSet(0, pAS);
	XFile->GetAniCtrl(key)->ResetTime();
}


void cMinion::BlueSetup()
{
	for (int i = 0; i < blue_minion.size(); i++)
	{
		if (blue_minion[i].direction == MINI_DEATH)
		{
			int rnd = rand() % 2;

			if (rnd == 0) blue_minion[i].rnd = RND_LEFT;
			else blue_minion[i].rnd = RND_RIGHT;

			int pos_rnd = (rand() % 5) - 2;

			blue_minion[i].coll_angleY = 0.0f;
			blue_minion[i].angleY = BLUE_ANGLE;

			blue_minion[i].pos = D3DXVECTOR3(BLUE_START_X, 1.0f, pos_rnd);
			blue_minion[i].dir = D3DXVECTOR3(0.2f, 0.0f, 0.0f);

			blue_minion[i].hp = 10;
			blue_minion[i].attack = 1;

			blue_minion[i].direction = MINI_STAY;
			break;
		}
	}

}

void cMinion::RedSetup()
{
	for (int i = 0; i < red_minion.size(); i++)
	{
		if (red_minion[i].direction == MINI_DEATH)
		{
			int rnd = rand() % 2;

			if (rnd == 0) red_minion[i].rnd = RND_LEFT;
			else red_minion[i].rnd = RND_RIGHT;

			int pos_rnd = (rand() % 5) - 2;

			red_minion[i].coll_angleY = 0.0f;
			red_minion[i].angleY = RED_ANGLE;

			red_minion[i].pos = D3DXVECTOR3(RED_START_X, 1.0f, pos_rnd);
			red_minion[i].dir = D3DXVECTOR3(-0.2f, 0.0f, 0.0f);

			red_minion[i].hp = 10;
			red_minion[i].attack = 1;

			red_minion[i].direction = MINI_STAY;
			break;
		}
	}
}

void cMinion::BlueUpdate(D3DXVECTOR3 chPos)
{
	for (unsigned int i = 0; i < blue_minion.size(); i++)
	{
		if (blue_minion[i].direction != MINI_DEATH)
		{
			D3DXMatrixRotationY(&blue_minion[i].matRot, blue_minion[i].angleY);

			D3DXMatrixTranslation(&blue_minion[i].matTrans, blue_minion[i].pos.x, blue_minion[i].pos.y, blue_minion[i].pos.z);

			// 방향벡터 초기화

			blue_minion[i].dir = D3DXVECTOR3(0.2f, 0.0f, 0.0f);

			//blue_minion[i].matRot = blue_minion[i].RotZ * blue_minion[i].RotX * blue_minion[i].RotY;

			//D3DXVec3TransformNormal(&blue_minion[i].dir, &blue_minion[i].dir, &blue_minion[i].matRot);

			blue_minion[i].matWorld = blue_minion[i].matScale * blue_minion[i].matRot * blue_minion[i].matTrans;

			blue_minion[i].c_World = blue_minion[i].c_Rot * blue_minion[i].matTrans;

			BlueDirection(i, chPos);
			BlueXfileUpdate(i);
		}
	}
	BlueMinionCollision();
	BlueMinionUnColl();
}

void cMinion::RedUpdate(D3DXVECTOR3 chPos)
{
	for (unsigned int i = 0; i < red_minion.size(); i++)
	{
		if (red_minion[i].direction != MINI_DEATH)
		{
			D3DXMatrixRotationY(&red_minion[i].matRot, red_minion[i].angleY);

			D3DXMatrixTranslation(&red_minion[i].matTrans, red_minion[i].pos.x, red_minion[i].pos.y, red_minion[i].pos.z);

			// 방향벡터 초기화

			red_minion[i].dir = D3DXVECTOR3(-0.2f, 0.0f, 0.0f);

			//red_minion[i].matRot = red_minion[i].RotZ * red_minion[i].RotX * red_minion[i].RotY;

			//D3DXVec3TransformNormal(&red_minion[i].dir, &red_minion[i].dir, &red_minion[i].matRot);

			red_minion[i].matWorld = red_minion[i].matScale * red_minion[i].matRot * red_minion[i].matTrans;

			red_minion[i].c_World = red_minion[i].c_Rot * red_minion[i].matTrans;

			RedDirection(i, chPos);
			RedXfileUpdate(i);
		}
	}

	RedMinionCollision();
	RedMinionUnColl();
}

void cMinion::BlueXfileUpdate(int index)
{
	XFile->GetAniCtrl(blue_minion[index].nKey)->AdvanceTime(g_pTimeManager->GetEllapsedTime(), NULL);
	double dA = XFile->GetAniCtrl(blue_minion[index].nKey)->GetTime();
	XFile->GetXFile(blue_minion[index].nKey)->Update();

	LPD3DXANIMATIONSET pAS = nullptr;
	LPD3DXANIMATIONSET pASCompare = nullptr;
	D3DXTRACK_DESC desc;

	if (blue_minion[index].direction == MINI_WALK)
	{
		XFile->GetAniCtrl(blue_minion[index].nKey)->GetAnimationSet(blue_minion[index].ani_walk, &pAS);
		XFile->GetAniCtrl(blue_minion[index].nKey)->GetTrackAnimationSet(0, &pASCompare);

		if (!strcmp(pAS->GetName(), pASCompare->GetName()))
		{
			XFile->GetAniCtrl(blue_minion[index].nKey)->GetTrackDesc(0, &desc);
		}
		else
		{
			XFile->GetAniCtrl(blue_minion[index].nKey)->SetTrackAnimationSet(0, pAS);
			XFile->GetAniCtrl(blue_minion[index].nKey)->SetTrackPosition(0, 0);
		}
	}

	if (blue_minion[index].direction == MINI_ATTACK)
	{
		XFile->GetAniCtrl(blue_minion[index].nKey)->GetAnimationSet(blue_minion[index].ani_attack, &pAS);
		XFile->GetAniCtrl(blue_minion[index].nKey)->GetTrackAnimationSet(0, &pASCompare);

		if (!strcmp(pAS->GetName(), pASCompare->GetName()))
		{
			XFile->GetAniCtrl(blue_minion[index].nKey)->GetTrackDesc(0, &desc);
		}
		else
		{
			XFile->GetAniCtrl(blue_minion[index].nKey)->SetTrackAnimationSet(0, pAS);
			XFile->GetAniCtrl(blue_minion[index].nKey)->SetTrackPosition(0, 0);
		}
	}
}

void cMinion::RedXfileUpdate(int index)
{
	XFile->GetAniCtrl(red_minion[index].nKey)->AdvanceTime(g_pTimeManager->GetEllapsedTime(), NULL);
	double dA = XFile->GetAniCtrl(red_minion[index].nKey)->GetTime();
	XFile->GetXFile(red_minion[index].nKey)->Update();

	LPD3DXANIMATIONSET pAS = nullptr;
	LPD3DXANIMATIONSET pASCompare = nullptr;
	D3DXTRACK_DESC desc;

	if (red_minion[index].direction == MINI_WALK)
	{
		XFile->GetAniCtrl(red_minion[index].nKey)->GetAnimationSet(red_minion[index].ani_walk, &pAS);
		XFile->GetAniCtrl(red_minion[index].nKey)->GetTrackAnimationSet(0, &pASCompare);

		if (!strcmp(pAS->GetName(), pASCompare->GetName()))
		{
			XFile->GetAniCtrl(red_minion[index].nKey)->GetTrackDesc(0, &desc);
		}
		else
		{
			XFile->GetAniCtrl(red_minion[index].nKey)->SetTrackAnimationSet(0, pAS);
			XFile->GetAniCtrl(red_minion[index].nKey)->SetTrackPosition(0, 0);
		}
	}

	if (red_minion[index].direction == MINI_ATTACK)
	{
		XFile->GetAniCtrl(red_minion[index].nKey)->GetAnimationSet(red_minion[index].ani_attack, &pAS);
		XFile->GetAniCtrl(red_minion[index].nKey)->GetTrackAnimationSet(0, &pASCompare);

		if (!strcmp(pAS->GetName(), pASCompare->GetName()))
		{
			XFile->GetAniCtrl(red_minion[index].nKey)->GetTrackDesc(0, &desc);
		}

		else
		{
			XFile->GetAniCtrl(red_minion[index].nKey)->SetTrackAnimationSet(0, pAS);
			XFile->GetAniCtrl(red_minion[index].nKey)->SetTrackPosition(0, 0);
		}
	}
}

void cMinion::BlueRender()
{
	for (unsigned int i = 0; i < blue_minion.size(); i++)
	{
		if (blue_minion[i].direction != MINI_DEATH)
		{
			BlueXfileRender(i);
		}
	}
}

void cMinion::RedRender()
{
	for (unsigned int i = 0; i < red_minion.size(); i++)
	{
		if (red_minion[i].direction != MINI_DEATH)
		{
			RedXfileRender(i);
		}
	}
}

void cMinion::BlueXfileRender(int index)
{
	XFile->GetXFile(blue_minion[index].nKey)->Render(blue_minion[index].matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cMinion::RedXfileRender(int index)
{
	XFile->GetXFile(red_minion[index].nKey)->Render(red_minion[index].matWorld);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void cMinion::BlueDirection(int index, D3DXVECTOR3 chPos)
{
	switch (blue_minion[index].direction)
	{
	case MINI_STAY:
		blue_minion[index].count++;

		if (blue_minion[index].count == 100)
		{
			blue_minion[index].direction = MINI_WALK;
		}

		break;
	case MINI_WALK:
	{
		if (blue_minion[index].pos.x < -BLUE_START_X)
			blue_minion[index].pos += blue_minion[index].dir;

		if (GetAggro(blue_minion[index], chPos))
			blue_minion[index].direction = MINI_AGGRO;

		if (OtherCollision(blue_minion, index))
		{
			blue_minion[index].direction = MINI_ATTACK;
		}

		blue_minion[index].angleY = BLUE_ANGLE;

	}

	break;
	case MINI_AGGRO:
	{
		D3DXVECTOR3 m_pos = blue_minion[index].pos;		// 미니언 포지션
		D3DXVECTOR3 m_dir = blue_minion[index].dir;		// 미니언 전방 벡터
		D3DXVECTOR3 p_pos = chPos;						// 캐릭터 포지션

		D3DXVECTOR3 mp_dir = p_pos - m_pos;				// 미니언이 캐릭터를 바라보는 벡터

														// 방향벡터는 모두 노멀라이징을 통해 단위 벡터화 시켜야함
		D3DXVec3Normalize(&m_dir, &m_dir);
		D3DXVec3Normalize(&mp_dir, &mp_dir);

		// 미니언이 주인공을 바라보는 벡터와 몬스터의 전방벡터를 이용해 내적을 구한다.
		float dot;		// 내적 값
		float radian;	// 내적한 값을 역코사인 해서 구한 최종 각도

						// 미니언 전방벡터와 몬스터가 주인공 캐릭터를 바라보는 벡터의 내적값을 구함
		dot = D3DXVec3Dot(&m_dir, &mp_dir);

		// 구한 내적값을 이용해 최종 각도를 구함
		// acos()함수는 double형을 반환하기 때문에 float형으로 형변환을 해줘야 함
		radian = (float)acos(dot);

		// 캐릭터가 미니언의 좌측에 있는지 우측에 있는지 구하는 방법
		// 첫번째로 미니언의 우향 벡터를 구해야함
		// 모든 방향벡터는 단위 벡터
		D3DXVECTOR3 right_dir;		// 미니언의 우향벡터값

									// 미니언의 전방벡터와 몬스터의 업벡터를 이용해 몬스터의 우향벡터를 구함
									// 여기서 D3DXVECTOR3(0.0f, 1.0f, 0.0f)가 업벡터이다.
		D3DXVec3Cross(&right_dir, &m_dir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		// 몬스터의 우향벡터와 몬스터가 주인공 캐릭터를 바라보는 벡터의 내적을 구함
		if (D3DXVec3Dot(&right_dir, &mp_dir) > 0)
		{
			D3DXMATRIXA16 rotY;
			D3DXMatrixRotationY(&rotY, -radian);

			blue_minion[index].angleY = -radian + BLUE_ANGLE;

			blue_minion[index].dir = D3DXVECTOR3(0.2f, 0.0f, 0.0f);

			float distance = GetDistance(chPos, blue_minion[index].pos);

			if (distance >= CHAR_MINI_ATTACK && distance < CHAR_MINI_RANGE) {
				D3DXVec3TransformNormal(&blue_minion[index].dir, &blue_minion[index].dir, &rotY);
				blue_minion[index].pos += blue_minion[index].dir;
			}

			if (distance < CHAR_MINI_ATTACK)
			{
				// 시선만 방향 따라다님, 공격
			}
		}

		else
		{
			// 오른쪽
			D3DXMATRIXA16 rotY;
			D3DXMatrixRotationY(&rotY, radian);

			blue_minion[index].angleY = radian + BLUE_ANGLE;

			blue_minion[index].dir = D3DXVECTOR3(0.2f, 0.0f, 0.0f);

			float distance = GetDistance(chPos, blue_minion[index].pos);

			if (distance >= CHAR_MINI_ATTACK && distance < CHAR_MINI_RANGE) {
				D3DXVec3TransformNormal(&blue_minion[index].dir, &blue_minion[index].dir, &rotY);

				blue_minion[index].pos += blue_minion[index].dir;
			}

			if (distance < CHAR_MINI_ATTACK)
			{
				// 시선만 방향 따라다님, 공격
			}
		}

		if (OtherCollision(blue_minion, index))
		{
			blue_minion[index].direction = MINI_ATTACK;
		}


		if (!GetAggro(blue_minion[index], chPos))
		{
			blue_minion[index].direction = MINI_WALK;
		}
	}
	break;

	case MINI_ATTACK:
	{
		// ATTACK 상태인 상대 미니언 중 거리가 가장 가까운 애를 공격

		int red_index = 0;
		float red_distance = 0;

		for (int i = 0; i < red_minion.size(); i++)
		{
			if (red_minion[i].direction == MINI_ATTACK)
			{
				red_distance = GetDistance(blue_minion[index].pos, red_minion[i].pos);
				red_index = i;
				break;
			}
		}

		for (int i = 0; i < red_minion.size(); i++)
		{
			if (red_minion[i].direction == MINI_ATTACK)
			{
				if (red_distance > GetDistance(blue_minion[index].pos, red_minion[i].pos))
				{
					red_distance = GetDistance(blue_minion[index].pos, red_minion[i].pos);
					red_index = i;
				}
			}
		}

		if (blue_minion[index].attack_count % 60 == 0)
		{
			if (red_minion[red_index].hp >= 0)
			{
				red_minion[red_index].hp -= blue_minion[index].attack;
			}

			else
			{
				red_minion[red_index].direction = MINI_DEATH;
			}
		}

		//=============================================

		D3DXVECTOR3 m_pos = blue_minion[index].pos;		// 미니언 포지션
		D3DXVECTOR3 m_dir = blue_minion[index].dir;		// 미니언 전방 벡터
		D3DXVECTOR3 p_pos = red_minion[red_index].pos;						// 캐릭터 포지션

		D3DXVECTOR3 mp_dir = p_pos - m_pos;				// 미니언이 캐릭터를 바라보는 벡터

														// 방향벡터는 모두 노멀라이징을 통해 단위 벡터화 시켜야함
		D3DXVec3Normalize(&m_dir, &m_dir);
		D3DXVec3Normalize(&mp_dir, &mp_dir);

		// 미니언이 주인공을 바라보는 벡터와 몬스터의 전방벡터를 이용해 내적을 구한다.
		float dot;		// 내적 값
		float radian;	// 내적한 값을 역코사인 해서 구한 최종 각도

						// 미니언 전방벡터와 몬스터가 주인공 캐릭터를 바라보는 벡터의 내적값을 구함
		dot = D3DXVec3Dot(&m_dir, &mp_dir);

		// 구한 내적값을 이용해 최종 각도를 구함
		// acos()함수는 double형을 반환하기 때문에 float형으로 형변환을 해줘야 함
		radian = (float)acos(dot);

		// 캐릭터가 미니언의 좌측에 있는지 우측에 있는지 구하는 방법
		// 첫번째로 미니언의 우향 벡터를 구해야함
		// 모든 방향벡터는 단위 벡터
		D3DXVECTOR3 right_dir;		// 미니언의 우향벡터값

									// 미니언의 전방벡터와 몬스터의 업벡터를 이용해 몬스터의 우향벡터를 구함
									// 여기서 D3DXVECTOR3(0.0f, 1.0f, 0.0f)가 업벡터이다.
		D3DXVec3Cross(&right_dir, &m_dir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		// 몬스터의 우향벡터와 몬스터가 주인공 캐릭터를 바라보는 벡터의 내적을 구함
		if (D3DXVec3Dot(&right_dir, &mp_dir) > 0)
		{
			D3DXMATRIXA16 rotY;
			D3DXMatrixRotationY(&rotY, -radian);

			blue_minion[index].angleY = -radian + BLUE_ANGLE;
		}

		else
		{
			// 오른쪽
			D3DXMATRIXA16 rotY;
			D3DXMatrixRotationY(&rotY, radian);

			blue_minion[index].angleY = radian + BLUE_ANGLE;
		}



		//=============================================

		blue_minion[index].attack_count++;

		if (!OtherCollision(blue_minion, index))
		{
			blue_minion[index].direction = MINI_WALK;
		}

	}
	break;

	case MINI_DEATH:


		break;
	}
}

void cMinion::RedDirection(int index, D3DXVECTOR3 chPos)
{
	switch (red_minion[index].direction)
	{
	case MINI_STAY:
		red_minion[index].count++;

		if (red_minion[index].count == 100)
		{
			red_minion[index].direction = MINI_WALK;
		}

		break;
	case MINI_WALK:
		if (red_minion[index].pos.x > -RED_START_X)
			red_minion[index].pos += red_minion[index].dir;

		if (GetAggro(red_minion[index], chPos))
			red_minion[index].direction = MINI_AGGRO;

		if (OtherCollision(red_minion, index))
		{
			red_minion[index].direction = MINI_ATTACK;
		}

		red_minion[index].angleY = RED_ANGLE;

		break;
	case MINI_AGGRO:
	{

		D3DXVECTOR3 m_pos = red_minion[index].pos;		// 미니언 포지션
		D3DXVECTOR3 m_dir = red_minion[index].dir;		// 미니언 전방 벡터
		D3DXVECTOR3 p_pos = chPos;						// 캐릭터 포지션

		D3DXVECTOR3 mp_dir = p_pos - m_pos;				// 미니언이 캐릭터를 바라보는 벡터

														// 방향벡터는 모두 노멀라이징을 통해 단위 벡터화 시켜야함
		D3DXVec3Normalize(&m_dir, &m_dir);
		D3DXVec3Normalize(&mp_dir, &mp_dir);

		// 미니언이 주인공을 바라보는 벡터와 몬스터의 전방벡터를 이용해 내적을 구한다.
		float dot;		// 내적 값
		float radian;	// 내적한 값을 역코사인 해서 구한 최종 각도

						// 미니언 전방벡터와 몬스터가 주인공 캐릭터를 바라보는 벡터의 내적값을 구함
		dot = D3DXVec3Dot(&m_dir, &mp_dir);

		// 구한 내적값을 이용해 최종 각도를 구함
		// acos()함수는 double형을 반환하기 때문에 float형으로 형변환을 해줘야 함
		radian = (float)acos(dot);

		// 캐릭터가 미니언의 좌측에 있는지 우측에 있는지 구하는 방법
		// 첫번째로 미니언의 우향 벡터를 구해야함
		// 모든 방향벡터는 단위 벡터
		D3DXVECTOR3 right_dir;		// 미니언의 우향벡터값

									// 미니언의 전방벡터와 몬스터의 업벡터를 이용해 몬스터의 우향벡터를 구함
									// 여기서 D3DXVECTOR3(0.0f, 1.0f, 0.0f)가 업벡터이다.
		D3DXVec3Cross(&right_dir, &m_dir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		// 몬스터의 우향벡터와 몬스터가 주인공 캐릭터를 바라보는 벡터의 내적을 구함
		if (D3DXVec3Dot(&right_dir, &mp_dir) > 0)
		{
			D3DXMATRIXA16 rotY;
			D3DXMatrixRotationY(&rotY, -radian);

			red_minion[index].angleY = -radian + RED_ANGLE;

			red_minion[index].dir = D3DXVECTOR3(-0.2f, 0.0f, 0.0f);

			float distance = GetDistance(chPos, red_minion[index].pos);

			if (distance >= CHAR_MINI_ATTACK && distance < CHAR_MINI_RANGE)
			{
				D3DXVec3TransformNormal(&red_minion[index].dir, &red_minion[index].dir, &rotY);
				red_minion[index].pos += red_minion[index].dir;
			}

			if (distance < CHAR_MINI_ATTACK)
			{
				// 시선만 방향 따라다님, 공격
			}
		}

		else
		{
			// 오른쪽
			D3DXMATRIXA16 rotY;
			D3DXMatrixRotationY(&rotY, radian);

			red_minion[index].angleY = radian + RED_ANGLE;

			red_minion[index].dir = D3DXVECTOR3(-0.2f, 0.0f, 0.0f);

			float distance = GetDistance(chPos, red_minion[index].pos);

			if (distance >= CHAR_MINI_ATTACK && distance < CHAR_MINI_RANGE) {
				D3DXVec3TransformNormal(&red_minion[index].dir, &red_minion[index].dir, &rotY);

				red_minion[index].pos += red_minion[index].dir;
			}

			if (distance < CHAR_MINI_ATTACK)
			{
				// 시선만 방향 따라다님, 공격
			}
		}

		if (OtherCollision(red_minion, index))
		{
			red_minion[index].direction = MINI_ATTACK;
		}


		if (!GetAggro(red_minion[index], chPos))
		{
			red_minion[index].direction = MINI_WALK;
		}
	}
	break;
	case MINI_ATTACK:
		// ATTACK 상태인 상대 미니언 중 거리가 가장 가까운 애를 공격
	{
		int blue_index = 0;
		float blue_distance = 0;

		for (int i = 0; i < blue_minion.size(); i++)
		{
			if (blue_minion[i].direction == MINI_ATTACK)
			{
				blue_distance = GetDistance(red_minion[index].pos, blue_minion[i].pos);
				blue_index = i;
				break;
			}
		}

		for (int i = 0; i < blue_minion.size(); i++)
		{
			if (blue_minion[i].direction == MINI_ATTACK)
			{
				if (blue_distance > GetDistance(red_minion[index].pos, blue_minion[i].pos))
				{
					blue_distance = GetDistance(red_minion[index].pos, blue_minion[i].pos);
					blue_index = i;
				}
			}
		}

		if (red_minion[index].attack_count % 60 == 0)
		{
			if (blue_minion[blue_index].hp >= 0)
			{
				blue_minion[blue_index].hp -= red_minion[index].attack;
			}

			else
			{
				blue_minion[blue_index].direction = MINI_DEATH;
			}
		}

		//=================================================

		D3DXVECTOR3 m_pos = red_minion[index].pos;		// 미니언 포지션
		D3DXVECTOR3 m_dir = red_minion[index].dir;		// 미니언 전방 벡터
		D3DXVECTOR3 p_pos = blue_minion[blue_index].pos;						// 캐릭터 포지션

		D3DXVECTOR3 mp_dir = p_pos - m_pos;				// 미니언이 캐릭터를 바라보는 벡터

														// 방향벡터는 모두 노멀라이징을 통해 단위 벡터화 시켜야함
		D3DXVec3Normalize(&m_dir, &m_dir);
		D3DXVec3Normalize(&mp_dir, &mp_dir);

		// 미니언이 주인공을 바라보는 벡터와 몬스터의 전방벡터를 이용해 내적을 구한다.
		float dot;		// 내적 값
		float radian;	// 내적한 값을 역코사인 해서 구한 최종 각도

						// 미니언 전방벡터와 몬스터가 주인공 캐릭터를 바라보는 벡터의 내적값을 구함
		dot = D3DXVec3Dot(&m_dir, &mp_dir);

		// 구한 내적값을 이용해 최종 각도를 구함
		// acos()함수는 double형을 반환하기 때문에 float형으로 형변환을 해줘야 함
		radian = (float)acos(dot);

		// 캐릭터가 미니언의 좌측에 있는지 우측에 있는지 구하는 방법
		// 첫번째로 미니언의 우향 벡터를 구해야함
		// 모든 방향벡터는 단위 벡터
		D3DXVECTOR3 right_dir;		// 미니언의 우향벡터값

									// 미니언의 전방벡터와 몬스터의 업벡터를 이용해 몬스터의 우향벡터를 구함
									// 여기서 D3DXVECTOR3(0.0f, 1.0f, 0.0f)가 업벡터이다.
		D3DXVec3Cross(&right_dir, &m_dir, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

		// 몬스터의 우향벡터와 몬스터가 주인공 캐릭터를 바라보는 벡터의 내적을 구함
		if (D3DXVec3Dot(&right_dir, &mp_dir) > 0)
		{
			D3DXMATRIXA16 rotY;
			D3DXMatrixRotationY(&rotY, -radian);

			red_minion[index].angleY = -radian + RED_ANGLE;
		}

		else
		{
			// 오른쪽
			D3DXMATRIXA16 rotY;
			D3DXMatrixRotationY(&rotY, radian);

			red_minion[index].angleY = radian + RED_ANGLE;
		}



		//=================================================
		red_minion[index].attack_count++;

		if (!OtherCollision(red_minion, index))
		{
			red_minion[index].direction = MINI_WALK;
		}
	}
	break;

	case MINI_DEATH:
		break;
	}
}

float cMinion::GetDistance(D3DXVECTOR3 a, D3DXVECTOR3 b)
{
	float x = a.x - b.x;
	float z = a.z - b.z;

	float distance = sqrt(x * x + z * z);

	return distance;
}

bool cMinion::TeamCollision(vector<tagMinion>& a, int index)
{
	if (a[index].team == TEAM_BLUE)
	{
		for (int i = 0; i < blue_minion.size(); i++)
		{
			if (i != index && blue_minion[i].direction != MINI_STAY)
			{
				if (GetDistance(a[index].pos, blue_minion[i].pos) <= 2.0f)
				{
					return true;
				}
			}
		}
		return false;
	}

	else
	{
		for (int i = 0; i < red_minion.size(); i++)
		{
			if (i != index && red_minion[i].direction != MINI_STAY)
			{
				if (GetDistance(a[index].pos, red_minion[i].pos) <= 2.0f)
				{
					//a[index].rnd = rand() % 2;
					return true;
				}
			}
		}
		return false;
	}
}

bool cMinion::OtherCollision(vector<tagMinion> & a, int index)
{
	if (a[index].team == TEAM_BLUE)
	{
		for (int i = 0; i < red_minion.size(); i++)
		{
			if (a[index].dis == LONG_DIS)
			{
				if (red_minion[i].direction != MINI_DEATH && GetDistance(a[index].pos, red_minion[i].pos) <= MINI_LONG_DIS)
				{
					return true;
				}
			}

			else
			{
				if (red_minion[i].direction != MINI_DEATH && GetDistance(a[index].pos, red_minion[i].pos) <= MINI_SHORT_DIS)
				{
					return true;
				}
			}
		}
	}


	else
	{
		for (int i = 0; i < blue_minion.size(); i++)
		{
			if (a[index].dis == LONG_DIS)
			{
				if (blue_minion[i].direction != MINI_DEATH && GetDistance(a[index].pos, blue_minion[i].pos) <= MINI_LONG_DIS)
				{
					return true;
				}
			}

			else
			{
				if (blue_minion[i].direction != MINI_DEATH && GetDistance(a[index].pos, blue_minion[i].pos) <= MINI_SHORT_DIS)
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool cMinion::GetAggro(tagMinion & a, D3DXVECTOR3 chPos)
{
	// 적군 캐릭터가 있을 때
	if (GetDistance(chPos, a.pos) < CHAR_MINI_RANGE)
	{
		return true;
	}

	return false;
}


float cMinion::Vector_To_Vector(D3DXVECTOR3 ch, D3DXVECTOR3 min)
{
	//두 벡터를 단위벡터로 만든다.
	D3DXVECTOR3 a(ch.x, 0, ch.z); //높이는 0으로 맞춤
	D3DXVECTOR3 b(min.x, 0, min.z);
	D3DXVec3Normalize(&a, &a);
	D3DXVec3Normalize(&b, &b);

	// 두 벡터를 내적한다.
	return (float)acos(D3DXVec3Dot(&a, &b));
}

void cMinion::BlueMinionCollision()
{
	for (int i = 0; i < blue_minion.size(); i++)
	{
		for (int j = 0; j < blue_minion.size(); j++)
		{
			if (i != j &&
				blue_minion[i].direction != MINI_STAY && blue_minion[j].direction != MINI_STAY &&
				blue_minion[i].direction != MINI_DEATH && blue_minion[j].direction != MINI_DEATH)
			{
				if (GetDistance(blue_minion[i].pos, blue_minion[j].pos) <= MINI_TO_MINI_RANGE)
				{
					blue_minion[i].coll = true;
					blue_minion[j].coll = false;
					break;
				}
			}
		}
	}

	for (int i = 0; i < blue_minion.size(); i++)
	{
		if (blue_minion[i].coll)
		{
			blue_minion[i].pos -= blue_minion[i].dir;
			blue_minion[i].coll_angleY = 0.0f;

			if (blue_minion[i].rnd == RND_LEFT)
			{
				blue_minion[i].coll_angleY -= D3DX_PI / 2;
			}

			else
			{
				blue_minion[i].coll_angleY += D3DX_PI / 2;
			}

			D3DXMATRIXA16 rot;
			/*D3DXMatrixRotationY(&rot, blue_minion[i].angleY);*/
			D3DXMatrixRotationY(&rot, blue_minion[i].coll_angleY);
			blue_minion[i].pos -= blue_minion[i].dir;
			blue_minion[i].dir = D3DXVECTOR3(0.2f, 0, 0);
			D3DXVec3TransformNormal(&blue_minion[i].dir, &blue_minion[i].dir, &rot);
			blue_minion[i].pos += blue_minion[i].dir;

		}
	}
}

void cMinion::BlueMinionUnColl()
{
	for (int i = 0; i < blue_minion.size(); i++)
	{
		for (int j = 0; j < blue_minion.size(); j++)
		{
			if (i != j && GetDistance(blue_minion[i].pos, blue_minion[j].pos) > MINI_TO_MINI_RANGE)
			{
				blue_minion[i].coll = false;
				blue_minion[j].coll = false;
				blue_minion[i].coll_angleY = blue_minion[j].coll_angleY = 0.0f;
			}
		}
	}
}

void cMinion::RedMinionCollision()
{
	for (int i = 0; i < red_minion.size(); i++)
	{
		for (int j = 0; j < red_minion.size(); j++)
		{
			if (i != j &&
				red_minion[i].direction != MINI_STAY && red_minion[j].direction != MINI_STAY &&
				red_minion[i].direction != MINI_DEATH && red_minion[j].direction != MINI_DEATH)
			{
				if (GetDistance(red_minion[i].pos, red_minion[j].pos) <= MINI_TO_MINI_RANGE)
				{
					red_minion[i].coll = true;
					red_minion[j].coll = false;
					break;
				}
			}
		}
	}

	for (int i = 0; i < red_minion.size(); i++)
	{
		if (red_minion[i].coll)
		{
			red_minion[i].pos -= red_minion[i].dir;
			red_minion[i].coll_angleY = 0.0f;

			if (red_minion[i].rnd == RND_LEFT)
			{
				red_minion[i].coll_angleY -= D3DX_PI / 4;
			}
			else
			{
				red_minion[i].coll_angleY -= D3DX_PI / 4;
			}

			D3DXMATRIXA16 rot;
			/*D3DXMatrixRotationY(&rot, red_minion[i].angleY);*/
			D3DXMatrixRotationY(&rot, red_minion[i].coll_angleY);
			red_minion[i].pos -= red_minion[i].dir;
			red_minion[i].dir = D3DXVECTOR3(-0.2f, 0, 0);
			D3DXVec3TransformNormal(&red_minion[i].dir, &red_minion[i].dir, &rot);
			red_minion[i].pos += red_minion[i].dir;
		}
	}
}

void cMinion::RedMinionUnColl()
{
	for (int i = 0; i < red_minion.size(); i++)
	{
		for (int j = 0; j < red_minion.size(); j++)
		{
			if (i != j && GetDistance(red_minion[i].pos, red_minion[j].pos) > MINI_TO_MINI_RANGE)
			{
				red_minion[i].coll = false;
				red_minion[j].coll = false;
				red_minion[i].coll_angleY = red_minion[j].coll_angleY = 0.0f;
			}
		}
	}
}