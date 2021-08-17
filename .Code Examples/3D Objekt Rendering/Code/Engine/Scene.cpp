#include "Scene.h"
#include "../../Code/General/Defines.h"

/*****************************************************************************/
// Konstruktor
/*****************************************************************************/
CScene::CScene(IVector2 _size, CEngine& _engine)
{
	m_pCamera = new CCamera(_size);
	m_pDirectionalLight = new CLight( *_engine.GetDevice(), 
									  *_engine.GetDevCon(), 
									  XMFLOAT3( 0.2f, 0.5, 1.0f ), 
									  XMFLOAT4( 0.1f, 0.1f, 0.1f, 1.0f ), 
									  XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f ) );


	float objSize = 0.5;

	std::vector<Vertex> cubeVertVect = 
	{ 
		/* Werte nach Würfel aus Stephan Jacobs Render-API, 
		   um Tangente und Binormale erweitert*/
		/*-------------------------------------------------------------------*/
		// Frontal Face
		/*-------------------------------------------------------------------*/
		Vertex( -1.0f, -1.0f, -1.0f, 	   // Position
				 1.0f,  1.0f,  1.0f, 1.0f, // Farbe
				 0.0f,  1.0f,			   // UV
				 0.0f,	0.0f, -1.0f,	   // Normal
				 1.0f,  0.0f,  0.0f,	   // Tangente
				 0.0f,  1.0f,  0.0f ),	   // Binormale

		Vertex( -1.0f,  1.0f, -1.0f,  	   // Position
				 1.0f,  1.0f,  1.0f, 1.0f, // Farbe
				 0.0f,  0.0f,  			   // UV
				 0.0f,	0.0f, -1.0f,  	   // Normal
				 1.0f,  0.0f,  0.0f,	   // Tangente
				 0.0f,  1.0f,  0.0f ),	   // Binormale

		Vertex(  1.0f,  1.0f, -1.0f,  	   // Position
				 1.0f,  1.0f,  1.0f, 1.0f, // Farbe
				 1.0f,  0.0f,			   // UV
				 0.0f,  0.0f, -1.0f,	   // Normal
				 1.0f,  0.0f,  0.0f,	   // Tangente
				 0.0f,  1.0f,  0.0f ),	   // Binormale

		Vertex(  1.0f, -1.0f, -1.0f,  	   // Position
				 1.0f,  1.0f,  1.0f, 1.0f, // Farbe
				 1.0f,  1.0f,			   // UV
				 0.0f,  0.0f, -1.0f,	   // Normal
				 1.0f,  0.0f,  0.0f,	   // Tangente
				 0.0f,  1.0f,  0.0f),	   // Binormale 
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Back Face
		/*-------------------------------------------------------------------*/
		Vertex( -1.0f, -1.0f,  1.0f,  	    // Position
				 1.0f,  1.0f,  1.0f,  1.0f, // Farbe		
				 1.0f,  1.0f,  			    // UV
				 0.0f,  0.0f,  1.0f,	    // Normal
				-1.0f,  0.0f,  0.0f,	    // Tangente
				 0.0f, -1.0f,  0.0f),	    // Binormale 

		Vertex(  1.0f, -1.0f,  1.0f,        // Position
				 1.0f,  1.0f,  1.0f,  1.0f, // Farbe				 
				 0.0f,  1.0f,  			    // UV
				 0.0f,  0.0f,  1.0f,	    // Normal
				-1.0f,  0.0f,  0.0f,	    // Tangente
				 0.0f, -1.0f,  0.0f ),	    // Binormale 

		Vertex( 1.0f,  1.0f,   1.0f,  	    // Position
				1.0f,  1.0f,   1.0f,  1.0f, // Farbe	
				0.0f,  0.0f,   			    // UV
				0.0f,  0.0f,   1.0f,		// Normal
			   -1.0f,  0.0f,   0.0f,		// Tangente
				0.0f, -1.0f,   0.0f ),	    // Binormale 
							   
		Vertex( -1.0f,  1.0f,  1.0f,  	 	// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 
				 1.0f,  0.0f,  				// UV
				 0.0f,  0.0f,  1.0f,		// Normal
				-1.0f,  0.0f,  0.0f,		// Tangente
				 0.0f, -1.0f,  0.0f ),		// Binormale 
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Top Face
		/*-------------------------------------------------------------------*/
		Vertex( -1.0f,  1.0f, -1.0f,   	    // Position
				 1.0f,  1.0f,  1.0f,  1.0f, // Farbe	 
				 0.0f,  1.0f,  			    // UV
				 0.0f,  1.0f,  0.0f,	    // Normal
				 1.0f,  0.0f,  0.0f,	    // Tangente
				 0.0f,  0.0f,  1.0f),	    // Binormale

		Vertex( -1.0f,  1.0f,  1.0f, 	 	// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 
				 0.0f,  0.0f,  				// UV
				 0.0f,  1.0f,  0.0f,		// Normal
				 1.0f,  0.0f,  0.0f,		// Tangente
				 0.0f,  0.0f,  1.0f ),		// Binormale 

		Vertex(  1.0f,  1.0f,  1.0f,  	    // Position
				 1.0f,  1.0f,  1.0f,  1.0f, // Farbe	 
				 1.0f,  0.0f,  			    // UV
				 0.0f,  1.0f,  0.0f,	    // Normal
				 1.0f,  0.0f,  0.0f,	    // Tangente
				 0.0f,  0.0f,  1.0f ),	    // Binormale 

		Vertex(  1.0f,  1.0f, -1.0f,  		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 
				 1.0f,  1.0f,  0.0f,		// UV
				 1.0f,  0.0f,  				// Normal
				 1.0f,  0.0f,  0.0f,		// Tangente
				 0.0f,  0.0f,  1.0f),		// Binormale 
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Bottom Face
		/*-------------------------------------------------------------------*/
		Vertex( -1.0f, -1.0f, -1.0f,  	    // Position
				 1.0f,  1.0f,  1.0f,  1.0f, // Farbe	 
				 1.0f,  1.0f,  			    // UV
				 0.0f, -1.0f,  0.0f,	    // Normal
				-1.0f,  0.0f,  0.0f,	    // Tangente
				 0.0f,  0.0f, -1.0f		    // Binormale 
		),
		Vertex(  1.0f, -1.0f, -1.0f, 	    // Position
				 1.0f,  1.0f,  1.0f,  1.0f, // Farbe	 
				 0.0f,  1.0f,  			    // UV
				 0.0f, -1.0f,  0.0f,	    // Normal
				-1.0f,  0.0f,  0.0f,	    // Tangente
				 0.0f,  0.0f, -1.0f ),	    // Binormale 
		
		Vertex(  1.0f, -1.0f,  1.0f, 		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 
				 0.0f,  0.0f,  				// UV
				 0.0f, -1.0f,  0.0f,		// Normal
				-1.0f,  0.0f,  0.0f,		// Tangente
				 0.0f,  0.0f, -1.0f ),		// Binormale 
		
		Vertex( -1.0f, -1.0f,  1.0f,  	 	// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 
				 1.0f,  0.0f,  				// UV
				 0.0f, -1.0f,  0.0f,		// Normal
				-1.0f,  0.0f,  0.0f,		// Tangente
				 0.0f,  0.0f, -1.0f ),		// Binormale 
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Left Face
		/*-------------------------------------------------------------------*/
		Vertex( -1.0f, -1.0f,  1.0f,  		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 	
				 0.0f,  1.0f,  				// UV
				-1.0f,  0.0f,  0.0f,		// Normal
				 0.0f,  0.0f, -1.0f,		// Tangente
				 0.0f,  1.0f,  0.0f ),		// Binormale

		Vertex( -1.0f,  1.0f,  1.0f,  		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 
				 0.0f,  0.0f,  				// UV
				-1.0f,  0.0f,  0.0f,		// Normal
				 0.0f,  0.0f, -1.0f,		// Tangente
				 0.0f,  1.0f,  0.0f ),		// Binormale 

		Vertex( -1.0f,  1.0f, -1.0f,  		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 	
				 1.0f,  0.0f,				// UV
				-1.0f,  0, 0,				// Normal
				 0.0f,  0.0f, -1.0f,		// Tangente
				 0.0f,  1.0f,  0.0f ),		// Binormale 

		Vertex( -1.0f, -1.0f, -1.0f,  		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 	
				 1.0f,  1.0f,  				// UV
				-1.0f,  0.0f,  0.0f,		// Normal
				 0.0f,  0.0f, -1.0f,		// Tangente
				 0.0f,  1.0f,  0.0f ),		// Binormale 
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Right Face
		/*-------------------------------------------------------------------*/
		Vertex(  1.0f, -1.0f, -1.0f,  	    // Position
				 1.0f,  1.0f,  1.0f,  1.0f, // Farbe	 	
				 0.0f,  1.0f,  			    // UV
				 1.0f,  0.0f,  0.0f,	    // Normal
				 0.0f,  0.0f,  1.0f,	    // Tangente
				 0.0f, -1.0f,  0.0f ),	    // Binormale 
		
		Vertex(  1.0f,  1.0f, -1.0f,  		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 	
				 0.0f,  0.0f,  				// UV
				 1.0f,  0.0f,  0.0f,		// Normal
				 0.0f,  0.0f,  1.0f,		// Tangente
				 0.0f, -1.0f,  0.0f ),		// Binormale 

		Vertex(  1.0f,  1.0f,  1.0f,  		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 	
				 1.0f,  0.0f,  				// UV
				 1.0f,  0.0f,  0.0f,		// Normal
				 0.0f,  0.0f,  1.0f,		// Tangente
				 0.0f, -1.0f,  0.0f ),		// Binormale 

		Vertex(  1.0f, -1.0f,  1.0f,  		// Position
				 1.0f,  1.0f,  1.0f,  1.0f,	// Farbe	 	
				 1.0f,  1.0f,  				// UV
				 1.0f,  0.0f,  0.0f,		// Normal
				 0.0f,  0.0f,  1.0f,		// Tangente
				 0.0f, -1.0f,  0.0f )		// Binormale 
		/*-------------------------------------------------------------------*/
	};

	std::vector<DWORD> cubeIdxVect = 
	{//Werte nach Würfel aus Stephan Jacobs Render-API
		/*-------------------------------------------------------------------*/
		// Front Face
		/*-------------------------------------------------------------------*/
		0,  1,  2,
		0,  2,  3,
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Back Face
		/*-------------------------------------------------------------------*/
		4,  5,  6,
		4,  6,  7,
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Top Face
		/*-------------------------------------------------------------------*/
		8,  9, 10,
		8, 10, 11,
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Bottom Face
		/*-------------------------------------------------------------------*/
		12, 13, 14,
		12, 14, 15,
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Left Face
		/*-------------------------------------------------------------------*/
		16, 17, 18,
		16, 18, 19,
		/*-------------------------------------------------------------------*/

		/*-------------------------------------------------------------------*/
		// Right Face
		/*-------------------------------------------------------------------*/
		20, 21, 22,
		20, 22, 23
		/*-------------------------------------------------------------------*/
	};

	/*-----------------------------------------------------------------------*/
	// Mittlerer Würfel (Matter Shader)
	/*-----------------------------------------------------------------------*/
	m_pRenderVect.push_back( new CRenderObject( 
									  *_engine.GetDevice(),
									  *_engine.GetDevCon(),
											
									  Transform( WFVector3( 0.0f, 0.0f, 2.0f ),
							 WFVector3::ZeroVector(),
							 WFVector3::OneVector()),
							 
							 //Vertices
							 cubeVertVect,
							 
							 //Indices
							 cubeIdxVect,
							 "Shader/MatteVertexShader.hlsl",
							 "Shader/MattePixelShader.hlsl",
							 "Assets/MattTexture_256x256_f1.png" ) );
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Rechter Würfel (spiegelnder Shader)
	/*-----------------------------------------------------------------------*/
	m_pRenderVect.push_back( new CRenderObject(
									  *_engine.GetDevice(),
									  *_engine.GetDevCon(),
									  Transform( WFVector3( 2.5f, 0.0f, 2.0f ),
									  WFVector3::ZeroVector(),
									  WFVector3::OneVector() ),

							 //Vertices
							 cubeVertVect,
							 
							 //Indices
							 cubeIdxVect,
							 "Shader/GlossyVertexShader.hlsl",
							 "Shader/GlossyPixelShader.hlsl",
							 "Assets/GlossyTexture_607x607_f1.png" ) );
	/*-----------------------------------------------------------------------*/

	/*-----------------------------------------------------------------------*/
	// Linker Würfel (rauer Shader)
	/*-----------------------------------------------------------------------*/
	m_pRenderVect.push_back( new CRenderObject( 
									 *_engine.GetDevice(),
									 *_engine.GetDevCon(),
									 Transform( WFVector3( -2.5f, 0.0f, 2.0f ),
									 WFVector3::ZeroVector(),
									 WFVector3::OneVector() ),
									 
							//Vertices
							cubeVertVect,
							
							//Indices
							cubeIdxVect,
							"Shader/RoughVertexShader.hlsl",
							"Shader/RoughPixelShader.hlsl",
							"Assets/RoughTexture_256x256_f1.png", 
							"Assets/RoughNormalMap_256x256_f1.png" ) );
	/*-----------------------------------------------------------------------*/
}
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CScene::Initialize()
{
	PROVE_RESULT( m_pDirectionalLight->Initialize() );

	for( CRenderObject* renderObj : m_pRenderVect ) 
	{
		PROVE_RESULT( renderObj->Initialize() );
	}

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Freigeben
/*****************************************************************************/
void CScene::Release()
{
	for( CRenderObject* renderObj : m_pRenderVect )
	{
		RELEASE_DELETE( renderObj );
	}
	RELEASE_DELETE( m_pDirectionalLight );
}
/*****************************************************************************/

/*****************************************************************************/
// Updaten
/*****************************************************************************/
int CScene::Update( CEngine& _engine )
{
	m_pCamera->ResetCamera( _engine.GetCameraReset() );

	m_pCamera->AddPosition( XMVectorSet( _engine.GetCameraPosition().x, 
										 _engine.GetCameraPosition().y, 
										 _engine.GetCameraPosition().z, 
										 M_F_DEFAULT_CAM_W) );

	m_pCamera->AddForward( XMVectorSet( _engine.GetCameraForward().x, 
										_engine.GetCameraForward().y, 
										_engine.GetCameraForward().z, 
										M_F_DEFAULT_CAM_W ) );

	m_pCamera->UpdateMatrices( _engine.GetWindowSize() );


	for( CRenderObject* renderObj : m_pRenderVect )
	{
		PROVE_RESULT( renderObj->Update( _engine.GetDeltaTime() ) );
	}


	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
/*****************************************************************************/
void CScene::Draw()
{
	for( CRenderObject* renderObj : m_pRenderVect )
	{
		renderObj->Draw( m_pCamera->GetViewMatrix(), 
						 m_pCamera->GetProjectionMatrix(), 
						 m_pCamera->GetCameraPosition());
	}

	m_pDirectionalLight->Draw();
}
/*****************************************************************************/
/*****************************************************************************/