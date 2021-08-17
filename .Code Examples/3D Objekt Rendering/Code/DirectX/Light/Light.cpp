#include "Light.h"
#include "../../General/Defines.h"


/*****************************************************************************/
// Konstruktor/Destruktor
/*****************************************************************************/
//Konstruktor
/*****************************************************************************/
CLight::CLight( ID3D11Device& _pD3DDevice, ID3D11DeviceContext & _pD3DDevCon, 
				const XMFLOAT3& _dir, const XMFLOAT4& _ambient, 
				const XMFLOAT4& _diff )
{
	m_pD3DDevice	  = &_pD3DDevice;
	m_pD3DDevCon	  = &_pD3DDevCon;

	m_light.direction = _dir;
	m_light.ambient	  = _ambient;
	m_light.diffuse   = _diff;
}
/*****************************************************************************/

/*****************************************************************************/
//Destruktor
/*****************************************************************************/
CLight::~CLight()
{
	RELEASE_DELETE( m_pD3DDevCon );
	RELEASE_DELETE( m_pD3DDevice );
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Initialisierungen
/*****************************************************************************/
//ConstBuffer-Beschreibung initialisieren
/*****************************************************************************/
D3D11_BUFFER_DESC CLight::InitConstBufDesc()
{
	D3D11_BUFFER_DESC constBufDesc;

	constBufDesc.ByteWidth			 = sizeof( FrameLightCB );
	constBufDesc.Usage				 = D3D11_USAGE_DEFAULT;
	constBufDesc.BindFlags			 = D3D11_BIND_CONSTANT_BUFFER;
	constBufDesc.CPUAccessFlags		 = M_I_DEFAULT_FLAG;
	constBufDesc.MiscFlags			 = M_I_DEFAULT_FLAG;
	constBufDesc.StructureByteStride = M_I_DEFAULT_STRIDE;

	return constBufDesc;
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisieren
/*****************************************************************************/
int CLight::Initialize()
{
	HRESULT hr;

	hr = m_pD3DDevice->CreateBuffer( &InitConstBufDesc(), NULL,
									 &m_pLightConstBuffer );
	if( FAILED( hr ) ) return M_I_ERROR_BUFFER_CREATION_FAILED;

	m_frameCB.light = m_light;

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Freigeben
/*****************************************************************************/
void CLight::Release()
{ 
	RELEASE_DELETE( m_pLightConstBuffer );
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
/*****************************************************************************/
void CLight::Draw()
{
	m_pD3DDevCon->UpdateSubresource( m_pLightConstBuffer, 
									 M_I_DEFAULT_SUBRESOURCE, NULL, &m_frameCB, 
									 M_I_DEFAULT_SRC_DATA, 
									 M_I_DEFAULT_SRC_ROW_PITCH );

	m_pD3DDevCon->PSSetConstantBuffers( M_I_DEFAULT_START_SLOT, M_I_NUM_BUF, 
										&m_pLightConstBuffer );
}
/*****************************************************************************/
/*****************************************************************************/