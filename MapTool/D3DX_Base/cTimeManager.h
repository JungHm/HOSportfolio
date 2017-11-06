#pragma once
#define g_pTimeManager	cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);

	DWORD m_dwLastUpdateTime; // ������ �ð�
	float m_fEllapsedTime;    // �������Ӵ� �����
	float m_fWorldTime;		  // ��ü �ð� �����

public:
	void Update();
	float GetLastUpdateTime();
	float GetEllapsedTime();
	float GetWorldTime();
};

