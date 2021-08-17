#include "RenderObject.h"
#include "../../General/Defines.h" 

/*****************************************************************************/
// Konstruktor
/*****************************************************************************/
CRenderObject::CRenderObject( ID3D11Device & _pD3DDevice,
							  ID3D11DeviceContext & _pD3DDevCon,
							  Transform _transform,
							  std::vector<Vertex> _vertVect,
							  std::vector<DWORD> _idxVect,
							  LPCSTR _vsPath,
							  LPCSTR _psPath,
							  LPCSTR _texPath, LPCSTR _normMapPath )
{
	m_pMesh		= new CMesh( _pD3DDevice, _pD3DDevCon, _transform,
							 _vertVect, _idxVect );

	m_pMaterial = new CMaterial( _pD3DDevice, _pD3DDevCon, _vsPath, _psPath, 
								 _texPath, _normMapPath );

	m_idxNumb = _idxVect.size();
}
/*****************************************************************************/

/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CRenderObject::Initialize()
{

	PROVE_RESULT( m_pMaterial->Initialize() );
	PROVE_RESULT( m_pMesh->Initialize() );
	PROVE_RESULT( m_pMaterial->CreateVertexLayout() );
	m_pMesh->SetPrimitiveTopology();
	PROVE_RESULT( m_pMaterial->CreateMatrixConstBuffer() );

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Freigabe
/*****************************************************************************/
void CRenderObject::Release()
{
	RELEASE_DELETE( m_pMesh );
	RELEASE_DELETE( m_pMaterial );
}
/*****************************************************************************/

/*****************************************************************************/
// Update
/*****************************************************************************/
int CRenderObject::Update( const double _deltaTime )
{
	m_pMesh->Update( _deltaTime );

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
/*****************************************************************************/
void CRenderObject::Draw( const XMMATRIX& _viewMatrix, 
						  const XMMATRIX& _projectionMatrix, 
						  const XMVECTOR& _camPos )
{
	m_pMesh->Draw();

	m_pMaterial->Draw( m_pMesh->GetWorldMatrix(), _viewMatrix, 
					   _projectionMatrix, _camPos, m_idxNumb );
}
/*****************************************************************************/