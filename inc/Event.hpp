/**
* Declaration of the the event handler class
* @file Event.h
* @author Gokul Krishnan
*/

#pragma once

#include <mutex>
#include <condition_variable>
#include <map>
#include <string>
#include <queue>
#include <thread>
#include <atomic>
#include <cstdint>
#include <FSM.hpp> 

namespace fsm
{
//Forward declare the classes
class FSM_State;
class FSM_Guard;

template <class Typename = uint8_t >
class EventDispatcher
{
	private:
		//Delete copy constructor, = operator and == operator
		EventDispatcher(EventDispatcher & p_obj) = delete;
		EventDispatcher& operator=(const EventDispatcher& p_obj) = delete;
		bool operator==(const EventDispatcher& p_obj) = delete;
		//Static data members

		//Static methods 

		//Private data members
		std::string m_name;
		std::thread * m_eventThread;
		std::queue<Typename> m_EventQueue; 
		std::unordered_map<Typename, FSM_Guard * > m_EventMap;
		std::mutex m_sync;
		std::mutex m_wait;
		std::condition_variable m_CondVar;
		bool m_Alive;
		std::atomic<bool> m_eventOccurred;
		//Private method
		void EventDispatcherThread(  )
		{
			//Run while alive
			while(m_Alive)
			{
				// Wait until some event vaiable is updated
			    std::unique_lock<std::mutex> lk(m_wait);
			    m_CondVar.wait(lk, [this]{return m_eventOccurred.load();});
			    while(!m_EventQueue.empty())
			    {
			    	//keep sending events to SM here
			    	m_sync.lock();
			    	try
			    	{	
			    		Typename l_event = m_EventQueue.front();
			    		m_EventQueue.pop();
			    		FSM_Guard * l_guard = m_EventMap.at(l_event);
			    		FSM::Instance().EventOccurred( l_guard , (void*)(this));
			    	}
			    	catch(...) //std::out_of_range thrown
			    	{
						FSM_LOG_WRITE ("Guard not found. Ignoring event");
						//Failure. Event-Guard mapping not present. Skip this event
			    		continue;
			    	}
					m_sync.unlock();
					
			    }
			    //Event queue is empty. Set event occurence to false
			    m_eventOccurred.store(false);
			}
		}

	protected :

	public :
			EventDispatcher( )
			{
				m_Alive = true;
				m_eventThread = nullptr;
				m_eventThread = new std::thread ( &EventDispatcher::EventDispatcherThread, this);
			}
			//Operations
			void ExitDispatcherThread()
			{
				m_Alive = false;
				m_eventOccurred.store(true);
				m_CondVar.notify_one();
				m_eventThread->join();
				delete m_eventThread;
			}
			void AddEventToEventQueue( const Typename& p_data )
			{
				m_sync.lock();
				m_EventQueue.push( p_data );
				m_sync.unlock();
				//Unblock dispatcher for first event only. 
				if ( false == m_eventOccurred.load() )
				{
					m_eventOccurred.store(true);
					m_CondVar.notify_one();
				}
			}
			void AddToEventMap( const Typename& p_data, FSM_Guard * p_guard )
			{
				m_sync.lock();
				m_EventMap.insert(std::make_pair( p_data, p_guard ));
				m_sync.unlock();
			}
	
};
}