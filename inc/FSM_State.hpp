/**
* Declaration of the FSM state class
* @file FSM_State.h
* @author Gokul Krishnan
*/

#pragma once

#include <mutex>
#include <string>

namespace fsm
{

class FSM_State
{
	private:
		//Delete default constructor, copy constructor, = operator and == operator
		FSM_State( ) = delete;
		FSM_State(FSM_State & p_obj) = delete;
		FSM_State& operator=(const FSM_State& p_obj) = delete;
		bool operator==(const FSM_State& p_obj) = delete;

		std::mutex m_sync;
		std::string m_name;
	protected :

	public :
			FSM_State(const std::string& p_smname );
			std::string getState() const;
			virtual void On_Entry() { }
			virtual void On_Exit() { }
			//Madatorily override the below functions.
			virtual void On_Execute ( ) = 0;
			virtual void On_Fail ( ) = 0;
};
}