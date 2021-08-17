/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Texture.h
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
#include <d3d11.h>

class CTexture
{
public:
	/*************************************************************************/
	// Konstrutor/Destruktor
	/*************************************************************************/
	CTexture() = delete;
	CTexture( ID3D11Device& _pD3DDevice, ID3D11DeviceContext& _pD3DDevCon, 
		      LPCSTR _texPath = "texture.png" );
	~CTexture();
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize();
	void Release();
	void Draw( UINT _startSlot = 0 );
	/*************************************************************************/


private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	const int M_I_SUCCESS = 0;
	const int M_I_ERROR_LOAD_SHADER_FROM_FILE_FAILED = -1;

	const FLOAT M_F_MIN_LOD = 0.0f;

	const UINT M_I_NUM_VIEWS = 1;
	/*************************************************************************/



	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	HRESULT hr;

	LPCSTR m_sTexturePath					   = "";

	ID3D11ShaderResourceView* m_pTexture	   = nullptr;
	ID3D11SamplerState*		  m_pSamplerState  = nullptr;

	ID3D11Device*			  m_pD3DDevice	   = nullptr;
	ID3D11DeviceContext*	  m_pD3DDevCon	   = nullptr;
	/*************************************************************************/
};