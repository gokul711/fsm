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
#include <Log.hpp>

namespace fsm
{
//Forward declare the classes
class FSM_State;
class FSM_Guard;

class FSM
{
	private:
		//Make constructor private. Always create via Init 
		FSM(const std::string& p_smname );
		//Delete copy constructor, = operator and == operator
		FSM(FSM & p_obj) = delete;
		FSM& operator=(const FSM& p_obj) = delete;
		bool operator==(const FSM& p_obj) = delete;
		//Static data members
		static std::mutex m_sync;
		static std::condition_variable m_condVar;
		static bool m_eventOccurred;
		static bool m_Alive;
		static std::thread * m_smThread;
		static FSM * m_Instance;
		//Static methods 
		static void FsmRunningThread( FSM * p_context);
		//Private data members
		FSM_Guard* m_eventGuard;
		FSM_State* m_currstate;
		void* m_dispatcher;
		std::string m_name;
		std::map <FSM_Guard* , std::pair<FSM_State*, FSM_State* >   >  m_transitionMap;
		//Private methods
		void PerformTransition( );
	protected :

	public :
			//Operations
			std::string getState() const;
			std::string getName() const;
			void AddDefault( FSM_State* p_currstate );
			void AddTransition(	FSM_State* p_currstate, 
								FSM_State* p_nextstate, 
								FSM_Guard * p_transguard
							);
			void EventOccurred( FSM_Guard* p_guard, void* p_dispatcher);
			//Static methods functions 
			static bool Init(const std::string& p_smname);
			static FSM& Instance();
			static void ShutDown();
	
};
}