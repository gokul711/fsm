/**
* Implementation of the FSM lass
* @file FSM.cpp
* @author Gokul Krishnan
*/


#include <FSM.hpp>
#include <FSM_State.hpp>
#include <FSM_Guard.hpp>
#include <FSM_Event_Variable.hpp>

#include <iostream>
using namespace std;

namespace fsm
{
FSM * FSM::m_Instance = nullptr;
//Operations
bool FSM::Init(const std::string& p_smname)
{
	try
	{
		m_Instance = new FSM( p_smname);
		return true;
	}
	catch(...)
	{
		return false;
	}
	
}
std::string FSM::getState() const
{
	return m_currstate->getState();
}
bool FSM::setState(FSM_State* p_newstate)
{
	m_currstate = p_newstate;
}
//Add Transitions
void FSM::AddDefault( FSM_State* p_currstate )
{
	m_currstate = p_currstate;
	m_currstate->On_Entry();
	m_currstate->On_Execute();
	m_currstate->On_Exit();
}
void FSM::AddTransition(FSM_State* p_currstate, FSM_State* p_nextstate, FSM_Guard * p_transguard)
{
	std::pair<FSM_State*, FSM_State* > l_trans = std::make_pair (p_currstate,p_nextstate);
	m_transitionMap.insert( std::make_pair ( p_transguard, std::make_pair (p_currstate,p_nextstate) ) );
}
void FSM::EventVariableUpdated( const FSM_Event_Variable * p_eventVar)
{
	if ( ! m_transitionMap.empty() ) 
	{
		bool l_guardCheck = false;
		std::pair<FSM_State*, FSM_State* > l_transiton2Execute;
		std::map <FSM_Guard* , std::pair<FSM_State*, FSM_State* > >::iterator l_transiton2ExecuteItr;

		FSM_Guard * l_guard = p_eventVar->getGuard();
		l_guardCheck = l_guard->On_Check();
		l_transiton2ExecuteItr = m_transitionMap.find(l_guard);
		if ( l_guardCheck &&              									  //Short circuit here if Guard evaluation fails
			 ( l_transiton2ExecuteItr != m_transitionMap.end() )   &&        //Short circuit here if the transition is not defined
			 ( l_transiton2ExecuteItr->second.first == m_currstate ) 		//Current state is not correct for the transition
		   )
		{
			m_currstate = l_transiton2ExecuteItr->second.second;
			m_currstate->On_Entry();
			m_currstate->On_Execute();
			m_currstate->On_Exit();
		}
		else
		{
			m_currstate->On_Fail();
		}
	}
}
//Static functions
FSM& FSM::Instance()
{
	if( nullptr == m_Instance)
	{
		FSM::Init(std::string(__FILE__));
	}
	return *(m_Instance);
}

}