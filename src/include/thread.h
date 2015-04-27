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

#ifndef THREAD_H
#define THREAD_H

#include <thread>

namespace threadpool {

class threadpool_t;

namespace detail {

//! base class with threadpool_t access
class thread_base
{
	friend class threadpool_base;
protected:
	bool running = true;
	threadpool_t* tp = nullptr;
	thread_base(threadpool_t& _tp);
	thread_base() = default;
};

}

class thread_t : public detail::thread_base
{
public:
	bool is_main_thread;
	std::thread thred;
	static void join_pool(threadpool_t* tp);
	void clean_up();
protected:
	thread_t(threadpool_t& _tp, bool is_main_thread);
public:
	void join();
	thread_t(threadpool_t& _tp) : thread_t(_tp, false) {}
	thread_t(const thread_t& ) = delete;
	// TODO: update threadpool about ptr change??
	thread_t(thread_t&& ) = default;
	thread_t() = default;

	thread_t& operator=(const thread_t& ) = delete;
	// TODO: update threadpool about ptr change??
	thread_t& operator=(thread_t&& ) = default;

	~thread_t();
};

class main_thread_t : public thread_t
{
public:
	main_thread_t(threadpool_t& _tp)
		: thread_t(_tp, true) {}

	//! runs this thread. this should be called by the main thread
	//! @note: you might want to release a thread of the threadpool
	//! @a before you call this function
	void acquire() { join_pool(tp); }

	// TODO: allow moving???
};

}

#endif // THREAD_H
