#pragma once
class iScene;

#define g_Scene cSceneManager::GetInstance()
class cSceneManager
{
	SINGLETONE(cSceneManager);
private:
	std::map<char*, iScene*> m_pScene;
	char* m_SceneName;
public:

	void SetUp();
	void Destroy();
	void Update();
	void Render();


	void AddScene(char* SceneName, iScene* pScene);
	void ChangeScene(char* SceneName);
};

