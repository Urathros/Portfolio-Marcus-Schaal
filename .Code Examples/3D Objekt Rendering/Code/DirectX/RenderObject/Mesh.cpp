#include "Mesh.h"
#include "../../General/Defines.h" //RELEASE_DELETE


/*****************************************************************************/
// Konstruktor/Destruktor
/*****************************************************************************/
// Konstruktor
/*****************************************************************************/
CMesh::CMesh( ID3D11Device & _pD3DDevice, ID3D11DeviceContext & _pD3DDevCon, 
			  Transform _transform, std::vector<Vertex> _vertVect, 
			  std::vector<DWORD> _idxVect )
{
	m_pD3DDevice	= &_pD3DDevice;
	m_pD3DDevCon	= &_pD3DDevCon;

	m_transform		= _transform;
	m_vertexVect	= _vertVect;
	m_indexVect		= _idxVect;
}
/*****************************************************************************/

/*****************************************************************************/
// Destruktor
/*****************************************************************************/
CMesh::~CMesh()
{
	m_indexVect		= {};
	m_vertexVect	= {};
	m_transform		= Transform::ZeroPRS();

	RELEASE_DELETE( m_pD3DDevCon );
	RELEASE_DELETE( m_pD3DDevice );
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Initialisierungen
/*****************************************************************************/
// Vertex-Puffer-Beschreibung initialisieren
/*****************************************************************************/
D3D11_BUFFER_DESC CMesh::InitVertBufDesc( UINT _iVertNum )
{
	UINT dataTypeSize = sizeof( Vertex );

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof( vertexBufferDesc ) );

	vertexBufferDesc.ByteWidth      = dataTypeSize * _iVertNum; //Puffer-Größe
	vertexBufferDesc.Usage          = D3D11_USAGE_DEFAULT; //Standard-Verwend.
	vertexBufferDesc.BindFlags      = D3D11_BIND_VERTEX_BUFFER; //VertexBuffer
	vertexBufferDesc.CPUAccessFlags = M_I_DEFAULT_FLAG;
	vertexBufferDesc.MiscFlags      = M_I_DEFAULT_FLAG;

	return vertexBufferDesc;
}
/*****************************************************************************/

/*****************************************************************************/
// Vertex-Puffer-Daten initialisieren
/*****************************************************************************/
D3D11_SUBRESOURCE_DATA CMesh::InitVertBufData( Vertex _vertexArr[] )
{
	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory( &vertexBufferData, sizeof( vertexBufferData ) );
	
	//Pointer der System Memory ist Vertex-Auflistung 
	vertexBufferData.pSysMem = _vertexArr; 

	return vertexBufferData;
}
/*****************************************************************************/

/*****************************************************************************/
// Vertex-Puffer initialisieren
/*****************************************************************************/
int CMesh::InitVertexBuffer()
{
	hr = m_pD3DDevice->CreateBuffer( &InitVertBufDesc( m_vertexVect.size() ), 
									 &InitVertBufData(
										const_cast<Vertex*>(
													 m_vertexVect.data() ) ), 
									 &m_pVertexBuffer );

	if( FAILED( hr ) ) return M_I_ERROR_VERTEX_BUFFER_CREATION_FAILED;

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Index-Puffer-Beschreibung initialisieren
/*****************************************************************************/
D3D11_BUFFER_DESC CMesh::InitIdxBufDesc( UINT _iIdxNumb )
{
	UINT dataTypeSize = sizeof( DWORD );

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof( indexBufferDesc ) );

	indexBufferDesc.ByteWidth	   = dataTypeSize * _iIdxNumb; //Puffer-Größe 
	indexBufferDesc.Usage		   = D3D11_USAGE_DEFAULT; //Standard-Verwendung
	indexBufferDesc.BindFlags	   = D3D11_BIND_INDEX_BUFFER; //IndexBuffer
	indexBufferDesc.CPUAccessFlags = M_I_DEFAULT_FLAG;
	indexBufferDesc.MiscFlags	   = M_I_DEFAULT_FLAG;

	return indexBufferDesc;
}
/*****************************************************************************/

/*****************************************************************************/
// Index-Puffer-Daten initialisieren
/*****************************************************************************/
D3D11_SUBRESOURCE_DATA CMesh::InitIdxBufData( DWORD _indexArr[] )
{
	D3D11_SUBRESOURCE_DATA indexBufferData;
	ZeroMemory( &indexBufferData, sizeof( indexBufferData ) );

	//Pointer der System Memory ist Vertex-Auflistung 
	indexBufferData.pSysMem = _indexArr; 

	return indexBufferData;
}
/*****************************************************************************/

/*****************************************************************************/
// Index-Puffer initialisieren
/*****************************************************************************/
int CMesh::InitIdxBuffer()
{
	hr = m_pD3DDevice->CreateBuffer( &InitIdxBufDesc( m_indexVect.size() ), 
									 &InitIdxBufData( 
										 const_cast<DWORD*>( 
														m_indexVect.data() ) ), 
									 &m_pIndexBuffer);

	if( FAILED( hr ) ) return M_I_ERROR_INDEX_BUFFER_CREATION_FAILED;

	return M_I_SUCCESS;
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CMesh::Initialize()
{
	PROVE_RESULT( InitVertexBuffer() );
	PROVE_RESULT( InitIdxBuffer()    );

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Freigabe
/*****************************************************************************/
void CMesh::Release()
{
	RELEASE_DELETE( m_pIndexBuffer  );
	RELEASE_DELETE( m_pVertexBuffer );
}
/*****************************************************************************/

/*****************************************************************************/
// Update
/*****************************************************************************/
int CMesh::Update( const double _deltaTime )  
{
	m_WorldMatrix = XMMatrixIdentity();

	m_translate = XMMatrixTranslation( m_transform.position.x, 
									   m_transform.position.y, 
									   m_transform.position.z );
	
	

	XMVECTOR quaternion = XMVectorSet( m_transform.rotation.x, 
									   m_transform.rotation.y, 
									   m_transform.rotation.z, 
									   M_F_TRANS_QUATER_W );

	m_rota = XMMatrixRotationQuaternion( quaternion );

	m_scale = XMMatrixScaling( m_transform.scale.x, 
							   m_transform.scale.y, 
							   m_transform.scale.z );

	m_WorldMatrix = MatrixMultiply( MatrixMultiply(m_scale, m_rota), 
									m_translate );

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
/*****************************************************************************/
void CMesh::Draw( UINT _offset )
{
	m_pD3DDevCon->IASetVertexBuffers( M_I_DEFAULT_START_SLOT, M_I_NUM_BUF, 
									  &m_pVertexBuffer, &vertexStride, 
									  &_offset );

	m_pD3DDevCon->IASetIndexBuffer( m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 
									_offset );
}
/*****************************************************************************/
/*****************************************************************************/