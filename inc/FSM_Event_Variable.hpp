/**
* Declaration of the FSM event variable class
* @file FSM_Event_Variable.h
* @author Gokul Krishnan
*/

#pragma once

#include <mutex>
#include <string>

namespace fsm
{
class FSM_Guard;
//Actual type must have overload of ==  and = operators.Defaults to char
template <class Typename = char >
class FSM_Event_Variable
{
	private:
		//Data member holing the actual value
		Typename m_data;
		//Delete copy constructor, = operator and == operator
		FSM_Event_Variable(FSM_Event_Variable & p_obj) = delete;
		FSM_Event_Variable& operator=(const FSM_Event_Variable& p_obj) = delete;
		bool operator==(const FSM_Event_Variable& p_obj) = delete;
	protected :
		FSM_Guard * m_guard;
		
	public :
			FSM_Event_Variable ( )
			{
				m_guard = nullptr;
			}
			void setValue(  const Typename& p_data )
			{
				if ( m_data != p_data )
				{
					m_data = p_data;
					FSM::Instance().EventOccurred( m_guard );
				}
				
			}
			Typename& getValue( )
			{
				return m_data;
			}
			FSM_Guard * getGuard() const
			{
				return m_guard;
			}
			void AddGuardCondition(FSM_Guard * p_guard)
			{
				m_guard = p_guard;
			}
			
	
};
}