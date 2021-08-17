/*****************************************************************************
* Project: 3D Objekt Rendering
* File   : Time.h
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
#include <windows.h>

// Nach Stephan Jacobs Timer aus DirectX11
class CTime
{
private:
	/*************************************************************************/
	// Timer
	/*************************************************************************/
	double UpdateTime();
	void   StartTimer();
	/*************************************************************************/

	void UpdateFrameTime();



public:
	/*************************************************************************/
	// Getter/Setter
	/*************************************************************************/
	inline double GetDeltaTime() const { return m_dCurrentFrameTime; }
	/*************************************************************************/



	/*************************************************************************/
	// Programmablauf
	/*************************************************************************/
	int Update();
	/*************************************************************************/



private:
	/*************************************************************************/
	// Konstanten
	/*************************************************************************/
	const int M_I_SUCCESS = 0;

	const long long M_I_TICK_COUNT_LIMIT = 0;
	const long long M_I_DEFAULT_TICK_COUNT = 0;

	const double M_F_UPDATE_TIME_LIMIT = 1.0;
	const long M_I_DEFAULT_FRAME_COUNT = 0;
	/*************************************************************************/



	/*************************************************************************/
	// Member-Variablen
	/*************************************************************************/
	double		 m_dSecondsPerCount   = 0.0;
	long long	 m_llCounterStart	  = 0;

	long		 m_lFrameCount		  = 0;
	long		 m_lFpS				  = 0;

	LARGE_INTEGER m_llWindowsTime;

	long long	  m_llTickCount;


	long long	  m_llLastFrameTime   = 0;
	double		  m_dCurrentFrameTime = 0.0;
	/*************************************************************************/
};

