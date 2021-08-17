/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : MatrixCB.h
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
#include <d3d11.h>
#include <xnamath.h>
#include "../General/Variables.h"

struct ObjMatrixCB
{
	XMMATRIX wvpMatrix;
	XMMATRIX worldMatrix;
	XMVECTOR cameraPosition;
};

struct FrameLightCB
{
	Light light;
};