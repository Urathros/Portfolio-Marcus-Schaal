#include "Time.h"
#include <iostream>
#include "../../Code/General/Defines.h"

/*****************************************************************************/
// Timer
/*****************************************************************************/
// Zeit updaten
/*****************************************************************************/
double CTime::UpdateTime()
{ 
	QueryPerformanceCounter( &m_llWindowsTime );
	return static_cast<double>  ( m_llWindowsTime.QuadPart - m_llCounterStart ) 
							  / m_dSecondsPerCount;;
}
/*****************************************************************************/

/*****************************************************************************/
// Timer Starten
/*****************************************************************************/
void CTime::StartTimer()
{
	LARGE_INTEGER cpuFrequency; //testen ob windows time
	QueryPerformanceFrequency( &cpuFrequency );//CPU-Zeit auslesen, longpointer
	m_dSecondsPerCount = static_cast<double>( cpuFrequency.QuadPart );
	QueryPerformanceCounter( &cpuFrequency );
	m_llCounterStart = cpuFrequency.QuadPart; //Timer starten
}
/*****************************************************************************/
/*****************************************************************************/



/*****************************************************************************/
// Zeit pro Frame updaten
/*****************************************************************************/
void CTime::UpdateFrameTime()
{
	QueryPerformanceCounter( &m_llWindowsTime );

	m_llTickCount = m_llWindowsTime.QuadPart - m_llLastFrameTime;
	m_llLastFrameTime = m_llWindowsTime.QuadPart;

	if( m_llTickCount < M_I_TICK_COUNT_LIMIT )
	{
		m_llTickCount = M_I_DEFAULT_TICK_COUNT;
		std::cout << "Fehler: Tick-Count kleiner 0" << std::endl;
	}

	m_dCurrentFrameTime =   static_cast<double>( m_llTickCount ) 
						  / m_dSecondsPerCount;
}
/*****************************************************************************/



/*****************************************************************************/
// Programmablauf
/*****************************************************************************/
// Updaten
/*****************************************************************************/
int CTime::Update()
{
	m_lFrameCount++;
	if( UpdateTime() > M_F_UPDATE_TIME_LIMIT )
	{
		m_lFpS = m_lFrameCount;
		std::cout << "FpS: " << m_lFpS << std::endl;
		m_lFrameCount = M_I_DEFAULT_FRAME_COUNT;
		StartTimer();
	}
	UpdateFrameTime();

	return M_I_SUCCESS;
}
/*****************************************************************************/
/*****************************************************************************/