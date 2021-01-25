#pragma once

class HObject
{
private:
	int m_inform[3];
	double m_average;
	int m_total;
	int m_Object[3];
	int m_id;
public:
	static int icount;
	//void operator+(int total);
	bool Init(int str,int hp, int mp) ;
	bool Render();
	bool Frame();
	bool Release();
	HObject();
};
