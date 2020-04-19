/**
* Declaration of the FSM class
* @file FSM.h
* @author Gokul Krishnan
*/

#pragma once

#include <mutex>
#include <string>
#include <map>

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
		}
		//Delete copy constructor, = operator and == operator
		FSM(FSM & p_obj) = delete;
		FSM& operator=(const FSM& p_obj) = delete;
		bool operator==(const FSM& p_obj) = delete;

		std::mutex m_sync;
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
			void EventVariableUpdated( const FSM_Event_Variable * p_eventVar);
			//Static functions 
			static FSM& Instance();
	
};
}