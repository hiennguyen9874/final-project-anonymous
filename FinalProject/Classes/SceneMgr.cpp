#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	LoadScene("Scenes");
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::LoadScene(std::string fileName)
{

}

SceneMgr* SceneMgr::m_Instance = nullptr;
SceneMgr* SceneMgr::getInstance()
{
	if (!m_Instance)
		m_Instance = new SceneMgr();
	return m_Instance;
}
