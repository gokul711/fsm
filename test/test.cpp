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
class GuardInteger2Character : public FSM_Guard
{
	public :
			bool On_Check(void * p_dispatcher) 
			{
				cout<<"GuardInteger2Character::On_Check"<<endl;
				bool l_ret = false;
				if ( p_dispatcher == (void*)(::event.getEventDispatcher()))
				{
					cout<<"Guard function called by InputEvent"<<endl;
					string curr = FSM::Instance().getState();
					if (  ("StateInt" == curr ) && 
						  ( InputEvent::CHARACTER == ::event.getValue() ) 
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
class GuardCharacter2Symbol : public FSM_Guard
{
	public :
			bool On_Check(void * p_dispatcher) 
			{
				cout<<"GuardCharacter2Symbol::On_Check"<<endl;
				bool l_ret = false;
				if ( p_dispatcher == (void*)(::event.getEventDispatcher()))
				{
					cout<<"Guard function called by InputEvent"<<endl;
					string curr = FSM::Instance().getState();
					if (  ("StateChar" == curr ) && 
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
class GuardSymbol2Integer : public FSM_Guard
{
	public :
			bool On_Check(void * p_dispatcher) 
			{
				cout<<"GuardSymbol2Integer::On_Check"<<endl;
				bool l_ret = false;
				if ( p_dispatcher == (void*)(::event.getEventDispatcher()))
				{
					cout<<"Guard function called by InputEvent"<<endl;
					string curr = FSM::Instance().getState();
					if (  ("StateSymbol" == curr ) && 
						  ( InputEvent::INTEGER == ::event.getValue() ) 
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
	GuardInteger2Character guardi2c; 
	GuardCharacter2Symbol guardc2s; 
	GuardSymbol2Integer guards2i; 
	//Add guards for each event
	event.AddGuardCondition( InputEvent::INTEGER, &guards2i);
	event.AddGuardCondition( InputEvent::CHARACTER, &guardi2c);
	event.AddGuardCondition( InputEvent::SYMBOL, &guardc2s);

	//Add transitions
	FSM::Instance().AddTransition(&i, &c, &guardi2c);
	FSM::Instance().AddTransition(&c, &s, &guardc2s);
	FSM::Instance().AddTransition(&s, &i, &guards2i);


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