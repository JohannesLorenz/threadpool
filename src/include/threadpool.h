/*************************************************************************/
/* threadpool - A simple ALSA implementation of an RT safe threadpool.   */
/* Copyright (C) 2015-2015                                               */
/* Johannes Lorenz (jlsf2013 @ sourceforge)                              */
/*                                                                       */
/* This program is free software; you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation; either version 3 of the License, or (at */
/* your option) any later version.                                       */
/* This program is distributed in the hope that it will be useful, but   */
/* WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      */
/* General Public License for more details.                              */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program; if not, write to the Free Software           */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA  */
/*************************************************************************/

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
//#include <mutex>
#include "semaphore.h" // TODO: std::sem?

namespace threadpool {

class thread_t;

namespace detail {

//! threadpool base class which exchanges data with thread_t.
class threadpool_base
{
protected:
	sem_t sem;
	std::vector<thread_t*> threads;
	std::vector<thread_t> zombies;
	bool quit_sequence = false;

private:
	friend class threadpool::thread_t;

	//! this will be called by a thread when it leaves the semaphore
	//! @return should return if the thread should enqueue again
	virtual bool callback() = 0;

	void enqueue();

	//! entry function for the thread
	void join();

	//! moves the threads ownership here after it has been (?) finished
	void die_here(thread_t& ill_thread);

	//! to be called by main thread
	void add_me(thread_t& self) {
		threads.push_back(&self);
	}
protected:
	static void set_tp_nullptr(thread_t* t);
};

}

class threadpool_t : public detail::threadpool_base
{
//	std::mutex init_mutex;
	
	bool release_thread() {
		return 0 == sem_post(&sem);
	}
	
	//! debugging: returns semaphore value
	int get_value();

	//friend class thread_t;

	void init();

public:
	threadpool_t() { init(); }

	//! careful, this is only allowed if no tasks are open
	//! otherwise, we'll call the destructor, and before
	//! quit_sequence gets true, another virtual callback is made.
	//! virtual callbacks are not allowed after dtor call.
	~threadpool_t();
};

}

#endif // THREADPOOL_H
