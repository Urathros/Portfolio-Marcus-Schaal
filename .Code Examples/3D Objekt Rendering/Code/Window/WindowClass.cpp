#include "WindowClass.h"

/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CWindowClass::Initialize( HINSTANCE _hInstance, const char* _name, 
							  WNDPROC _wndProc)
{
	if( _name == nullptr ) return M_I_ERROR_NULLPTR_NAME;

	m_pWndClassName = _name; 
	m_hInstance = _hInstance;

	//1. describe window class (erstellt Fensterklasse mit eigenschaften)
	m_wndClassEx.cbSize = sizeof( m_wndClassEx );
	m_wndClassEx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	m_wndClassEx.lpfnWndProc = _wndProc;
	m_wndClassEx.cbClsExtra = NULL;
	m_wndClassEx.cbWndExtra = NULL;
	m_wndClassEx.hInstance = m_hInstance;
	m_wndClassEx.hIcon = LoadIcon( NULL, IDI_ASTERISK );  
	m_wndClassEx.hCursor = LoadCursor( NULL, IDC_ARROW ); 
	m_wndClassEx.hbrBackground = reinterpret_cast<HBRUSH>( COLOR_WINDOW );
	m_wndClassEx.lpszMenuName = NULL;
	m_wndClassEx.lpszClassName = m_pWndClassName;  

	// 2. register window class
	if( !RegisterClassEx( &m_wndClassEx ) )
	{
		MessageBox( 0, M_S_REGISTER_ERROR, M_S_ERROR, MB_OK | MB_ICONERROR );
		return M_I_ERROR_MSG_FAILED;
	}
	else return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Finalisierung
/*****************************************************************************/
void CWindowClass::Finalize()
{
	UnregisterClass( m_pWndClassName, m_hInstance );

	m_hInstance = nullptr;
	m_pWndClassName = nullptr;
	m_wndClassEx = { };
}
/*****************************************************************************/