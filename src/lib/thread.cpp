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
#include <iostream>
#include "thread.h"
#include "threadpool.h"

namespace threadpool {
namespace detail {

thread_base::thread_base(threadpool_t &_tp) : tp(&_tp)
{
}

}

void thread_t::join_pool(threadpool_t *tp) {
	tp->join();
}

void thread_t::clean_up()
{
	if(running) {
		if(tp) {
			tp->die_here(*this);
			// tp->die_here(std::move(*this));
			// thred.join();
		}
		else join();
	}
}

thread_t::thread_t(threadpool_t &_tp, bool is_main_thread) :
	thread_base(_tp),
	is_main_thread(is_main_thread),
	thred(is_main_thread ? std::thread() : std::thread(join_pool, &_tp))
{
	(void)is_main_thread; // TODO?
	_tp.add_me(*this);
}

void thread_t::join() { thred.join();  }



thread_t::~thread_t() { clean_up(); }

}
