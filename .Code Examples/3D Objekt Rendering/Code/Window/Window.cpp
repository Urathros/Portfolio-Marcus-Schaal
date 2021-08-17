#include "Window.h"
#include "../../Code/General/Defines.h"

#pragma comment(lib, "winmm.lib")

const HWND I_DEFAULT_HWND = 0;
const int I_DEFAULT_QUIT_MSG = 0;
const int I_SUCCESS = 1;
const LPCSTR S_QUIT_MSG = "Programm beenden?";
const LPCSTR S_PROG_TITLE = "XtremeViewer";

/*****************************************************************************/
// Windows-Prozedur
/*****************************************************************************/
LRESULT CALLBACK WndProc( HWND _hWnd, UINT _msg, WPARAM _wParam, 
						  LPARAM _lParam )
{
	switch( _msg )
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage( I_DEFAULT_QUIT_MSG );
		return I_SUCCESS;

	//Tastaturinput
	case WM_KEYDOWN:
		if( _wParam == VK_ESCAPE )
		{
			int msgboxID = MessageBox( I_DEFAULT_HWND, S_QUIT_MSG,
									   S_PROG_TITLE,   MB_YESNO 
													 | MB_ICONQUESTION );

			if( msgboxID == IDYES )
			{
				PostQuitMessage( I_DEFAULT_QUIT_MSG );
				return I_SUCCESS;
			}
		}
		break;

	default:
		return DefWindowProc( _hWnd, _msg, _wParam, _lParam );
	}
}
/*****************************************************************************/





/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CWindow::Initialize( HINSTANCE _hInstance, IVector2 _size, int _nCmdShow, 
						 const char* _name )
{
	if( _name == nullptr ) return M_I_ERROR_NULLPTR_NAME;

	int result = M_I_SUCCESS;

	m_pWndClass = new CWindowClass();
	result = m_pWndClass->Initialize( _hInstance, _name, WndProc );

	if( result != M_I_DEFAULT_RESULT) return result;
	else
	{
		// 3. calculate window size (optional)
		RECT lpRect = { M_I_RECT_SIZE, M_I_RECT_SIZE, _size.x + M_I_RECT_SIZE, 
						_size.y + M_I_RECT_SIZE };
		DWORD dwStyle = WS_OVERLAPPEDWINDOW; 
		BOOL bMenu = false;

		AdjustWindowRect(&lpRect, dwStyle, bMenu);

		// 4. create window
		m_hWnd = CreateWindowEx( NULL, m_pWndClass->GetLpszClassName(), _name,
								 dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
								 lpRect.right - lpRect.left,
								 lpRect.bottom - lpRect.top,
								 nullptr, nullptr, m_pWndClass->GetHInstance(), 
								 NULL );


		if (!m_hWnd)
		{
			MessageBox( I_DEFAULT_HWND, M_S_WINDOW_ERROR, M_S_ERROR,
						MB_OK | MB_ICONERROR );
			result = M_I_ERROR_CREATE_WINDOW_FAILED;
		}
		else
		{
			// 5. show window
			ShowWindow( m_hWnd, _nCmdShow );
			SetFocus(  m_hWnd );
		}

		return result;
		
	}
}
/*****************************************************************************/

/*****************************************************************************/
// Programm läuft
/*****************************************************************************/
bool CWindow::Run()
{
	MSG msg = {};

	if( PeekMessage( &msg, nullptr, 0, UINT_MAX, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage(  &msg );

		if( msg.message == WM_QUIT ) return false;
	}

	return true;
}
/*****************************************************************************/

/*****************************************************************************/
// Finalisierung
/*****************************************************************************/
void CWindow::Finalize()
{
	HWND m_hWnd = nullptr;

	FINALIZE_DELETE( m_pWndClass );
}
/*****************************************************************************/