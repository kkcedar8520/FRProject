#include "JH_Input.h"


DWORD  JH_Input::KeyCheck(DWORD inputkey)
{
	SHORT iKEY = GetAsyncKeyState(inputkey);
	
	if (iKEY & 0x8000)
	{
		if (m_StateKey[inputkey]==KEY_FREE ||
			m_StateKey[inputkey]==KEY_HOLD)
		{
			return m_StateKey[inputkey] = KEY_PUSH;
		}
		else
		{
			return m_StateKey[inputkey] = KEY_HOLD;
		}
	}
	else
	{
		if (m_StateKey[inputkey]==KEY_HOLD||
			m_StateKey[inputkey]==KEY_PUSH)
		{
			return m_StateKey[inputkey] = KEY_UP;
		}
		else
		{
		}
			return m_StateKey[inputkey] = KEY_FREE;
	}
	return m_StateKey[inputkey];
}
bool JH_Input::Init()
{
	ZeroMemory(&m_StateKey, sizeof(DWORD) * 256);
	return true;
}
bool JH_Input::Render()
{
	return true;
}
bool JH_Input::Frame()
{
	GetCursorPos(&m_MousePos);
	ScreenToClient(g_hwnd, &m_MousePos);
	return true;
}
bool JH_Input::Release()
{
	return true;
}
JH_Input::JH_Input()
{
	memset(&m_StateKey, 0, sizeof(m_StateKey));

}


JH_Input::~JH_Input()
{
}
