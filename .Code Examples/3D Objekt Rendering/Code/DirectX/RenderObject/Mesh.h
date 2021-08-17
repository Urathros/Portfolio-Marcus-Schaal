/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Mesh.h
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
#include <iostream>
#include <vector>
#include "../../General/Variables.h"


class CMesh 
{
public:
	/*************************************************************************/
	// Konstrutor/Destruktor
	/*************************************************************************/
	CMesh() = delete;
	CMesh( ID3D11Device& _pD3DDevice, ID3D11DeviceContext& _pD3DDevCon, 
		   Transform _transform          = Transform::ZeroPRS(), 
		   std::vector<Vertex> _vertVect = {}, 
		   std::vector<DWORD> _idxVect   = {} );
	~CMesh();
	/*************************************************************************/



private:
	/*************************************************************************/
	// Puffer-Initialisierungen
	/*************************************************************************/
	D3D11_BUFFER_DESC InitVertBufDesc( UINT _iVertNum );
	D3D11_SUBRESOURCE_DATA InitVertBufData( Vertex _vertexArr[] );
	int InitVertexBuffer();

	D3D11_BUFFER_DESC InitIdxBufDesc( UINT _iIdxNumb );
	D3D11_SUBRESOURCE_DATA InitIdxBufData( DWORD _indexArr[] );
	int InitIdxBuffer();
	/*************************************************************************/



	/*************************************************************************/
	// Matrix
	/*************************************************************************/
	inline XMMATRIX MatrixMultiply( XMMATRIX _1st, XMMATRIX _2nd )
	{
		XMMATRIX result;
		result._11 =   ( _1st._11 * _2nd._11 ) + ( _1st._12 * _2nd._21 ) 
					 + ( _1st._13 * _2nd._31 ) + ( _1st._14 * _2nd._41 );
		result._12 =   ( _1st._11 * _2nd._12 ) + ( _1st._12 * _2nd._22 ) 
					 + ( _1st._13 * _2nd._32 ) + ( _1st._14 * _2nd._42 );
		result._13 =   ( _1st._11 * _2nd._13 ) + ( _1st._12 * _2nd._23 ) 
					 + ( _1st._13 * _2nd._33 ) + ( _1st._14 * _2nd._43 );
		result._14 =   ( _1st._11 * _2nd._14 ) + ( _1st._12 * _2nd._24 ) 
					 + ( _1st._13 * _2nd._34 ) + ( _1st._14 * _2nd._44 );
		result._21 =   ( _1st._21 * _2nd._11 ) + ( _1st._22 * _2nd._21 ) 
					 + ( _1st._23 * _2nd._31 ) + ( _1st._24 * _2nd._41 );
		result._22 =   ( _1st._21 * _2nd._12 ) + ( _1st._22 * _2nd._22 ) 
					 + ( _1st._23 * _2nd._32 ) + ( _1st._24 * _2nd._42 );
		result._23 =   ( _1st._21 * _2nd._13 ) + ( _1st._22 * _2nd._23 ) 
					 + ( _1st._23 * _2nd._33 ) + ( _1st._24 * _2nd._43 );
		result._24 =   ( _1st._21 * _2nd._14 ) + ( _1st._22 * _2nd._24 ) 
					 + ( _1st._23 * _2nd._34 ) + ( _1st._24 * _2nd._44 );
		result._31 =   ( _1st._31 * _2nd._11 ) + ( _1st._32 * _2nd._21 ) 
					 + ( _1st._33 * _2nd._31 ) + ( _1st._34 * _2nd._41 );
		result._32 =   ( _1st._31 * _2nd._12 ) + ( _1st._32 * _2nd._22 ) 
					 + ( _1st._33 * _2nd._32 ) + ( _1st._34 * _2nd._42 );
		result._33 =   ( _1st._31 * _2nd._13 ) + ( _1st._32 * _2nd._23 ) 
					 + ( _1st._33 * _2nd._33 ) + ( _1st._34 * _2nd._43 );
		result._34 =   ( _1st._31 * _2nd._14 ) + ( _1st._32 * _2nd._24 ) 
					 + ( _1st._33 * _2nd._34 ) + ( _1st._34 * _2nd._44 );
		result._41 =   ( _1st._41 * _2nd._11 ) + ( _1st._42 * _2nd._21 ) 
					 + ( _1st._43 * _2nd._31 ) + ( _1st._44 * _2nd._41 );
		result._42 =   ( _1st._41 * _2nd._12 ) + ( _1st._42 * _2nd._22 ) 
					 + ( _1st._43 * _2nd._32 ) + ( _1st._44 * _2nd._42 );
		result._43 =   ( _1st._41 * _2nd._13 ) + ( _1st._42 * _2nd._23 ) 
					 + ( _1st._43 * _2nd._33 ) + ( _1st._44 * _2nd._43 );
		result._44 =   ( _1st._41 * _2nd._14 ) + ( _1st._42 * _2nd._24 ) 
					 + ( _1st._43 * _2nd._34 ) + ( _1st._44 * _2nd._44 );

		return result;
	}
	/*************************************************************************/



public:
	/*************************************************************************/
	// Getter/Setter
	/*************************************************************************/
	inline XMMATRIX GetWorldMatrix() const{ return m_WorldMatrix; };

	inline void SetPrimitiveTopology() 
	{ 
		m_pD3DDevCon->IASetPrimitiveTopology(
									   D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ); 
	};
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize();
	void Release();
	int Update(const double _deltaTime);
	void Draw(UINT _offset = 0);
	/*************************************************************************/

private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	/*-----------------------------------------------------------------------*/
	// Rückgabewerte
	/*-----------------------------------------------------------------------*/
	const int M_I_SUCCESS							  =  0;
	const int M_I_ERROR_VERTEX_BUFFER_CREATION_FAILED = -1;
	const int M_I_ERROR_INDEX_BUFFER_CREATION_FAILED  = -2;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// default
	/*-----------------------------------------------------------------------*/
	const UINT M_I_DEFAULT_FLAG						  =  0;
	const UINT M_I_DEFAULT_START_SLOT				  =  0;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Matrix
	/*-----------------------------------------------------------------------*/
	const FLOAT M_F_TRANS_QUATER_W					  = 1.0f;
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// constant buffer
	/*-----------------------------------------------------------------------*/
	const UINT M_I_NUM_BUF							  = 1;
	/*-----------------------------------------------------------------------*/
	/*************************************************************************/



	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	HRESULT hr;

	UINT vertexStride				  = sizeof(Vertex); //Paketgröße

	/*-----------------------------------------------------------------------*/
	// Device
	/*-----------------------------------------------------------------------*/
	ID3D11Device*		 m_pD3DDevice = nullptr;
	ID3D11DeviceContext* m_pD3DDevCon = nullptr;
	/*-----------------------------------------------------------------------*/


	/*-----------------------------------------------------------------------*/
	// Puffer
	/*-----------------------------------------------------------------------*/
	ID3D11Buffer* m_pVertexBuffer	  = nullptr;
	ID3D11Buffer* m_pIndexBuffer	  = nullptr;
	/*-----------------------------------------------------------------------*/


	std::vector<Vertex> m_vertexVect  = {};
	std::vector<DWORD> m_indexVect	  = {};

	/*-----------------------------------------------------------------------*/
	//Transform
	/*-----------------------------------------------------------------------*/
	Transform m_transform			  = Transform::ZeroPRS();
	float m_fRotaAngle				  = 0;

	XMMATRIX m_WorldMatrix			  = XMMatrixIdentity(); 
	
	XMMATRIX m_translate			  = XMMatrixIdentity();
	XMMATRIX m_scale				  = XMMatrixIdentity();
	XMMATRIX m_rota					  = XMMatrixIdentity();
	/*-----------------------------------------------------------------------*/
	/*************************************************************************/
};