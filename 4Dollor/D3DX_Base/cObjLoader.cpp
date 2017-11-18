#include "stdafx.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cMtlTex.h"


cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}

void cObjLoader::Load(OUT std::vector<cGroup*>& vecGroup, IN char * szFolder, IN char * szFile)
{
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;
	std::vector<ST_PNT_VERTEXT> vecVertex;

	std::string sMtlName;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	while (true)
	{
		if (feof(fp))
		{
			if (!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}
			break;
		}

		char szBuf[1024];
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szBuf, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szBuf[0] == 'g' || szBuf[0] == 'o')
		{
			if (!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szBuf[1] == 't')
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));

			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szBuf[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEXT v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
		}
	}

	fclose(fp);


	for each (auto p in m_mapMtlTex)
	{
		SAFE_RELEASE(p.second);
	}
	m_mapMtlTex.clear();
}

void cObjLoader::LoadMtlLib(char * szFolder, char * szMtlFile)
{
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szMtlFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;
	int nAttrID = 0;

	while (true)
	{
		if (feof(fp))
			break;

		char szBuf[1024];
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);

			if (m_mapMtlTex.find(sMtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[sMtlName] = new cMtlTex;
				m_mapMtlTex[sMtlName]->SetAttrID(nAttrID);
				nAttrID++;
			}
		}
		else if (szBuf[0] == 'K')
		{
			if (szBuf[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.r = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.g = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.b = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.a = 1.0f;
			}
			if (szBuf[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.r = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.g = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.b = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.a = 1.0f;
			}
			if (szBuf[1] == 's')
			{
				float r, g, b;
				sscanf_s(szBuf, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.r = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.g = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.b = 1;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		else if (szBuf[0] == 'm')
		{
			char szTextFile[1024];
			sscanf_s(szBuf, "%*s %s", szTextFile, 1024);
			sFullPath = string(szFolder);
			sFullPath += string("/") + string(szTextFile);

			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(pTexture);
		}
	}

	fclose(fp);
}

void cObjLoader::LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface,
	IN char * szFolder,
	IN char * szFile,
	IN D3DXMATRIXA16 * pMat)
{
	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;
	std::vector<D3DXVECTOR3> vecV;

	while (true)
	{
		if (feof(fp))
			break;

		char szBuf[1024];
		fgets(szBuf, 1024, fp);
		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]);

			for (int i = 0; i < 3; i++)
			{
				vecSurface.push_back(vecV[nIndex[i] - 1]);
			}
		}
	}

	fclose(fp);

	if (pMat)
	{
		for (int i = 0; i < vecSurface.size(); i++)
		{
			D3DXVec3TransformCoord(
				&vecSurface[i],
				&vecSurface[i],
				pMat);
		}
	}
}

LPD3DXMESH cObjLoader::LoadMesh(OUT vector<cMtlTex*>& vecMtlTex, IN char * szFolder, IN string szFile)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;
	vector<ST_PNT_VERTEXT> vecVertex;
	vector<DWORD>		   vecAttrBuf;

	string sMtlName;
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	while (true)
	{
		char szBuf[1024];
		fgets(szBuf, 1024, fp);

		if (feof(fp)) break;

		if (szBuf[0] == '#') continue;

		else if (szBuf[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szBuf, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szBuf[0] == 'v')
		{
			if (szBuf[1] == ' ')	  // 정점 버텍스
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szBuf[1] == 't') // 텍스쳐 버텍스
			{
				float u, v;
				sscanf_s(szBuf, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, 1.0f - v));
			}
			else if (szBuf[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szBuf[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szBuf, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
		}
		else if (szBuf[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szBuf, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEXT v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}

			vecAttrBuf.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);

	vecMtlTex.resize(m_mapMtlTex.size());
	for each (auto it in m_mapMtlTex)
	{
		vecMtlTex[it.second->GetAttrID()] = it.second;
	}

	// 빈 매쉬 생성
	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecAttrBuf.size(), vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEXT::FVF, g_pD3DDevice, &pMesh);

	// 버텍스 버퍼
	ST_PNT_VERTEXT* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEXT));
	pMesh->UnlockVertexBuffer();

	// 인덱스 버퍼
	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (int i = 0; i < vecVertex.size(); i++)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	// 어트리뷰트 버퍼
	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	// 최적화
	vector<DWORD> vecAdj(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}
