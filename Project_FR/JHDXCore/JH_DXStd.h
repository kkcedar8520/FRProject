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
#include<utility>
#include"JH_DXHelperEX.h"


//Memory leack detector
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include<crtdbg.h>


#pragma warning(disable:4005)
#ifdef _DEBUG
#pragma comment(lib, "JHDXCore_d")
#pragma comment(lib,"assimp")//Modle Importer library
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#ifndef DBG_NEW
//	#define DBG_NEW new ( _CLIENT_BLOCK, __FILE__, __LINE__)
//	#define malloc(s) _malloc_dbg(s,_NORMAL_BLOCK, __FILE__, __LINE__)
//	#define new DBG_NEW
//#endif 

#else
#pragma comment(lib,"JHDXCore_R")
#endif
using namespace Microsoft::WRL;







#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "fmod_vc.lib")
#define TCORE_START int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPTSTR  lpCmdLIne,int  nCmdShow){
#define TCORE_RUN(s,d) { ToolCore  gDemo;if (gDemo.InitWindow(L#s,d)){gDemo.Run();}return 1; }
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


template<typename T>
void VectorCleaner(std::vector<T>& v)
{
	
	std::vector<T>().swap(v);
}

enum P_POSITION
{
	P_BACK = 0,
	P_FRONT,
	P_ONPLANE,
	P_SPANNING
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
struct JH_Box
{
	// aabb							//
	D3DXVECTOR3 vMin;
	D3DXVECTOR3 vMax;

	// obb							//축에 회전된 박스
	D3DXVECTOR3 vCenter;
	D3DXVECTOR3 vAxis[3];
	float fExtent[3];
	float fExtentXZ;			//y값을 고려하지 않은 상자의 대각선 길이

	JH_Box()
	{
		Init();
	}
	void Init()
	{
		vMin = D3DXVECTOR3(-1, -1, -1);
		vMax = D3DXVECTOR3(1, 1, 1);
		vCenter = D3DXVECTOR3(0, 0, 0);

		vAxis[0] = D3DXVECTOR3{ 1,0,0 };
		vAxis[1] = D3DXVECTOR3{ 0,1,0 };
		vAxis[2] = D3DXVECTOR3{ 0,0,1 };

		fExtent[0] = vMax.x-vCenter.x;
		fExtent[1] = vMax.y - vCenter.y;
		fExtent[2] = vMax.z - vCenter.z;
	}
	void CreateBox(D3DXMATRIX matTransform)
	{
		Init();
		D3DXMATRIX mSRT, mS, mR;
		D3DXVECTOR3	vS, vT;
		D3DXQUATERNION qR;
		D3DXMatrixIdentity(&mSRT);D3DXMatrixIdentity(&mS);D3DXMatrixIdentity(&mR);

		D3DXMatrixDecompose(&vS, &qR, &vT, &matTransform);

		D3DXMatrixScaling(&mS, vS.x, vS.y, vS.z);
		D3DXMatrixRotationQuaternion(&mR, &qR);


		mSRT = mS * mR;
		mSRT._41 = vT.x;
		mSRT._42 = vT.y;
		mSRT._43 = vT.z;
		
		fExtent[0] *= vS.x;
		fExtent[1] *= vS.y;
		fExtent[2] *= vS.z;
	
		D3DXVec3TransformCoord(&vAxis[0], &vAxis[0], &mR);
		D3DXVec3TransformCoord(&vAxis[1], &vAxis[1], &mR);
		D3DXVec3TransformCoord(&vAxis[2], &vAxis[2], &mR);

		D3DXVec3Normalize(&vAxis[0], &vAxis[0]);
		D3DXVec3Normalize(&vAxis[1], &vAxis[1]);
		D3DXVec3Normalize(&vAxis[2], &vAxis[2]);

		vCenter = vT;

		vMax = vCenter + vAxis[0]*vS.x + vAxis[1]*vS.y + vAxis[2]*vS.z;
		vMin = vCenter - vAxis[0] * vS.x - vAxis[1] * vS.y - vAxis[2] * vS.z;
	
	

		
	}
	void SetScale(D3DXVECTOR3& vScale)
	{
	
		fExtent[0] *= fExtent[0] * vScale.x;
		fExtent[1] *= fExtent[1] * vScale.y;
		fExtent[2] *= fExtent[2] * vScale.z;

		vMax = vCenter + vAxis[0]*fExtent[0] + vAxis[1] * fExtent[1] + vAxis[2] * fExtent[2];
		vMin = vCenter - vAxis[0] * fExtent[0] - vAxis[1] * fExtent[1] - vAxis[2] * fExtent[2];


	}
	void SetRotation(D3DXMATRIX& Mat)
	{

		D3DXVec3TransformCoord(&vAxis[0], &vAxis[0], &Mat);
		D3DXVec3TransformCoord(&vAxis[1], &vAxis[1], &Mat);
		D3DXVec3TransformCoord(&vAxis[2], &vAxis[2], &Mat);

		D3DXVec3TransformCoord(&vMin, &vMin, &Mat);
		D3DXVec3TransformCoord(&vMax, &vMax, &Mat);
	}
	void SetPosition(D3DXVECTOR3& vPos)
	{

		vCenter = vPos;
		vMax = vPos;
		vMin = vPos;

	}
};
struct JH_PLANE
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
	void CreatePlane(D3DXVECTOR3 v0, D3DXVECTOR3 vDir)//평면의 방정식을 통한 ax+by+cz+d=0 공식으로 d=-(ax+by+cz)이다.
	{
		D3DXVec3Normalize(&vDir, &vDir);
		fA = vDir.x;
		fB = vDir.y;
		fC = vDir.z;

		fD = -(fA*v0.x + fB * v0.y + fC * v0.z);
	}
	void	Normalize()
	{
		float fMag = sqrt(fA*fA + fB * fB + fC * fC);
		fA = fA / fMag;
		fB = fB / fMag;
		fC = fC / fMag;
		fD = fD / fMag;
	}
};

struct JH_RAY
{
	D3DXVECTOR3 vOrigin;
	D3DXVECTOR3 vDirection;
	D3DXVECTOR3 vEnd;
	D3DXVECTOR3 vPoint;
	float		fExtent;
	JH_RAY()
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