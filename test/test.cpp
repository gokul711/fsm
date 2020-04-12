#include <FSM.hpp>
#include <FSM_State.hpp>
#include <FSM_Guard.hpp>
#include <FSM_Event_Variable.hpp>

#include <iostream>
#include <thread>

using namespace std;
using namespace fsm;
enum Events : int //Always define as int
{
	ONE, //Atleast one event is required 
	TWO,
	THREE,
	LAST // Mandatory. No event variable should be created
};

//States
class StateOne : public FSM_State
{
	public :
			StateOne():FSM_State("StateOne")
			{

			}
			virtual void On_Execute() 
			{
				cout<<"StateOne::On_Execute"<<endl;
			}
			virtual void On_Fail ( ) 
			{
				cout<<"State transition failed"<<endl;
			}
};
class StateTwo : public FSM_State
{
	public :
			StateTwo():FSM_State("StateTwo")
			{

			}
			virtual void On_Execute() 
			{
				cout<<"StateTwo::On_Execute"<<endl;
			}
			virtual void On_Fail ( ) 
			{
				cout<<"State transition failed"<<endl;
			}
};
class StateThree : public FSM_State
{
	public :
			StateThree():FSM_State("StateThree")
			{

			}
			virtual void On_Execute() 
			{
				cout<<"StateThree::On_Execute"<<endl;
			}
			virtual void On_Fail ( ) 
			{
				cout<<"State transition failed"<<endl;
			}
};
//Guards
class GuardOne : public FSM_Guard
{
	public :
			bool On_Check() 
			{
				cout<<"GuardOne::On_Check"<<endl;
				return true;
			}
};

class GuardTwo : public FSM_Guard
{
	public :
			bool On_Check() 
			{
				cout<<"GuardTwo::On_Check"<<endl;
				return true;
			}
};

class GuardThree : public FSM_Guard
{
	public :
			bool On_Check() 
			{
				cout<<"GuardThree::On_Check"<<endl;
				return true;
			}
};
int main(int argc, char ** argv)
{
	//Create the state machine
	FSM::Init("FSM_Test");

	//Create the states
	StateOne l_state1;
	StateTwo l_state2;
	StateThree l_state3;

	//Add default state
	FSM::Instance().AddDefault( &l_state1 );

	//Create event variables
	FSM_Event_Variable l_event1;//1-2 transition
	FSM_Event_Variable l_event2;//2-3 transition
	FSM_Event_Variable l_event3;//3-1 transition

	//Create guards
	GuardOne l_guard1; //1-2 transition
	GuardTwo l_guard2; //2-3 transition
	GuardThree l_guard3; //3-1 transition

	//Add guard conditions
	l_event1.AddGuardCondition( &l_guard1 );
	l_event2.AddGuardCondition( &l_guard2 );
	l_event3.AddGuardCondition( &l_guard3 );


	//Add transitions
	FSM::Instance().AddTransition(&l_state1, &l_state2, &l_guard1);
	FSM::Instance().AddTransition(&l_state2, &l_state3, &l_guard2);
	FSM::Instance().AddTransition(&l_state3, &l_state1, &l_guard3);

	bool l_run = true;
	while(l_run)
	{
		int i;
		cout<<"Current State : "<<FSM::Instance().getState()<<endl;
		cout<<"Enter state to transition to : \n1. Two \n2. Three \n3. One\n4. Exit"<<endl;
		cin>>i;
		switch(i)
		{
			case 1: l_event1.setValue( );
					break;
			case 2: l_event2.setValue( );
					break;
			case 3: l_event3.setValue( );
					break;
			default : 
					l_run  = false;
					break;
		}
	}

	return 0;
}