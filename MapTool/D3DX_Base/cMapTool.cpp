#include "stdafx.h"
#include "cMapTool.h"
#include "cGrid.h"
#include "cInfomation.h"
#include "cPicking.h"
#include "cSaveLoad.h"
#include "cHeightMap.h"

cMapTool::cMapTool()
	: m_pGrid(NULL)
	, m_pInfo(NULL)
	, m_pHeightMap(NULL)
	, m_isPicking(false)
	, m_nCount(0)
	, m_fStartX(0.0f)
	, m_fStartZ(0.0f)
	, m_fEndX(0.0f)
	, m_fEndZ(0.0f)
	, m_nFirstIndex(0)
{
	m_eAllocateState = ALLOCATE_NONE;
}

cMapTool::~cMapTool()
{	
	SAFE_RELEASE(m_sObj.pMesh);
	SAFE_RELEASE(m_sCollisionBox.pMesh);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pInfo);
	SAFE_DELETE(m_pHeightMap);
	SAFE_DELETE(m_pSaveLoad);
}

void cMapTool::SetUpPickingObj()
{
	// 오브젝트 구조체 초기화
	ZeroMemory(&m_sObj, sizeof(OBJECT));
	D3DXMatrixIdentity(&m_sObj.matWorld);
	D3DXMatrixIdentity(&m_sObj.matScal);
	D3DXMatrixIdentity(&m_sObj.matRotY);
	D3DXMatrixIdentity(&m_sObj.matTrans);
	m_sObj.vScaling = D3DXVECTOR3(0.03f, 0.03f, 0.03f);

	// 충돌용 박스 구조체 초기화
	ZeroMemory(&m_sCollisionBox, sizeof(ST_BOX));
	D3DXMatrixIdentity(&m_sCollisionBox.matWorld);
	D3DXMatrixIdentity(&m_sCollisionBox.matScal);
	D3DXMatrixIdentity(&m_sCollisionBox.matRotY);
	D3DXMatrixIdentity(&m_sCollisionBox.matTrans);
	m_sCollisionBox.vScaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXCreateBox(g_pD3DDevice, 30.0f, 20.0f, 13.0f, &m_sCollisionBox.pMesh, NULL);

	// 노드용 스페어 구조체 초기화
	ZeroMemory(&m_sNodeSphere, sizeof(ST_SPHERE));
	D3DXMatrixIdentity(&m_sNodeSphere.matWrold);
	m_sNodeSphere.isSelected = false;
	D3DXCreateSphere(g_pD3DDevice, 2.5f, 15, 15, &m_sNodeSphere.pMesh, NULL);
}

void cMapTool::Setup()
{
	SetUpPickingObj();

	m_pHeightMap = new cHeightMap;
	m_pHeightMap->Setup("HeightMap/", "backGround.raw", "HeightMap.jpg");

	m_pSaveLoad = new cSaveLoad;

	m_pInfo = new cInfomation;
	m_pInfo->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup("Grid", "field2.png", 65, 115, 5.0f);

	m_sObj.pMesh = m_pSaveLoad->GetObjMesh(m_nIndex);
	m_sObj.nKind = m_nIndex;

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void cMapTool::Update()
{
	// ui로 바꿔준다
	if (KEY->isOnceKeyDown(VK_F3))
	{
		m_eAllocateState++;
	}

	if (KEY->isOnceKeyDown(VK_F4))
	{
		m_eAllocateState--;
	}

	if (KEY->isOnceKeyDown(VK_F5))
	{
		m_pSaveLoad->RemoveNode();
	}

	if (KEY->isOnceKeyDown(VK_LBUTTON))
	{
		switch (m_eAllocateState)
		{
		case ALLOCATE_OBJECT:
			m_pSaveLoad->CreateObj(
				m_nIndex,
				m_sObj.pMesh,
				m_pSaveLoad->GetMapObjMtltex(m_nIndex),
				m_pSaveLoad->GetFileName(m_nIndex),
				m_sObj.vScaling, m_sObj.vPosition,
				m_sObj.fAngleY);
			break;

		case ALLOCATE_COLLISION_BOX:
			m_pSaveLoad->CreateBox(
				m_sCollisionBox.pMesh,
				m_sCollisionBox.vScaling,
				m_sCollisionBox.vPosition,
				m_sCollisionBox.fAngleY);
			break;

		case ALLOCATE_DIJKSTRA_NODE_SPHERE:
			vector<NODE> vecNode;
			vecNode.resize(0);

			m_pSaveLoad->CreateNodeSphere(
				m_sNodeSphere.pMesh,
				m_sNodeSphere.vCenter,
				vecNode
			);
			break;
		}
	}

	m_pInfo->SetScale(m_sObj.vScaling.x);
	m_pInfo->SetRotation(m_sObj.fAngleY);
	m_pInfo->SetPosition(m_sObj.vPosition);
	m_pInfo->SetObjKind(m_sObj.nKind);
	m_pInfo->SetObjNum(m_pSaveLoad->GetFieldObjNum());
}

void cMapTool::Render()
{
	if (m_pInfo) m_pInfo->Render();
	if (m_pGrid) m_pGrid->Render();
	if (m_pHeightMap) m_pHeightMap->Render();

	switch (m_eAllocateState)
	{
	case ALLOCATE_OBJECT:
		D3DXMatrixScaling(&m_sObj.matScal, m_sObj.vScaling.x, m_sObj.vScaling.y, m_sObj.vScaling.z);
		D3DXMatrixRotationY(&m_sObj.matRotY, m_sObj.fAngleY);
		D3DXMatrixTranslation(&m_sObj.matTrans, m_sObj.vPosition.x, m_sObj.vPosition.y, m_sObj.vPosition.z);

		m_sObj.matWorld = m_sObj.matScal * m_sObj.matRotY * m_sObj.matTrans;

		g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(130, 255, 255, 255));
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_sObj.matWorld);

		for (size_t i = 0; i < m_pSaveLoad->GetMapObjMtltex(m_nIndex).size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_pSaveLoad->GetMapObjMtltex(m_nIndex)[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_pSaveLoad->GetMapObjMtltex(m_nIndex)[i]->GetTexture());
			m_sObj.pMesh->DrawSubset(i);
		}
		break;

	case ALLOCATE_COLLISION_BOX:
		D3DXMatrixScaling(&m_sCollisionBox.matScal, m_sCollisionBox.vScaling.x, m_sCollisionBox.vScaling.y, m_sCollisionBox.vScaling.z);
		D3DXMatrixRotationY(&m_sCollisionBox.matRotY, m_sCollisionBox.fAngleY);
		D3DXMatrixTranslation(&m_sCollisionBox.matTrans, m_sCollisionBox.vPosition.x, m_sCollisionBox.vPosition.y, m_sCollisionBox.vPosition.z);
		
		m_sCollisionBox.matWorld = m_sCollisionBox.matScal * m_sCollisionBox.matRotY * m_sCollisionBox.matTrans;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_sCollisionBox.matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetTexture(0, NULL);

		m_sCollisionBox.pMesh->DrawSubset(0);
		break;

	case ALLOCATE_DIJKSTRA_NODE_SPHERE:
		D3DXMatrixTranslation(&m_sNodeSphere.matTrans, m_sNodeSphere.vCenter.x, m_sNodeSphere.vCenter.y, m_sNodeSphere.vCenter.z);

		m_sNodeSphere.matWrold = m_sNodeSphere.matTrans;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_sNodeSphere.matWrold);
		g_pD3DDevice->SetRenderState(D3DRS_TEXTUREFACTOR, D3DCOLOR_ARGB(255, 255, 255, 255));
		g_pD3DDevice->SetTexture(0, NULL);

		m_sNodeSphere.pMesh->DrawSubset(0);
		break;
	}

	if (m_pSaveLoad) m_pSaveLoad->CreateObjRender();
}

void cMapTool::ObjPicking(IN UINT message, IN WPARAM wParam, IN LPARAM lParam)
{		
	if (m_eAllocateState == ALLOCATE_NONE) return;

	cPicking cRay = cPicking::CalcWorldSpace(LOWORD(lParam), HIWORD(lParam));
	D3DXVECTOR3 vOutPos;

	if (m_eAllocateState == ALLOCATE_NODE_LINE && KEY->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < m_pSaveLoad->GetFieldNodeSphere().size(); i++)
		{
			m_pSaveLoad->GetFieldNodeSphere()[i].isSelected = cRay.IntersectSphere(&m_pSaveLoad->GetFieldNodeSphere()[i]);

			if (m_pSaveLoad->GetFieldNodeSphere()[i].isSelected)
			{
				// 노드 연결 카운트 증가
				m_nCount++;

				// 선택한 노드들의 라인을 그려줄 벡터에 담기
				ST_PC_VERTEXT v;
				v.p = m_pSaveLoad->GetFieldNodeSphere()[i].vCenter;
				v.c = D3DCOLOR_XRGB(255, 255, 255);
				m_pSaveLoad->GetNodeLinde().push_back(v);

				if (m_nCount == 1)
				{
					m_nFirstIndex = i;
					m_fStartX = m_pSaveLoad->GetFieldNodeSphere()[i].vCenter.x;
					m_fStartZ = m_pSaveLoad->GetFieldNodeSphere()[i].vCenter.z;
				}

				if (m_nCount == 2)
				{
					m_fEndX = m_pSaveLoad->GetFieldNodeSphere()[i].vCenter.x;
					m_fEndZ = m_pSaveLoad->GetFieldNodeSphere()[i].vCenter.z;

					// 비용 계산
					float fCost = getDistance(m_fStartX, m_fStartZ, m_fEndX, m_fEndZ);

					NODE node;

					node.fCost = fCost;
					node.nIndex = i;

					m_pSaveLoad->GetFieldNodeSphere()[m_nFirstIndex].vecLink.push_back(node);

					node.nIndex = m_nFirstIndex;

					m_pSaveLoad->GetFieldNodeSphere()[i].vecLink.push_back(node);

					// 이미 연결 되있는 노드라면 다시 삭제
					for (int j = 0; j < m_pSaveLoad->GetFieldNodeSphere()[m_nFirstIndex].vecLink.size() - 1; j++)
					{
						if (m_pSaveLoad->GetFieldNodeSphere()[m_nFirstIndex].vecLink[j].fCost == node.fCost)
						{
							m_pSaveLoad->GetFieldNodeSphere()[m_nFirstIndex].vecLink.pop_back();
							m_pSaveLoad->GetFieldNodeSphere()[i].vecLink.pop_back();
							m_pSaveLoad->GetNodeLinde().pop_back();
							m_pSaveLoad->GetNodeLinde().pop_back();
							break;
						}
					}

					m_pSaveLoad->GetFieldNodeSphere()[m_nFirstIndex].isSelected = false;
					m_pSaveLoad->GetFieldNodeSphere()[i].isSelected = false;
					// 카운트 다시 초기화
					m_nCount = 0;	
				}

				break;
			}
		}
	}

	switch (message)
	{
	case WM_MOUSEMOVE:
		for (int i = 0; i < m_pGrid->GetPicVertex().size(); i += 3)
		{
			m_isPicking = cRay.IntersectTri(
				m_pGrid->GetPicVertex()[i].p,
				m_pGrid->GetPicVertex()[i + 1].p,
				m_pGrid->GetPicVertex()[i + 2].p,
				vOutPos);

			if (m_isPicking)
			{
				m_sObj.vPosition = vOutPos;
				m_sCollisionBox.vPosition.x = vOutPos.x;
				m_sCollisionBox.vPosition.y = vOutPos.y + 10;
				m_sCollisionBox.vPosition.z = vOutPos.z;
				m_sNodeSphere.vCenter = vOutPos;
				break;
			}
		}
		break;

	case WM_MOUSEWHEEL:
		if (KEY->isStayKeyDown('R'))
		{
			switch (m_eAllocateState)
			{
			case ALLOCATE_OBJECT:
				m_sObj.vScaling.x += (GET_WHEEL_DELTA_WPARAM(wParam) / 30000.f);
				m_sObj.vScaling.y += (GET_WHEEL_DELTA_WPARAM(wParam) / 30000.f);
				m_sObj.vScaling.z += (GET_WHEEL_DELTA_WPARAM(wParam) / 30000.f);
				break;

			case ALLOCATE_COLLISION_BOX:
				m_sCollisionBox.vScaling.x += (GET_WHEEL_DELTA_WPARAM(wParam) / 3000.f);
				break;
			}
		}
		break;
	}

	if (KEY->isOnceKeyDown('Q'))
	{
		switch (m_eAllocateState)
		{
		case ALLOCATE_OBJECT:
			m_sObj.fAngleY -= D3DX_PI / 18;
			break;

		case ALLOCATE_COLLISION_BOX:
			m_sCollisionBox.fAngleY -= D3DX_PI / 18;
			break;
		}
	}

	if (KEY->isOnceKeyDown('E'))
	{
		switch (m_eAllocateState)
		{
		case ALLOCATE_OBJECT:
			m_sObj.fAngleY += D3DX_PI / 18;
			break;

		case ALLOCATE_COLLISION_BOX:
			m_sCollisionBox.fAngleY += D3DX_PI / 18;
			break;
		}
	}

	m_sObj.pMesh = m_pSaveLoad->GetObjMesh(m_nIndex);
	m_sObj.nKind = m_nIndex;
}

void cMapTool::ObjSave()
{
	m_pSaveLoad->SaveFieldObj();
}

void cMapTool::ObjLoad()
{
	m_pSaveLoad->LoadFieldObj();
}

void cMapTool::ObjRemove()
{
	m_pSaveLoad->RemoveObj();
}
