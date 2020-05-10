/**
* Declaration of the FSM event variable class
* @file FSM_Event_Variable.h
* @author Gokul Krishnan
*/

#pragma once

#include <mutex>
#include <string>
#include <cstdint>
#include <cstring>
#include <Event.hpp>
namespace fsm
{
class FSM_Guard;
//Actual type must have overload of ==, !=   and = operators.Defaults to char
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

		FSM_Guard* m_guard;
	protected :
		
	public :
			FSM_Event_Variable ( )
			{
				FSM_LOG_FUNC_ENTER(   );
				m_eventDispatcher = new EventDispatcher<Typename>;
				std::memset(&m_data, 0 , sizeof(m_data));
				FSM_LOG_FUNC_EXIT( );
			}
			~FSM_Event_Variable()
			{
				FSM_LOG_FUNC_ENTER(   );
				m_eventDispatcher->ExitDispatcherThread();
				delete m_eventDispatcher;
				FSM_LOG_FUNC_EXIT( );
			}
			void setValue(  const Typename& p_data )
			{

				FSM_LOG_FUNC_ENTER(   );
				m_data = p_data;
				m_eventDispatcher->AddEventToEventQueue( m_data );
				FSM_LOG_FUNC_EXIT( );
				
			}
			Typename& getValue( ) 
			{
				FSM_LOG_FUNC_ENTER(   );
				FSM_LOG_FUNC_EXIT( );
				return m_data;
				
			}	
			void AddGuardCondition(const Typename& p_data, FSM_Guard * p_guard)
			{
				FSM_LOG_FUNC_ENTER(   );
				m_guard = p_guard;
				m_eventDispatcher->AddToEventMap(p_data, p_guard);
				FSM_LOG_FUNC_EXIT( );
			}
			EventDispatcher<Typename>* getEventDispatcher() const 
			{
				FSM_LOG_FUNC_ENTER(   );
				FSM_LOG_FUNC_EXIT( );
				return m_eventDispatcher;
				
			}
};
}