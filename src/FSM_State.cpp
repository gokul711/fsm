/**
* Implementation of the FSM state lass
* @file FSM_State.cpp
* @author Gokul Krishnan
*/

#include <FSM_State.hpp>
#include <Log.hpp>

namespace fsm
{

FSM_State::FSM_State(const std::string& p_smname )
{
	FSM_LOG_FUNC_ENTER( );
	m_name = p_smname;
	FSM_LOG_FUNC_EXIT( );
}
std::string FSM_State::getState() const
{
	FSM_LOG_FUNC_ENTER( );
	return m_name;
	FSM_LOG_FUNC_EXIT( );
}

}