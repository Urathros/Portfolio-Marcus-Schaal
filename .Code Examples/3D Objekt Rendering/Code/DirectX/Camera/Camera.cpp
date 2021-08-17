#include "Camera.h"

/*****************************************************************************/
// Konstruktor
/*****************************************************************************/
CCamera::CCamera( const IVector2& _size )
{
	//View-Vektoren setzen
	m_position = XMVectorSet( M_F_DEFAULT_X, M_F_DEFAULT_Y, 
							  M_F_CAM_DEPTH_POS, M_F_DEFAULT_W );
	m_forward = XMVectorZero();
	m_up = XMVectorSet( M_F_DEFAULT_X, M_F_CAM_UP_DIR, 
						M_F_DEFAULT_Z, M_F_DEFAULT_W );

	//Matritzen setzen
	UpdateMatrices(_size);
}
/*****************************************************************************/

/*****************************************************************************/
// Matrizen updaten
/*****************************************************************************/
void CCamera::UpdateMatrices( const IVector2& _size )
{
	//Aspect-Ratio aus Fenstergröße
	m_fAspectRatio =   static_cast<FLOAT>( _size.x ) 
					 / static_cast<FLOAT>( _size.y );

	//Matrizen updaten
	m_viewMatrix = XMMatrixLookAtLH( m_position, m_forward, m_up );
	m_projectionMatrix = 
		XMMatrixPerspectiveFovLH( M_F_FOV_ANGLE, m_fAspectRatio, 
								  M_F_NEAR_PLANE, M_F_FAR_PLANE );
}
/*****************************************************************************/