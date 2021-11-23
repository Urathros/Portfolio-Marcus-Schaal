/*****************************************************************************
* Project	: Genius Template Library
* File		: GeniusFunction.h
* Date		: 17.10.2021
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
* 	17.10.2021	MS	Created,
*					+class: CPtr
*
* 	22.10.21	MS	+CPtr: ctor overload for auto-lambda-variables.
*
*	08.11.21	MS	+CPtr:Forward implemented
*
*	13.11.21	MS	+CPtr: functor = for Lambdas
*
*	20.11.21	MS	+CPtr: ctor for pure-lambdas, CastToCallable
*
*	22.11.21	MS	+CPtr: functor == and !=
******************************************************************************/
#ifndef _GENIUS_FUNCTION_H
#define _GENIUS_FUNCTION_H

#include "GeniusCore.h"

namespace GTL
{
	namespace Func
	{
		/*********************************************************************/
		// Default Signature Class
		/*********************************************************************/
		template <typename SignatureType = void>
		class CPtr : CPtr<decltype(&SignatureType::operator())> {};
		/*********************************************************************/


		/*********************************************************************/
		// Function-Pointer-Overload with body
		/*********************************************************************/
		/* A class,
		 * that reference a function/method or lambda 
		 * to a smart function-pointer. */
		template <typename ReturnType, typename... Args>
		class CPtr<ReturnType( Args... )> final
		{
			/*****************************************************************/
			// Using
			/*****************************************************************/
			//A generic function-pointer.
			using FuncPtrType = ReturnType(*)( Args... );

			//A return-value for ctor-agument lambda-expressions.
			template <typename InnerReturnType, typename...>
			using ReturnValue = decltype( DeclareValue<InnerReturnType>()
												 ( DeclareValue<Args>()... ) );

			//A function-pointer for ctor-agument lambda-expressions.
			template <typename InnerReturnType, typename...>
			using LambdaPtrType =
				decltype(static_cast< ReturnValue<InnerReturnType, Args...>
											(InnerReturnType::*)(Args...) const
									>( &InnerReturnType::operator() ) );
			/*****************************************************************/



		public:
			/*****************************************************************/
			// Constructor/Destructor
			/*****************************************************************/
			/*---------------------------------------------------------------*/
			// Constructor
			/*---------------------------------------------------------------*/
			// The default ctor.
			inline CPtr() noexcept {}

			// The ctor for regular Functions/Methods.
			inline constexpr CPtr( const FuncPtrType& _pFunc = nullptr )
				: m_pCallable( _pFunc ) {}

			// The ctor for lambda-expressions and auto-var-lambdas.
			template <typename LambdaType,
				LambdaPtrType<LambdaType, Args...> = nullptr>
				inline constexpr CPtr( const LambdaType& _func )
				: m_pCallable( CastToCallable( _func ) ) {}
			/*---------------------------------------------------------------*/


			/*---------------------------------------------------------------*/
			//Destructor
			/*---------------------------------------------------------------*/
			// The default destructor
			~CPtr();
			/*---------------------------------------------------------------*/
			/*****************************************************************/




			/*****************************************************************/
			// Getter/Setter
			/*****************************************************************/
			/*---------------------------------------------------------------*/
			// Getter
			/*---------------------------------------------------------------*/
			// A Getter-Method, that returns the Function-Pointer.
			operator FuncPtrType() const;
			/*---------------------------------------------------------------*/


			/*---------------------------------------------------------------*/
			// Setter
			/*---------------------------------------------------------------*/
			// A Setter-Method, for regular Functions/Methods as Parameters.
			CPtr<ReturnType( Args... )>& operator= 
				( const FuncPtrType& _pFunc );

			/* A Setter-Method, for lambda-expressions and auto-var-lambdas
			 * as Parameters. */
			template <typename LambdaType>
			CPtr<ReturnType( Args... )>& operator= ( LambdaType&& _func );
			/*---------------------------------------------------------------*/
			/*****************************************************************/



		private:
			/*****************************************************************/
			// Inline-Methods
			/*****************************************************************/
			/* A Method, 
			 * that casts a Lambda-expression to a callable Function-Pointer.*/
			template <typename LambdaType>
			inline constexpr typename 
				FuncPtrType CastToCallable( const LambdaType& _func )
			{
				static LambdaType func = Forward( _func );

				return static_cast<FuncPtrType>( 
							   [](Args... _args) 
							   { return func( Forward<Args>( _args )... ); } );
			}
			/*****************************************************************/



		public:
			/*****************************************************************/
			// Functors
			/*****************************************************************/
			/*---------------------------------------------------------------*/
			// Invoke
			/*---------------------------------------------------------------*/
			// A anonymous method, that invokes the Function of the Pointer.
			ReturnType operator()( Args&&... _args );
			/*---------------------------------------------------------------*/


			/*---------------------------------------------------------------*/
			// boolean expressions
			/*---------------------------------------------------------------*/
			/* A anonymous bool-method, that checks, 
			 * whether the object and the agument are equal.*/
			bool operator== ( const FuncPtrType& _pOtherFunc );

			/* A anonymous bool-method, that checks, 
			* wheter the object and the agument are not equal.*/
			bool operator!= ( const FuncPtrType& _pOtherFunc );
			/*---------------------------------------------------------------*/
			/*****************************************************************/

		protected:
			/*****************************************************************/
			// Member-Variable
			/*****************************************************************/
			// The capsulated callable function-pointer of the object.
			FuncPtrType m_pCallable = nullptr;
			/*****************************************************************/
		};
		/*********************************************************************/
	}
}
#endif //_GENIUS_FUNCTION_H

namespace GTL
{
	namespace Func
	{

		/*********************************************************************/
		// Destructor
		/*********************************************************************/
		template<typename ReturnType, typename ...Args>
		CPtr<ReturnType( Args... )>::~CPtr()
		{
			if( m_pCallable != nullptr ) m_pCallable = nullptr;
		}
		/*********************************************************************/



		/*********************************************************************/
		// Getter
		/*********************************************************************/
		template<typename ReturnType, typename ...Args>
		CPtr<ReturnType( Args... )>::operator FuncPtrType() const
		{
			return m_pCallable; 
		}
		/*********************************************************************/



		/*********************************************************************/
		// Setter
		/*********************************************************************/
		template<typename ReturnType, typename ...Args>
		CPtr<ReturnType( Args... )>& 
			CPtr<ReturnType( Args... )>::operator=( const FuncPtrType& _pFunc )
		{
			if( _pFunc == nullptr ) return M_I_ERROR_IS_NULLPTR;

			m_pCallable = _pFunc; 

			return *this;
		}
		/*********************************************************************/



		/*********************************************************************/
		// Setter-Overload
		/*********************************************************************/
		template<typename ReturnType, typename ...Args>
		template<typename LambdaType>
		CPtr<ReturnType( Args... )>& 
			CPtr<ReturnType( Args... )>::operator=( LambdaType&& _func )
		{
			m_pCallable = CastToCallable( _func );  
			return *this;
		}
		/*********************************************************************/



		/*********************************************************************/
		// Invoke
		/*********************************************************************/
		template<typename ReturnType, typename ...Args>
		ReturnType CPtr<ReturnType( Args... )>::operator()( Args && ..._args )
		{
			if( m_pCallable != nullptr )
			{
				return( *m_pCallable )( Forward( _args )... );
			}
			else return ReturnType();
		}
		/*********************************************************************/



		/*********************************************************************/
		// Check Equality
		/*********************************************************************/
		template<typename ReturnType, typename ...Args>
		inline bool CPtr<ReturnType( Args... )>::operator== 
			( const FuncPtrType& _pOtherFunc )
		{
			return static_cast<bool>( m_pCallable == _pOtherFunc );
		}
		/*********************************************************************/



		/*********************************************************************/
		// Check Inequality
		/*********************************************************************/
		template<typename ReturnType, typename ...Args>
		inline bool CPtr<ReturnType( Args... )>::operator!=
			( const FuncPtrType& _pOtherFunc )
		{
			return static_cast<bool>(m_pCallable != _pOtherFunc);
		}
		/*********************************************************************/
	}
}
