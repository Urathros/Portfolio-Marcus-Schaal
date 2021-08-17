#include "Texture.h"
#include <D3DX11.h>
#include "../../General/Defines.h"

/*****************************************************************************/
// Konstruktor/Destruktor
/*****************************************************************************/
// Konstruktor
/*****************************************************************************/
CTexture::CTexture( ID3D11Device& _pD3DDevice, 
					ID3D11DeviceContext & _pD3DDevCon, LPCSTR _texPath )
{
	m_pD3DDevice   = &_pD3DDevice;
	m_pD3DDevCon   = &_pD3DDevCon;

	m_sTexturePath = _texPath;
}
/*****************************************************************************/

/*****************************************************************************/
// Destruktor
/*****************************************************************************/
CTexture::~CTexture()
{
	m_sTexturePath = "";

	RELEASE_DELETE( m_pD3DDevCon );
	RELEASE_DELETE( m_pD3DDevice );
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CTexture::Initialize()
{
	D3DX11CreateShaderResourceViewFromFile( m_pD3DDevice, m_sTexturePath, 
											NULL, NULL, &m_pTexture, &hr );
	if (FAILED(hr)) return M_I_ERROR_LOAD_SHADER_FROM_FILE_FAILED;

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER; 
	samplerDesc.MinLOD = M_F_MIN_LOD; //beste Stufe
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX; //größtmöglichste Stufe

	m_pD3DDevice->CreateSamplerState( &samplerDesc, &m_pSamplerState );

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Freigeben
/*****************************************************************************/
void CTexture::Release()
{
	RELEASE_DELETE( m_pTexture );
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
void CTexture::Draw( UINT _startSlot )
{
	m_pD3DDevCon->PSSetShaderResources( _startSlot, M_I_NUM_VIEWS, 
										&m_pTexture );

	m_pD3DDevCon->PSSetSamplers( _startSlot, M_I_NUM_VIEWS, &m_pSamplerState );
}
/*****************************************************************************/