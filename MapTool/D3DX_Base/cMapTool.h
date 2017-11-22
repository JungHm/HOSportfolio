#pragma once

class cGrid;
class cInfomation;
class cSaveLoad;
class cHeightMap;

// ���� �������� ��ġ���� ���� �������� �˷��ִ� ����
enum ALLOCATE_STATE
{
	ALLOCATE_NONE,					// �ƹ����� ���� �ʴ� ����
	ALLOCATE_OBJECT,				// ������Ʈ ��ġ ����
	ALLOCATE_COLLISION_BOX,			// �浹 �ڽ� ��ġ ����
	ALLOCATE_DIJKSTRA_NODE_SPHERE,	// ���ͽ�Ʈ�� ��� ����� ��ġ ����
	ALLOCATE_NODE_LINE				// ��� ���� ���� ��ġ ����
};

class cMapTool
{
private:
	cGrid*			m_pGrid;			// �׸��� Ŭ����
	cSaveLoad*		m_pSaveLoad;		// ���̺� �ε� Ŭ����
	cHeightMap*		m_pHeightMap;		// ���̸� Ŭ����
	cInfomation*	m_pInfo;			// ���� ����	Ŭ����
	OBJECT			m_sObj;				// ���� ���콺�� �����̴� ������Ʈ ����
	ST_BOX			m_sCollisionBox;;	// �浹�� �ڽ�
	ST_SPHERE_NODE	m_sNodeSphere;		// ���ͽ�Ʈ�� �˰����� ��� ������ �����
	bool			m_isPicking;		// ��ŷ ���� ����
	SYNTHESIZE(int, m_nIndex, Index);	// �������� ������Ʈ�� �ε���
	SYNTHESIZE(int, m_eAllocateState, AllocateState);	// ���� ��ġ����
	int				m_nCount;			// ��� ���� ī��Ʈ
	float			m_fStartX, m_fStartZ;
	float			m_fEndX, m_fEndZ;
	int				m_nFirstIndex;

public:
	cMapTool();
	~cMapTool();

	void Setup();
	void Update();
	void Render();
	
	// ��ŷ ������ ������Ʈ �ʱ�ȭ
	void SetUpPickingObj();
	// ������Ʈ ��ŷ, ��ġ�� S * R * T ���� �Լ�
	void ObjPicking(IN UINT message, IN WPARAM wParam, IN LPARAM lParam);
	// ������Ʈ ���̺�
	void ObjSave();
	// ������Ʈ �ε�
	void ObjLoad();
	// ������Ʈ �����
	void ObjRemove();
};

