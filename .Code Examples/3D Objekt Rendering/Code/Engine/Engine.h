/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Engine.h
* Date   : 13.11.2020
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	13.11.20	MS	Created
******************************************************************************/
#pragma once
#include "../../Code/Window/Window.h"
#include "../DirectX/DirectInput.h"
#include "Time.h"
#include "../DirectX/RasterizerStage.h"

class CEngine
{
public:
	/*************************************************************************/
	// Konstruktor
	/*************************************************************************/
	CEngine();
	/*************************************************************************/

	/*************************************************************************/
	// Getter
	/*************************************************************************/
	/*-----------------------------------------------------------------------*/
	// Device
	/*-----------------------------------------------------------------------*/
	inline ID3D11Device* GetDevice() const { return m_pDirect3D->GetDevice(); }
	
	inline ID3D11DeviceContext* GetDevCon() const 
	{ 
		return m_pDirect3D->GetDevCon(); 
	}
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Delta-Time
	/*-----------------------------------------------------------------------*/
	inline double GetDeltaTime() const { return m_pTime->GetDeltaTime(); }
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Kamera
	/*-----------------------------------------------------------------------*/
	bool GetCameraReset() const { return m_pDirectInput->GetCameraReset(); }

	FVector3 GetCameraPosition() const 
	{ 
		return m_pDirectInput->GetCameraPosition(); 
	}

	FVector3 GetCameraForward() const 
	{ 
		return m_pDirectInput->GetCameraForward(); 
	}
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Fenster
	/*-----------------------------------------------------------------------*/
	inline IVector2 GetWindowSize() const 
	{ 
		return m_pMainWindow->GetWindowSize(); 
	}
	/*-----------------------------------------------------------------------*/
	/*************************************************************************/
 


	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize( HINSTANCE _hInstance, IVector2 _size, int _nCmdShow, 
					const char* _name );
	void Finalize();
	bool Run();
	int DetectInput();
	int Update();
	void ClearView();
	void Draw();
	/*************************************************************************/

private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	const int M_I_SUCCESS = 0;
	/*************************************************************************/



	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	CWindow* m_pMainWindow		    = nullptr;

	CDirect3D* m_pDirect3D		    = nullptr;

	CDirectInput* m_pDirectInput    = nullptr;

	CTime* m_pTime				    = nullptr;

	CRasterizerStage* m_pRasterizer = nullptr;
	/*************************************************************************/
};

