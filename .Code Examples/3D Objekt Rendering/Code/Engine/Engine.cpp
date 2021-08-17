#include "Engine.h"
#include "../../Code/General/Defines.h"

/*****************************************************************************/
// Konstruktor
/*****************************************************************************/
CEngine::CEngine()
{
	m_pMainWindow	= new CWindow();
	m_pDirect3D		= new CDirect3D();
	m_pDirectInput	= new CDirectInput();
	m_pTime			= new CTime();
}
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CEngine::Initialize( HINSTANCE _hInstance, IVector2 _size, 
						 int _nCmdShow, const char* _name )
{
	PROVE_RESULT( m_pMainWindow->Initialize( _hInstance, _size, 
											 _nCmdShow, _name ) );

	PROVE_RESULT( m_pDirect3D->Initialize( _hInstance, 
										   m_pMainWindow->GetHWND(), 
										   _size ) );

	PROVE_RESULT( m_pDirectInput->Initialize( _hInstance, 
											  m_pMainWindow->GetHWND() ) );

	m_pRasterizer = new CRasterizerStage( *m_pDirect3D->GetDevice(), 
										  *m_pDirect3D->GetDevCon() );
	PROVE_RESULT( m_pRasterizer->Initialize() );

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Finalisieren
/*****************************************************************************/
void CEngine::Finalize()
{
	RELEASE_DELETE(  m_pRasterizer  );
	delete m_pTime;
	m_pTime = nullptr;
	RELEASE_DELETE(  m_pDirectInput );
	RELEASE_DELETE(  m_pDirect3D    );
	FINALIZE_DELETE( m_pMainWindow  );
}
/*****************************************************************************/

/*****************************************************************************/
// Programm läuft
/*****************************************************************************/
bool CEngine::Run()
{
	return m_pMainWindow->Run();
}
/*****************************************************************************/

/*****************************************************************************/
// Eingabe ermitteln
/*****************************************************************************/
int CEngine::DetectInput()
{
	return m_pDirectInput->DetectInput( m_pTime->GetDeltaTime() );
}
/*****************************************************************************/

/*****************************************************************************/
// Update
/*****************************************************************************/
int CEngine::Update()
{
	PROVE_RESULT( m_pTime->Update() );
	PROVE_RESULT( m_pDirectInput->DetectInput( m_pTime->GetDeltaTime() ) );

	m_pRasterizer->ChangeStage( m_pDirectInput->GetRasterState() );
	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Viewport leeren
/*****************************************************************************/
void CEngine::ClearView()
{
	m_pDirect3D->ClearView();
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
/*****************************************************************************/
void CEngine::Draw()
{
	m_pRasterizer->Draw();
	m_pDirect3D->Draw();
}
/*****************************************************************************/
/*************************************************************************/