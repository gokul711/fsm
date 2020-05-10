/**
* Declaration of the the event handler class
* @file Event.h
* @author Gokul Krishnan
*/

#pragma once

#include <iostream>
#include <initializer_list>
using namespace std;

//#define ENABLE_SM_LOGS  //Uncomment to enable SM logs.

#define FSM_LOG_WRITE( msg, ... ) fsmWriteLogMessageToStdOut(__LINE__, __FUNCTION__,  __FILE__, msg, __VA_ARGS__)

#ifdef ENABLE_SM_LOGS

#define FSM_LOG_FUNC_ENTER(   ) fsmWriteLogMessageToStdOut(__LINE__, __FUNCTION__,  __FILE__, "Enter")
#define FSM_LOG_FUNC_EXIT(   ) fsmWriteLogMessageToStdOut(__LINE__, __FUNCTION__,  __FILE__, "Exit")

#else

#define FSM_LOG_FUNC_ENTER(   )  
#define FSM_LOG_FUNC_EXIT(   ) 

#endif

//void fsmWriteLogMessageToStdOut(int line, const char * functionName, const char* fileName, std::string msg);

template <class Type>
void fsmWriteLogMessageToStdOut( int line, const char * functionName, const char* fileName, std::initializer_list<Type> list )
{
    std::string l_msg;
    std::string l_fname(fileName);
    size_t l_pos = l_fname.find_last_of('/');
    
    for( auto elem : list )
    {
         l_msg += elem;
    }
    cout<<endl<<l_fname.substr(l_pos+1)<<" : "<<functionName <<" : "<<line<<" "<<l_msg<<endl;
}