#pragma once
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <sstream>
#include<assert.h>
#pragma comment(lib,"ws2_32.lib")

template<class T> class Singleton
{
public:
	static T& GetInstance()
	{
		static T Instance;
		return Instance;
	}
};