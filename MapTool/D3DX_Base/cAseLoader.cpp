#include "stdafx.h"
#include "Asciitok.h"
#include "cAseLoader.h"
#include "cAseNode.h"
#include "cMtlTex.h"


cAseLoader::cAseLoader()
{
}


cAseLoader::~cAseLoader()
{
}

cAseNode * cAseLoader::Load(char * szFullPath)
{
	cAseNode* pRoot = NULL;

	fopen_s(&m_fp, szFullPath, "r");

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
		{
			ProcessSCENE();
		}
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cAseNode* pNode = ProcessGEOMOBJECT();
			if (pRoot == NULL)
			{
				pRoot = pNode;
				SetSceneFrame(pRoot);
			}
		}
	}
	fclose(m_fp);

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	pRoot->CalcOriginLocalTM(NULL);

	return pRoot;
}

char * cAseLoader::GetToken()
{
	int nReadCnt = 0;
	bool isQuote = false;

	while (true)
	{
		char c = fgetc(m_fp);

		if (feof(m_fp))
			break;

		if (c == '\"')
		{
			if (isQuote)	break;

			isQuote = true;
			continue;
		}

		if (!isQuote && IsWhite(c))
		{
			if (nReadCnt == 0)
				continue;
			else
				break;
		}

		m_szToken[nReadCnt++] = c;
	}

	if (nReadCnt == 0)
		return NULL;

	m_szToken[nReadCnt] = '\0';

	return m_szToken;
}

int cAseLoader::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoader::GetFloat()
{
	return (float)atof(GetToken());
}

bool cAseLoader::IsWhite(IN char c)
{
	return c < 33;
}

bool cAseLoader::IsEqual(IN char * str1, IN char * str2)
{
	return strcmp(str1, str2) == 0;
}

void cAseLoader::ProcessSCENE()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_FIRSTFRAME))
		{
			m_dwFirstFrame = GetInteger();
		}
		else if (IsEqual(szToken, ID_LASTFRAME))
		{
			m_dwLastFrame = GetInteger();
		}
		else if (IsEqual(szToken, ID_FRAMESPEED))
		{
			m_dwFrameSpeed = GetInteger();
		}
		else if (IsEqual(szToken, ID_TICKSPERFRAME))
		{
			m_dwTicksPerFrame = GetInteger();
		}

	} while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL_LIST()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			for each (auto p in m_vecMtlTex)
			{
				SAFE_RELEASE(p);
			}
			m_vecMtlTex.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MATERIAL))
		{
			int nIndex = GetInteger();
			m_vecMtlTex[nIndex] = new cMtlTex;
			ProcessMATERIAL(m_vecMtlTex[nIndex]);
		}

	} while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL(OUT cMtlTex * pMtlTex)
{
	D3DMATERIAL9	mtl;
	ZeroMemory(&mtl, sizeof(D3DMATERIAL9));

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_AMBIENT))
		{
			mtl.Ambient.r = GetFloat();
			mtl.Ambient.g = GetFloat();
			mtl.Ambient.b = GetFloat();
			mtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			mtl.Diffuse.r = GetFloat();
			mtl.Diffuse.g = GetFloat();
			mtl.Diffuse.b = GetFloat();
			mtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			mtl.Specular.r = GetFloat();
			mtl.Specular.g = GetFloat();
			mtl.Specular.b = GetFloat();
			mtl.Specular.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtlTex);
		}

	} while (nLevel > 0);

	pMtlTex->SetMaterial(mtl);
}

void cAseLoader::ProcessMAP_DIFFUSE(OUT cMtlTex * pMtlTex)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_BITMAP))
		{
			szToken = GetToken();
			pMtlTex->SetTexture( g_pTextureManager->GetTexture(szToken));
		}
	} while (nLevel > 0);
}

cAseNode* cAseLoader::ProcessGEOMOBJECT()
{
	cAseNode* pNode = new cAseNode;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_NODE_NAME))
		{
			m_mapNode[GetToken()] = pNode;
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			m_mapNode[GetToken()]->AddChild(pNode);
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pNode);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pNode);
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			int nIndex = GetInteger();
			pNode->SetMtlTex(m_vecMtlTex[nIndex]);
		}
		else if (IsEqual(szToken, ID_TM_ANIMATION))
		{
			ProcessTM_ANIMATION(pNode);
		}
	} while (nLevel > 0);

	return pNode;
}

void cAseLoader::ProcessMESH(OUT cAseNode * pNode)
{
	std::vector<ST_PNT_VERTEXT>	vecVertex;
	std::vector<D3DXVECTOR3>	vecV;
	std::vector<D3DXVECTOR2>	vecVT;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if (IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecVertex, vecV);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecVertex, vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NORMALS(vecVertex);
		}
	} while (nLevel > 0);

	D3DXMATRIXA16	matInv;
	D3DXMatrixInverse(&matInv, 0, &pNode->GetWorldTM());
	for (size_t i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInv);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInv);
	}
	
	pNode->BuildVB(vecVertex);
	//pNode->SetVertex(vecVertex);
}

void cAseLoader::ProcessMESH_VERTEX_LIST(OUT std::vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_FACE_LIST(OUT std::vector<ST_PNT_VERTEXT>& vecVertex, IN std::vector<D3DXVECTOR3> vecV)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_FACE))
		{
			int nIndex = GetInteger();
			GetToken();
			vecVertex[nIndex * 3].p = vecV[GetInteger()];
			GetToken();
			vecVertex[nIndex * 3 + 2].p = vecV[GetInteger()];
			GetToken();
			vecVertex[nIndex * 3 + 1].p = vecV[GetInteger()];
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_NORMALS(OUT std::vector<ST_PNT_VERTEXT>& vecVertex)
{
	int nIndex = 0;
	int nLevel = 0;
	int arrModIndex[3] = { 0, 2, 1 };
	int nModCnt = 0;

	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nIndex = GetInteger();
			nModCnt = 0;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			D3DXVECTOR3 n;
			n.x = GetFloat();
			n.z = GetFloat();
			n.y = GetFloat();
			vecVertex[nIndex * 3 + arrModIndex[nModCnt++]].n = n;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_TVERTLIST(OUT std::vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;

	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_TVERT))
		{
			int nIndex = GetInteger();
			vecVT[nIndex].x = GetFloat();
			vecVT[nIndex].y = 1.0f - GetFloat();
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_TFACELIST(OUT std::vector<ST_PNT_VERTEXT>& vecVertex, IN std::vector<D3DXVECTOR2> vecVT)
{
	int nLevel = 0;

	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_MESH_TFACE))
		{
			int nIndex = GetInteger();
			vecVertex[nIndex * 3].t = vecVT[GetInteger()];
			vecVertex[nIndex * 3 + 2].t = vecVT[GetInteger()];
			vecVertex[nIndex * 3 + 1].t = vecVT[GetInteger()];
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessNODE_TM(OUT cAseNode * pNode)
{
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity(&matWorld);

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
			matWorld._14 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
			matWorld._34 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
			matWorld._24 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
			matWorld._44 = 1.0f;
		}
	} while (nLevel > 0);

	pNode->SetWorldTM(matWorld);
}

void cAseLoader::ProcessTM_ANIMATION(OUT cAseNode * pNode)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_POS_TRACK))
		{
			ProcessCONTROL_POS_TRACK(pNode);
		}
		else if (IsEqual(szToken, ID_ROT_TRACK))
		{
			ProcessCONTROL_ROT_TRACK(pNode);
		}
	} while (nLevel > 0);

}

void cAseLoader::ProcessCONTROL_ROT_TRACK(OUT cAseNode * pNode)
{
	std::vector<ST_ROT_SAMPLE>	vecRotTrack;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_ROT_SAMPLE))
		{
			ST_ROT_SAMPLE s;
			s.nFrame = GetInteger();
			s.q.x = GetFloat();
			s.q.z = GetFloat();
			s.q.y = GetFloat();
			s.q.w = GetFloat();

			//s.q.x *= sinf(s.q.w / 2.0f);
			//s.q.z *= sinf(s.q.w / 2.0f);
			//s.q.y *= sinf(s.q.w / 2.0f);
			//s.q.w = cosf(s.q.w / 2.0f);

			D3DXQuaternionRotationAxis(&s.q, 
				&D3DXVECTOR3(s.q.x, s.q.y, s.q.z),
				s.q.w);

			if (!vecRotTrack.empty())
			{
				s.q = vecRotTrack.back().q * s.q;
			}

			vecRotTrack.push_back(s);
		}
	} while (nLevel > 0);

	pNode->SetRotTrack(vecRotTrack);
}

void cAseLoader::ProcessCONTROL_POS_TRACK(OUT cAseNode * pNode)
{
	std::vector<ST_POS_SAMPLE>	vecPosTrack;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			nLevel++;
		}
		else if (IsEqual(szToken, "}"))
		{
			nLevel--;
		}
		else if (IsEqual(szToken, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE s;
			s.nFrame = GetInteger();
			s.v.x = GetFloat();
			s.v.z = GetFloat();
			s.v.y = GetFloat();
			vecPosTrack.push_back(s);
		}
	} while (nLevel > 0);

	pNode->SetPosTrack(vecPosTrack);
}

void cAseLoader::SetSceneFrame(OUT cAseNode * pRoot)
{
	pRoot->m_dwFirstFrame = m_dwFirstFrame;
	pRoot->m_dwLastFrame = m_dwLastFrame;
	pRoot->m_dwFrameSpeed= m_dwFrameSpeed;
	pRoot->m_dwTicksPerFrame= m_dwTicksPerFrame;
}
