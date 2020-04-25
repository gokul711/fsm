/**
* Implementation of the FSM test application
* @file test.cpp
* @author Gokul Krishnan
*/


#include <FSM.hpp>
#include <FSM_State.hpp>
#include <FSM_Guard.hpp>
#include <FSM_Event_Variable.hpp>

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
using namespace fsm;

//Events
enum InputEvent
{
INTEGER,
CHARACTER,
SYMBOL,
GENERIC
};

//Create event variables
FSM_Event_Variable<InputEvent> event;
//States
class StateInt : public FSM_State
{
	public :
			StateInt():FSM_State("StateInt")
			{

			}
			virtual void On_Execute() 
			{
				cout<<"StateInt::On_Execute"<<endl;
			}
			virtual void On_Fail ( ) 
			{
				cout<<"State transition attempt failed"<<endl;
			}
};
class StateChar : public FSM_State
{
	public :
			StateChar():FSM_State("StateChar")
			{

			}
			virtual void On_Execute() 
			{
				cout<<"StateChar::On_Execute"<<endl;
			}
			virtual void On_Fail ( ) 
			{
				cout<<"State transition attempt failed"<<endl;
			}
};
class StateSymbol : public FSM_State
{
	public :
			StateSymbol():FSM_State("StateSymbol")
			{

			}
			virtual void On_Execute() 
			{
				cout<<"StateSymbol::On_Execute"<<endl;
			}
			virtual void On_Fail ( ) 
			{
				cout<<"State transition attempt failed"<<endl;
			}
};
//Guards
class GuardCommon : public FSM_Guard
{
	public :
			bool On_Check(void * p_dispatcher) 
			{
				cout<<"GuardOne::On_Check"<<endl;
				bool l_ret = false;
				if ( p_dispatcher == (void*)(::event.getEventDispatcher()))
				{
					cout<<"Guard function called by InputEvent"<<endl;
					string curr = FSM::Instance().getState();
					if (  ("StateInt" != curr ) && 
						  ( InputEvent::INTEGER == ::event.getValue() ) 
					   )
					{
						l_ret = true;
						cout<<"Guard evaluation success"<<endl;
					}
					else if (  ("StateChar" != curr ) && 
						  ( InputEvent::CHARACTER == ::event.getValue() ) 
					   )
					{
						l_ret = true;
						cout<<"Guard evaluation success"<<endl;
					}
					else if (  ("StateSymbol" != curr ) && 
						  ( InputEvent::SYMBOL == ::event.getValue() ) 
					   )
					{
						l_ret = true;
						cout<<"Guard evaluation success"<<endl;
					}
					else
					{
						cout<<"Guard evaluation failed"<<endl;
					} 
				}
				else
				{
					cout<<"Unknown event"<<endl;
				}
				return l_ret;
			}
};

int main(int argc, char ** argv)
{
	//Create the state machine
	FSM::Init("FSM_Test");

	//Create the states
	StateInt i;;
	StateChar c;
	StateSymbol s;

	//Add default state
	FSM::Instance().AddDefault( &i );

	//Create guards
	GuardCommon guardc; 
	//Add guards for each event
	event.AddGuardCondition( InputEvent::INTEGER, &guardc);
	event.AddGuardCondition( InputEvent::CHARACTER, &guardc);
	event.AddGuardCondition( InputEvent::SYMBOL, &guardc);
	event.AddGuardCondition( InputEvent::GENERIC, &guardc);
	//Add transitions
	FSM::Instance().AddTransition(&i, &c, &guardc);
	FSM::Instance().AddTransition(&c, &s, &guardc);
	FSM::Instance().AddTransition(&s, &i, &guardc);


	bool l_run = true;
	while(l_run && ( 1 == argc ))
	{
		int i;
		cout<<"Enter choice to generate event : \n1. Interger \n2. Character  \n3. Symbol \n4. Current State \n5. Exit"<<endl;
		cin>>i;
		switch(i)
		{
			case 1: /*cout<<"Enter value : "<<endl;
					int ival;
					cin>>ival;*/
					event.setValue( InputEvent::INTEGER );
					break;
			case 2: /*cout<<"Enter value : "<<endl;
					char cval;
					cin>>cval;*/
					event.setValue( InputEvent::CHARACTER );
					break;
			case 3: /*cout<<"Enter value : "<<endl;
					char sval;
					cin>>sval;*/
					event.setValue( InputEvent::SYMBOL );
					break;
			case 4: cout<<"Current State : "<<FSM::Instance().getState()<<endl;
					break;
			default : 
					l_run  = false;
					break;
		}
	}
	if ( argc > 1) // Run automated tests for any command line input
	{	

	}

	FSM::ShutDown();

	return 0;
}