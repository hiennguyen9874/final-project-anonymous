#pragma once
#include <string>
#include <vector>
#include "MapTMX.h"

class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();
	void LoadScene(std::string fileName);
	static SceneMgr* getInstance();
	RefPtr<MapTMX> GetMap() { return this->m_map; }
private:
	static SceneMgr* m_Instance;
	RefPtr<MapTMX> m_map = nullptr;
};

