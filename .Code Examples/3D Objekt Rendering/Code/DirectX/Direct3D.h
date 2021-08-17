/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Direct3D.h
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
*	19.10.20	MS	d3d11.h inkludiert,
*					+Member-Variablen: m_pD3DDevice, m_pD3DDevCon, 
*									   m_pSwapChain, m_pRenderTargetView,
*					+Methoden: Initialize, Release, Update, Draw
******************************************************************************/
#pragma once
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include "../General/Variables.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
class CDirect3D
{
private:
	/*************************************************************************/
	// Initialisierungen
	/*************************************************************************/
	DXGI_MODE_DESC InitBufferDesc( IVector2 _size );

	DXGI_SWAP_CHAIN_DESC InitSwapChainDesc( HWND _hWnd, 
											DXGI_MODE_DESC _bufferDesc );

	D3D11_TEXTURE2D_DESC InitDepthStencilDesc( IVector2 _size );
	/*************************************************************************/



public:
	/*************************************************************************/
	// Getter/Setter
	/*************************************************************************/
	inline ID3D11Device* GetDevice() const { return m_pD3DDevice; }
	inline ID3D11DeviceContext* GetDevCon() const { return m_pD3DDevCon; }
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize( HINSTANCE _hInstance, HWND _hWnd, IVector2 _size );
	void Release();
	void ClearView();
	void Draw();
	/*************************************************************************/



private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	/*-----------------------------------------------------------------------*/
	// Rückgabewerte
	/*-----------------------------------------------------------------------*/
	const int M_I_SUCCESS									= 0;
	const int M_I_ERROR_DEVICE_OR_SWAPCHAIN_CREATION_FAILED = -1;
	const int M_I_ERROR_SWAPCHAIN_BUFFER_FAILED				= -2;
	const int M_I_ERROR_RENDER_TARGET_CREATION_FAILED		= -3;
	const int M_I_ERROR_STENCIL_BUFFER_CREATION_FAILED		= -4;
	const int M_I_ERROR_STENCIL_VIEW_CREATION_FAILED		= -5;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	//bufferDescription
	/*-----------------------------------------------------------------------*/
	const UINT M_I_FRAMES  = 60;
	const UINT M_I_SECONDS = 1;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	//swapChain 
	/*-----------------------------------------------------------------------*/
	const UINT M_I_SAMPLE_DESC_COUNT = 1;
	const UINT M_I_MAX_QUALITY		 = 0;
	const UINT M_I_BUFFER_NUMBER	 = 1;
	const UINT M_I_SYNC_INTERVAL	 = 0;
	/*-----------------------------------------------------------------------*/

	const FLOAT M_F_BGC_DEFAULT_COLOR = 0.0f;
	const FLOAT M_F_BGC_DEFAULT_ALPHA = 1.0f;

	/*-----------------------------------------------------------------------*/
	// Tiefen-Stencil-Beschreibung
	/*-----------------------------------------------------------------------*/
	const UINT M_I_STENCIL_MIP_LEVEL	= 1;
	const UINT M_I_STENCIL_ARR_SIZE		= 1; //da einen DepthStencilView
	const UINT M_I_STENCIL_DESC_COUNT	= 1; //einen Stencil-Buffer
	const UINT M_I_STENCIL_DESC_QUALITY = 0; //Höchste Qualitätsstufe
	/*-----------------------------------------------------------------------*/

	const UINT M_I_DEFAULT_FLAG = 0;

	const UINT M_I_NUM_VIEWS	= 1;

	/*-----------------------------------------------------------------------*/
	// Viewport
	/*-----------------------------------------------------------------------*/
	const FLOAT M_F_VIEW_TOP_LEFT  = 0;
	const FLOAT M_F_VIEW_MIN_DEPTH = 0;
	const FLOAT M_F_VIEW_MAX_DEPTH = 1;
	const UINT M_I_CLEAR_DEPTH	   = 1;
	const UINT8 M_I_CLEAR_STENCIL  = 0;
	/*-----------------------------------------------------------------------*/
	/*************************************************************************/



	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	D3DXCOLOR backgroundColor = D3DXCOLOR(	M_F_BGC_DEFAULT_COLOR, 
											M_F_BGC_DEFAULT_COLOR, 
											M_F_BGC_DEFAULT_COLOR, 
											M_F_BGC_DEFAULT_ALPHA );

	ID3D11Device*			m_pD3DDevice		  = nullptr;
	ID3D11DeviceContext*	m_pD3DDevCon		  = nullptr;
	IDXGISwapChain*			m_pSwapChain		  = nullptr; //front/back-buffer
	ID3D11RenderTargetView* m_pRenderTargetView	  = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView   = nullptr;
	ID3D11Texture2D*		m_pDepthStencilBuffer = nullptr;

	D3D11_VIEWPORT			m_viewport = {};
	/*************************************************************************/
};

