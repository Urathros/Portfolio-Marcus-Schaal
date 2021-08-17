/*****************************************************************************
* Project: DirectX9Stuff
* File   : Defines.h
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
*					+defines: FINALIZE_DELETE
******************************************************************************/
#pragma once

/*****************************************************************************/
// Macros
/*****************************************************************************/

/*****************************************************************************/
//nach Ralf H�wes SDLFramework
/*****************************************************************************/
// Finalisieren und zerst�ren
/*****************************************************************************/
#define FINALIZE_DELETE(x)	\
{							\
	if( (x) != nullptr )	\
	{						\
		(x)->Finalize();	\
		delete (x);			\
		(x) = nullptr;		\
	}						\
}
/*****************************************************************************/
/*****************************************************************************/


/*****************************************************************************/
// Freigeben und zerst�ren
/*****************************************************************************/
#define RELEASE_DELETE(x)	\
{							\
	if( (x) != nullptr )	\
	{						\
		(x)->Release();		\
		(x) = nullptr;		\
	}						\
}
/*****************************************************************************/



/*****************************************************************************/
// Ergebnis �berpr�fen
/*****************************************************************************/

#define PROVE_RESULT(x)		\
{							\
	if (x != 0) return x;	\
}

/*****************************************************************************/
/*****************************************************************************/