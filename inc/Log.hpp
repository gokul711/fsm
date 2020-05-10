/**
* Helper macros for logging
* @file Log.hpp
* @author Gokul Krishnan
*/

#pragma once

#include <iostream>
#include <initializer_list>
#include <type_traits>
using namespace std;

//#define ENABLE_SM_LOGS  //Uncomment to enable SM logs.

#define FSM_LOG_WRITE(msg, ... ) fsmWriteLogMessageToStdOut(__LINE__, __FUNCTION__,  __FILE__, msg, ##__VA_ARGS__)

#ifdef ENABLE_SM_LOGS

#define FSM_LOG_FUNC_ENTER(   ) fsmWriteLogMessageToStdOut(__LINE__, __FUNCTION__,  __FILE__, "Enter")
#define FSM_LOG_FUNC_EXIT(   ) fsmWriteLogMessageToStdOut(__LINE__, __FUNCTION__,  __FILE__, "Exit")

#else

#define FSM_LOG_FUNC_ENTER(   )  
#define FSM_LOG_FUNC_EXIT(   ) 

#endif

//void fsmWriteLogMessageToStdOut(int line, const char * functionName, const char* fileName, std::string msg);

template <typename Type >
std::string getLogMessageToStdOut( Type msg )
{
   if ( false == std::is_same<Type, std::string>::value )
   {
   		return ( std::string(msg));
   }
   else
   {
   		return msg;
   }
}

template <typename Type, typename... Args>
std::string getLogMessageToStdOut( Type msg1, Args... args )
{
   if ( false == std::is_same<Type, std::string>::value )
   {
   		return(std::string(msg1) + getLogMessageToStdOut(args...));
   }
   else
   {
   		return(msg1 + getLogMessageToStdOut(args...));
   }
}

template <typename Type, typename... Args>
void fsmWriteLogMessageToStdOut( int line, const char * functionName, const char* fileName, Type msg1, Args... args )
{
    std::string l_msg = getLogMessageToStdOut ( msg1, args...);
    std::string l_fname(fileName);
    size_t l_pos = l_fname.find_last_of('/');
    cout<<endl<<l_fname.substr(l_pos+1)<<" : "<<functionName <<" : "<<line<<" "<<l_msg<<endl;
}