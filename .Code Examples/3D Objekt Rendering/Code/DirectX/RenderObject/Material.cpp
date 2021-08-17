#include "Material.h"
#include "../../General/Defines.h" //RELEASE_DELETE
#include "Windows.h"
#include <iostream>
#include <vector>


/*****************************************************************************/
// Konstruktor/Destruktor
/*****************************************************************************/
// Konstruktor
/*****************************************************************************/
CMaterial::CMaterial( ID3D11Device & _pD3DDevice, 
					  ID3D11DeviceContext & _pD3DDevCon, 
					  LPCSTR _vsPath, LPCSTR _psPath, 
					  LPCSTR _texPath, LPCSTR _normMapPath )
{
	//DirectX
	m_pD3DDevice = &_pD3DDevice;
	m_pD3DDevCon = &_pD3DDevCon;

	//Shader
	m_sVertexShaderPath = _vsPath;
	m_sPixelShaderPath = _psPath;

	//Textur
	m_pTexture = new CTexture( _pD3DDevice, _pD3DDevCon, _texPath );

	//Wenn NormalMap existiert
	if( _normMapPath != "" )
	{
		m_pNormalMap = new CTexture( _pD3DDevice, _pD3DDevCon, _normMapPath );
		m_pNormalMapExists = true;
	}
}
/*****************************************************************************/

/*****************************************************************************/
//Destrutor
/*****************************************************************************/
CMaterial::~CMaterial()
{
	//Wenn Normalmap Existiert
	if( m_pNormalMapExists )
	{
		RELEASE_DELETE( m_pNormalMap );
	}
	RELEASE_DELETE( m_pTexture );

	m_sPixelShaderPath  = "";
	m_sVertexShaderPath = "";

	RELEASE_DELETE( m_pD3DDevCon );
	RELEASE_DELETE( m_pD3DDevice );
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Shader erstellen
/*****************************************************************************/
//Shader kompilieren
/*****************************************************************************/
int CMaterial::CompileShader()
{
	D3DX11CompileFromFile( m_sVertexShaderPath, 0, 0, 
						   M_S_SHADER_MAIN, M_S_VERTEX_SHADER,
						   0, 0, 0, &m_pVertexShaderBuffer, 0, &hr );

	if( FAILED( hr ) ) return M_I_ERROR_COMPILE_VS_BUFFER_FAILED;


	D3DX11CompileFromFile( m_sPixelShaderPath, 0, 0, 
						   M_S_SHADER_MAIN, M_S_PIXEL_SHADER,
						   0, 0, 0, &m_pPixelShaderBuffer, 0, &hr );

	if( FAILED( hr ) ) return M_I_ERROR_COMPILE_PS_BUFFER_FAILED;


	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// ShaderObjekte erstellen
/*****************************************************************************/
int CMaterial::CreateShaderObjects()
{
	/*-----------------------------------------------------------------------*/
	//VertexShader
	/*-----------------------------------------------------------------------*/
	hr = m_pD3DDevice->CreateVertexShader(
									m_pVertexShaderBuffer->GetBufferPointer(),
									m_pVertexShaderBuffer->GetBufferSize(),
									NULL, &m_pVertexShader );

	if( FAILED( hr ) ) return M_I_VERTEX_SHADER_CREATION_FAILED;
	/*-----------------------------------------------------------------------*/


	/*-----------------------------------------------------------------------*/
	//PixelShader
	/*-----------------------------------------------------------------------*/
	hr = m_pD3DDevice->CreatePixelShader(
									m_pPixelShaderBuffer->GetBufferPointer(),
									m_pPixelShaderBuffer->GetBufferSize(),
									NULL, &m_pPixelShader );

	if( FAILED( hr ) ) return M_I_PIXEL_SHADER_CREATION_FAILED;
	/*-----------------------------------------------------------------------*/

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
//Shader setzen
/*****************************************************************************/
void CMaterial::SetShader()
{
	m_pD3DDevCon->VSSetShader( m_pVertexShader, nullptr, 0 );
	m_pD3DDevCon->PSSetShader( m_pPixelShader, nullptr, 0 );
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Initialisierungen
/*****************************************************************************/
// Layout-Positionsaufbau erstellen
/*****************************************************************************/
D3D11_INPUT_ELEMENT_DESC CMaterial::CreateLayoutPos( UINT _offset ) const
{
	D3D11_INPUT_ELEMENT_DESC m_layoutPos;

	m_layoutPos.SemanticName		 = M_S_POS_NAME;
	m_layoutPos.SemanticIndex		 = M_I_DEFAULT_SEMANTIC_IDX;
	m_layoutPos.Format				 = DXGI_FORMAT_R32G32B32_FLOAT;
	m_layoutPos.InputSlot			 = M_I_DEFAULT_INPUT_SLOT;
	m_layoutPos.AlignedByteOffset	 = _offset;
	m_layoutPos.InputSlotClass		 = D3D11_INPUT_PER_VERTEX_DATA;
	m_layoutPos.InstanceDataStepRate = M_I_DEFAULT_DATA_STEP_RATE;

	return m_layoutPos;
}
/*****************************************************************************/

/*****************************************************************************/
// Layout-Farbaufbau erstellen
/*****************************************************************************/
D3D11_INPUT_ELEMENT_DESC CMaterial::CreateLayoutColor( UINT _offset ) const
{
	D3D11_INPUT_ELEMENT_DESC m_layoutColor;

	m_layoutColor.SemanticName			= M_S_COLOR_NAME;
	m_layoutColor.SemanticIndex			= M_I_DEFAULT_SEMANTIC_IDX;
	m_layoutColor.Format				= DXGI_FORMAT_R32G32B32A32_FLOAT;
	m_layoutColor.InputSlot				= M_I_DEFAULT_INPUT_SLOT;
	m_layoutColor.AlignedByteOffset		= _offset + M_I_COLOR_OFFSET;
	m_layoutColor.InputSlotClass		= D3D11_INPUT_PER_VERTEX_DATA;
	m_layoutColor.InstanceDataStepRate	= M_I_DEFAULT_DATA_STEP_RATE;

	return m_layoutColor;
}
/*****************************************************************************/

/*****************************************************************************/
// Layout-Textur-Koordinatenaufbau erstellen
/*****************************************************************************/
D3D11_INPUT_ELEMENT_DESC CMaterial::CreateLayoutTexCoord( UINT _offset ) const
{
	D3D11_INPUT_ELEMENT_DESC m_layoutTexCoord;

	m_layoutTexCoord.SemanticName		  = M_S_TEX_COORD_NAME;
	m_layoutTexCoord.SemanticIndex		  = M_I_DEFAULT_SEMANTIC_IDX;
	m_layoutTexCoord.Format				  = DXGI_FORMAT_R32G32_FLOAT;
	m_layoutTexCoord.InputSlot			  = M_I_DEFAULT_INPUT_SLOT;
	m_layoutTexCoord.AlignedByteOffset	  = _offset + M_I_TEX_COORD_OFFSET;
	m_layoutTexCoord.InputSlotClass		  = D3D11_INPUT_PER_VERTEX_DATA;
	m_layoutTexCoord.InstanceDataStepRate = M_I_DEFAULT_DATA_STEP_RATE;

	return m_layoutTexCoord;
}
/*****************************************************************************/

/*****************************************************************************/
// Layout-Normalenaufbau erstellen
/*****************************************************************************/
D3D11_INPUT_ELEMENT_DESC CMaterial::CreateLayoutNorm( UINT _offset ) const
{
	D3D11_INPUT_ELEMENT_DESC m_layoutNorm;

	m_layoutNorm.SemanticName		  = M_S_NORM_NAME;
	m_layoutNorm.SemanticIndex		  = M_I_DEFAULT_SEMANTIC_IDX;
	m_layoutNorm.Format				  = DXGI_FORMAT_R32G32B32_FLOAT;
	m_layoutNorm.InputSlot			  = M_I_DEFAULT_INPUT_SLOT;
	m_layoutNorm.AlignedByteOffset	  = _offset + M_I_NORM_OFFSET;
	m_layoutNorm.InputSlotClass		  = D3D11_INPUT_PER_VERTEX_DATA;
	m_layoutNorm.InstanceDataStepRate = M_I_DEFAULT_DATA_STEP_RATE;

	return m_layoutNorm;
}
/*****************************************************************************/

/*****************************************************************************/
// Layout-Tangentenaufbau erstellen
/*****************************************************************************/
D3D11_INPUT_ELEMENT_DESC CMaterial::CreateLayoutTan( UINT _offset ) const
{
	D3D11_INPUT_ELEMENT_DESC m_layoutTan;

	m_layoutTan.SemanticName		 = M_S_TAN_NAME;
	m_layoutTan.SemanticIndex		 = M_I_DEFAULT_SEMANTIC_IDX;
	m_layoutTan.Format				 = DXGI_FORMAT_R32G32B32_FLOAT;
	m_layoutTan.InputSlot			 = M_I_DEFAULT_INPUT_SLOT;
	m_layoutTan.AlignedByteOffset	 = _offset + M_I_TAN_OFFSET;
	m_layoutTan.InputSlotClass		 = D3D11_INPUT_PER_VERTEX_DATA;
	m_layoutTan.InstanceDataStepRate = M_I_DEFAULT_DATA_STEP_RATE;

	return m_layoutTan;
}
/*****************************************************************************/

/*****************************************************************************/
// Layout-Binormalenaufbau erstellen
/*****************************************************************************/
D3D11_INPUT_ELEMENT_DESC CMaterial::CreateLayoutBinorm( UINT _offset ) const
{
	D3D11_INPUT_ELEMENT_DESC m_layoutBinorm;

	m_layoutBinorm.SemanticName			= M_S_BINORM_NAME;
	m_layoutBinorm.SemanticIndex		= M_I_DEFAULT_SEMANTIC_IDX;
	m_layoutBinorm.Format				= DXGI_FORMAT_R32G32B32_FLOAT;
	m_layoutBinorm.InputSlot			= M_I_DEFAULT_INPUT_SLOT;
	m_layoutBinorm.AlignedByteOffset	= _offset + M_I_BINORM_OFFSET;
	m_layoutBinorm.InputSlotClass		= D3D11_INPUT_PER_VERTEX_DATA;
	m_layoutBinorm.InstanceDataStepRate = M_I_DEFAULT_DATA_STEP_RATE;

	return m_layoutBinorm;
}
/*****************************************************************************/

/*****************************************************************************/
// Layout-Array erstellen
/*****************************************************************************/
void CMaterial::CreateLayoutArr( D3D11_INPUT_ELEMENT_DESC* _layoutArr ) 
{
	if (_layoutArr == nullptr) return; // Sicherheitsabfrage

	//Position
	_layoutArr[0] = CreateLayoutPos();

	//Farbe
	_layoutArr[1] = CreateLayoutColor( _layoutArr[0].AlignedByteOffset );

	//Textur-Koordinate
	_layoutArr[2] = CreateLayoutTexCoord( _layoutArr[1].AlignedByteOffset );

	//Normale
	_layoutArr[3] = CreateLayoutNorm( _layoutArr[2].AlignedByteOffset );

	//Tangente
	_layoutArr[4] = CreateLayoutTan( _layoutArr[3].AlignedByteOffset );

	//Binormale
	_layoutArr[5] = CreateLayoutBinorm( _layoutArr[4].AlignedByteOffset );
}
/*****************************************************************************/

/*****************************************************************************/
// Vertex-Layout erstellen
/*****************************************************************************/
int CMaterial::CreateVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC m_layoutArr[6] = {};
	CreateLayoutArr(m_layoutArr);


	UINT m_iArrSize = ARRAYSIZE( m_layoutArr );

	hr = m_pD3DDevice->CreateInputLayout( m_layoutArr, m_iArrSize,
									m_pVertexShaderBuffer->GetBufferPointer(), 
									m_pVertexShaderBuffer->GetBufferSize(), 
										  &m_pVertexLayout );
	if( FAILED( hr ) ) return M_I_INPUT_LAYOUT_CREATION_FAILED;

	m_pD3DDevCon->IASetInputLayout( m_pVertexLayout );

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Matrix-ConstantBuffer erstellen
/*****************************************************************************/
int CMaterial::CreateMatrixConstBuffer()
{
	D3D11_BUFFER_DESC constBufDesc;

	constBufDesc.ByteWidth			 = sizeof(ObjMatrixCB);
	constBufDesc.Usage				 = D3D11_USAGE_DEFAULT;
	constBufDesc.BindFlags			 = D3D11_BIND_CONSTANT_BUFFER;
	constBufDesc.CPUAccessFlags		 = M_I_DEFAULT_FLAG;
	constBufDesc.MiscFlags			 = M_I_DEFAULT_FLAG;
	constBufDesc.StructureByteStride = M_I_DEFAULT_STRIDE;

	m_pD3DDevice->CreateBuffer( &constBufDesc, NULL, &m_pLightConstBuffer );

	return M_I_SUCCESS;
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialize
/*****************************************************************************/
int CMaterial::Initialize()
{
	//Shader kompilieren
	PROVE_RESULT( CompileShader() );

	//Shader-Objekte erstellen
	PROVE_RESULT( CreateShaderObjects() );

	//Shader setzen
	SetShader();

	PROVE_RESULT( m_pTexture->Initialize() );
	if( m_pNormalMapExists ) { PROVE_RESULT(m_pNormalMap->Initialize()); }

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Freigabe
/*****************************************************************************/
void CMaterial::Release()
{
	RELEASE_DELETE( m_pLightConstBuffer	  );
	RELEASE_DELETE( m_pPixelShader		  );
	RELEASE_DELETE( m_pVertexShader       );
	RELEASE_DELETE( m_pPixelShaderBuffer  );
	RELEASE_DELETE( m_pVertexShaderBuffer );
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
/*****************************************************************************/
void CMaterial::Draw( XMMATRIX _worldMatrix, XMMATRIX _viewMatrix, 
					  XMMATRIX _projectionMatrix, XMVECTOR _camPos, 
					  UINT _idxNumb )
{
	m_pD3DDevCon->IASetInputLayout( m_pVertexLayout );
	SetShader();

	m_WVPMatrix = _worldMatrix * _viewMatrix * _projectionMatrix;

	m_matrixCB.wvpMatrix = TransposeMatrix( m_WVPMatrix );
	m_matrixCB.worldMatrix = TransposeMatrix( _worldMatrix );
	m_matrixCB.cameraPosition = _camPos;

	m_pD3DDevCon->UpdateSubresource( m_pLightConstBuffer, 
									 M_I_DEFAULT_SUBRESOURCE, NULL, 
									 &m_matrixCB, M_I_DEFAULT_SRC_DATA, 
									 M_I_DEFAULT_SRC_ROW_PITCH );

	m_pD3DDevCon->VSSetConstantBuffers( M_I_DEFAULT_START_SLOT, M_I_NUM_BUF, 
										&m_pLightConstBuffer );

	m_pTexture->Draw( M_I_DEFAULT_START_SLOT );

	if( m_pNormalMapExists ) //wenn NormalmapExistiert
	{
		m_pNormalMap->Draw( M_I_NORM_MAP_START_SLOT );
	}

	m_pD3DDevCon->DrawIndexed( _idxNumb, StartIdxLoca, vertBufLoca ); 
}
/*****************************************************************************/
/*****************************************************************************/
