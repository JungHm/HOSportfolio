#pragma once

class cGrid;
class cInfomation;
class cSaveLoad;

class cMapTool
{
private:
	cGrid*			m_pGrid;			// �׸��� Ŭ����
	cInfomation*	m_pInfo;			// ���� ����	Ŭ����
	cSaveLoad*		m_pSaveLoad;		// ���̺� �ε� Ŭ����
	OBJECT			m_sObj;				// ���� ���콺�� �����̴� ������Ʈ ����
	int				m_nIndex;			// �������� ������Ʈ�� �ε���
	bool			m_isPicking;		// ��ŷ ���� ����
	bool			m_isAllocate;		// ��ġ ����

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

