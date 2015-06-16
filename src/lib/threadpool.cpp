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

#include "thread.h"
#include "threadpool.h"

namespace threadpool {
namespace detail {

void threadpool_base::enqueue() { sem_wait(&sem); }

void threadpool_base::join(thread_t &self)
{
	//	(void) t;
	/*	init_mutex.lock();
	threads.push_back(&t); // TODO: insert ordered?
	init_mutex.unlock();*/
	// TODO: make this thread-safe: locks

	//std::cerr << "join: " << this << std::endl;
	bool go_on = true;
	do {
		enqueue();
		go_on = !quit_sequence && callback();
	} while(go_on);

	self.tp = nullptr;

	//std::cerr << "end join: " << this << std::endl;
}

/*
	a thread could simply die without notifying the threadpool
	however, in this case, such threads should be joined,
	and only the threadpool class can do so
*/
void threadpool_base::die_here(thread_t &ill_thread) {
	//std::cerr << "dying: " << this << std::endl;
#if 0
	ill_thread.running = false; // don't die twice
	zombies.push_back(std::move(ill_thread));
#endif
	ill_thread.zombie = true;
}

void threadpool_base::set_tp_nullptr(thread_t *t)
{
	t->tp = nullptr;
}

}

int threadpool_t::get_value()
{
	int ret;
	sem_getvalue(&sem, &ret);
	return ret;
}

void threadpool_t::init()
{
	sem_init(&sem, 0, 0);
	quit_sequence.store(false);
}

threadpool_t::~threadpool_t()
{
	/*
		generally, in order to avoid race conditions, we can not yet
		delete everything. the order is:
		 * allow all threads to stop soon
		 * join all threads
		 * then, in single-threaded mode, delete members
	*/


	quit_sequence = true;

	// init_mutex.lock();
/*	std::cerr << "this: " << this  << std::endl;
	std::cerr << "threads: " << threads.size()  << std::endl;
	std::cerr << "zombies: " << zombies.size()  << std::endl;*/
/*	for(thread_t* t : threads)
	 set_tp_nullptr(t);*/
	std::size_t sz = n_threads; // threads.size();
	// init_mutex.unlock();
	for(int count = sz; count; --count) // TODO: while(sz-->0)
	 release_thread();
//	for(thread_t& t : zombies)
//	 t.join();
	sem_destroy(&sem);
}

}

