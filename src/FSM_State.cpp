/**
* Implementation of the FSM state lass
* @file FSM_State.cpp
* @author Gokul Krishnan
*/

#include <FSM_State.hpp>

namespace fsm
{

FSM_State::FSM_State(const std::string& p_smname )
{
	m_name = p_smname;
}
std::string FSM_State::getState() const
{
	return m_name;
}

}