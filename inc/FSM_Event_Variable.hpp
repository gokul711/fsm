/**
* Declaration of the FSM event variable class
* @file FSM_Event_Variable.h
* @author Gokul Krishnan
*/

#pragma once

#include <mutex>
#include <string>
#include <cstdint>
#include <Event.hpp>
namespace fsm
{
//Actual type must have overload of ==  and = operators.Defaults to char
template <class Typename = uint8_t >
class FSM_Event_Variable
{
	private:
		//Data member holing the actual value
		Typename m_data;
		//Delete copy constructor, = operator and == operator
		FSM_Event_Variable(FSM_Event_Variable & p_obj) = delete;
		FSM_Event_Variable& operator=(const FSM_Event_Variable& p_obj) = delete;
		bool operator==(const FSM_Event_Variable& p_obj) = delete;
		EventDispatcher<Typename> * m_eventDispatcher;
	protected :
		
	public :
			FSM_Event_Variable ( )
			{
				m_eventDispatcher = new EventDispatcher<Typename>;
			}
			void setValue(  const Typename& p_data )
			{
				if ( m_data != p_data )
				{
					m_data = p_data;
					m_eventDispatcher->AddEventToEventQueue( m_data );
				}
				
			}
			Typename& getValue( )
			{
				return m_data;
			}	
};
}