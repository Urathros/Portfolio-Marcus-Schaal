/*****************************************************************************
* Project: DirectX9Stuff
* File   : Window.h
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
*					+Includes: <Windows.h>, "WindowClass.h",
*					+Member-Variablen: m_pWndClass, m_hWnd,
*					+Methoden: Initialize, Run, Finalize,
*					+Funktionen: WndProc,
*					WindowClass in Initialize initialisiert, 
*					Fenstergröße berechnet, Fenster erstellt, Fenster angezeigt
*
*	22.10.20	MS	+Methoden: GetHWND, Run-Parameter _direct3D, 
*					Run um _direct3D.Render, _direct3D.Draw erweitert
******************************************************************************/
#pragma once
#include <Windows.h> //HWND
#include "WindowClass.h" //WindowClass
#include "../DirectX/Direct3D.h" //_direct3D
#include "../General/Variables.h"

class CWindow
{
public:
	HWND GetHWND() { return m_hWnd; }
	inline IVector2 GetWindowSize()
	{ 
		RECT windowRect;
		IVector2 size = IVector2::ZeroVector();
		
		GetWindowRect(m_hWnd, &windowRect);

		size.x = windowRect.right - windowRect.left - 16;
		size.y = windowRect.bottom - windowRect.top - 39;

		return size;
	}

	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize( HINSTANCE _hInstance, IVector2 _size, 
					int _nCmdShow, const char* _name );
	bool Run();
	void Finalize();
	/*************************************************************************/



private:



	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	const int M_I_DEFAULT_RESULT = 0;
	const int M_I_SUCCESS = 1;
	const int M_I_ERROR_NULLPTR_NAME = -1;
	const int M_I_ERROR_CREATE_WINDOW_FAILED = -2;

	const LONG M_I_RECT_SIZE = 100;
	const LPCSTR M_S_WINDOW_ERROR = "Create Window error";
	const LPCSTR M_S_ERROR = "Error";
	/*************************************************************************/

	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	CWindowClass* m_pWndClass = nullptr;
	HWND		  m_hWnd	  = nullptr;
	/*************************************************************************/
};

