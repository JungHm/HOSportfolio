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
				pRoot->m_dwFirstFrame = m_dwFirstFrame;
				pRoot->m_dwLastFrame = m_dwLastFrame;
				pRoot->m_dwTicksPerFrame = m_dwTicksPerFrame;
				pRoot->m_dwFrameSpeed = m_dwFrameSpeed;
			}
		}
	}
	fclose(m_fp);

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

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
			pMtlTex->SetTexture(g_pTextureManager->GetTexture(szToken));
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
			char* pName = GetToken();
			m_mapNode[pName]->AddChild(pNode);
			pNode->GetparentNode() = m_mapNode[pName];
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
	D3DXMATRIXA16 matInverse; D3DXMatrixIdentity(&matInverse);
	D3DXMatrixInverse(&matInverse, 0, &pNode->GetWorldTM());
	for (int i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInverse);
	}
	pNode->SetVertex(vecVertex);

	if (pNode->GetparentNode() != NULL)
	{
		/*D3DXMATRIXA16 matLocal;
		D3DXMatrixInverse(&matInverse, NULL, &pNode->GetparentNode()->GetWorldTM());
		matLocal = pNode->GetWorldTM()*matInverse;
		pNode->SetLocalTM(matLocal);*/
		pNode->CalcOriginLocalTM(&pNode->GetparentNode()->GetWorldTM());
	}
	else
	{
		pNode->SetLocalTM(pNode->GetWorldTM());
	}
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
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
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
			mat._11 = GetFloat();
			mat._13 = GetFloat();
			mat._12 = GetFloat();
			mat._14 = 0;
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			mat._31 = GetFloat();
			mat._33 = GetFloat();
			mat._32 = GetFloat();
			mat._34 = 0;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			mat._21 = GetFloat();
			mat._23 = GetFloat();
			mat._22 = GetFloat();
			mat._24 = 0;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			mat._41 = GetFloat();
			mat._43 = GetFloat();
			mat._42 = GetFloat();
			mat._44 = 1;
		}
	} while (nLevel > 0);
	pNode->SetWorldTM(mat);
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
	int nLevel = 0;
	std::vector<CTRL_ROT> tRot;
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
			float x, y, z, w;
			CTRL_ROT temp;
			temp.frame = GetInteger();
			x = GetFloat();
			z = GetFloat();
			y = GetFloat();
			w = GetFloat();
			temp.rot = D3DXQUATERNION((float)sinf(w / 2.f)*x,
				(float)sinf(w / 2.f)*y, 
				(float)sinf(w / 2.f)*z, 
				(float)cosf(w / 2.f));
			//D3DXQuaternionRotationAxis(&temp.rot, &D3DXVECTOR3(x, y, z), w);
			tRot.push_back(temp);
		}

	} while (nLevel > 0);
	for (int i = 1; i < tRot.size(); i++)
	{
		//D3DXQuaternionMultiply(&tRot[i].rot, &tRot[i - 1].rot, &tRot[i].rot);
		tRot[i].rot = tRot[i - 1].rot*tRot[i].rot;
	}
	pNode->SetRotTrack(tRot);
}

void cAseLoader::ProcessCONTROL_POS_TRACK(OUT cAseNode * pNode)
{
	int nLevel = 0;
	std::vector<CTRL_POS> pos;
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
			CTRL_POS tPos;
			tPos.frame = GetInteger();
			tPos.pos.x = GetFloat();
			tPos.pos.z = GetFloat();
			tPos.pos.y = GetFloat();
			pos.push_back(tPos);
		}

	} while (nLevel > 0);
	pNode->SetPosTrack(pos);
}
