/**
* Declaration of the FSM guard class
* @file FSM_Guard.h
* @author Gokul Krishnan
*/


#pragma once

#include <mutex>
#include <string>

namespace fsm
{

class FSM_Guard
{
	private:
		//Delete copy constructor, = operator and == operator
		FSM_Guard(FSM_Guard & p_obj) = delete;
		FSM_Guard& operator=(const FSM_Guard& p_obj) = delete;
		bool operator==(const FSM_Guard& p_obj) = delete;
	protected :

	public :
			FSM_Guard()
			{
				
			}
			//Operations
			virtual bool On_Check() = 0;
	
};
}