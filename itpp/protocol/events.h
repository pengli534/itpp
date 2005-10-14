/*!
 * \file 
 * \brief Definitions of an event-based simulation class
 * \author Anders Persson
 *
 * $Date$
 * $Revision$
 *
 * -------------------------------------------------------------------------
 *
 * IT++ - C++ library of mathematical, signal processing, speech processing,
 *        and communications classes and functions
 *
 * Copyright (C) 1995-2005  (see AUTHORS file for a list of contributors)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * -------------------------------------------------------------------------
 */

#ifndef EVENTS_H
#define EVENTS_H

#include <list>
#include <queue>
#include <deque>
#include <string>
#include <iostream>
#include <itpp/base/itassert.h>

namespace itpp {
  //typedef long double Ttype; // 128-bit floating point time.
  typedef double Ttype; // 64-bit floating point time.
  //typedef long unsigned int Ttype; // 64-bit unsigned integer time.

  class Event_Queue;
  class Base_Event;
  class Base_Signal;

  /*!

  */
  class Base_Event {
  public:
    friend class Base_Signal;

    friend class Event_Queue;

    friend struct Compare_Base_Event_Times;
  
    //! Schedule an event at time \c delta_time from now
    Base_Event(const Ttype delta_time) {  // The event will occur in 'delta_time' time units from now! 	  
      it_assert(delta_time>=0, "Only causal simulations are possible");
      active = true;
      delta_t = delta_time;
      expire_t = 0; // Will be set correctly upon calling Event_Queue::add().
      id = global_id++;
    }

    //!
    virtual ~Base_Event(){}

    //! Cancel an event
    void cancel(){ active = false; } 

  protected:
    virtual void exec(void) = 0;
    Ttype delta_t;
    Ttype expire_t;
    bool active;
    unsigned long long int id;
    static unsigned long long int global_id;
  };

  //!
  struct Compare_Base_Event_Times {
    //!
    bool operator()(Base_Event *event1, Base_Event *event2) {
      if(event1->expire_t == event2->expire_t) // Equal expire times.
	return (event1->id > event2->id); // Base comparison on the event id.   
      else
	return (event1->expire_t > event2->expire_t); // Different expire times. Regular comparison.
    }
  };

  /*!

  */
  class Event_Queue {
  public:
    friend class Base_Signal;

    //!
    Event_Queue(){}
    //!
    ~Event_Queue(){}
    
    //! Add event to Queue
    static void add(Base_Event *e);  
    //! Return current time
    static Ttype now(){return t;}  
    //! Start executing events
    static void start();  
    //! Stop execution of events
    static void stop();
    //! Remove all events
    static void clear();
  protected:
    //static void cancel_all(Base_Signal *s);
  private:
    typedef std::deque<Base_Event*, std::allocator< Base_Event* > >::iterator Base_Event_Iterator;
    static void _run();
    static bool keep_running;
    static Ttype t; // Current time.
    static std::priority_queue<Base_Event*, 
      std::deque<Base_Event*, std::allocator<Base_Event*> >, 
      Compare_Base_Event_Times> event_queue; // Queue for the Events.
  };

  /*!

  */
  template <class ObjectType>
    class Event : public Base_Event {
  public:
    //!
    Event(ObjectType *object_pointer, void (ObjectType::*object_function_pointer)(), const Ttype delta_time) : Base_Event(delta_time) {
      po = object_pointer;
      pm = object_function_pointer;
    }
      
      //!
      virtual ~Event(){}

      //! Execute (call) the assigned function
      virtual void exec(void) { (*po.*pm)(); }  

  private:
      void (ObjectType::*pm)(); // Pointer to class member function to be executed on event expire.
      ObjectType *po; // Pointer to object who's member function is to be executed on event expire.
  };
  
  /*!

  */
  template <class ObjectType, class DataType> class Data_Event : public Base_Event {
  public:
    //!
    Data_Event(ObjectType *object_pointer, 
	       void (ObjectType::*object_function_pointer)(DataType data), 
	       DataType data, const Ttype delta_time) : Base_Event(delta_time) {
      po = object_pointer;
      pm = object_function_pointer;
      u = data;
    }

      //!
      virtual ~Data_Event(){}

      //! Execute (call) the assigned function with user data.
      virtual void exec(void) {
	(*po.*pm)(u);
      }

  private:
      void (ObjectType::*pm)(DataType data); // Pointer to class member function to be executed on event expire.
      ObjectType* po; // Pointer to object who's member function is to be executed on event expire.
      DataType u; // User data.
  };

} // namespace itpp

#endif // #ifndef EVENTS_H
