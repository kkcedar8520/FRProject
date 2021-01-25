#pragma once
#include"SelectModel.h"
class StdSelect:public SelectModel
{
	FD_SET m_rSet; // FD( FILE DESCRIPTOR 약자 자신이 사용할 파일 또는 장치에대한 고유 식별값)
	FD_SET m_wSet; // 소켓함수를 쓰면 정수값이 반환되는데 이값이 FD( FILE DESCRIPTOR) 
					//	이값은 같은 프로그램안에서 중복되지않기 때문에  고유값으로 사용가능
public:
	bool Frame();
public:
	StdSelect(SOCKET sock);
	virtual ~StdSelect();
};

