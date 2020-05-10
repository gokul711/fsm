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
enum class IntegerEvent
{
ZERO, // Unused - 0 valuae
ONE,
TWO,
THREE,
FOUR
};

//Events
enum class CharacterEvent
{
UNDEF, //Undefined 0 value
AA,
BE,
CE,
DE
};

//Events
enum class SymbolEvent
{
NOSYMBOL, //Undefined 0 value
AT,
HASH,
DOLLAR,
AND
};


//Create event variables
FSM_Event_Variable<IntegerEvent> eventVariableInteger;
FSM_Event_Variable<CharacterEvent> eventVariableCharacter;
FSM_Event_Variable<SymbolEvent> eventVariableSymbol;
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
class GenericGuard : public FSM_Guard
{
	public :
			bool On_Check(void * p_dispatcher) 
			{
				cout<<"GenericGuard::On_Check"<<endl;
				bool l_ret = false;
				if ( p_dispatcher == (void*)(::eventVariableInteger.getEventDispatcher()))
				{
					cout<<"Guard function called by Integer event"<<endl;
					string curr = FSM::Instance().getState();
					if (  ("StateInt" != curr ) 
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
				else if ( p_dispatcher == (void*)(::eventVariableCharacter.getEventDispatcher()))
				{
					cout<<"Guard function called by Character event"<<endl;
					string curr = FSM::Instance().getState();
					if (  ("StateChar" != curr ) 
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
				else if ( p_dispatcher == (void*)(::eventVariableSymbol.getEventDispatcher()))
				{
					cout<<"Guard function called by Symbol event"<<endl;
					string curr = FSM::Instance().getState();
					if (  ("StateSymbol" != curr ) 
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
	GenericGuard g1;
	//Add guards for each event
	eventVariableInteger.AddGuardCondition( IntegerEvent::ONE, &g1);
	eventVariableCharacter.AddGuardCondition( CharacterEvent::AA, &g1);
	eventVariableSymbol.AddGuardCondition( SymbolEvent::HASH, &g1);

	//Add transitions
	FSM::Instance().AddTransition(&i, &c, &g1);
	FSM::Instance().AddTransition(&c, &s, &g1);
	FSM::Instance().AddTransition(&s, &i, &g1);


	bool l_run = true;
	while(l_run && ( 1 == argc ))
	{
		int i;
		cout<<"Enter choice to generate event : \n1. Interger \n2. Character  \n3. Symbol \n4. Current State \n5. Exit"<<endl;
		cin>>i;
		switch(i)
		{
			case 1: cout<<"Enter value : "<<endl;
					int ival;
					cin>>ival;
					eventVariableInteger.setValue( IntegerEvent::ONE );
					break;
			case 2: cout<<"Enter value : "<<endl;
					char cval;
					cin>>cval;
					eventVariableCharacter.setValue( CharacterEvent::AA );
					break;
			case 3: cout<<"Enter value : "<<endl;
					char sval;
					cin>>sval;
					eventVariableSymbol.setValue( SymbolEvent::HASH );
					break;
			case 4: cout<<"Current State : "<<FSM::Instance().getState()<<endl;
					break;
			default : 
					l_run  = false;
					break;
		}
	}
	if ( argc > 1) // Run and exit 
	{	

	}

	FSM::ShutDown();

	return 0;
}