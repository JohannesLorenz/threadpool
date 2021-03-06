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

// only data access before thread runs
thread_base::thread_base(threadpool_t &_tp) : tp(&_tp)
{
}

}

void thread_t::join_pool(threadpool_t *tp, thread_t* self) {
	tp->join(*self);
}

void thread_t::clean_up() // only called by main thread after initialisation
{
	zombie = true;
	if(running) { // running: main thread only
		// we might be out of any threadpool
		if(tp) { // tp:
			tp->die_here(*this);
			// tp->die_here(std::move(*this));
			// thred.join();
		}
		else join();
	}
}

thread_t::thread_t(threadpool_t &_tp, bool is_main_thread) :
	thread_base(_tp),
	is_main_thread(is_main_thread)
	//thred(is_main_thread ? std::thread() : std::thread(join_pool, &_tp))
{
	_tp.count_me(*this);
	thred = is_main_thread ? std::thread() : std::thread(join_pool, &_tp, this);
	// no access by main thread afterwards

	// TODO: in ctor would be nice, but after _tp.add_me -> maybe when initing thread_base?
}

// access to thred is main only
void thread_t::join() { thred.join(); }

// safety relies on clean_up
thread_t::~thread_t() { clean_up(); }

}
