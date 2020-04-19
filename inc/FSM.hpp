/**
* Declaration of the FSM class
* @file FSM.h
* @author Gokul Krishnan
*/

#pragma once

#include <mutex>
#include <condition_variable>
#include <string>
#include <map>
#include <thread>

namespace fsm
{
//Forward declare the classes
class FSM_State;
class FSM_Guard;
class FSM_Event_Variable;

class FSM
{
	private:
		//Make default constructor private. Always create via Init 
		FSM(const std::string& p_smname )
		{
			m_currstate = nullptr;
			m_name = p_smname;
			m_smThread = nullptr;
			m_eventOccurred = false;
			m_eventVar = nullptr;
			m_Alive = true;
		}
		//Delete copy constructor, = operator and == operator
		FSM(FSM & p_obj) = delete;
		FSM& operator=(const FSM& p_obj) = delete;
		bool operator==(const FSM& p_obj) = delete;
		//FSM running thread function
		static void FsmRunningThread( FSM * p_context)
		{
			//Run while alive
			while(m_Alive)
			{
				// Wait until some event vaiable is updated
			    std::unique_lock<std::mutex> lk(m_sync);
			    m_condVar.wait(lk, []{return m_eventOccurred;});
			    p_context->PerformTransition();
			}
		}
		// Actual state transition is done here
		void PerformTransition( );
		static std::mutex m_sync;
		static std::condition_variable m_condVar;
		static bool m_eventOccurred;
		static bool m_Alive;
		static std::thread * m_smThread;
		FSM_Event_Variable * m_eventVar;
		static FSM * m_Instance;
		FSM_State* m_currstate;
		std::string m_name;
		std::map <FSM_Guard* , std::pair<FSM_State*, FSM_State* >   >  m_transitionMap;
	protected :

	public :
			//Operations
			static bool Init(const std::string& p_smname);
			std::string getState() const;
			bool setState(FSM_State* p_newstate);
			//Add transition
			void AddDefault( FSM_State* p_currstate );
			void AddTransition(	FSM_State* p_currstate, 
								FSM_State* p_nextstate, 
								FSM_Guard * p_transguard
							);
			void EventVariableUpdated( FSM_Event_Variable * p_eventVar);
			static void ShutDown()
			{
				m_Alive = false;
				m_eventOccurred = true;
				//Unblock SM running thread
				m_condVar.notify_one();
				//Wait for SM thread to join
				m_smThread->join();
				//deallocate SM and thread pointers
				delete m_smThread;
				delete m_Instance;
			}
			//Static functions 
			static FSM& Instance();
	
};
}