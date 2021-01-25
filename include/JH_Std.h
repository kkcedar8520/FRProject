#pragma once
#include<Windows.h>
#include<tchar.h>
#include<iostream>
#include<assert.h>
#include<string>
#include<map>
#include<vector>
#include<list>
#include<algorithm>
#ifdef _DEBUG
#pragma comment(lib, "JHCoreLib.Lib")
#else
#endif
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"msimg32.lib")

//#pragma comment(lib, "fmod_vc.lib")
#define TCORE_START int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPTSTR  lpCmdLIne,int  nCmdShow){
#define TCORE_RUN(s) { Sample  gDemo;if (gDemo.CreateWin(L#s)){gDemo.Run();}return 1; }
#define TCORE_END }
#define GAME_RUN(s)  TCORE_START; TCORE_RUN(s); TCORE_END;

#define X_PI (3.141592)
#define RadianToDegree(fRadian) (fRadian* (180.0f/X_PI ))
#define DegreeToRadian(fDegree) (fDegree* (X_PI/ 180.0f))

extern HWND		g_hwnd;
extern HINSTANCE		g_hInstance;
extern HDC		g_hScreenDC;
extern HDC		g_hOffScreenDC;
extern float g_SecondPerFrame;
extern RECT g_rtClient;

struct hPoint
{
	float x;
	float y;
};