/*****************************************************************************
* Project: DirectX9Stuff
* File   : main.cpp
* Date   : 01.10.2020
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	01.10.20	MS	Created,
*					+Funktionen: WinMain,
*					+Includes:<Windows.h>, "Window.h"
*					lokale Variablen (width, height, result, mainWindow) 
*					für WinMain,
*					WinMain initialisiert, run und finalisiert,
*					primitiver Update-Loop
*
*	19.10.20	MS	lokale Variable (direct3D),
*					+Funktion: RunMessageLoop
******************************************************************************/

#include <windows.h> //für WinMain
#include "Engine/Engine.h"
#include "Engine/Scene.h"
#include "General/Defines.h" 
#include "General/Variables.h"

/*****************************************************************************/
// Konstanten
/*****************************************************************************/
const int I_DEFAULT_RESULT	= 1;
const int I_RESULT_LIMIT	= 0;
const int I_RESULT_ERROR	= -1;
const int I_WND_SIZE_X		= 800;
const int I_WND_SIZE_Y		= 600;
const std::string S_TITLE	= "XtremeViewer";
/*****************************************************************************/

//Ordner- und Klassenstruktur ist von der Projektmappe "DirectX_evening" und dem Projekt "DirectX11" von David Hackbarth inspiriert.
// Der Aufbau der Renderpipeline eher von Stephan Jacobs "DirectX11_SAE"

/*****************************************************************************/
// Updaten
/*****************************************************************************/
int Update(CEngine& _engine, CScene& _scene)
{
	PROVE_RESULT(_engine.DetectInput());

	PROVE_RESULT(_engine.Update());
	PROVE_RESULT(_scene.Update(_engine));
}
/*****************************************************************************/

/*****************************************************************************/
// Zeichnen
/*****************************************************************************/
void Draw( CEngine& _engine, CScene& _scene )
{
	_engine.ClearView();
	_scene.Draw();
	_engine.Draw();
}
/*****************************************************************************/

/*****************************************************************************/
// Programm-Kaskade
/*****************************************************************************/
int RunMessageLoop( int _result,CEngine& _engine, CScene& _scene )
{
	if( _result != I_RESULT_LIMIT ) return I_RESULT_ERROR;
	else
	{

		while( true )
		{
			if( !_engine.Run() ) break;
			else
			{
				_result = Update( _engine, _scene );
				Draw( _engine, _scene );
			}
		}
	}
	return _result;
}
/*****************************************************************************/

/*****************************************************************************/
// Hauptfunktion
/*****************************************************************************/
int CALLBACK WinMain( HINSTANCE _hInstance, HINSTANCE _hInstancePrev, 
					  LPSTR _lpCmdLine, int _nCmdShow )
{
	int result = I_DEFAULT_RESULT; 
	IVector2 size = IVector2( I_WND_SIZE_X, I_WND_SIZE_Y);

	CEngine* pEngine = new CEngine();
	result = pEngine->Initialize( _hInstance, size, _nCmdShow, 
								  S_TITLE.c_str() );

	CScene* pScene = new CScene( size, *pEngine);
	result = pScene->Initialize();
	
	//Programm-Kaskade
	result = RunMessageLoop( result, *pEngine, *pScene );  

	RELEASE_DELETE( pScene );
	FINALIZE_DELETE( pEngine );

	return result;
}
/*****************************************************************************/