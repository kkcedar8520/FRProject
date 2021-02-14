#pragma once
#ifndef JH_DXSTD_H

#define JH_DXSTD_H

#include<Windows.h>
#include<tchar.h>
#include<iostream>
#include<assert.h>
#include<string>
#include<map>
#include<unordered_map>
#include<vector>
#include<list>
#include<queue>
#include<algorithm>
#include"JH_DXHelperEX.h"


//Memory leack detector
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include<crtdbg.h>


#pragma warning(disable:4005)
#ifdef _DEBUG
#pragma comment(lib, "JHDXCore_d")
#pragma comment(lib,"assimp")//Modle Importer library
//#ifndef DBG_NEW
//	#define DBG_NEW new ( _NORMAL_BLOCK, __FILE__, __LINE__)
//	#define new DBG_NEW
//#endif 

#else
#pragma comment(lib,"JHDXCore_R")
#endif
using namespace Microsoft::WRL;



#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "fmod_vc.lib")
#define TCORE_START int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPTSTR  lpCmdLIne,int  nCmdShow){
#define TCORE_RUN(s,d) { Sample  gDemo;if (gDemo.InitWindow(L#s,d)){gDemo.Run();}return 1; }
#define TCORE_END }
#define GAME_RUN(s,d)  TCORE_START; TCORE_RUN(s,d); TCORE_END;

#define X_PI (3.141592)
#define RadianToDegree(fRadian) (fRadian* (180.0f/X_PI ))
#define DegreeToRadian(fDegree) (fDegree* (X_PI/ 180.0f))
#define DXFLAG(s) if(FAILED())




extern HWND		g_hwnd;
extern HINSTANCE		g_hInstance;
extern HDC		g_hScreenDC;
extern HDC		g_hOffScreenDC;
extern float g_SecondPerFrame;
extern RECT g_rtClient;
extern float g_fProgramTime;


typedef basic_string<TCHAR> T_STR;
typedef basic_string<wchar_t> W_STG;
typedef basic_string<char>  C_STR;
typedef vector<T_STR>		T_STR_VECTOR;
typedef basic_string<TCHAR>::iterator	T_ITOR;
typedef basic_string<wchar_t>::iterator	W_ITOR;
typedef basic_string<char>::iterator	C_ITOR;
typedef vector<T_STR>		T_ARRAY_ITOR;
typedef vector<DWORD>				DWORD_VECTOR;
typedef	vector< DWORD >::iterator	DWORD_VECTOR_ITOR;
typedef list<DWORD>					DWORD_LIST;
typedef list<DWORD>::iterator		DWORD_LIST_ITOR;
typedef list< HANDLE >				HANDLE_LIST;
typedef	list< HANDLE >::iterator	HANDLE_LIST_ITOR;





template<class T> class Singleton
{
public:
	static T& GetInstance()
	{
		static T Instance;
		return Instance;
	}
};
#endif

enum F_POSITION
{
	FRONT = 0,
	SPANNING,
	BACK,
};
struct BOUNDINGBOX
{
	D3DXVECTOR3 vCenter;
	//aabb
	D3DXVECTOR3 vMin;
	D3DXVECTOR3 vMax;
	//obb
	D3DXVECTOR3 vAxis[3];//축벡터
	float		fExtent[3];// 축의 길이
};
struct SPHERE
{
	D3DXVECTOR3 vCenter;
	float	Radius;

};

struct FT_PLANE
{
	float fA, fB, fC, fD;
	void CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
	{

		D3DXVECTOR3 dir1 = v1 - v0;
		D3DXVECTOR3 dir2 = v2 - v0;

		D3DXVECTOR3 vNormal;
		D3DXVec3Cross(&vNormal, &dir1, &dir2);

		D3DXVec3Normalize(&vNormal, &vNormal);

		fA = vNormal.x;
		fB = vNormal.y;
		fC = vNormal.z;

		fD = -((fA*v0.x) + (fB * v0.y) + (fC*v0.z));

	}
	void CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 vDir)
	{
		D3DXVec3Normalize(&vDir, &vDir);
		fA = vDir.x;
		fB = vDir.y;
		fC = vDir.z;

		fD = -(fA*v0.x + fB * v0.y + fC * v0.z);
	}
};
struct H_RAY
{
	D3DXVECTOR3 vOrigin;
	D3DXVECTOR3 vDirection;
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 vPoint;
	float		fExtent;
	H_RAY()
	{
		fExtent = -1;
		//fExtent > 0  세그먼트
	}
};

#ifndef SAFE_ZERO
#define SAFE_ZERO(A)				{ A = 0; }
#endif

#ifndef SAFE_NEW
#define SAFE_NEW(A, B)				{ if (!A) A = new B; }
#endif 

#ifndef SAFE_DEL
#define SAFE_DEL(A)					{ if (A) delete A; (A)=NULL; }
#endif 

#ifndef SAFE_NEW_ARRAY
#define SAFE_NEW_ARRAY(A, B, C)		{ if (!A && C) A = new B[C]; }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(A)		{ if (A) delete [] A; (A)=NULL; }
#endif 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(A)				{ if(A) { (A)->Release(); (A)=NULL; } }
#endif 

#ifndef SAFE_NEW_CLEAR
#define SAFE_NEW_CLEAR( A, B )			{ if (!A) A = new B; if(A) memset( A, 0, sizeof(B) ); };
#endif 

#ifndef SAFE_NEW_ARRAY_CLEAR
#define SAFE_NEW_ARRAY_CLEAR( A, B, C )	{ if (!A && C) A = new B[C]; if(A) memset( A, 0, sizeof(B)*C ); };
#endif

#if defined(DEBUG) | defined(_DEBUG) 
#ifndef H_RETURN
#define H_RETURN(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256]={0,};\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
		MessageBox(NULL, buffer,output,MB_OK); return hr;}\
	}
#endif
#ifndef H
#define H(x){ if (FAILED(x)){\
		LPWSTR output;\
		WCHAR buffer[256]={0,};\
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS |FORMAT_MESSAGE_ALLOCATE_BUFFER,\
		NULL,x,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&output,0,NULL);\
		wsprintf(buffer,L"File=%s\nLine=%s", xstr(__FILE__),xstr(__LINE__));\
		MessageBox(NULL, buffer,output,MB_OK);}\
	}
#endif
#else
#ifndef H_RETURN
#define H_RETURN(x) (x)
#endif
#ifndef H
#define H(x) (x)
#endif
#endif
//////////////////////////////////////////////
//  매크로
//////////////////////////////////////////////_
#define str(x) L#x
#define xstr(x) str(x)
#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;

static std::wstring mtw(std::string data)
{
	return  std::wstring(data.begin(), data.end());
}
static std::string wtm(std::wstring data)
{
	return std::string(data.begin(), data.end());
}