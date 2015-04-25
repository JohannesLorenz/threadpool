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
	std::thread thred;
	static void join_pool(threadpool_t* tp);
	void clean_up();
public:
	void join();
	thread_t(threadpool_t& _tp);
	thread_t(const thread_t& ) = delete;
	thread_t(thread_t&& ) = default;
	thread_t() = default;

	thread_t& operator=(const thread_t& ) = delete;
	thread_t& operator=(thread_t&& ) = default;

	~thread_t();
};

}

#endif // THREAD_H
