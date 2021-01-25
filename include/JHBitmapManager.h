#pragma once
#include"JHBitMap.h"
#include<map>
#include<string>

using namespace std;
class JHBitmapManager
{
public:
	std::wstring m_szPath;

	int m_ilndex;
	std::map<std::wstring, JHBitMap*> m_List;
public:
	bool Release();
	JHBitMap* Load(const TCHAR* filename);
	static JHBitmapManager&Get()
	{
		static JHBitmapManager mgr;
		return mgr;
	}

public:
	JHBitmapManager();
	virtual ~JHBitmapManager();
};

#define BM_MGR JHBitmapManager::Get()