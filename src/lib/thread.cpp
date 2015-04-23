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

namespace threadpool
{

void thread_t::join_pool(thread_t *t, threadpool_t *tp) {
	tp->join(*t);
}

void thread_t::clean_up() {
	std::cerr << "cleanup" << std::endl;
	if(tp) { // if tp still exists and ???
       	tp->die_here(*this);
//	 tp->die_here(std::move(*this));
//	thred.join();
	std::cerr << "dying..." << std::endl;
	}
	else if(running)
	 join();
}

void thread_t::join() { thred.join();  }

thread_t::thread_t(threadpool_t &_tp) :
	thred(join_pool, this, &_tp),
	tp(&_tp)
{
	_tp.add_me(*this);
}

thread_t::~thread_t() { clean_up(); }
}
