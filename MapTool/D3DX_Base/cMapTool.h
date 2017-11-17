#pragma once

class cGrid;
class cInfomation;
class cSaveLoad;
class cHeightMap;

class cMapTool
{
private:
	cGrid*			m_pGrid;			// �׸��� Ŭ����
	cInfomation*	m_pInfo;			// ���� ����	Ŭ����
	cSaveLoad*		m_pSaveLoad;		// ���̺� �ε� Ŭ����
	OBJECT			m_sObj;				// ���� ���콺�� �����̴� ������Ʈ ����
	cHeightMap*		m_pHeightMap;		// ���̸� Ŭ����
	SYNTHESIZE(int, m_nIndex, Index);	// �������� ������Ʈ�� �ε���
	bool			m_isPicking;		// ��ŷ ���� ����
	bool			m_isAllocate;		// ��ġ �غ� ����

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
	// ������Ʈ ��ġ, ����, ���̺�, �ε�
	void ObjAllocate();
};

