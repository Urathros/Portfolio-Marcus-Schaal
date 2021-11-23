/*****************************************************************************
* Project	: Genius Template Library
* File		: GeniusCore.h
* Date		: 21.11.2021
* Author	: Marcus Schaal (MS)
* Language	: C++14
*
* These coded instructions, statements, and computer programs contain
* proprietary information of the author and are protected by Federal
* copyright law. They may not be disclosed to third parties or copied
* or duplicated in any form, in whole or in part, without the prior
* written consent of the author.
*
* History:
*	21.11.21	MS	Created,
*					+Functions: DeclareRef, DeclareValue, Forward
* 
*	23.11.21	MS	+Const: M_I_ERROR_IS_NULLPTR
******************************************************************************/

#ifndef _GENIUS_CORE_H
#define _GENIUS_CORE_H

namespace GTL
{
	/*************************************************************************/
	// Error-Constants
	/*************************************************************************/
	const char M_I_ERROR_IS_NULLPTR = -1;
	/*************************************************************************/

	/*************************************************************************/
	// Declare Reference
	/*************************************************************************/
	// Function, that declares the reference to the r-value of the type.
	template <typename RValueType, typename RefType = RValueType&&>
	inline RefType DeclareRef( int ) noexcept;
	/*************************************************************************/



	/*************************************************************************/
	// Declare Value
	/*************************************************************************/
	// Function that converts any Type to a reference-type.
	template <typename ValueType>
	inline auto DeclareValue( void ) noexcept 
		-> decltype( DeclareRef<ValueType>( 0 ) );
	/*************************************************************************/



	/*************************************************************************/
	// Forward
	/*************************************************************************/
	// Function that Forwards lvalues the Type as either lvalues or as rvalues.
	template<typename ValueType>
	inline constexpr ValueType&& Forward( ValueType& _arg ) noexcept
	{
		return static_cast<ValueType&&>( _arg );
	}
	/*************************************************************************/
}

#endif //_GENIUS_CORE_H

