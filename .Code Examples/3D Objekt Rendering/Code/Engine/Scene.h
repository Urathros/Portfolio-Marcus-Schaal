/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Scene.h
* Date   : 13.11.2020
* Author : Marcus Schaal (MS)
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	13.11.20	MS	Created
******************************************************************************/
#pragma once
#include "../DirectX/RenderObject/RenderObject.h" 
#include "../DirectX/Camera/Camera.h"
#include "../DirectX/Light/Light.h"
#include <iostream>
#include <vector>
#include "Engine.h"

class CScene
{
public:
	/*************************************************************************/
	// Konstruktor
	/*************************************************************************/
	CScene( IVector2 _size, CEngine& _engine );
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Initialize();
	void Release();
	int Update( CEngine& _engine );
	void Draw();
	/*************************************************************************/



private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	const int   M_I_SUCCESS		  = 0;
	const FLOAT M_F_DEFAULT_CAM_W = 0.0f;
	/*************************************************************************/



	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	CCamera*					m_pCamera			= nullptr;
	CLight*						m_pDirectionalLight = nullptr;
	std::vector<CRenderObject*> m_pRenderVect		= {};
	/*************************************************************************/
};