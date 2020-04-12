
#include <FSM.hpp>
#include <FSM_Guard.hpp>
#include <FSM_Event_Variable.hpp>

namespace fsm
{
//Add guard evaluations
void FSM_Event_Variable::AddGuardCondition(FSM_Guard * p_guard)
{
	m_guard = p_guard;
}
void FSM_Event_Variable::setValue( )
{
	FSM::Instance().EventVariableUpdated( this );
}

}