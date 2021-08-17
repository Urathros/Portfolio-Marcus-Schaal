/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Material.h
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
#include <D3DX11.h>
#include <D3DX10.h>
#include <iostream>
#include "../MatrixCB.h"
#include "Texture.h"

class CMaterial 
{
public:
	/*************************************************************************/
	// Konstrutor/Destruktor
	/*************************************************************************/
	CMaterial() = delete;
	CMaterial( ID3D11Device& _pD3DDevice, ID3D11DeviceContext& _pD3DDevCon, 
			   LPCSTR _vsPath = "MatteVertexShader.hlsl", 
			   LPCSTR _psPath = "MattePixelShader.hlsl", 
			   LPCSTR _texPath = "texture.png", LPCSTR _normMapPath = "" );

	~CMaterial();
	/*************************************************************************/

private:
	/*************************************************************************/
	// Shader erstellen
	/*************************************************************************/
	int CompileShader();
	int CreateShaderObjects();
	void SetShader();
	/*************************************************************************/

	/*************************************************************************/
	// Matrix
	/*************************************************************************/
	inline XMMATRIX TransposeMatrix( const XMMATRIX& _mat ) 
	{ 
		XMMATRIX transposable;

		transposable._11 = _mat._11;
		transposable._12 = _mat._21;
		transposable._13 = _mat._31;
		transposable._14 = _mat._41;

		transposable._21 = _mat._12;
		transposable._22 = _mat._22;
		transposable._23 = _mat._32;
		transposable._24 = _mat._42;

		transposable._31 = _mat._13;
		transposable._32 = _mat._23;
		transposable._33 = _mat._33;
		transposable._34 = _mat._43;

		transposable._41 = _mat._14;
		transposable._42 = _mat._24;
		transposable._43 = _mat._34;
		transposable._44 = _mat._44;
		
		return transposable;
	}
	/*************************************************************************/


	/*************************************************************************/
	// Initialisierungen
	/*************************************************************************/
private:
	D3D11_INPUT_ELEMENT_DESC CreateLayoutPos(	   UINT _offset = 0 ) const;
	D3D11_INPUT_ELEMENT_DESC CreateLayoutColor(	   UINT _offset = 0 ) const;
	D3D11_INPUT_ELEMENT_DESC CreateLayoutTexCoord( UINT _offset = 0 ) const;
	D3D11_INPUT_ELEMENT_DESC CreateLayoutNorm(	   UINT _offset = 0 ) const;
	D3D11_INPUT_ELEMENT_DESC CreateLayoutTan(	   UINT _offset = 0 ) const;
	D3D11_INPUT_ELEMENT_DESC CreateLayoutBinorm(   UINT _offset = 0 ) const;

	void CreateLayoutArr( D3D11_INPUT_ELEMENT_DESC* _layoutArr );

public:
	int CreateVertexLayout();
	int CreateMatrixConstBuffer();
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize();
	void Release();
	void Draw( XMMATRIX _worldMatrix, XMMATRIX _viewMatrix, 
			   XMMATRIX _projectionMatrix, XMVECTOR _camPos, UINT _idxNumb );
	/*************************************************************************/

private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	/*-----------------------------------------------------------------------*/
	// Rückgabewert
	/*-----------------------------------------------------------------------*/
	const int M_I_SUCCESS = 0;
	const int M_I_ERROR_COMPILE_VS_BUFFER_FAILED = -1;
	const int M_I_ERROR_COMPILE_PS_BUFFER_FAILED = -2;
	const int M_I_VERTEX_SHADER_CREATION_FAILED  = -3;
	const int M_I_PIXEL_SHADER_CREATION_FAILED   = -4;
	const int M_I_INPUT_LAYOUT_CREATION_FAILED   = -5;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// default
	/*-----------------------------------------------------------------------*/
	const UINT M_I_DEFAULT_SEMANTIC_IDX			 = 0;
	const UINT M_I_DEFAULT_INPUT_SLOT			 = 0;
	const UINT M_I_DEFAULT_DATA_STEP_RATE		 = 0;
	const UINT M_I_DEFAULT_FLAG = 0;
	const UINT M_I_DEFAULT_STRIDE = 0;
	const UINT M_I_DEFAULT_SUBRESOURCE = 0;
	const UINT M_I_DEFAULT_SRC_DATA = 0;
	const UINT M_I_DEFAULT_SRC_ROW_PITCH = 0;
	const UINT M_I_DEFAULT_START_SLOT = 0;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// constant buffer
	/*-----------------------------------------------------------------------*/
	const UINT M_I_NUM_BUF = 1;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Shader
	/*-----------------------------------------------------------------------*/
	const LPCSTR M_S_SHADER_MAIN			   	 = "main";
	const LPCSTR M_S_VERTEX_SHADER				 = "vs_4_0";
	const LPCSTR M_S_PIXEL_SHADER				 = "ps_4_0";
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Layout
	/*-----------------------------------------------------------------------*/
	const LPCSTR M_S_POS_NAME					 = "POSITION";
	const LPCSTR M_S_COLOR_NAME					 = "COLOR";
	const LPCSTR M_S_TEX_COORD_NAME				 = "TEXCOORD";
	const LPCSTR M_S_NORM_NAME					 = "NORMAL";
	const LPCSTR M_S_TAN_NAME					 = "TANGENT";
	const LPCSTR M_S_BINORM_NAME				 = "BINORMAL";

	const UINT M_I_COLOR_OFFSET					 = 12;
	const UINT M_I_TEX_COORD_OFFSET				 = 16;
	const UINT M_I_NORM_OFFSET					 = 8;
	const UINT M_I_TAN_OFFSET					 = 12;
	const UINT M_I_BINORM_OFFSET			   	 = 12;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Normal-Map
	/*-----------------------------------------------------------------------*/
	const UINT M_I_NORM_MAP_START_SLOT = 1;
	/*-----------------------------------------------------------------------*/
	/*************************************************************************/


	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	UINT StartIdxLoca = 0;
	UINT vertBufLoca = 0;

	bool m_pNormalMapExists = false;

	/*-----------------------------------------------------------------------*/
	//DirectX
	/*-----------------------------------------------------------------------*/
	ID3D11Device*		 m_pD3DDevice = nullptr;
	ID3D11DeviceContext* m_pD3DDevCon = nullptr;

	HRESULT hr;
	/*-----------------------------------------------------------------------*/

	LPCSTR m_sVertexShaderPath = "";
	LPCSTR m_sPixelShaderPath = "";

	/*-----------------------------------------------------------------------*/
	//Buffer
	ID3D11VertexShader* m_pVertexShader = nullptr; //für Shader-Quellcode
	ID3D10Blob* m_pVertexShaderBuffer = nullptr;

	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D10Blob* m_pPixelShaderBuffer = nullptr;

	ID3D11InputLayout* m_pVertexLayout = nullptr;

	ID3D11Buffer* m_pLightConstBuffer = nullptr;
	ObjMatrixCB m_matrixCB;
	/*-----------------------------------------------------------------------*/


	/*-----------------------------------------------------------------------*/
	//WVP
	/*-----------------------------------------------------------------------*/
	XMMATRIX m_WVPMatrix = XMMatrixIdentity();
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	//Texture
	/*-----------------------------------------------------------------------*/
	CTexture* m_pTexture = nullptr;
	CTexture* m_pNormalMap = nullptr;
	/*-----------------------------------------------------------------------*/
	/*************************************************************************/
};

