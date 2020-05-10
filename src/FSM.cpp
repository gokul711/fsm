/**
* Implementation of the FSM lass
* @file FSM.cpp
* @author Gokul Krishnan
*/

#include <FSM.hpp>
#include <FSM_State.hpp>
#include <FSM_Guard.hpp>
#include <algorithm>

namespace fsm
{
//Static data member instantiation
FSM * FSM::m_Instance = nullptr;
std::mutex FSM::m_sync;
std::condition_variable FSM::m_condVar;
bool FSM::m_eventOccurred = false;
std::thread * FSM::m_smThread = nullptr;
bool FSM::m_Alive = true;

//Constructor is private. Always create via Init 
FSM::FSM(const std::string& p_smname )
{
	FSM_LOG_FUNC_ENTER( );
	m_currstate = nullptr;
	m_name = p_smname;
	m_smThread = nullptr;
	m_eventOccurred = false;
	m_eventGuard = nullptr;
	m_dispatcher = nullptr;
	m_Alive = true;
	FSM_LOG_FUNC_EXIT( );
}
bool FSM::Init(const std::string& p_smname)
{
	FSM_LOG_FUNC_ENTER( );
	if ( nullptr == m_Instance )
	{
		try
		{
			m_Instance = new FSM( p_smname);  //Create SM object
			m_smThread = new std::thread ( &FSM::FsmRunningThread, m_Instance); //Create SM thread
			return true;
		}
		catch(...)
		{
			return false;
		}
	}
	FSM_LOG_FUNC_EXIT( );
	return true;
}
std::string FSM::getState() const
{
	FSM_LOG_FUNC_ENTER( );
	FSM_LOG_FUNC_EXIT( );
	return m_currstate->getState();
	
}
std::string FSM::getName() const
{
	FSM_LOG_FUNC_ENTER( );
	FSM_LOG_FUNC_EXIT( );
	return m_name;
	
}
//Add default ransitions
void FSM::AddDefault( FSM_State* p_currstate )
{
	FSM_LOG_FUNC_ENTER( );
	m_currstate = p_currstate;
	m_currstate->On_Entry();
	m_currstate->On_Execute();
	m_currstate->On_Exit();
	FSM_LOG_FUNC_EXIT( );
}
void FSM::AddTransition(FSM_State* p_currstate, FSM_State* p_nextstate, FSM_Guard * p_transguard)
{
	FSM_LOG_FUNC_ENTER( );
	std::pair<FSM_State*, FSM_State* > l_trans = std::make_pair (p_currstate,p_nextstate);
	m_transitionMap.insert( std::make_pair ( p_transguard, std::make_pair (p_currstate,p_nextstate) ) );
	FSM_LOG_FUNC_EXIT( );
}
void FSM::EventOccurred( FSM_Guard* p_guard, void* p_dispatcher)
{
	FSM_LOG_FUNC_ENTER( );
	m_eventOccurred = true;
	m_eventGuard = p_guard;
	m_dispatcher = p_dispatcher;
	//Unblock SM running thread
	m_condVar.notify_one();
	FSM_LOG_FUNC_EXIT( );
}
//FSM running thread function
void FSM::FsmRunningThread( FSM * p_context)
{
	FSM_LOG_FUNC_ENTER( );
	//Run while alive
	while(m_Alive)
	{
		// Wait until some event vaiable is updated
	    std::unique_lock<std::mutex> lk(m_sync);
	    m_condVar.wait(lk, []{return m_eventOccurred;});
	    p_context->PerformTransition();
	}
	FSM_LOG_FUNC_EXIT( );
}
void FSM::ShutDown()
{
	FSM_LOG_FUNC_ENTER( );
	//Set thread control variable to false
	m_Alive = false;
	//Signal event occurred
	m_eventOccurred = true;
	//Unblock SM running thread
	m_condVar.notify_one();
	//Wait for SM thread to join
	m_smThread->join();
	//deallocate SM and thread pointers
	delete m_smThread;
	delete m_Instance;
	FSM_LOG_FUNC_EXIT( );
}
void FSM::PerformTransition( )
{
	FSM_LOG_FUNC_ENTER( );
	if ( ( ! m_transitionMap.empty() ) &&
		 ( nullptr != m_eventGuard )
	   ) 
	{
		std::unordered_map <FSM_Guard* , std::pair<FSM_State*, FSM_State* > >::iterator l_transiton2ExecuteItr;
		auto l_range = m_transitionMap.equal_range(m_eventGuard);
		for ( l_transiton2ExecuteItr = l_range.first; l_transiton2ExecuteItr != l_range.second; l_transiton2ExecuteItr++)
		{
			if ( ( l_transiton2ExecuteItr->second.first == m_currstate ) &&
				 ( l_transiton2ExecuteItr->first->On_Check( m_dispatcher ) )
			   )
			{
				m_currstate = l_transiton2ExecuteItr->second.second;
				m_currstate->On_Entry();
				m_currstate->On_Execute();
				m_currstate->On_Exit();
				break;
			}
		}
	}
	//Reset variables
	m_eventOccurred = false;
	m_eventGuard = nullptr;
	m_dispatcher = nullptr;
	FSM_LOG_FUNC_EXIT( );
}
//Static functions
FSM& FSM::Instance()
{
	FSM_LOG_FUNC_ENTER( );
	if( nullptr == m_Instance)
	{
		FSM::Init(std::string(__FILE__));
	}
	return *(m_Instance);
	FSM_LOG_FUNC_EXIT( );
}

}