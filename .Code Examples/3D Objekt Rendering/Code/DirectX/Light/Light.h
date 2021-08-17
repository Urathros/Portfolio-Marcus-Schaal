/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Light.h
* Date   : 16.11.2020
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	16.11.20	MS	Created, +Konstruktor,
*					+Methoden: Initialize, Release, Draw,
*					+Member-Variablen: m_pLightConstBuffer, m_light, m_frameCB,
*									   m_pD3DDevice, m_pD3DDevCon
******************************************************************************/
#pragma once
#include "../MatrixCB.h"

class CLight
{
public:
	/*************************************************************************/
	// Konstruktor/Destruktor
	/*************************************************************************/
	CLight() = delete;
	CLight( ID3D11Device& _pD3DDevice, ID3D11DeviceContext& _pD3DDevCon, 
			const XMFLOAT3& _dir, const XMFLOAT4& _ambient, 
			const XMFLOAT4& _diff );

	~CLight();
	/*************************************************************************/
private:
	D3D11_BUFFER_DESC InitConstBufDesc();

public:
	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int  Initialize();
	void Release();
	void Draw();
	/*************************************************************************/

private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	// default
	const UINT M_I_DEFAULT_FLAG   = 0;
	const UINT M_I_DEFAULT_STRIDE = 0;
	const UINT M_I_DEFAULT_SUBRESOURCE = 0;
	const UINT M_I_DEFAULT_SRC_DATA = 0;
	const UINT M_I_DEFAULT_SRC_ROW_PITCH = 0;
	const UINT M_I_DEFAULT_START_SLOT = 0;

	const UINT M_I_NUM_BUF = 1;

	// Rückgabewert
	const int M_I_SUCCESS = 0;
	const int M_I_ERROR_BUFFER_CREATION_FAILED = -1;
	/*************************************************************************/

	/*************************************************************************/
	//Member-Variablen
	/*************************************************************************/
	// Buffer
	ID3D11Buffer* m_pLightConstBuffer = nullptr;

	// Licht
	Light        m_light;
	FrameLightCB m_frameCB;

	// DirectX
	ID3D11Device* m_pD3DDevice		  = nullptr;
	ID3D11DeviceContext* m_pD3DDevCon = nullptr;
	/*************************************************************************/
};

