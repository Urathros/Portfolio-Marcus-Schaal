/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : RasterizerStage.h
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
#include <d3d11.h>

/*****************************************************************************/
// Art der Rasterisierung
/*****************************************************************************/
enum RASTER_STAGE { RS_NONE, RS_SOLID, RS_WIRE_FRAME, RS_COUNT };
/*****************************************************************************/

class CRasterizerStage
{
public:
	/*************************************************************************/
	// Konstruktor/Destruktor
	/*************************************************************************/
	CRasterizerStage() = delete;
	CRasterizerStage( ID3D11Device & _pD3DDevice, 
					  ID3D11DeviceContext& _pD3DDevCon );
	~CRasterizerStage();
	/*************************************************************************/



	/*************************************************************************/
	// Initialisierungen
	/*************************************************************************/
	D3D11_RASTERIZER_DESC InitSolidDesc();
	D3D11_RASTERIZER_DESC InitWireFrameDesc();
	/*************************************************************************/

	void ChangeStage( bool _keyDown );


	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize();
	void Release();
	void Draw();
	/*************************************************************************/

private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	/*-----------------------------------------------------------------------*/
	// Rückgabewerte
	/*-----------------------------------------------------------------------*/
	const int M_I_SUCCESS					= 0;
	const int M_I_ERROR_CREATE_SOLID_FAILED = -1;
	const int M_I_ERROR_CREATE_WIRE_FAILED  = -2;
	/*-----------------------------------------------------------------------*/
	/*************************************************************************/



	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	HRESULT hr;

	//Obj mit komplettem Status, austauschbar
	ID3D11RasterizerState* m_pSolidState	 = nullptr;
	ID3D11RasterizerState* m_pWireFrameState = nullptr;

	ID3D11Device*		   m_pD3DDevice		 = nullptr;
	ID3D11DeviceContext*   m_pD3DDevCon		 = nullptr;

	RASTER_STAGE		   m_lastStage		 = RASTER_STAGE::RS_NONE;
	RASTER_STAGE		   m_currentStage	 = RASTER_STAGE::RS_NONE;
	/*************************************************************************/
};