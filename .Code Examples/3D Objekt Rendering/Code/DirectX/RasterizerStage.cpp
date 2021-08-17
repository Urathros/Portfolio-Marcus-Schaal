#include "RasterizerStage.h"
#include "../General/Defines.h"


/*************************************************************************/
// Konstruktor/Destruktor
/*************************************************************************/
// Konstruktor
/*************************************************************************/
CRasterizerStage::CRasterizerStage( ID3D11Device & _pD3DDevice, 
									ID3D11DeviceContext& _pD3DDevCon )
{
	m_pD3DDevice = &_pD3DDevice;
	m_pD3DDevCon = &_pD3DDevCon;
}
/*************************************************************************/

/*************************************************************************/
// Destruktor
/*************************************************************************/
CRasterizerStage::~CRasterizerStage()
{
	RELEASE_DELETE( m_pD3DDevCon );
	RELEASE_DELETE( m_pD3DDevice );
}
/*************************************************************************/



/*************************************************************************/
// Initialisierungen
/*************************************************************************/
// Solide Rasterisierung initialisieren
/*************************************************************************/
D3D11_RASTERIZER_DESC CRasterizerStage::InitSolidDesc()
{
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory( &solidDesc, sizeof( solidDesc ) );

	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;

	return solidDesc;
}
/*************************************************************************/

/*************************************************************************/
// Wireframe-Rasterisierung initialisieren
/*************************************************************************/
D3D11_RASTERIZER_DESC CRasterizerStage::InitWireFrameDesc()
{
	D3D11_RASTERIZER_DESC wireFrameDesc;
	ZeroMemory( &wireFrameDesc, sizeof( wireFrameDesc ) );

	wireFrameDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireFrameDesc.CullMode = D3D11_CULL_NONE;

	return wireFrameDesc;
}
/*************************************************************************/
/*************************************************************************/



/*************************************************************************/
// Rasterisierung ändern
/*************************************************************************/
void CRasterizerStage::ChangeStage( bool _keyDown )
{
	if( _keyDown && m_currentStage == RASTER_STAGE::RS_SOLID )
	{
		m_currentStage = RASTER_STAGE::RS_WIRE_FRAME;
	}
	else if( _keyDown && m_currentStage == RASTER_STAGE::RS_WIRE_FRAME )
	{
		m_currentStage = RASTER_STAGE::RS_SOLID;
	}
}
/*************************************************************************/



/*************************************************************************/
// Programmablauf
/*************************************************************************/
// Initialisierung
/*************************************************************************/
int CRasterizerStage::Initialize()
{
	hr = m_pD3DDevice->CreateRasterizerState( &InitSolidDesc(), 
											  &m_pSolidState );
	if( FAILED( hr ) ) return M_I_ERROR_CREATE_SOLID_FAILED;

	
	hr = m_pD3DDevice->CreateRasterizerState( &InitWireFrameDesc(), 
											  &m_pWireFrameState );
	if( FAILED( hr ) ) return M_I_ERROR_CREATE_WIRE_FAILED;

	return M_I_SUCCESS;
}
/*************************************************************************/

/*************************************************************************/
// Freigeben
/*************************************************************************/
void CRasterizerStage::Release()
{
	RELEASE_DELETE( m_pWireFrameState );
	RELEASE_DELETE( m_pSolidState );
}
/*************************************************************************/

/*************************************************************************/
// Zeichnen
/*************************************************************************/
void CRasterizerStage::Draw()
{
	switch( m_currentStage )
	{
	case RASTER_STAGE::RS_SOLID: 
		if( m_lastStage != RASTER_STAGE::RS_SOLID )
		{
			m_pD3DDevCon->RSSetState( m_pSolidState );
			m_lastStage = RASTER_STAGE::RS_SOLID;
		}
		break;

	case RASTER_STAGE::RS_WIRE_FRAME: 
		if( m_lastStage != RASTER_STAGE::RS_WIRE_FRAME )
		{
			m_pD3DDevCon->RSSetState( m_pWireFrameState );
			m_lastStage = RASTER_STAGE::RS_WIRE_FRAME;
		}
		break;

	default:
		m_currentStage = RASTER_STAGE::RS_SOLID;
		m_lastStage = RASTER_STAGE::RS_SOLID;
		m_pD3DDevCon->RSSetState( m_pSolidState );
		break;
	}
}
/*************************************************************************/
/*************************************************************************/