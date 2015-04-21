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

#include <iostream>
#include <vector>
#include <mutex>
#include "semaphore.h" // TODO: std::sem?

namespace threadpool {

class thread_t;

class threadpool_t
{
	/*struct thread_home
	{
		thread* t;
		mailbox;
	};*/
	sem_t sem;

	std::mutex m;
	std::vector<thread_t*> threads;
	
	void enqueue() { sem_wait(&sem);  }

	void join(thread_t& t) {
	//	(void) t;
		m.lock();
		threads.push_back(&t); // TODO: insert ordered?
		m.unlock();
		// TODO: make this thread-safe: locks
		enqueue();
	}

	bool release_thread() {
		return 0 == sem_post(&sem);
	}
	
	// debugging
	int get_value() {
		int ret;
		sem_getvalue(&sem, &ret);
		return ret;
	}

	friend class thread_t;

public:
	threadpool_t() {
		sem_init(&sem, 0, 0);
	}
	~threadpool_t() {
		std::cerr << get_value() << std::endl;
		while(release_thread()) {
			std::cerr<<"post"<<std::endl;
		}
		for(thread_t* t : threads) {
	//		std::cerr << "joining..." << std::endl;
	//		t->join();
		}
		sem_destroy(&sem);
	}
};

}

#endif // THREADPOOL_H
