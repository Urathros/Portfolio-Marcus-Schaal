/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : RenderObject.h
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
#include "Material.h"
#include "Mesh.h"

class CRenderObject
{
public:
	/*************************************************************************/
	// Konstrutor
	/*************************************************************************/
	CRenderObject() = delete;

	CRenderObject( ID3D11Device & _pD3DDevice,
				   ID3D11DeviceContext & _pD3DDevCon,
				   Transform _transform			 = Transform::ZeroPRS(),
				   std::vector<Vertex> _vertVect = {},
				   std::vector<DWORD> _idxVect   = {},
				   LPCSTR _vsPath = "MattVertexShader.hlsl",
				   LPCSTR _psPath = "MattPixelShader.hlsl",
				   LPCSTR _texPath = "texture.png", LPCSTR _normMapPath = "" );
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize();
	void Release();
	int Update( const double _deltaTime );
	void Draw( const XMMATRIX& _viewMatrix, const XMMATRIX& _projectionMatrix, 
			   const XMVECTOR& _camPos );
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
	UINT m_idxNumb		   = 0;
	CMaterial* m_pMaterial = nullptr;
	CMesh* m_pMesh		   = nullptr;
	/*************************************************************************/
};