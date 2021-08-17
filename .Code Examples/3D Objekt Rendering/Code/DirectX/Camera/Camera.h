/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Camera.h
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
*	13.11.20	MS	Created, +Konstruktor,
*					+Methoden: GetViewMatrix, GetProjectionMatrix,
*							   GetCameraPosition, ResetCamera, AddPosition
*							   AddForward,
*					+Konstanten: M_F_CAM_DEPTH_POS, M_F_CAM_UP_DIR, M_F_PI,
*								 M_F_FOV_ANGLE, M_F_NEAR_PLANE, M_F_FAR_PLANE,
*					+Member-Variablen: m_fAspectRatio, m_viewMatrix,
*									   m_projectionMatrix, m_position,
*									   m_forward, m_up
******************************************************************************/
#pragma once
#include <d3d11.h>
#include <xnamath.h>
#include "../../General/Variables.h"

class CCamera
{
public:
	/*************************************************************************/
	// Konstruktor
	/*************************************************************************/
	CCamera() = delete;
	CCamera( const IVector2& _size );
	/*************************************************************************/


	/*************************************************************************/
	// Getter/Setter
	/*************************************************************************/
	inline XMMATRIX GetViewMatrix()		  const	{ return m_viewMatrix; }
	inline XMMATRIX GetProjectionMatrix() const { return m_projectionMatrix; }
	inline XMVECTOR GetCameraPosition()   const	{ return m_position; }

	inline void ResetCamera( bool _reset ) 
	{
		if( _reset )
		{
			m_position = XMVectorSet( M_F_DEFAULT_X, M_F_DEFAULT_Y, 
									  M_F_CAM_DEPTH_POS, M_F_DEFAULT_W );
			m_forward = XMVectorZero();
		}
	}
	inline void AddPosition( const XMVECTOR& _pos )  { m_position += _pos; }
	inline void AddForward( const XMVECTOR& _front ) { m_forward += _front; }
	/*************************************************************************/


	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	void UpdateMatrices( const IVector2& _size );
	/*************************************************************************/

private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	// default
	const FLOAT M_F_DEFAULT_X		= 0.0f;
	const FLOAT M_F_DEFAULT_Y		= 0.0f;
	const FLOAT M_F_DEFAULT_Z		= 0.0f;
	const FLOAT M_F_DEFAULT_W		= 0.0f;

	//Camera Position
	const FLOAT M_F_CAM_DEPTH_POS	= -4.0f;
	const FLOAT M_F_CAM_UP_DIR		= 1.0f;

	//Field of View
	const FLOAT M_F_PI				= 3.14159265f;
	const FLOAT M_F_FOV_ANGLE		= 0.5F * M_F_PI;
	const FLOAT M_F_NEAR_PLANE		= 1.0f;
	const FLOAT M_F_FAR_PLANE		= 1000.0f;
	/*************************************************************************/

	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/

	FLOAT m_fAspectRatio			= 0.0f;

	XMMATRIX m_viewMatrix			= XMMatrixIdentity();
	XMMATRIX m_projectionMatrix		= XMMatrixIdentity();

	XMVECTOR m_position				= XMVectorZero();
	XMVECTOR m_forward				= XMVectorZero();
	XMVECTOR m_up					= XMVectorZero();
	/*************************************************************************/
};

