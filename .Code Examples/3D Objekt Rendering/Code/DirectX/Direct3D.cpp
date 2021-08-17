#include "Direct3D.h"
#include "../General/Defines.h" //RELEASE_DELETE

/*****************************************************************************/
// Initialisierungen
/*****************************************************************************/
// Puffer-Beschreibung initialisieren
/*****************************************************************************/
DXGI_MODE_DESC CDirect3D::InitBufferDesc( IVector2 _size )
{
	DXGI_MODE_DESC bufferDesc; 
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );

	bufferDesc.Width				   = _size.x;
	bufferDesc.Height				   = _size.y;
	bufferDesc.RefreshRate.Numerator   = M_I_FRAMES; //Frames
	bufferDesc.RefreshRate.Denominator = M_I_SECONDS; //Per Seconds
	bufferDesc.Format				   = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering		   = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling				   = DXGI_MODE_SCALING_UNSPECIFIED;

	return bufferDesc;
}
/*****************************************************************************/

/*****************************************************************************/
// Swap-Chain Beschreibung initialisieren
/*****************************************************************************/
DXGI_SWAP_CHAIN_DESC CDirect3D::InitSwapChainDesc( HWND _hWnd, 
												   DXGI_MODE_DESC _bufferDesc )
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));


	//bufferDesc-Methode mit Rückgabe aufrufen
	swapChainDesc.BufferDesc = _bufferDesc;

	swapChainDesc.SampleDesc.Count   = M_I_SAMPLE_DESC_COUNT;

	swapChainDesc.SampleDesc.Quality = M_I_MAX_QUALITY; //höchste Qualität
	
	//auf Buffer soll gerendert werden
	swapChainDesc.BufferUsage		 = DXGI_USAGE_RENDER_TARGET_OUTPUT; 

	swapChainDesc.BufferCount		 = M_I_BUFFER_NUMBER;

	swapChainDesc.OutputWindow		 = _hWnd; //wird in Fenster angezeigt

	swapChainDesc.Windowed			 = TRUE; //kein Fullscreen

	//frontBuffer nach verwendung entfernen
	swapChainDesc.SwapEffect		 = DXGI_SWAP_EFFECT_DISCARD; 

	swapChainDesc.Flags				 = NULL; //nicht nötig


	return swapChainDesc;
}
/*****************************************************************************/

/*****************************************************************************/
// Tiefen-Stencil-Beschreibung initialisieren
/*****************************************************************************/
D3D11_TEXTURE2D_DESC CDirect3D::InitDepthStencilDesc(IVector2 _size)
{
	D3D11_TEXTURE2D_DESC depthStencilDesc;


	depthStencilDesc.Width				= _size.x;
	depthStencilDesc.Height				= _size.y;
	depthStencilDesc.MipLevels			= M_I_STENCIL_MIP_LEVEL;
	depthStencilDesc.ArraySize			= M_I_STENCIL_ARR_SIZE;
	depthStencilDesc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT; 
	depthStencilDesc.SampleDesc.Count	= M_I_STENCIL_DESC_COUNT;
	depthStencilDesc.SampleDesc.Quality = M_I_STENCIL_DESC_QUALITY;
	depthStencilDesc.Usage				= D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags			= D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags		= M_I_DEFAULT_FLAG;
	depthStencilDesc.MiscFlags			= M_I_DEFAULT_FLAG;


	return depthStencilDesc;
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CDirect3D::Initialize( HINSTANCE _hInstance, HWND _hWnd, IVector2 _size )
{
	HRESULT hr; 

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE; 

	//Swapchain erstellen
	hr = D3D11CreateDeviceAndSwapChain( NULL, driverType,
										NULL, NULL,
										NULL, NULL, D3D11_SDK_VERSION,  
										&InitSwapChainDesc(  _hWnd, 
													 InitBufferDesc( _size ) ),
										&m_pSwapChain, &m_pD3DDevice, NULL, 
										&m_pD3DDevCon );

	if( FAILED( hr ) ) return M_I_ERROR_DEVICE_OR_SWAPCHAIN_CREATION_FAILED;
	

	ID3D11Texture2D* backBuffer = nullptr;
	const UINT nullBuffer = 0;

	hr = m_pSwapChain->GetBuffer( nullBuffer, __uuidof( ID3D11Texture2D ),
								  reinterpret_cast<void**>( &backBuffer ) );

	if( FAILED( hr ) ) return M_I_ERROR_SWAPCHAIN_BUFFER_FAILED;


	hr = m_pD3DDevice->CreateRenderTargetView( backBuffer, NULL, 
											   &m_pRenderTargetView );

	if( FAILED( hr ) ) return M_I_ERROR_RENDER_TARGET_CREATION_FAILED;

	backBuffer->Release();


	hr = m_pD3DDevice->CreateTexture2D( &InitDepthStencilDesc( _size ), NULL, 
										&m_pDepthStencilBuffer );

	if( FAILED( hr ) ) return M_I_ERROR_STENCIL_BUFFER_CREATION_FAILED;


	hr = m_pD3DDevice->CreateDepthStencilView( m_pDepthStencilBuffer, NULL,
											  &m_pDepthStencilView );

	if( FAILED( hr ) ) return M_I_ERROR_STENCIL_VIEW_CREATION_FAILED;


	m_pD3DDevCon->OMSetRenderTargets( M_I_NUM_VIEWS, &m_pRenderTargetView,
									  m_pDepthStencilView );


	ZeroMemory(&m_viewport, sizeof(m_viewport));

	m_viewport.Width = _size.x;
	m_viewport.Height = _size.y;
	m_viewport.TopLeftX = M_F_VIEW_TOP_LEFT;
	m_viewport.TopLeftY = M_F_VIEW_TOP_LEFT;

	//Scale
	m_viewport.MinDepth = M_F_VIEW_MIN_DEPTH; //normalisierte minimale Tiefe
	m_viewport.MaxDepth = M_F_VIEW_MAX_DEPTH; //normalisierte maximale Tiefe

	m_pD3DDevCon->RSSetViewports( M_I_NUM_VIEWS, &m_viewport );

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Freigeben
/*****************************************************************************/
void CDirect3D::Release()
{
	RELEASE_DELETE( m_pDepthStencilView );
	RELEASE_DELETE( m_pDepthStencilBuffer );
	RELEASE_DELETE( m_pRenderTargetView );
	RELEASE_DELETE( m_pD3DDevCon );
	RELEASE_DELETE( m_pD3DDevice );
	RELEASE_DELETE( m_pSwapChain );
}
/*****************************************************************************/

/*****************************************************************************/
// Viewport leeren
/*****************************************************************************/
void CDirect3D::ClearView()
{
	m_pD3DDevCon->ClearRenderTargetView( m_pRenderTargetView, backgroundColor );

	m_pD3DDevCon->ClearDepthStencilView( m_pDepthStencilView, 
										   D3D11_CLEAR_DEPTH 
										 | D3D11_CLEAR_STENCIL, 
										 M_I_CLEAR_DEPTH, M_I_CLEAR_STENCIL );
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
/*****************************************************************************/
void CDirect3D::Draw()
{
	m_pSwapChain->Present(M_I_SYNC_INTERVAL, M_I_DEFAULT_FLAG);
}
/*****************************************************************************/
/*****************************************************************************/