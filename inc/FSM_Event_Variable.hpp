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
class FSM_Event_Variable
{
	private:
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
			void setValue( );
			FSM_Guard * getGuard() const
			{
				return m_guard;
			}
			void AddGuardCondition(FSM_Guard * p_guard);
			
	
};
}