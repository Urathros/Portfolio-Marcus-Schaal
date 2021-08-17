/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : DirectInput.h
* Date   : 07.11.2020
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	07.11.20	MS	Created
******************************************************************************/
#pragma once
#include <dinput.h>
#include "../General/Variables.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class CDirectInput
{
private:

public:
	/*************************************************************************/
	// Getter
	/*************************************************************************/
	inline bool		GetCameraReset()	const { return m_bCameraReset; }
	inline FVector3 GetCameraPosition() const { return m_cameraPosition; }
	inline FVector3 GetCameraForward()  const { return m_cameraForward; }

	inline bool		GetRasterState()	const { return m_bRasterState; }
	/*************************************************************************/



	/*************************************************************************/
	// Tastatureingabe erfragen
	/*************************************************************************/
private:
	void ResetCamera();
	void ChangeCameraPos( const double _deltaTime );
	void ChangeCameraDirection( const double _deltaTime );
	void DetectKeystate( const double _deltaTime );
public:
	int DetectInput( const double _deltaTime );
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize( HINSTANCE _hInstance, HWND _hWnd );
	void Release();
	/*************************************************************************/



private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	/*-----------------------------------------------------------------------*/
	// Rückgabewerte
	/*-----------------------------------------------------------------------*/
	const int M_I_SUCCESS = 0;
	const int M_I_ERROR_INPUT_8_CREATION_FAILED = -1;
	const int M_I_ERROR_KEYBOARD_DEV_CREATION_FAILED = -2;
	const int M_I_ERROR_MOUSE_DEV_CREATION_FAILED = -3;
	const int M_I_ERROR_KEY_DATA_FORMAT_FAILED = -4;
	const int M_I_ERROR_KEY_COORP_LEVEL_FAILED = -5;
	const int M_I_ERROR_MOUSE_DATA_FORMAT_FAILED = -6;
	const int M_I_ERROR_MOUSE_COORP_LEVEL_FAILED = -7;
	const int M_I_ERROR_MOUSE_DEV_STATE_FAILED = -8;
	const int M_I_ERROR_KEY_DEV_STATE_FAILED = -9;
	/*-----------------------------------------------------------------------*/

	// Keyboard
	const int M_I_KEYSTATE_FLAG = 0x80;

	// Movement
	const float M_F_CAM_MOVE = 1.5f;
	const float M_F_CAM_FORWARD = 100.0f;
	/*************************************************************************/



	/*************************************************************************/
	// Member-Varibalen
	/*************************************************************************/
	HRESULT hr;

	IDirectInputDevice8* m_pMouseDevice   = nullptr;
	IDirectInputDevice8* m_pKeboardDevice = nullptr;

	DIMOUSESTATE m_lastMouseState;
	DIMOUSESTATE m_currentMouseState;

	BYTE m_keyboardStateArr[256]		  = {};

	LPDIRECTINPUT8 m_lpDirectInput;

	bool m_bCameraReset					  = false;
	FVector3 m_cameraPosition			  = FVector3::ZeroVector();
	FVector3 m_cameraForward			  = FVector3::ZeroVector();


	bool m_bRasterState				 	  = false;
	/*************************************************************************/
};