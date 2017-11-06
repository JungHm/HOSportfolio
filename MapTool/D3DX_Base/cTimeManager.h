#pragma once
#define g_pTimeManager	cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);

	DWORD m_dwLastUpdateTime; // 마지막 시간
	float m_fEllapsedTime;    // 한프레임당 경과량
	float m_fWorldTime;		  // 전체 시간 경과량

public:
	void Update();
	float GetLastUpdateTime();
	float GetEllapsedTime();
	float GetWorldTime();
};

