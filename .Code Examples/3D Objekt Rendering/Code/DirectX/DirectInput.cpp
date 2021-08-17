#include "DirectInput.h"
#include "../General/Defines.h"

/*****************************************************************************/
// Tastatureingabe erfragen
/*****************************************************************************/
// Kamera auf Ursprungsposition setzen
/*****************************************************************************/
void CDirectInput::ResetCamera()
{
	if( m_keyboardStateArr[DIK_F] & M_I_KEYSTATE_FLAG )
	{
		m_bCameraReset = true;
	}
}
/*****************************************************************************/

/*****************************************************************************/
// Kameraposition ändern
/*****************************************************************************/
void CDirectInput::ChangeCameraPos( const double _deltaTime )
{
	if(   ( m_keyboardStateArr[DIK_UP] & M_I_KEYSTATE_FLAG ) 
		| ( m_keyboardStateArr[DIK_W] & M_I_KEYSTATE_FLAG  ) )
	{
		m_cameraPosition.z += M_F_CAM_MOVE * _deltaTime;
	}
	else if(   ( m_keyboardStateArr[DIK_LEFT] & M_I_KEYSTATE_FLAG ) 
			 | ( m_keyboardStateArr[DIK_A] & M_I_KEYSTATE_FLAG	  ) )
	{
		m_cameraPosition.x -= M_F_CAM_MOVE * _deltaTime;
	}
	else if(   ( m_keyboardStateArr[DIK_DOWN] & M_I_KEYSTATE_FLAG ) 
			 | ( m_keyboardStateArr[DIK_S] & M_I_KEYSTATE_FLAG    ) )
	{
		m_cameraPosition.z -= M_F_CAM_MOVE * _deltaTime;
	}
	else if(   ( m_keyboardStateArr[DIK_RIGHT] & M_I_KEYSTATE_FLAG ) 
			 | ( m_keyboardStateArr[DIK_D] & M_I_KEYSTATE_FLAG	   ) )
	{
		m_cameraPosition.x += M_F_CAM_MOVE * _deltaTime;
	}
}
/*****************************************************************************/

/*****************************************************************************/
// Kamerarichtung ändern
/*****************************************************************************/
void CDirectInput::ChangeCameraDirection( const double _deltaTime )
{
	if( m_currentMouseState.lX < m_lastMouseState.lX )
	{
		m_cameraForward.x += M_F_CAM_FORWARD * _deltaTime;
	}
	else if( m_currentMouseState.lX > m_lastMouseState.lX )
	{
		m_cameraForward.x -= M_F_CAM_FORWARD * _deltaTime;
	}
	else if( m_currentMouseState.lY < m_lastMouseState.lY )
	{
		m_cameraForward.y -= M_F_CAM_FORWARD * _deltaTime;
	}
	else if( m_currentMouseState.lY > m_lastMouseState.lY )
	{
		m_cameraForward.y += M_F_CAM_FORWARD * _deltaTime;
	}
}
/*****************************************************************************/

/*****************************************************************************/
// Tastenstatus ermitteln
/*****************************************************************************/
void CDirectInput::DetectKeystate( const double _deltaTime )
{

	if( m_keyboardStateArr[DIK_LCONTROL] & M_I_KEYSTATE_FLAG )
	{
		ResetCamera();
		ChangeCameraPos( _deltaTime ); 
		ChangeCameraDirection( _deltaTime );
	}

	m_bRasterState = false;
	if( m_keyboardStateArr[DIK_RETURN] & M_I_KEYSTATE_FLAG )
	{
		m_bRasterState = true;
	}
}
/*****************************************************************************/

/*****************************************************************************/
// Tastendruck ermitteln
/*****************************************************************************/
int CDirectInput::DetectInput( const double _deltaTime )
{
	//Eingabe-Geräte auslesen
	m_pKeboardDevice->Acquire();
	m_pMouseDevice->Acquire();

	//Eingabe übergeben
	hr = m_pMouseDevice->GetDeviceState( sizeof(DIMOUSESTATE), 
										 &m_currentMouseState );
	if( FAILED( hr ) ) return M_I_ERROR_MOUSE_DEV_STATE_FAILED;

	hr = m_pKeboardDevice->GetDeviceState( sizeof( m_keyboardStateArr ), 
										   ( LPVOID )&m_keyboardStateArr ); 
	if (FAILED(hr)) return M_I_ERROR_KEY_DEV_STATE_FAILED;

	//Kamera-Steuerung
	m_bCameraReset = false;
	m_cameraPosition = FVector3::ZeroVector();
	m_cameraForward = FVector3::ZeroVector();


	DetectKeystate(_deltaTime);


	m_lastMouseState = m_currentMouseState;

	return M_I_SUCCESS;
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Initialisierung
/*****************************************************************************/
int CDirectInput::Initialize( HINSTANCE _hInstance, HWND _hWnd )
{

	//DirectInput erstellen
	hr = DirectInput8Create( _hInstance, DIRECTINPUT_VERSION, 
							 IID_IDirectInput8, 
							 reinterpret_cast<void**>( &m_lpDirectInput ), 
							 NULL );
	if( FAILED( hr ) ) return M_I_ERROR_INPUT_8_CREATION_FAILED;
	

	//Devices erstellen
	hr = m_lpDirectInput->CreateDevice( GUID_SysKeyboard, 
										&m_pKeboardDevice, NULL );
	if( FAILED( hr ) ) return M_I_ERROR_KEYBOARD_DEV_CREATION_FAILED;

	hr = m_lpDirectInput->CreateDevice( GUID_SysMouse, &m_pMouseDevice, 
										NULL );
	if( FAILED( hr ) ) return M_I_ERROR_MOUSE_DEV_CREATION_FAILED;


	//Keyboard-Einstellungen
	hr = m_pKeboardDevice->SetDataFormat( &c_dfDIKeyboard ); 
	if( FAILED( hr ) ) return M_I_ERROR_KEY_DATA_FORMAT_FAILED;

	//Nur Fenster im Vordergrund
	hr = m_pKeboardDevice->SetCooperativeLevel( _hWnd, 
												  DISCL_FOREGROUND 
												| DISCL_NONEXCLUSIVE ); 
	if( FAILED( hr ) ) return M_I_ERROR_KEY_COORP_LEVEL_FAILED;


	//Maus-Einstellungen
	hr = m_pMouseDevice->SetDataFormat( &c_dfDIMouse );//Standart-Einstellungen
	if( FAILED( hr ) ) return M_I_ERROR_MOUSE_DATA_FORMAT_FAILED;

	//Fenster in Vordergrund, keine Win-Shortcuts
	hr = m_pMouseDevice->SetCooperativeLevel( _hWnd,   DISCL_FOREGROUND 
													 | DISCL_EXCLUSIVE 
													 | DISCL_NOWINKEY ); 
	if( FAILED( hr ) ) return M_I_ERROR_MOUSE_COORP_LEVEL_FAILED;

	return M_I_SUCCESS;
}
/*****************************************************************************/

/*****************************************************************************/
// Freigeben
/*****************************************************************************/
void CDirectInput::Release()
{
	RELEASE_DELETE( m_pMouseDevice );
	RELEASE_DELETE( m_pKeboardDevice );
}
/*****************************************************************************/
/*****************************************************************************/