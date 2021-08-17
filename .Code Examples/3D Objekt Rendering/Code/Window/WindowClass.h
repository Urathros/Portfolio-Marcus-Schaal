/*****************************************************************************
* Project: DirectX9Stuff
* File   : WindowClass.h
* Date   : 01.10.2020
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	01.10.20	MS	Created,
*					+Includes: <Windows.h>,
*					+Member-Variablen: m_pWndClassName, m_hInstance, 
*									   m_wndClassEx,
*					+Methoden: Initialize, Finalize,
*					+Getter: GetHInstance, GetLpszClassName
******************************************************************************/
#pragma once
#include <Windows.h> //HWND

class CWindowClass
{
public:
	/*************************************************************************/
	//Getter
	/*************************************************************************/
	inline HINSTANCE GetHInstance() { return m_wndClassEx.hInstance; }
	inline LPCSTR GetLpszClassName() { return m_wndClassEx.lpszClassName; }
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize( HINSTANCE _hInstance, const char* _name,
					WNDPROC _wndProc );
	void Finalize();
	/*************************************************************************/


private: 
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	const int M_I_SUCCESS = 0;
	const int M_I_ERROR_NULLPTR_NAME = -1;
	const int M_I_ERROR_MSG_FAILED = -2;

	const LPCSTR M_S_REGISTER_ERROR = "Register class error";
	const LPCSTR M_S_ERROR = "Error";
	/*************************************************************************/

	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	const char* m_pWndClassName = nullptr;
	HINSTANCE m_hInstance = nullptr;

	WNDCLASSEX m_wndClassEx = { };
	/*************************************************************************/
};

